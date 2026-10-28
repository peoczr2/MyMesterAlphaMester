#!/usr/bin/env python3
"""A feladatkönyvtár generálója.

Bemenet:
  - a feladatmappák (feladat.pdf, minta.zip, task.cpp) és a mappanevek (sorszám, cím, csillagok)
  - library/meta/*.json: a megoldók által írt metaadatok (módszer, kategória, cél, címkék)
  - az ellenőrzés eredménye (library/tools/validate.py)

Kimenet (mind generált, kézzel ne szerkeszd):
  - SUMMARY.md minden olyan mappában, ahol feladatok vannak (témakör = táblázat,
    fölötte csak áttekintés)
  - library/INDEX.md        : teljes áttekintés kategóriánként és témakörönként
  - library/catalog.json    : gépi katalógus (plan.py ezt használja)
  - library/catalog.csv     : táblázatos export

Használat:
    python3 library/tools/catalog.py            # ellenőrzés (cache-elt) + generálás
    python3 library/tools/catalog.py --no-validate   # csak a meglévő eredmények
    python3 library/tools/catalog.py --only "Kezdő/"  # csak a megadott útvonal-előtagra ellenőriz
"""
import csv
import glob
import hashlib
import json
import os
import re
import sys
from concurrent.futures import ProcessPoolExecutor

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import validate  # noqa: E402

LIB_ROOT = validate.LIB_ROOT
MESTER = validate.MESTER
META_DIR = os.path.join(LIB_ROOT, 'meta')
CACHE = os.path.join(LIB_ROOT, '.work', 'status-cache.json')
SKIP_DIRS = {'.git', '.github', '.infagent', 'library'}

NUM_TITLE = re.compile(r'^\s*(\d+)\.\s*(.*?)\s*$')
TRAILING_STARS = re.compile(r'\s*\*+\s*$')

STATUS_LABEL = {
    'kész': '✅ kész',
    'hibás': '❌ hibás',
    'nincs minta': '🟡 nincs minta',
    'speciális': '🟡 speciális',
    'nincs megoldás': '⬜ nincs megoldás',
    'kézi': '🟡 kézi ellenőrzés',
}
STATUS_ORDER = ['kész', 'kézi', 'nincs minta', 'speciális', 'hibás', 'nincs megoldás']
GOALS = ['Bevezetés', 'Magyarázat', 'Mélyebb megértés']


def find_exercises():
    """Minden feladatmappa (feladat.pdf / minta.zip / task.cpp alapján), relatív úttal."""
    found = []
    for dirpath, dirnames, filenames in os.walk(MESTER):
        dirnames[:] = sorted(d for d in dirnames if d not in SKIP_DIRS)
        if dirpath == MESTER:
            continue
        if {'feladat.pdf', 'minta.zip', 'task.cpp'} & set(filenames):
            found.append(os.path.relpath(dirpath, MESTER))
    return sorted(found)


def parse_name(name):
    m = NUM_TITLE.match(name)
    number = int(m.group(1)) if m else None
    rest = m.group(2) if m else name
    m_stars = re.search(r'(\*+)\s*$', rest)
    stars = len(m_stars.group(1)) if m_stars else 0
    title = TRAILING_STARS.sub('', rest).strip()
    return number, title, stars


def load_meta():
    """library/meta/*.json összefésülése; a később (ábécé szerint) olvasott fájl nyer."""
    meta = {}
    for fn in sorted(glob.glob(os.path.join(META_DIR, '*.json'))):
        with open(fn, encoding='utf-8') as f:
            for entry in json.load(f):
                cur = meta.setdefault(entry['path'], {})
                for k, v in entry.items():
                    if v not in (None, '', []):
                        cur[k] = v
    return meta


