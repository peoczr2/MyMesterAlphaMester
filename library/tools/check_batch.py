#!/usr/bin/env python3
"""Egy batch eredményének gyors ellenőrzése: állapotok, töröl-e valamit a repó (git).

Használat: python3 library/tools/check_batch.py K-011 [R-004 ...]
"""
import json
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
LIB_ROOT = os.path.dirname(HERE)
MESTER = os.path.dirname(LIB_ROOT)
BATCHES = os.path.join(LIB_ROOT, '.work', 'batches')


def main(ids):
    for bid in ids:
        with open(os.path.join(BATCHES, bid + '.json'), encoding='utf-8') as f:
            paths = json.load(f)['paths']
        counts = {}
        for p in paths:
            r = subprocess.run([sys.executable, os.path.join(HERE, 'validate.py'), p],
                               capture_output=True, text=True, cwd=MESTER)
            status = r.stdout.splitlines()[0].split('  ')[0].strip() if r.stdout else 'hiba'
            counts[status] = counts.get(status, 0) + 1
            if status != 'kész':
                print(f'  {bid}: {status:<14} {p}')
        print(f'{bid}: {counts}')
    deleted = subprocess.run(['git', 'status', '--porcelain'], capture_output=True, text=True,
                             cwd=MESTER).stdout
    gone = [l for l in deleted.splitlines() if l.startswith(' D') or l.startswith('D ')]
    print(f'git: törölt fájlok a munkafában: {len(gone)}')
    for l in gone:
        print('  ' + l)
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
