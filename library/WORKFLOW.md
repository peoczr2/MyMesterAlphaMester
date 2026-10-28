# Megoldási munkafolyamat

Ez a dokumentum a feladatok megoldásának, felülvizsgálatának és nyilvántartásának egységes szabályait tartalmazza. Minden megoldó ágens (Haiku, Sonnet) ezt követi. Az ágensnek csak a kapott **batch-fájlban** felsorolt mappákon szabad dolgoznia.

## 1. Egy feladatmappa tartalma

| Fájl | Szerep |
|---|---|
| `feladat.pdf` | a feladat szövege – ez a forrás |
| `minta.zip` | mintabemenetek (`be1.txt`, `ki1.txt`, …) – a validátor ebből tesztel |
| `task.cpp` | a megoldás: magyarázat + hint-blokk + kód |

Más fájlt a feladatmappába nem teszel (sem binárist, sem jegyzetet).

## 2. A `task.cpp` kötelező felépítése

```cpp
/*
Megoldás lényege:
(3–10 mondat, magyarul: a kulcsgondolat, miért helyes, az időigény)
*/
/*
Hint 1: || … ||
Hint 2: || … ||
*/
#include <bits/stdc++.h>
using namespace std;
…
```

Szabályok:
- Az első blokk a magyarázat (magyarul).
- A második blokk **közvetlenül** utána jön: nincs üres sor, nincs `//` sor, nincs más komment vagy kód köztük.
- A hintek sorszáma 1-től folyamatos (`Hint 1`, `Hint 2`, …). Minden hint konkrét a feladatra nézve; helyőrző (`…`, `...`) nem megengedett. Egy hint lehet több sor is, de a `|| … ||` jelölés a hint végén záruljon.
- A hintek fokozatosak: 1. irány / kulcs-megfigyelés, 2. adatszerkezet vagy képlet, 3. (ha kell) részletes lépések. Teljes kódot a hintben **nem** adunk.
- Hintek száma a nehézséghez igazodjon: alapfeladat 1–2, közepes 2–3, nehéz 3–4. Ne tölts ki felesleges hintet.
- Bemenet/kimenet: szabványos be- és kimenet (`cin`/`cout`), a feladat formátuma szerint. C++17.
- A kód legyen egyszerű és tiszta; a fő függvény `main()`.

## 3. Ellenőrzés

```bash
timeout 300s python3 library/tools/validate.py "<feladatmappa relatív útja>"
```

A validátor: formátumot, fordítást (`g++ -O2 -std=c++17`), és a `minta.zip` párjait futtatja (időkorláttal, szóköz-érzéketlen összevetéssel). Állapotai:

| Állapot | Jelentés | Teendő |
|---|---|---|
| `kész` | formátum rendben, fordul, minden minta stimmel | ez a cél |
| `hibás` | formátum-, fordítási vagy mintahiba | javítsd, és futtasd újra |
| `nincs minta` | nincs be/ki pár a zipben | a megoldás fusson le kézzel, a note-ban írd le |
| `speciális` | zsűri/grader alapú vagy interaktív feladat | a note-ban írd le, mit kell kézzel ellenőrizni |

Több helyes kimenetű feladatnál (pl. „bármely megfelelő felosztás”) a minta eltérhet, miközben a megoldás helyes. Ilyenkor **ne** írd át a kimenetet a mintához. Írj egy rövid ellenőrző programot a munkakönyvtárban, ami a kimenet érvényességét igazolja, és a metaadatba tedd: `"minta": "kézi"`, a `note`-ban pedig egy mondatban az indoklást.

A `"minta": "kézi"` jelölés **szigorú**: csak akkor használható, ha
- a feladatszöveg szerint több helyes kimenet lehet, vagy
- a mintafájl egyértelműen hibás (a feladatszöveg és a minta ellentmond egymásnak), és ezt a note-ban konkrétan megjelölöd (melyik sor, melyik szám), és egy független brute-force / ellenőrző program igazolja a saját kimenetedet.

Ha a saját kimeneted nem egyezik a mintával, és nem tudod igazolni a fentieket, a feladat maradjon `hibás`, `blocked: true` és a note-ban a kérdés. Ne használd a `kézi` jelölést azért, hogy a feladat átmenjen.

## 4. Metaadat – `library/meta/<batch-id>.json`

Minden batch a saját fájljába ír egy **JSON-tömböt**, egy objektummal feladatonként:

```json
[
  {
    "path": "Kezdő/Programozási tételek: keresés/10. Korcsolyázós nap a Balatonon *",
    "method": "Lineáris bejárás, egy feltétel szerinti számlálás",
    "category": "Keresés",
    "difficulty": 2,
    "goal": "Bevezetés",
    "tags": ["keresés", "tömb", "számlálás"],
    "note": "",
    "minta": "",
    "blocked": false,
    "solved_by": "haiku"
  }
]
```