def sig_of(path):
    src = os.path.join(MESTER, path, 'task.cpp')
    if not os.path.exists(src):
        return None
    digest = hashlib.sha1(open(src, 'rb').read())
    zpath = os.path.join(MESTER, path, 'minta.zip')
    digest.update(str(os.path.getsize(zpath) if os.path.exists(zpath) else 0).encode())
    digest.update(str(os.path.getmtime(validate.__file__)).encode())  # új ellenőrző -> újra fut
    return digest.hexdigest()


def _validate_one(path):
    return validate.validate(os.path.join(MESTER, path))


def run_validation(paths, cache, only=None):
    todo = []
    for p in paths:
        sig = sig_of(p)
        if sig is None:
            continue
        cached = cache.get(p)
        if cached and cached.get('sig') == sig:
            continue
        if only and not p.startswith(only):
            continue
        todo.append((p, sig))
    print(f'ellenőrzés: {len(todo)} feladat (cache-ben: {len([p for p in paths if p in cache])})', file=sys.stderr)
    if todo:
        with ProcessPoolExecutor(max_workers=os.cpu_count()) as pool:
            for (p, sig), res in zip(todo, pool.map(_validate_one, [p for p, _ in todo], chunksize=4)):
                cache[p] = {'sig': sig, 'result': res}
        os.makedirs(os.path.dirname(CACHE), exist_ok=True)
        with open(CACHE, 'w', encoding='utf-8') as f:
            json.dump(cache, f, ensure_ascii=False)


def build_records(no_validate=False, only=None):
    cache = {}
    if os.path.exists(CACHE):
        with open(CACHE, encoding='utf-8') as f:
            cache = json.load(f)
    paths = find_exercises()
    if not no_validate:
        run_validation(paths, cache, only)
    meta = load_meta()

    records = []
    for p in paths:
        parts = p.split(os.sep)
        name = parts[-1]
        number, title, stars = parse_name(name)
        m = meta.get(p, {})
        if m.get('problematic'):
            continue  # megoldhatatlan vagy hibás feladat: lásd library/problematic/
        result = cache.get(p, {}).get('result')
        status = result['status'] if result else 'nincs megoldás'
        if status in ('hibás', 'nincs minta') and m.get('minta') == 'kézi' and result and result['compile'] == 'ok' and result['format_ok']:
            status = 'kézi'  # több helyes kimenet van: a mintát kézzel (indoklással) ellenőrizték
        if m.get('minta') == 'speciális' and result:
            status = 'speciális'  # zsűri/grader-alapú: a validátor futtatása nem bizonyítja a helyességet
        if status == 'kész' and m.get('minta') == 'kézi':
            status = 'kézi'  # a validátor átment, de a mintát a megoldó hibásnak jelölte: nem tekinthető gépi ellenőrzöttnek
        topic_dir = os.path.dirname(p)
        topic_title = parse_name(os.path.basename(topic_dir))[1] if topic_dir else ''
        difficulty = stars or m.get('difficulty')
        records.append({
            'path': p,
            'category': parts[0],
            'topic': os.path.relpath(topic_dir, parts[0]) if len(parts) > 2 else '',
            'topic_dir': topic_dir,
            'topic_title': topic_title,
            'number': number,
            'title': title,
            'folder': name,
            'stars': stars,
            'difficulty': difficulty,
            'goal': m.get('goal', ''),
            'method': m.get('method', ''),
            'category_label': m.get('category') or topic_title,
            'tags': m.get('tags', []),
            'note': m.get('note', ''),
            'has_pdf': os.path.exists(os.path.join(MESTER, p, 'feladat.pdf')),
            'has_solution': os.path.exists(os.path.join(MESTER, p, 'task.cpp')),
            'status': status,
            'samples_passed': (result or {}).get('samples_passed', 0),
            'samples_total': (result or {}).get('samples_total', 0),
        })
    return records


def fmt_num(n):
    return '' if n is None else str(n)


def fmt_diff(r):
    return str(r['difficulty']) if r['difficulty'] else '–'


def esc(s):
    return (s or '–').replace('|', '\\|').replace('\n', ' ')


