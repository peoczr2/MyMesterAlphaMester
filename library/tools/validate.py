#!/usr/bin/env python3
"""Ellenőrzi egy vagy több feladatmappa megoldását.

Használat:
    python3 library/tools/validate.py "<feladatmappa>" [még egy mappa ...]
    python3 library/tools/validate.py --json "<feladatmappa>"

Lépések:
  1. formátum: magyarázó blokk, majd közvetlenül utána a Hint-blokk (sorszámozva)
  2. fordítás: g++ -std=c++17, a munkakönyvtárban (nem kerül bináris a feladatmappába)
  3. minta: a minta.zip be/ki (vagy in/out) párjai, időkorlátos futtatás, soronkénti összevetés

Állapotok:
  kész              - formátum rendben, fordul, minden minta stimmel
  hibás             - fordul, de mintán hibázik (vagy formátumhiba / fordítási hiba)
  nincs megoldás    - nincs task.cpp
  nincs minta       - formátum és fordítás rendben, de nincs futtatható minta
  speciális         - zsűri/grader-alapú vagy interaktív feladat, automatikusan nem tesztelhető
"""
import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
import zipfile

LIB_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))  # .../mester/library
MESTER = os.path.dirname(LIB_ROOT)
WORK = os.path.join(LIB_ROOT, '.work')

COMPILE_TIMEOUT = 90
RUN_TIMEOUT = 10

PLACEHOLDER = re.compile(r'^\s*(\.\.\.|…|)\s*$')
HUNGARIAN_CHARS = set('áéíóöőúüűÁÉÍÓÖŐÚÜŰ')


def check_format(src):
    """Visszaad (ok, problémalista). A szerkezetet a sorok alapján ellenőrzi."""
    problems = []
    lines = src.splitlines()

    start = next((i for i, l in enumerate(lines) if l.strip().startswith('/*')), None)
    if start is None:
        return False, ['nincs /* ... */ magyarázó blokk']
    end = next((i for i in range(start, len(lines)) if '*/' in lines[i]), None)
    if end is None:
        return False, ['a magyarázó blokk nincs lezárva']

    expl = '\n'.join(lines[start:end + 1])
    body = expl.replace('/*', '').replace('*/', '')
    if len(body.strip()) < 40:
        problems.append('a magyarázó blokk túl rövid')
    if not (set(body) & HUNGARIAN_CHARS) and not re.search(r'\b(a|az|és|egy|hogy|ezért|mert)\b', body):
        problems.append('a magyarázat nem tűnik magyarnak')

    hstart = end + 1
    if hstart >= len(lines) or not lines[hstart].strip().startswith('/*'):
        problems.append('a magyarázat után közvetlenül nem a Hint-blokk következik (üres sor vagy más kód/komment van köztük)')
        return False, problems
    hend = next((i for i in range(hstart, len(lines)) if '*/' in lines[i]), None)
    if hend is None:
        problems.append('a Hint-blokk nincs lezárva')
        return False, problems

    inner = '\n'.join(lines[hstart:hend + 1])
    inner = inner.replace('/*', '', 1)
    inner = inner[:inner.rfind('*/')] if '*/' in inner else inner
    markers = list(re.finditer(r'Hint\s+(\d+):\s*\|\|', inner))
    hint_nums = [int(m.group(1)) for m in markers]
    for i, m in enumerate(markers):
        stop = markers[i + 1].start() if i + 1 < len(markers) else len(inner)
        text = inner[m.end():stop]
        if not text.rstrip().endswith('||'):
            problems.append(f'a Hint {m.group(1)} nincs || ... || között lezárva')
            continue
        body = text.rstrip()[:-2].strip()
        if PLACEHOLDER.match(body) or len(body) < 10:
            problems.append(f'üres/helyőrző hint: Hint {m.group(1)}')
    stray = re.sub(r'Hint\s+\d+:\s*\|\|.*?\|\|', '', inner, flags=re.S).strip()
    if stray and not markers:
        problems.append('a Hint-blokkban nincs Hint sor')
    if not hint_nums:
        problems.append('nincs Hint sor a Hint-blokkban')
    elif hint_nums != list(range(1, len(hint_nums) + 1)):
        problems.append(f'a hint-számozás nem 1-től folyamatos: {hint_nums}')

    rest = '\n'.join(lines[hend + 1:])
    if not re.search(r'\bmain\s*\(', rest):
        problems.append('a magyarázat utáni részben nincs main()')
    return not problems, problems


def sample_pairs(names):
    """Bemenet/kimenet párok a fájlnevekből, szám szerint párosítva."""
    ins, outs = {}, {}
    for n in names:
        b = os.path.basename(n).lower()
        m = re.match(r'^(?:be|in|input)\.?(\d+)\.txt$', b) or re.match(r'^in\.(\d+)$', b) or re.match(r'^in(\d+)\.txt$', b)
        if m:
            ins[m.group(1)] = n
            continue
        m = re.match(r'^(?:ki|out|output|k)\.?(\d+)\.txt$', b) or re.match(r'^out\.(\d+)$', b) or re.match(r'^out(\d+)\.txt$', b)
        if m:
            outs[m.group(1)] = n
    if 'be.txt' in [os.path.basename(n).lower() for n in names] and 'ki.txt' in [os.path.basename(n).lower() for n in names]:
        be = next(n for n in names if os.path.basename(n).lower() == 'be.txt')
        ki = next(n for n in names if os.path.basename(n).lower() == 'ki.txt')
        ins.setdefault('', be)
        outs.setdefault('', ki)
    return [(ins[k], outs[k]) for k in sorted(ins) if k in outs]


