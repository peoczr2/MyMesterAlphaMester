# Geometriai algoritmusok – oktatási összefoglaló

> Batch mód: ez a fájl folyamatosan bővül. Az első batch-ben a **1, 2, 6, 7, 8, 11** feladatokhoz készült kész C++ megoldás.

Skála:
- **Nehézség 1–5**: 1 = nagyon alap, 5 = nagyon összetett
- **Ajánlott használat**: `Bevezetés` / `Magyarázat` / `Mélyebb megértés`

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | Árnyék | Sweep, láthatóság | Irány szerinti lineáris sweep, árnyékhatár maximum fenntartása | 2 | Magyarázat | ✅ kész |
| 2 | Autópálya | Konvex burok, tartóegyenes | Egyesített ponthalmaz konvex burka, különböző színű szomszédos burokpont keresése | 3 | Magyarázat | ✅ kész |
| 3 | Bekerítő háromszög | Pontok, üres háromszög | Fix él + harmadik csúcs keresés, pont-bennevan és „empty triangle” feltétel | 4 | Mélyebb megértés | ⏳ következő batch |
| 4 | Csomópontok | Síkgráf, útvonal | Nem metsző szakaszokkal erős összefüggőség kialakítása geometriai feltételekkel | 4 | Mélyebb megértés | ⏳ következő batch |
| 5 | Épület | Téglalap-unió, lyukak | Rács/kompresszió + komponensek, belső udvarok kerület/terület számítás | 4 | Mélyebb megértés | ⏳ következő batch |
| 6 | Épület kerülete | Sweep line, szegmentfa | Téglalap-unió külső kerület: x-söprés + fedett hossz + szakaszszám | 4 | Mélyebb megértés | ✅ kész |
| 7 | Fák kivágása | Pont poligonban | Ray casting (sugármetszés) egyszerű ortogonális poligonra | 2 | Magyarázat | ✅ kész |
| 8 | Futárok | Lineáris mozgás metszése | Időintervallum átfedés + két lineáris pozíciófüggvény metszésvizsgálata | 1 | Bevezetés | ✅ kész |
| 9 | Háromszög | Pontok, üres háromszög | q-t fedő, de más pontot nem fedő háromszög keresése | 4 | Mélyebb megértés | ⏳ következő batch |
| 10 | Háromszög kerítés | Optimalizálás geometriában | Harmadik csúcs választás: q belül, pontszám minimum a háromszögben | 4 | Mélyebb megértés | ⏳ következő batch |
| 11 | Házak | Sweep, árnyékprofil | Balról jövő fény: maximum árnyék-intercept fenntartása | 2 | Magyarázat | ✅ kész |
| 12 | Hegy | Láthatósági gráf / DP | Minimális közvetítő szám láthatósági kapcsolatokkal | 4 | Mélyebb megértés | ⏳ következő batch |
| 13 | Kerítés | Konvex burok / határ | Bekerítés-jellegű minimális határkonstrukció | 3 | Magyarázat | ⏳ következő batch |
| 14 | Lámpák | Láthatóság | Megvilágított tartományok metszete/egyesítése | 3 | Magyarázat | ⏳ következő batch |
| 15 | Lefedő egyenesek | Felezősík/fedés | Egyenesek minimális lefedési vagy szeparációs feltétele | 3 | Magyarázat | ⏳ következő batch |
| 16 | Négyszög alakú terület | Sokszög-terület | Metszés + területszámítás négyszögre redukálva | 3 | Magyarázat | ⏳ következő batch |
| 17 | Park | Alap síkgeometria | Egyszerű távolság/terület/perem számítás | 1 | Bevezetés | ⏳ következő batch |
| 18 | Poligon | Alap poligon műveletek | Terület, orientáció, konvexitás, metszés alapok | 2 | Bevezetés | ⏳ következő batch |
| 19 | Poligonok metszése | Poligon clip/metszés | Metsző sokszög számítása, terület/perem | 4 | Mélyebb megértés | ⏳ következő batch |
| 20 | Szoborpark | Fedés/optimalizálás | Geometriai optimalizálás korlátokkal | 4 | Mélyebb megértés | ⏳ következő batch |
| 21 | Telek | Alap sokszög | Szakasz-háromszög metszet és eset-szétválasztás | 1 | Bevezetés | ✅ kész |
| 22 | Terv | Konstrukciós geometria | Feltételeknek megfelelő síkbeli konstrukció | 2 | Magyarázat | ⏳ következő batch |
| 23 | Vágás | Felező egyenes / darabolás | Poligon-útszakasz metszésszám alapján darabszám | 1 | Bevezetés | ✅ kész |
| 24 | Zárt poligon készítése | Rendezés, konstrukció | x-monoton (bitonikus) egyszerű poligon konstrukció | 3 | Magyarázat | ✅ kész |
| 25 | Épület belső udvarai | Téglalap-unió lyukai | Unió komplementjének lyukkomponensei | 5 | Mélyebb megértés | ⏳ következő batch |
| 26 | Facsemeték bekerítése | Konvex burok / minimális kerítés | Pontok bekerítése minimális határral | 4 | Mélyebb megértés | ⏳ következő batch |
| 27 | Háromszög | Háromszög-feltételek | Üres háromszög konstrukció irány-rendezéssel | 2 | Magyarázat | ✅ kész |
| 28 | Oszlopok | Vetület, takarás | Origóból látható pontok száma irány-normalizálással | 1 | Bevezetés | ✅ kész |
| 29 | Épület elhagyása | Útvonaltervezés geometriában | Akadályok közti minimális/érvényes út | 4 | Mélyebb megértés | ⏳ következő batch |
| 30 | Elválasztó egyenes | Szeparáció | Két halmaz lineáris szeparálhatósága | 5 | Mélyebb megértés | ⏳ következő batch |
| 31 | Pontok poligonban | Geometriai lekérdezések | Több pont gyors PIP tesztje (logaritmikus/lineáris) | 5 | Mélyebb megértés | ⏳ következő batch |
| 32 | Négyzetek | Téglalap/négyzet metszés | Fedés, metszés, unió vagy optimális kiválasztás | 4 | Mélyebb megértés | ⏳ következő batch |
| 33 | Repterek | Távolságoptimalizálás | Legközelebbi pontpár / minimax jelleg | 4 | Mélyebb megértés | ⏳ következő batch |
| 34 | Épület | Komplex uniófeladat | Épület-geometria (lyukak/perem/komponensek) | 4 | Mélyebb megértés | ⏳ következő batch |
| 35 | Autópálya | Haladó szeparáció | Tartóegyenes/konvex burok haladó változat | 5 | Mélyebb megértés | ⏳ következő batch |
| 36 | Poligon | Haladó poligon | Clip/metszés/lekérdezés komplexebb korlátokkal | 3 | Magyarázat | ⏳ következő batch |
| 37 | Négyszög | Konvexitás / döntés | Négyszög-feltételek, terület, metszések | 2 | Magyarázat | ⏳ következő batch |
| 38 | Szuperhuszár | Geometria + kombinatorika | Rácspont/sík pontok speciális támadási reláció | 4 | Mélyebb megértés | ⏳ következő batch |
| 39 | Facsemete | Bekerítés / helyzet | Pont helyzetének döntése kerítéshez képest | 2 | Magyarázat | ⏳ következő batch |
| 40 | Konvex négyszög | Konvex geometria | Konvex négyszög konstrukció/ellenőrzés | 3 | Magyarázat | ⏳ következő batch |
| 41 | Bekerítés konvex négyszöggel | Optimalizált bekerítés | Konvex 4-szög választás pontokra | 5 | Mélyebb megértés | ⏳ következő batch |
| 42 | Szurikáta | Haladó síkgeometria | Láthatóság + optimalizáció kombináció | 5 | Mélyebb megértés | ⏳ következő batch |
| 43 | Szakaszok | Szakaszmetszések | Metszésszám / metsző párok detektálása | 3 | Magyarázat | ⏳ következő batch |
| 44 | Házak | Árnyék/lefedés | Épületprofil-láthatóság jellegű feladat | 2 | Magyarázat | ⏳ következő batch |
| 45 | Várfalak száma | Poligon topológia | Várfal-szakaszok összefüggő komponenseinek száma | 3 | Magyarázat | ✅ kész |
| 46 | Várfalak hossza | Kerület számítás | Komponensenkénti falhossz, kívülről befelé rendezve | 3 | Magyarázat | ✅ kész |
| 47 | Úthálózatbővítés | Geometriai gráfépítés | Nem metsző új élek + elérhetőség javítás | 4 | Mélyebb megértés | ⏳ következő batch |

## Batch állapot
- **Elkészült C++ megoldások**: 1, 2, 6, 7, 8, 11, 21, 23, 24, 27, 28, 45, 46
- **Következő batch javaslat**: 3, 4, 5, 9, 10
