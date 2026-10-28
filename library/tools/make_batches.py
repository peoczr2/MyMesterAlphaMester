#!/usr/bin/env python3
"""Megoldói batch-fájlok készítése a katalógus (catalog.json) alapján.

Használat:
    python3 library/tools/make_batches.py --mode solve --filter "Kezdő/" --prefix K --size 4
    python3 library/tools/make_batches.py --mode revise --filter "Haladó/" --prefix R
    python3 library/tools/make_batches.py --mode meta --filter "Haladó/" --prefix M --size 15
    python3 library/tools/make_batches.py --mode escalate --filter "CEOI" --prefix zS --model sonnet

Módok (melyik feladat kerül be):
    solve     : nincs task.cpp (állapot: nincs megoldás)
    revise    : van task.cpp, de hibás (formátum / fordítás / minta)
    meta      : kész vagy kézi/minta-nélküli, de nincs módszer-leírása a metaadatban
    escalate  : nincs megoldás vagy hibás – erősebb modellnek (Sonnet)

A batch-fájlok: library/.work/batches/<prefix>-<NNN>.json
Egy batch a feladatokat témakörön belül tartja össze, hogy egy ágens egy témát lásson.
"""
import argparse
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
LIB_ROOT = os.path.dirname(HERE)
CATALOG = os.path.join(LIB_ROOT, 'catalog.json')
OUT_DIR = os.path.join(LIB_ROOT, '.work', 'batches')


def select(records, mode):
    out = []
    for r in records:
        st = r['status']
        if mode == 'solve' and st == 'nincs megoldás':
            out.append(r)
        elif mode == 'revise' and st in ('hibás',) and r['has_solution']:
            out.append(r)
        elif mode == 'meta' and st in ('kész', 'kézi', 'nincs minta', 'speciális') and not r['method']:
            out.append(r)
        elif mode == 'escalate' and st in ('nincs megoldás', 'hibás'):
            out.append(r)
    return out


def chunks_by_topic(recs, size):
    by_topic = {}
    for r in recs:
        by_topic.setdefault(r['topic_dir'] if 'topic_dir' in r else os.path.dirname(r['path']), []).append(r)
    for topic in sorted(by_topic):
        items = by_topic[topic]
        for i in range(0, len(items), size):
            yield items[i:i + size]


def main(argv):
    ap = argparse.ArgumentParser()
    ap.add_argument('--mode', required=True, choices=['solve', 'revise', 'meta', 'escalate'])
    ap.add_argument('--filter', action='append', default=[], help='útvonal-előtag (többször is megadható)')
    ap.add_argument('--prefix', required=True, help='batch-azonosító előtag, pl. K, R, M, zS')
    ap.add_argument('--size', type=int, default=4)
    ap.add_argument('--model', default='haiku', choices=['haiku', 'sonnet'])
    ap.add_argument('--start', type=int, default=1, help='első batch-sorszám')
    ap.add_argument('--limit', type=int, default=0, help='legfeljebb ennyi batch (0 = mind)')
    args = ap.parse_args(argv)

    with open(CATALOG, encoding='utf-8') as f:
        records = json.load(f)
    if args.filter:
        records = [r for r in records if any(r['path'].startswith(p) for p in args.filter)]
    recs = select(records, args.mode)
    os.makedirs(OUT_DIR, exist_ok=True)

    batches = list(chunks_by_topic(recs, args.size))
    if args.limit:
        batches = batches[:args.limit]
    for n, items in enumerate(batches, start=args.start):
        bid = f'{args.prefix}-{n:03d}'
        payload = {
            'id': bid,
            'mode': args.mode,
            'model': args.model,
            'paths': [r['path'] for r in items],
            'meta_file': f'library/meta/{bid}.json',
        }
        with open(os.path.join(OUT_DIR, bid + '.json'), 'w', encoding='utf-8') as f:
            json.dump(payload, f, ensure_ascii=False, indent=1)
    print(f'{args.mode}: {len(recs)} feladat, {len(batches)} batch ({args.prefix}-{args.start:03d}…)')
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
