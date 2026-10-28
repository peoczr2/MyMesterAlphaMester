#!/usr/bin/env python3
"""Óravázlat készítése a feladatkönyvtárból.

Példák:
    python3 library/tools/plan.py --topic "Gráfok, mélységi" --diff 1-2 --count 5
    python3 library/tools/plan.py --topic "Programozási tételek: keresés" --goal Bevezetés
    python3 library/tools/plan.py --tag prefixösszeg --diff 2-3 --out plans/prefix.md
    python3 library/tools/plan.py --category Haladó --status any --diff 4 --count 3

Szűrők (többször is megadhatók, ÉS kapcsolatban):
    --category  gyűjtemény neve (pl. Kezdő, Középhaladó, Haladó, NT, OKTV, IOI Válogató, CEOI)
    --topic     témakör vagy útvonal-részlet (kis-nagybetű nem számít)
    --tag       címke (részleges egyezés)
    --diff      nehézség: N vagy N-M (1–5)
    --goal      Bevezetés | Magyarázat | Mélyebb megértés
    --status    kész (alapértelmezés) | kézi | any

Rendezés: órai cél (Bevezetés → Magyarázat → Mélyebb), majd nehézség, majd sorszám.
A `--count` a kiválasztott feladatok számát korlátozza (egyenletesen a sorrendben).
"""
import argparse
import datetime
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
LIB_ROOT = os.path.dirname(HERE)
MESTER = os.path.dirname(LIB_ROOT)
CATALOG = os.path.join(LIB_ROOT, 'catalog.json')
GOAL_ORDER = {'Bevezetés': 0, 'Magyarázat': 1, 'Mélyebb megértés': 2}
STATUS_TEXT = {'kész': '✅ kész', 'kézi': '🟡 kézi ellenőrzés', 'nincs minta': '🟡 nincs minta',
               'speciális': '🟡 speciális', 'hibás': '❌ hibás', 'nincs megoldás': '⬜ nincs megoldás'}


def parse_range(text):
    if text is None:
        return None
    if '-' in text:
        a, b = text.split('-', 1)
        return int(a), int(b)
    return int(text), int(text)


def matches(r, args, diff_range):
    if args.category and r['category'].lower() != args.category.lower():
        return False
    if args.topic and not any(args.topic.lower() in x.lower() for x in (r['path'], r['topic_title'])):
        return False
    if args.tag and not any(args.tag.lower() in t.lower() for t in r['tags']):
        return False
    if diff_range is not None:
        d = r['difficulty']
        if d is None or not (diff_range[0] <= d <= diff_range[1]):
            return False
    if args.goal and r['goal'] != args.goal:
        return False
    if args.status != 'any' and r['status'] != args.status:
        return False
    return True


def link(path, out_dir):
    return os.path.relpath(os.path.join(MESTER, path), out_dir) + '/'


def cell(text):
    return (text or '–').replace('|', '\\|')


def build(records, args):
    diff_range = parse_range(args.diff)
    picked = [r for r in records if matches(r, args, diff_range)]
    picked.sort(key=lambda r: (GOAL_ORDER.get(r['goal'], 9), r['difficulty'] or 9,
                               r['number'] if r['number'] is not None else 10**6, r['title']))
    if args.count and len(picked) > args.count:
        step = len(picked) / args.count
        picked = [picked[int(i * step)] for i in range(args.count)]

    out_dir = os.path.dirname(os.path.abspath(args.out)) if args.out else os.getcwd()
    filters = [f'{k}: {v}' for k, v in [('gyűjtemény', args.category), ('témakör', args.topic),
                                          ('címke', args.tag), ('nehézség', args.diff),
                                          ('cél', args.goal), ('állapot', args.status)] if v]
    lines = [
        '# Óravázlat',
        '',
        f'- Szűrők: {"; ".join(filters) if filters else "nincs (minden feladat)"}',
        f'- Készült: {datetime.date.today().isoformat()} · találat: {len(picked)} feladat',
        '',
        '| # | Feladat | Gyűjtemény / témakör | Módszer | Nehézség | Órai cél | Állapot |',
        '|---|---|---|---|---:|---|---|',
    ]
    for i, r in enumerate(picked, 1):
        title = r['title'] or r['folder']
        lines.append('| {i} | [{t}](<{l}>) | {c} / {tk} | {m} | {d} | {g} | {s} |'.format(
            i=i, t=cell(title), l=link(r['path'], out_dir), c=cell(r['category']), tk=cell(r['topic_title']),
            m=cell(r['method']), d=r['difficulty'] or '–', g=cell(r['goal']),
            s=STATUS_TEXT.get(r['status'], r['status'])))
    lines += ['', '## Javasolt menet', '']
    if not picked:
        lines.append('_Nincs találat. Lazítsd a szűrőket (pl. `--status any`, szélesebb `--diff`)._')
    for i, r in enumerate(picked, 1):
        role = {'Bevezetés': 'bemelegítés', 'Magyarázat': 'fő ötlet', 'Mélyebb megértés': 'kihívás'}.get(r['goal'], 'gyakorlás')
        lines.append(f'{i}. **{role}:** {r["title"] or r["folder"]} – {r["method"] or "módszer még nincs leírva"}')
    lines.append('')
    return '\n'.join(lines)


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--category')
    ap.add_argument('--topic')
    ap.add_argument('--tag')
    ap.add_argument('--diff')
    ap.add_argument('--goal', choices=list(GOAL_ORDER))
    ap.add_argument('--status', default='kész', choices=['kész', 'kézi', 'nincs minta', 'speciális', 'hibás',
                                                         'nincs megoldás', 'any'])
    ap.add_argument('--count', type=int, default=0)
    ap.add_argument('--out')
    args = ap.parse_args(argv)

    with open(CATALOG, encoding='utf-8') as f:
        records = json.load(f)
    text = build(records, args)
    if args.out:
        os.makedirs(os.path.dirname(os.path.abspath(args.out)), exist_ok=True)
        with open(args.out, 'w', encoding='utf-8') as f:
            f.write(text)
        print(f'óravázlat: {args.out}')
    else:
        print(text)
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