def link_to(from_dir, target_dir, label, file_name=None):
    """Markdown-link a from_dir-ből target_dir (vagy annak file_name fájlja) felé."""
    rel = os.path.relpath(target_dir, from_dir)
    if file_name:
        target = file_name if rel == '.' else os.path.join(rel, file_name)
    else:
        target = rel + '/'
    return f'[{esc(label)}](<{target}>)'


def counts(records):
    c = {s: 0 for s in STATUS_ORDER}
    for r in records:
        c[r['status']] = c.get(r['status'], 0) + 1
    c['total'] = len(records)
    return c


def summary_line(c):
    return (f"{c['total']} feladat · ✅ kész {c.get('kész', 0)} · ❌ hibás {c.get('hibás', 0)} · "
            f"🟡 kézi {c.get('kézi', 0)} · 🟡 nincs minta/speciális {c.get('nincs minta', 0) + c.get('speciális', 0)} · "
            f"⬜ nincs megoldás {c.get('nincs megoldás', 0)}")


def write_leaf_summary(topic_abs, records, title):
    rows = sorted(records, key=lambda r: (r['number'] if r['number'] is not None else 10**6, r['title']))
    c = counts(records)
    lines = [
        f'# {title} – oktatási összefoglaló',
        '',
        '> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` '
        'fájlokból és az automatikus ellenőrzésből jönnek.',
        '',
        f'Összesítés: {summary_line(c)}',
        '',
        'Skála:',
        '- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.',
        '- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)',
        '',
        '| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |',
        '|---|---|---|---|---:|---|---|',
    ]
    for r in rows:
        link = link_to(topic_abs, os.path.join(MESTER, r['path']), r['title'] or r['folder'])
        lines.append('| {n} | {t} | {cat} | {m} | {d} | {g} | {s} |'.format(
            n=fmt_num(r['number']), t=link, cat=esc(r['category_label']), m=esc(r['method']),
            d=fmt_diff(r), g=esc(r['goal']), s=STATUS_LABEL[r['status']]))
    lines.append('')
    write(os.path.join(topic_abs, 'SUMMARY.md'), '\n'.join(lines))


def write_overview(dir_abs, children, title):
    """children: [(child_abs_dir, child_title, records)]"""
    total = []
    for _, _, recs in children:
        total.extend(recs)
    c = counts(total)
    lines = [
        f'# {title} – áttekintés',
        '',
        '> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel.',
        '',
        f'Összesítés: {summary_line(c)}',
        '',
        '| Témakör | Feladatok | ✅ kész | ❌ hibás | ⬜ nincs megoldás |',
        '|---|---:|---:|---:|---:|',
    ]
    for child_abs, child_title, recs in sorted(children, key=lambda x: x[1]):
        cc = counts(recs)
        lines.append('| {l} | {t} | {k} | {h} | {m} |'.format(
            l=link_to(dir_abs, child_abs, child_title, 'SUMMARY.md'), t=cc['total'],
            k=cc.get('kész', 0), h=cc.get('hibás', 0), m=cc.get('nincs megoldás', 0)))
    lines.append('')
    write(os.path.join(dir_abs, 'SUMMARY.md'), '\n'.join(lines))


def write(path, text):
    with open(path, 'w', encoding='utf-8') as f:
        f.write(text)


