#!/usr/bin/env python3
"""Egyszeri import: a meglévő SUMMARY.md táblázatok sorait metaadat-fájlba menti.

Kimenet: library/meta/000-bootstrap.json (a feladatmappa-útvonalak szerint).
A generáló (catalog.py) ezt olvassa be először, így a korábban kézzel írt
módszer-, kategória- és nehézségadatok nem vesznek el.
"""
import json
import os
import re
import sys

LIB_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MESTER = os.path.dirname(LIB_ROOT)
OUT = os.path.join(LIB_ROOT, 'meta', '000-bootstrap.json')

NUM_TITLE = re.compile(r'^\s*(\d+)\.\s*(.*?)\s*$')
STARS = re.compile(r'\s*\*+\s*$')


def norm(s):
    return re.sub(r'[\s\*]+', ' ', s).strip().lower()


def find_summaries():
    for dirpath, dirnames, filenames in os.walk(MESTER):
        dirnames[:] = [d for d in dirnames if d not in ('.git', '.github', '.infagent', 'library')]
        if 'SUMMARY.md' in filenames:
            yield dirpath


def parse_table(path):
    rows, header = [], None
    with open(path, encoding='utf-8') as f:
        for line in f:
            line = line.strip()
            if not line.startswith('|'):
                header = None if line == '' else header
                continue
            cells = [c.strip() for c in line.strip('|').split('|')]
            if header is None:
                if any(c in ('Feladat', 'Kategória') for c in cells):
                    header = cells
                continue
            if set(''.join(cells)) <= set('-: '):
                continue
            rows.append(dict(zip(header, cells)))
    return rows


def set_key(name):
    return re.sub(r'[\s/∕]', '', name).lower()


def match_set(sdir, verseny):
    """A SUMMARY 'Verseny' neve és a mappanév eltérhet (pl. '2018/19' vs '2018 ∕ 19')."""
    for name in os.listdir(sdir):
        if os.path.isdir(os.path.join(sdir, name)) and set_key(name) == set_key(verseny):
            return name
    return None


def pick_folder(base, number, title):
    """A táblázat sorához tartozó feladatmappa megkeresése: szám + cím alapján."""
    if not os.path.isdir(base):
        return None
    candidates = []
    for name in os.listdir(base):
        full = os.path.join(base, name)
        m = NUM_TITLE.match(name)
        if os.path.isdir(full) and m and int(m.group(1)) == number:
            candidates.append((name, m.group(2)))
    if not candidates:
        return None
    if len(candidates) == 1:
        return candidates[0][0]
    for name, t in candidates:
        if norm(STARS.sub('', t)) == norm(STARS.sub('', title)):
            return name
    return candidates[0][0]


def main():
    entries = []
    for sdir in sorted(find_summaries()):
        rel_dir = os.path.relpath(sdir, MESTER)
        for row in parse_table(os.path.join(sdir, 'SUMMARY.md')):
            feladat = row.get('Feladat', '')
            m = NUM_TITLE.match(feladat)
            if '#' in row and row['#'].isdigit():
                number, title = int(row['#']), feladat
            elif m:
                number, title = int(m.group(1)), m.group(2)
            else:
                continue
            base = sdir
            if 'Verseny' in row:
                base = os.path.join(sdir, match_set(sdir, row['Verseny']) or row['Verseny'])
            folder = pick_folder(base, number, title)
            if folder is None:
                print('nincs mappa:', rel_dir, number, title, file=sys.stderr)
                continue
            path = os.path.relpath(os.path.join(base, folder), MESTER)
            diff = row.get('Nehézság', '').strip()
            entries.append({
                'path': path,
                'method': row.get('Röviden használt módszer / algoritmus', '').strip(),
                'category': row.get('Kategória', '').strip(),
                'difficulty': int(diff) if diff.isdigit() else None,
                'goal': row.get('Órai cél', '').strip(),
                'tags': [],
                'note': 'SUMMARY.md-ből importálva',
                'solved_by': 'korábbi',
            })
    entries = [e for e in entries if e['method']]
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    with open(OUT, 'w', encoding='utf-8') as f:
        json.dump(entries, f, ensure_ascii=False, indent=1)
    print(f'{len(entries)} bejegyzés -> {os.path.relpath(OUT, MESTER)}')


if __name__ == '__main__':
    main()
