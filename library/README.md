# Feladatkönyvtár – használati útmutató

Ez a könyvtár a `mester/` mappa feladatait rendezi úgy, hogy belőlük gyorsan lehessen óravázlatot készíteni. A mappaszerkezet és a feladatmappák változatlanok maradtak; a könyvtár a meglévő mappákra épül, és generált áttekintéseket készít hozzájuk.

- Tartalomjegyzék: [INDEX.md](INDEX.md)
- Megoldási szabályok (formátum, hintek, ellenőrzés): [WORKFLOW.md](WORKFLOW.md)
- Gráf-feladatsor (OKTV, nehézségi sorrendben): [../oktv_graph_ladder.md](../oktv_graph_ladder.md)

## 1. Szerkezet

```
mester/
├── Kezdő/                         gyűjtemény
│   ├── Programozási tételek: keresés/   témakör
│   │   ├── SUMMARY.md             a témakör táblázata (generált)
│   │   └── 10. Korcsolyázós nap a Balatonon */   feladatmappa
│   │       ├── feladat.pdf        a feladat szövege
│   │       ├── minta.zip          mintabemenetek és -kimenetek
│   │       └── task.cpp           megoldás: magyarázat + hint-blokk + kód
├── Középhaladó/
├── Haladó/
├── NT, OKTV, IOI Válogató/        versenyek; a témakör itt a verseny (forduló)
├── CEOI (Közép-Európai Informatikai Diákolimpia)/
└── library/                       ez a könyvtár
    ├── INDEX.md                   tartalomjegyzék (generált)
    ├── catalog.csv / catalog.json  teljes katalógus (generált)
    ├── meta/                      módszer, kategória, cél, címkék (kézi/ágens adat)
    ├── tools/                     validate.py, catalog.py, plan.py, make_batches.py
    └── WORKFLOW.md                megoldási szabályok
```

- **Gyűjtemény** (első szint): Kezdő, Középhaladó, Haladó, NT/OKTV/IOI Válogató, CEOI.
- **Témakör** (második szint): az algoritmikus téma (pl. „Gráfok, mélységi bejárás”), vagy versenyeknél a forduló.
- **Feladat**: a mappanév `sorszám. cím csillagok` formájú. A csillagok a nehézség (`*` … `****`); csillag nélkül a nehézséget a megoldó becsülte.

Minden témakör-mappában és gyűjteményben van egy `SUMMARY.md`: a témakör táblázata (feladat, kategória, módszer, nehézség, órai cél, állapot), illetve a gyűjtemény áttekintése. Ezeket a generátor írja, kézzel ne szerkeszd.

## 2. Állapotok

| Állapot | Jelentés |
|---|---|
| ✅ kész | van megoldás, formátuma rendben, fordul, minden minta stimmel |
| 🟡 kézi ellenőrzés | több helyes kimenet van; a mintát kézzel, indoklással ellenőrizték |
| 🟡 nincs minta | van megoldás, de a feladathoz nincs futtatható minta |
| 🟡 speciális | zsűri-, grader- vagy interaktív feladat; automatikusan nem tesztelhető |
| ❌ hibás | formátum-, fordítási vagy mintahiba |
| ⬜ nincs megoldás | még nincs `task.cpp` |

Az állapotot a `validate.py` határozza meg minden futtatáskor, nem kézzel.

## 3. Óraterv készítése

A `plan.py` a katalógusból választ feladatokat, és Markdown óravázlatot ír (feladatlista, javasolt sorrend, linkek a mappákhoz). A parancsokat a `mester/` mappából futtasd:

```bash
python3 library/tools/plan.py --topic "Programozási tételek: keresés" --goal Bevezetés
python3 library/tools/plan.py --topic "Gráfok, mélységi" --diff 1-2 --count 5
python3 library/tools/plan.py --tag prefixösszeg --diff 2-3 --count 4 --out library/plans/prefix.md
python3 library/tools/plan.py --category Haladó --diff 3 --count 6 --status any
```

Szűrők:

| Kapcsoló | Jelentés |
|---|---|
| `--category` | gyűjtemény neve (pontosan) |
| `--topic` | témakör vagy útvonal-részlet |
| `--tag` | tanórai címke (részleges egyezés) |
| `--diff` | nehézség: `N` vagy `N-M` (1–5) |
| `--goal` | `Bevezetés`, `Magyarázat` vagy `Mélyebb megértés` |
| `--status` | `kész` (alapértelmezés), `kézi`, `any` vagy más állapot |
| `--count` | ennyi feladatot ad vissza, egyenletesen a sorrendben |

Egy óra jellemzően 4–6 feladat: egy `Bevezetés`, két `Magyarázat`, egy `Mélyebb megértés` jó kiindulás. A `--count` a sorrendet is tartja (könnyebbtől a nehezebbig).

## 4. Metaadat

A `library/meta/*.json` fájlok tartalmazzák, ami a mappanevekből nem derül ki: a használt módszert, a témakör-címkét, az órai célt és a tanórai címkéket. A `000-bootstrap.json` a korábbi `SUMMARY.md` táblázatokból készült. A többi fájlt a megoldó batch-ek írják (lásd [WORKFLOW.md](WORKFLOW.md) 4. szakasz).

## 5. Frissítés

```bash
python3 library/tools/catalog.py                  # ellenőrzés (gyorsítótárral) + minden generált fájl
python3 library/tools/catalog.py --no-validate    # csak az utolsó ellenőrzés eredményei
python3 library/tools/validate.py "Kezdő/Programozási tételek: keresés/10. Korcsolyázós nap a Balatonon *"
```

Az ellenőrzés gyorsítótára a `library/.work/` mappában van (a `.gitignore` kizárja).

## 6. Ismert korlátok

- A mappanevekben van egy-két helyesírási hiba és ütközés (pl. két `33. Repterek`); a katalógus ettől nem változik, a `path` mező a pontos mappanév.
- A `WARNING.md` (a mester gyökerében) a minta.zip-ekben hiányzó vagy fölösleges fájlokat sorolja. Ezek a validátornál minta-hibaként jelennek meg, amíg a zip nincs javítva.
- Az interaktív és grader-alapú feladatok (pl. „Interaktív feladatok”, CEOI-grader) nem futtathatók a minta.zip alapján; állapotuk `speciális`.
- A `plans/` vagy más kimeneti mappa létrehozása a `plan.py --out` kapcsolóval történik; a repóban nincs előre létrehozott `plans/` mappa.