def normalize(text):
    """Szóköz- és sortörés-érzéketlen összevetés: a tokenek sorozata számít."""
    return text.split()


def extract_samples(folder, work):
    zpath = os.path.join(folder, 'minta.zip')
    sdir = os.path.join(work, 'sample')
    if not os.path.exists(zpath):
        return [], [], sdir
    try:
        z = zipfile.ZipFile(zpath)
    except zipfile.BadZipFile:
        return [], [], sdir
    names = [n for n in z.namelist() if not n.endswith('/')]
    flat = {}
    for n in names:
        flat.setdefault(os.path.basename(n), n)
    os.makedirs(sdir, exist_ok=True)
    for base, n in flat.items():
        with z.open(n) as src, open(os.path.join(sdir, base), 'wb') as dst:
            dst.write(src.read())
    return names, sample_pairs(list(flat.keys())), sdir


def read_sample(path):
    """Minta-fájl bájtjai UTF-8-ban: a BOM-os UTF-16 mintákat átkódolja."""
    with open(path, 'rb') as f:
        data = f.read()
    if data[:2] in (b'\xff\xfe', b'\xfe\xff'):
        return data.decode('utf-16').encode('utf-8')
    if data.startswith(b'\xef\xbb\xbf'):
        return data[3:]
    return data


def run_samples(binary, pairs, sdir):
    failed, passed = [], 0
    for inp, outp in pairs:
        try:
            run = subprocess.run([binary], input=read_sample(os.path.join(sdir, inp)), capture_output=True,
                                 timeout=RUN_TIMEOUT, cwd=sdir)
        except subprocess.TimeoutExpired:
            failed.append(f'{inp}: időtúllépés')
            continue
        expected = read_sample(os.path.join(sdir, outp)).decode('utf-8', 'replace')
        got = run.stdout.decode('utf-8', 'replace')
        if normalize(got) == normalize(expected):
            passed += 1
        else:
            failed.append(f'{inp}: eltérő kimenet')
    return passed, failed


def validate(folder):
    rel = os.path.relpath(os.path.abspath(folder), MESTER)
    result = {'path': rel, 'cpp': False, 'format_ok': None, 'format_problems': [],
              'compile': 'skip', 'compile_error': '', 'samples_total': 0, 'samples_passed': 0,
              'sample_failures': [], 'status': 'nincs megoldás'}
    src_path = os.path.join(folder, 'task.cpp')
    if not os.path.exists(src_path):
        return result
    result['cpp'] = True
    with open(src_path, encoding='utf-8', errors='replace') as f:
        src = f.read()

    result['format_ok'], result['format_problems'] = check_format(src)

    key = hashlib.sha1(rel.encode()).hexdigest()[:12]
    work = os.path.join(WORK, key)
    src_dir = os.path.join(work, 'src')
    os.makedirs(src_dir, exist_ok=True)
    binary = os.path.join(work, 'task.bin')
    with open(os.path.join(src_dir, 'task.cpp'), 'w', encoding='utf-8') as f:
        f.write(src)
    # A témakör közös fejléce (#include "../common.hpp") a feladatmappához képest él:
    # a munkakönyvtárban ugyanígy work/src/../common.hpp-ként kell megtalálnia.
    shared, shared_copy = os.path.join(folder, '..', 'common.hpp'), os.path.join(work, 'common.hpp')
    if os.path.exists(shared):
        shutil.copy(shared, shared_copy)
    elif os.path.exists(shared_copy):
        os.remove(shared_copy)
    if os.path.exists(binary):
        os.remove(binary)
    try:
        comp = subprocess.run(['g++', '-O2', '-std=c++17', '-o', binary, os.path.join(src_dir, 'task.cpp')],
                              capture_output=True, text=True, timeout=COMPILE_TIMEOUT, cwd=src_dir)
        result['compile'] = 'ok' if comp.returncode == 0 and os.path.exists(binary) else 'fail'
        compile_stderr = comp.stderr
    except subprocess.TimeoutExpired:
        result['compile'] = 'fail'
        compile_stderr = 'fordítás időtúllépés'
    if result['compile'] == 'fail':
        result['compile_error'] = '\n'.join(compile_stderr.splitlines()[:6])

    names, pairs, sdir = extract_samples(folder, work)
    special = bool(names) and not pairs and any(
        n.lower().endswith(('.h', '.hpp', '.pas', '.java', '.py', '.c')) for n in names)
    result['samples_total'] = len(pairs)
    if pairs and result['compile'] == 'ok':
        passed, failed = run_samples(binary, pairs, sdir)
        result['samples_passed'] = passed
        result['sample_failures'] = failed

    if result['compile'] == 'fail' or result['format_ok'] is False or result['sample_failures']:
        result['status'] = 'hibás'
    elif special and not pairs:
        result['status'] = 'speciális'
    elif not pairs:
        result['status'] = 'nincs minta'
    else:
        result['status'] = 'kész'
    return result


def main(argv):
    as_json = '--json' in argv
    folders = [a for a in argv if a != '--json']
    if not folders:
        print(__doc__)
        return 2
    out = [validate(f) for f in folders]
    if as_json:
        print(json.dumps(out if len(out) > 1 else out[0], ensure_ascii=False, indent=1))
    else:
        for r in out:
            print(f"{r['status']:<16} {r['path']}")
            if r['format_problems']:
                for p in r['format_problems']:
                    print(f'    formátum: {p}')
            if r['compile'] == 'fail':
                print('    fordítás: HIBA')
                print('    ' + r['compile_error'].replace('\n', '\n    '))
            if r['samples_total']:
                print(f"    minta: {r['samples_passed']}/{r['samples_total']}")
            for f in r['sample_failures']:
                print(f'    minta-hiba: {f}')
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
