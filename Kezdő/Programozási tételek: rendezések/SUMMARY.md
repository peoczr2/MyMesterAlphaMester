# Programozási tételek: rendezések – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 34 feladat · ✅ kész 23 · ❌ hibás 0 · 🟡 kézi 11 · 🟡 nincs minta/speciális 0 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Felvételi](<1. Felvételi */>) | Iteratív ponthatár-keresés | Ponthatárok iteratív emelése, ha a szak megsérti a keretfeltételt | 1 | Mélyebb megértés | ✅ kész |
| 2 | [Futók](<2. Futók */>) | Páronkénti összehasonlítás | Minden párra a találkozási idő kiszámítása, egész másodpercre kerekítve, halmazba gyűjtve | 1 | Magyarázat | ✅ kész |
| 3 | [Futóverseny](<3. Futóverseny */>) | Rendezés: rangsorolás | Futási idő = célidő − rajtszám, rendezés, csoportonként helyezés holtversennyel. | 1 | Bevezetés | ✅ kész |
| 4 | [Gazda szilvafái](<4. Gazda szilvafái */>) | Rendezés, mohó kiválasztás | Összefüggő szakaszok száma: nyárfaszám szerint csökkenő rendezés, mohó összeadás | 1 | Magyarázat | ✅ kész |
| 5 | [Inverz orgonasíp elrendezés](<5. Inverz orgonasíp elrendezés */>) | Rendezés, sorozat átrendezése | Csökkenő rendezés, majd váltakozva a sor elejére és végére töltés | 1 | Bevezetés | ✅ kész |
| 6 | [Kalapácsvető verseny](<6. Kalapácsvető verseny */>) | Rendezés, egyedi összehasonlítás | Dobássorok csökkenő rendezése, lexikografikus összehasonlítás, stabil rendezés | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 7 | [Kalapácsvető verseny selejtezője](<7. Kalapácsvető verseny selejtezője */>) | Rendezés, kiválasztás küszöbbel | H-t elérők és a legjobbak K-ig; csökkenő rendezés dobás szerint | 1 | Magyarázat | ✅ kész |
| 8 | [Legolcsóbb almák](<8. Legolcsóbb almák */>) | Rendezés, kiválasztás | Napi szimuláció: aktuális árak tömbje, rendezés (ár, sorszám) szerint | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 9 | [Magasugró verseny](<9. Magasugró verseny **/>) | Egyedi rendezési kulcs | Versenyzőnként magasságonkénti eredményvektor, lexikografikus rendezés | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 10 | [Mozgat](<10. Mozgat */>) | Szakaszlista, szimuláció | Szakaszlista: a szöveget összefüggő sortartományokkal tároljuk | 1 | Magyarázat | ✅ kész |
| 11 | [OKTV](<11. OKTV */>) | Többkulcsos rendezés | Többkulcsos rendezés a fordulók sorrendjében | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 12 | [Olimpia](<12. Olimpia */>) | Számlálás, rendezés | Érmek számlálása, majd többkulcsos rendezés | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 13 | [Orgonasíp elrendezés](<13. Orgonasíp elrendezés */>) | Rendezés, elrendezés | Csökkenő rendezés, majd a legnagyobbtól kezdve váltakozó balra-jobbra elhelyezés a középtől. | 1 | Bevezetés | ✅ kész |
| 14 | [Párosítás](<14. Párosítás */>) | Rendezés, mohó párosítás | Rendezés után mohó párosítás: mindig a legkisebb, még legyőzhető ellenféllel. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 15 | [Ütemez](<15. Ütemez */>) | Ütemezés, Johnson-szabály | Johnson-szabály: csoportosítás A_i≤B_i szerint, rendezés, majd két gép idejének szimulálása. | 1 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 16 | [Üvegválogatás](<16. Üvegválogatás */>) | Mohó választás, cserék száma | A legtöbb fehéret tartalmazó rekeszek tiszta fehérek; a többi fehér összege, a vegyes rekesz korrekciójával. | 1 | Magyarázat | ✅ kész |
| 17 | [Hallgató felező](<17. Hallgató felező */>) | Rendezés, kiválasztás | Pontszámok csökkenő rendezése, a ceil(N/2)-edik elem kiválasztása | 1 | Bevezetés | ✅ kész |
| 18 | [Hallgatók sorrendje](<18. Hallgatók sorrendje **/>) | Többkulcsos rendezés | Többkulcsos rendezés összehasonlító függvénnyel, végső kulcsnak a sorszám | 2 | Magyarázat | ✅ kész |
| 19 | [Legnagyobb lakások](<19. Legnagyobb lakások */>) | Rendezés, K. elem | Alapterületek csökkenő rendezése, a K. értéknél nem kisebbek megszámlálása | 1 | Bevezetés | ✅ kész |
| 20 | [Magasugró verseny](<20. Magasugró verseny ***/>) | Rendezés: lexikografikus kulcs | Magasságonként értékvektor, csökkenő magasság szerint lexikografikus rendezés. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 21 | [Olimpiára kijutó versenyzők](<21. Olimpiára kijutó versenyzők ***/>) | Rendezés: pontozás | Pontösszegzés, a K. helyezett pontszáma adja a kijutási határt. | 3 | Bevezetés | ✅ kész |
| 22 | [Termékhasznok](<22. Termékhasznok **/>) | Rendezés: legnagyobb értékek | Haszon számítása, csökkenő rendezés, az első K érték kiírása. | 2 | Bevezetés | ✅ kész |
| 23 | [Tó körüli települések](<23. Tó körüli települések/>) | Kör: sorrend rekonstrukció | 1-estől és legközelebbi településtől mért távolságokkal oldalakat határozunk meg, majd rendezünk. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 24 | [Programozási verseny](<24. Programozási verseny/>) | Rendezés: összetett kulcs | Versenyzőnként összegyűjtött helyezési pontok, összeg szerinti rendezés, egyenlőségnél lexikografikus pontlista-összehasonlítás. | 3 | Magyarázat | ✅ kész |
| 25 | [Konténerek rendezése](<25. Konténerek rendezése/>) | Rendezés: rekurzív felosztás | Oszlopok szomszédos összeolvasztása elkülönülő értékhalmazok mentén, rekurzív felosztással. | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 26 | [Kavicsok](<26. Kavicsok/>) | Mohó algoritmus, számlálás | Mohó megoldás: a kupacméretek gyakoriságából a legnagyobb K érték összege. | 2 | Magyarázat | ✅ kész |
| 27 | [Kavicsok 1](<27. Kavicsok 1/>) | Mohó algoritmus, számlálás | Mohó megoldás gyakoriságtömbből, a legnagyobb K érték összege; a kupacokat nem tároljuk. | 2 | Magyarázat | ✅ kész |
| 28 | [Kavicsok 2](<28. Kavicsok 2/>) | Mohó: bináris keresés | Mohó választás: K legnagyobb kupac, bináris keresés a K-adik értékre. | 3 | Magyarázat | ✅ kész |
| 29 | [Kavicsok 3](<29. Kavicsok 3/>) | Mohó: kupac, bináris keresés | Streamelt K legnagyobb kupac min-kupacban, bináris keresés a K-adik értékre. | 3 | Magyarázat | ✅ kész |
| 30 | [Kavicsok 4](<30. Kavicsok 4/>) | Mohó: kupac, bináris keresés | Streamelt K legnagyobb kupac min-kupacban, bináris keresés a K-adik értékre. | 4 | Mélyebb megértés | ✅ kész |
| 31 | [Konténerek rendezése](<31. Konténerek rendezése/>) | Rendezés: műveletsor | Buborékrendezés az üres hely segítségével: a szomszédos inverz párokat négy lépéses cserével rendezzük. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 32 | [Sok csoportra osztás](<32. Sok csoportra osztás/>) | Rendezés: csoportosítás | Pontszámok rendezése, a T-nél nagyobb szomszédos különbségek közül a K-1 legnagyobb. | 2 | Bevezetés | ✅ kész |
| 33 | [Világranglista](<33. Világranglista/>) | Rendezés: ranglista frissítés | Ranglista összefésülése: csak a javított versenyzők mozognak, egyetlen bejárással számolunk helyezést. | 3 | Magyarázat | ✅ kész |
| 34 | [Késés](<34. Késés ****/>) | Keresés: utolsó előfordulás | Az évszámok utolsó előfordulási indexei közül a minimumot keressük; rendezéssel csoportosítunk. | 4 | Bevezetés | ✅ kész |