| Mező | Tartalom |
|---|---|
| `path` | a feladatmappa útvonala a `mester/` mappától, pontosan (a batch-fájlból) |
| `method` | a használt módszer 1 mondatban, magyarul, legfeljebb 15 szó |
| `category` | témakör-címke, legfeljebb 4 szó (pl. „Prefixösszeg”, „Gráf: BFS”, „Dinamikus programozás”) |
| `difficulty` | 1–5 egész: a te becslésed (a mappanév csillagai felülírják) |
| `goal` | `Bevezetés` (alapok, egy ötlet) · `Magyarázat` (egy trükk, egy adatszerkezet) · `Mélyebb megértés` (több lépéses ötlet, bizonyítás) |
| `tags` | 2–4 kisbetűs tanórai címke |
| `note` | rövid megjegyzés: minta-eltérés oka, blokkolás oka, zsűri-specialitás. Üres, ha nincs |
| `minta` | `"kézi"`, ha több helyes kimenet van (lásd 3.), különben üres |
| `blocked` | `true`, ha 3 próbálkozás után sem `kész` |
| `solved_by` | `"haiku"` vagy `"sonnet"` (a te modelled) |

A `method` ne tartalmazzon státuszt („task.cpp megvan”, „hátra van”, stb.) – csak a módszert írd le.

## 5. Próbálkozási keret

- Feladatonként legfeljebb **3** érdemi próbálkozás.
- Ha az első megközelítés nem működik, a következő legyen **másmilyen** ötlet (más adatszerkezet, más invariáns, brute-force ellenőrzés a kisméretű esetekre). Ugyanazt a hibás ötletet ne írd újra.
- Brute-force ellenőrzés kis bemeneteken segít eldönteni, melyik értelmezés a helyes – a feladat szövegét és a mintákat tekintsd forrásnak.
- 3 próbálkozás után sem `kész`: a legjobb változatot hagyd a `task.cpp`-ben (fordulóképes legyen, ha lehet), a metaadatban `"blocked": true`, a `note`-ban pedig a holtágak rövid felsorolása. Ne írj be hamis `kész` állapotot.

## 6. Felülvizsgálat (már létező `task.cpp`)

1. Futtasd a validátort, és olvasd el a feladatot és a meglévő megoldást.
2. `kész` esetén a kódot ne írd át: csak a metaadatot készítsd el a magyarázat alapján.
3. Formátumhiba esetén a magyarázat és a hintek szerkezetét javítsd (hiányzó hintet pótolj, sorrendet igazíts). A kódhoz csak akkor nyúlj, ha az hibás.
4. Minta- vagy fordítási hiba esetén keresd meg a hibát, javítsd, és futtasd újra a validátort.
5. A magyarázatban ne maradjon elavult státusz vagy munkanapló-jellegű szöveg; a magyarázat a megoldás **lényegét** írja le magyarul.

## 7. Tilos és kötelező

- Csak a batch-fájlban megadott mappákban dolgozz. Más feladatot ne oldj meg, más mappát ne módosíts.
- A feladatmappában lévő **meglévő fájlt nem törölsz és nem mozgatsz** (pl. `task_bin`, `task`, `task.out`, `minta.zip`, `feladat.pdf`), még akkor sem, ha binárisnak látszik. Ezek a repó részei. Ha egy binárist „kidobnál”, hagyd helyben; a munkakönyvtárba (`library/.work/`) csak másolatot készíts.
- `SUMMARY.md`, `library/INDEX.md`, `library/catalog.*`, a `.github/` és a `library/tools/` mappa nem a te feladatod: ezeket nem módosíthatod.
- Ne használj git-írást (commit, add, stash, checkout). Ne telepíts csomagot.
- Kész megoldást az internetről ne keress; fogalmakat, definíciókat szabad.
- Minden parancs legyen időkorlátos (`timeout …`). A fordítás és a futtatás is.
- Ideiglenes fájlok (kicsomagolt minták, binárisok, brute-force programok) a `library/.work/<batch-id>/` mappába kerüljenek; a repóban ne maradjon binári.
- A munka végén rövid választ adj: `<batch-id>: kész X/Y, blokkolt: <feladatszámok>`.

## 8. Útvonalak

- Feladatmappák: a `mester/` alatt (lásd a [README.md](README.md)-t).
- Validátor: `library/tools/validate.py`
- Metaadat-batch: `library/meta/<batch-id>.json`
- Munkakönyvtár: `library/.work/<batch-id>/`
