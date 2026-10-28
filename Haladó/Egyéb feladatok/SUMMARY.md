# Egyéb feladatok – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 53 feladat · ✅ kész 41 · ❌ hibás 0 · 🟡 kézi 9 · 🟡 nincs minta/speciális 3 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Átfedő intervallumok](<1. Átfedő intervallumok */>) | Intervallumok, kupac | Bal végpont szerinti rendezés, K legnagyobb jobb végpont minimumkupaccal | 1 | Mélyebb megértés | ✅ kész |
| 2 | [Átutalások](<2. Átutalások */>) | Mohó párosítás | Nettó egyenlegek kiszámítása, majd az adósok és hitelezők mohó párosítása. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 3 | [Betűfelismerés](<3. Betűfelismerés */>) | Pixelgrafika, vonalelemzés | Szegmentálás üres oszlopokkal, majd végpontok és elágazások száma és helye alapján osztályozás. | 1 | Magyarázat | ✅ kész |
| 4 | [Csillagtérkép](<4. Csillagtérkép */>) | Legnagyobb téglalap | Alsó és felső sorpár rögzítése, leghosszabb csillagmentes oszlopszakasz | 1 | Magyarázat | ✅ kész |
| 5 | [Csoki](<5. Csoki */>) | Prefixösszeg, maradékok | Prefixösszegek maradékai, minden maradékhoz az utolsó előfordulás | 1 | Magyarázat | ✅ kész |
| 6 | [Csőposta](<6. Csőposta */>) | Szimuláció: ütközések | Eseményvezérelt szimuláció, láncolt listában tartott szomszédos ütközési párokkal és min-kupaccal. | 1 | Mélyebb megértés | ✅ kész |
| 7 | [Délkert](<7. Délkert */>) | Bináris keresés: hozzárendelés | Bináris keresés a K időkorlátra, utána a kényszerített és rugalmas termelők kapacitás szerinti szétosztása. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 8 | [Dominó nyertes](<8. Dominó nyertes **/>) | Játékelmélet: memoizált keresés | Memoizált DFS a játékállapotokon (maradék dominók, szabad vég, kör), kimenetelek bitmaszkos egyesítése. | 2 | Magyarázat | ✅ kész |
| 9 | [Fenyőfa](<9. Fenyőfa **/>) | Prefixösszeg: téglalap | Kétdimenziós prefixösszeg, minden sor- és oszlopintervallum-párra O(1) téglalap-ellenőrzés, minimális terület. | 2 | Bevezetés | ✅ kész |
| 10 | [Folt határa](<10. Folt határa */>) | Lánckód, kontúrkövetés | Perem-bejárás a Moore-szomszédsággal, az óramutató szerint, az előző iránytól indulva. | 1 | Magyarázat | ✅ kész |
| 11 | [Fordítóprogram](<11. Fordítóprogram **/>) | Fordítóprogram, tár | Két menetes fordítás: címkék előre kiszámítása, majd a [X] hivatkozások feloldása a teljes tár alapján. | 2 | Magyarázat | ✅ kész |
| 12 | [Futár](<12. Futár */>) | Intervallum-párosítás, csúszó ablak | Csúszó ablakos párosítás: ellentétes irány és az indulások különbsége kisebb, mint O. | 1 | Magyarázat | ✅ kész |
| 13 | [Genetika](<13. Genetika **/>) | Visszalépéses keresés, sztring | Visszalépéses keresés balról jobbra: K aktív darab, a leghosszabb új darab választása. | 2 | Mélyebb megértés | ✅ kész |
| 14 | [Gyöngy](<14. Gyöngy */>) | Csúszó ablak, körkörös tömb | Csúszó ablak körkörösen: a piros és zöld számlálót lépésenként O(1)-gyel frissítjük. | 1 | Bevezetés | ✅ kész |
| 15 | [Helyesírás](<15. Helyesírás */>) | Sztring-átalakítás, szóközök | Szomszédos karakterpárok osztályozása: a tiltó szabály felülírja a kötelezőt, egyébként a bemeneti szóköz-viszony marad. | 1 | Bevezetés | ✅ kész |
| 16 | [Intervallumok](<16. Intervallumok **/>) | Intervallum-tartalmazás, Fenwick-fa | Rendezés kezdőpont szerint, fordított sorrendben Fenwick-fával számoljuk a tartalmazott intervallumokat. | 2 | Magyarázat | ✅ kész |
| 17 | [Jegyek](<17. Jegyek */>) | Hézagok, maximin kiválasztás | A négy legnagyobb hézag a különböző pontszámok között; a ponthatár a felső pontszám előtti egész. | 1 | Magyarázat | ✅ kész |
| 18 | [Jelek](<18. Jelek */>) | Rekurzív felismerés, zárójelezés | Az A-szavakat U a U b bontással, rekurzívan ellenőrizzük; a B-szavakat zárójel-egyensúllyal. | 1 | Mélyebb megértés | ✅ kész |
| 19 | [Kapcsoló](<19. Kapcsoló */>) | Dinamikus programozás | Bekötött nyomtatók halmazát állapotként követő DP, 8 maszkon | 1 | Magyarázat | ✅ kész |
| 20 | [Katonák](<20. Katonák */>) | Rendezés, Manhattan-távolság | A két tengely független: rendezéssel kapjuk a célokat; előbb függőleges, utána vízszintes mozgatás. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 21 | [Kavicsok](<21. Kavicsok */>) | Memoizált keresés | Bitmaszk-állapotok memoizált rekurzív keresése, a végállapotok minimuma | 1 | Magyarázat | ✅ kész |
| 22 | [Képben kép keresése](<22. Képben kép keresése */>) | Mintaillesztés, hash | Kétdimenziós gördülő hash, egyezés után közvetlen ellenőrzés | 1 | Mélyebb megértés | ✅ kész |
| 23 | [Képtömörítés futammal](<23. Képtömörítés futammal */>) | Futamhossz-kódolás | Soronkénti futamhossz-kódolás az azonos betűk összefüggő szakaszaival | 1 | Bevezetés | ✅ kész |
| 24 | [Képtömörítés változással](<24. Képtömörítés változással */>) | Futamhossz-kódolás, változás | Első sor futamhossz-kódolása, utána csak az előzőtől eltérő szakaszok | 1 | Magyarázat | ✅ kész |
| 25 | [Kerekasztal](<25. Kerekasztal **/>) | Permutáció ciklusai | Minden körkörös eltolásra a permutáció ciklusait számoljuk; a csere N mínusz a ciklusok száma. | 2 | Magyarázat | ✅ kész |
| 26 | [Kísérlet](<26. Kísérlet */>) | Intervallumok, kupac | Keletkezés szerint rendezés, K legnagyobb pusztulási idő kupaccal | 1 | Mélyebb megértés | ✅ kész |
| 27 | [Körút](<27. Körút **/>) | Prefixösszeg, csúszóablak | Duplázott prefixösszegek csúszóablakos minimuma; ha nincs körbejárás, monoton veremmel számolunk. | 2 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 28 | [Lámpagyújtogató](<28. Lámpagyújtogató */>) | Bitműveletek, paritás | XOR-egyenletek: sor- és oszlopkapcsolók az első sor alapján, komplementerrel | 1 | Magyarázat | ✅ kész |
| 29 | [Lapok](<29. Lapok */>) | Diszjunkt halmazok | Hátulról festés DSU-val, majd komponensek számolása DSU-val | 1 | Mélyebb megértés | ✅ kész |
| 30 | [Lefedés két intervallummal](<30. Lefedés két intervallummal */>) | Intervallumok, szegmensfa | Bal végpont szerinti rendezés, szegmensfa a maximális jobb végponthoz | 1 | Mélyebb megértés | ✅ kész |
| 31 | [Legnagyobb hasznú téglalap](<31. Legnagyobb hasznú téglalap */>) | Prefixösszeg, téglalap | Osztópárok szerinti téglalapméretek, 2D prefixösszeggel kiértékelve | 1 | Magyarázat | ✅ kész |
| 32 | [Legrövidebb szakasz](<32. Legrövidebb szakasz **/>) | Csúszó ablak | Sajtárusok pozícióinak K-as csúszó ablaka, minimális különbség | 2 | Bevezetés | 🟡 nincs minta |
| 33 | [Legsűrűbb fás terület](<33. Legsűrűbb fás terület */>) | Prefixösszeg, sűrűség | Sorpárok rögzítése, oszlopösszegek, sűrűség keresztszorzással | 1 | Magyarázat | ✅ kész |
| 34 | [Lineáris közelítés](<34. Lineáris közelítés **/>) | Lineáris interpoláció | Ismert pontok közötti interpoláció, a széleken az első, illetve utolsó szakasz folytatása. | 2 | Bevezetés | 🟡 kézi ellenőrzés |
| 35 | [LOGO optimalizálás](<35. LOGO optimalizálás **/>) | Átírási szabályok, verem | Balról jobbra, verem jellegű feldolgozással: minden új utasítás után ismételt szabályalkalmazás. | 2 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 36 | [Mintakeresés](<36. Mintakeresés **/>) | Mintakeresés, minimális ablak | Prefixenként a legkésőbbi kezdőindexet tároljuk, így minden jobb végre a legrövidebb ablak adódik. | 2 | Magyarázat | ✅ kész |
| 37 | [Munka](<37. Munka **/>) | Kétmutatós módszer | Kétmutatós technika: nemnegatív jövedelmek miatt a bal határ csak előre léphet. | 2 | Bevezetés | 🟡 nincs minta |
| 38 | [Négyzet](<38. Négyzet **/>) | Geometria: négyzet ponthalmazban | Rögzített bal alsó csúcsból kiindulva a sorbeli és oszlopbeli távolságlisták metszete adja a négyzetet. | 2 | Mélyebb megértés | ✅ kész |
| 39 | [Nyaklánc](<39. Nyaklánc */>) | Ciklikus tömb, súlyozott összeg | Vágás léptetésekor a súlyok csak 1-gyel változnak két félsorozaton, így az összérték O(1)-gyel frissíthető. | 1 | Magyarázat | ✅ kész |
| 40 | [Nyelvi teszt](<40. Nyelvi teszt */>) | Mintaillesztés, rekurzív elemzés | A kulcsot fává bontjuk, és a megoldás illeszkedését pozíciók halmazával ellenőrizzük. | 1 | Magyarázat | ✅ kész |
| 41 | [Puffer](<41. Puffer **/>) | Szimuláció, prioritási sor | Érkezési sorrendben, minimum-kupacban tárolt várakozó csomagokkal szimuláljuk a puffert. | 2 | Magyarázat | ✅ kész |
| 42 | [Repterek](<42. Repterek ***/>) | Gráf: BFS, negyedsíkok | Szélességi bejárás a (0,0) pontból, a negyedsíkokra szegmensfával, törölt pontokkal. | 3 | Mélyebb megértés | ✅ kész |
| 43 | [Sokszög területe](<43. Sokszög területe **/>) | Geometria: Pick-tétel | Pick-tétel: a területet cipőformulával, a határpontokat élenkénti gcd-vel számoljuk. | 2 | Magyarázat | ✅ kész |
| 44 | [Szálloda](<44. Szálloda */>) | Feltételes keresés | Kérdésenként végigszűrjük a személyeket, majd a legfiatalabbat vagy legidősebbet választjuk. | 1 | Bevezetés | ✅ kész |
| 45 | [Szójáték](<45. Szójáték **/>) | Részsorozat: legrövidebb ablak | Részsorozat-illesztés DP-vel: minden végponthoz a legkésőbbi kezdőindexet követjük. | 2 | Magyarázat | ✅ kész |
| 46 | [Téglalap](<46. Téglalap **/>) | Geometria: üres téglalap | Oldalpont-típusok szerinti esetszétválasztás, rekordlépcsők, prefix-minimum és bináris keresés. | 2 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 47 | [Töréspróba](<47. Töréspróba **/>) | Rekurzió: binomiális összeg | Binomiális összeg Σ C(t,i) ≥ H, a legkisebb t bináris kereséssel. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 48 | [Tükörszó](<48. Tükörszó */>) | Szövegfeldolgozás: tükörszó | Balról jobbra leghosszabb betűbontás, majd a betűk fordított sorrendű kiírása. | 1 | Magyarázat | ✅ kész |
| 49 | [Üvegválogató robot](<49. Üvegválogató robot */>) | Szélsőérték: három különböző láda | Mindhárom fajtára a három legnagyobb láda, 27 kombináció kipróbálása. | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 50 | [Vitorlás](<50. Vitorlás */>) | Ablak, legrövidebb szakasz | Csúszó ablak a megfelelő napok sorozatán: K egymás utáni megfelelő nap legkisebb hossza. | 1 | Bevezetés | ✅ kész |
| 51 | [Wagons](<51. Wagons */>) | Verem, szimuláció | Háromnapos láncképlet (három első elakadás), korlátos keresőfa a beállításokra, bitkészletek. | 1 | Mélyebb megértés | 🟡 nincs minta |
| 52 | [Ütemezés](<52. Ütemezés/>) | Ütemezés: Pareto-állapotok | Pareto-optimális (idő, haszon) állapotok határidő szerinti bővítése, a kiválasztott munkák 64 bites maszkban. | 3 | Magyarázat | ✅ kész |
| 53 | [Ládapakolás](<53. Ládapakolás/>) | DP: két nyitott láda | Két nyitott láda (terhelés, másik terhelés) állapotai költség szerint Pareto-tárolva; O(N·L) tömbös DP. | 4 | Magyarázat | ✅ kész |