def generate_summaries(records):
    """Témakör-mappák: táblázat. Az ennél feljebbi mappák (gyűjtemény, kategória): áttekintés."""
    by_topic = {}
    for r in records:
        by_topic.setdefault(os.path.dirname(r['path']), []).append(r)

    for topic_rel, recs in by_topic.items():
        title = parse_name(os.path.basename(topic_rel))[1] or os.path.basename(topic_rel)
        write_leaf_summary(os.path.join(MESTER, topic_rel), recs, title)

    summary_dirs = set(by_topic)
    for topic_rel in by_topic:
        parent = os.path.dirname(topic_rel)
        while parent not in ('', '.'):
            summary_dirs.add(parent)
            parent = os.path.dirname(parent)

    for dir_rel in sorted(summary_dirs - set(by_topic)):
        children = []
        for child in sorted(summary_dirs):
            if os.path.dirname(child) != dir_rel:
                continue
            recs = [r for r in records if r['path'] == child or r['path'].startswith(child + os.sep)]
            title = parse_name(os.path.basename(child))[1] or os.path.basename(child)
            children.append((os.path.join(MESTER, child), title, recs))
        if children:
            write_overview(os.path.join(MESTER, dir_rel), children, os.path.basename(dir_rel))


def write_index(records):
    lines = [
        '# Feladatkönyvtár – tartalomjegyzék',
        '',
        '> Generált fájl (`library/tools/catalog.py`). A használatát és a tanóra-tervezést lásd: [README.md](README.md).',
        '',
        f'Összesítés: {summary_line(counts(records))}',
        '',
        '| Gyűjtemény | Témakörök | Feladatok | ✅ kész | ❌ hibás | ⬜ nincs megoldás |',
        '|---|---:|---:|---:|---:|---:|',
    ]
    for cat in sorted({r['category'] for r in records}):
        recs = [r for r in records if r['category'] == cat]
        cc = counts(recs)
        topics = {os.path.dirname(r['path']) for r in recs}
        lines.append('| {l} | {tn} | {t} | {k} | {h} | {m} |'.format(
            l=link_to(os.path.join(LIB_ROOT), os.path.join(MESTER, cat), cat, 'SUMMARY.md'),
            tn=len(topics), t=cc['total'], k=cc.get('kész', 0), h=cc.get('hibás', 0), m=cc.get('nincs megoldás', 0)))
    lines.append('')
    for cat in sorted({r['category'] for r in records}):
        lines.append(f'## {cat}')
        lines.append('')
        recs = [r for r in records if r['category'] == cat]
        for t in sorted({os.path.dirname(r['path']) for r in recs}):
            tr = [r for r in recs if os.path.dirname(r['path']) == t]
            cc = counts(tr)
            label = parse_name(os.path.basename(t))[1] or os.path.basename(t)
            lines.append(f"- {link_to(LIB_ROOT, os.path.join(MESTER, t), label, 'SUMMARY.md')} — "
                         f"{cc['total']} feladat, ✅ {cc.get('kész', 0)}, ❌ {cc.get('hibás', 0)}, "
                         f"⬜ {cc.get('nincs megoldás', 0)}")
        lines.append('')
    write(os.path.join(LIB_ROOT, 'INDEX.md'), '\n'.join(lines))


def write_catalog(records):
    with open(os.path.join(LIB_ROOT, 'catalog.json'), 'w', encoding='utf-8') as f:
        json.dump(records, f, ensure_ascii=False, indent=1)
    cols = ['path', 'category', 'topic', 'number', 'title', 'difficulty', 'goal', 'method',
            'category_label', 'tags', 'status', 'samples_passed', 'samples_total']
    with open(os.path.join(LIB_ROOT, 'catalog.csv'), 'w', encoding='utf-8', newline='') as f:
        w = csv.writer(f)
        w.writerow(['útvonal', 'gyűjtemény', 'témakör', 'sorszám', 'cím', 'nehézség', 'órai cél', 'módszer',
                    'kategória', 'címkék', 'állapot', 'minta_ok', 'minta_össz'])
        for r in records:
            w.writerow([r[c] if c != 'tags' else ';'.join(r[c]) for c in cols])


def main(argv):
    no_validate = '--no-validate' in argv
    only = None
    if '--only' in argv:
        only = argv[argv.index('--only') + 1]
    records = build_records(no_validate=no_validate, only=only)
    generate_summaries(records)
    write_index(records)
    write_catalog(records)
    print(summary_line(counts(records)))
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
