# Geometriai algoritmusok – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 48 feladat · ✅ kész 28 · ❌ hibás 0 · 🟡 kézi 17 · 🟡 nincs minta/speciális 3 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Árnyék](<1. Árnyék **/>) | Geometria: sweep, prefixmaximum | Fény irányában bejárva a g = h - k·x értékek prefixmaximumához hasonlítjuk a szakaszokat. | 2 | Magyarázat | ✅ kész |
| 2 | [Autópálya](<2. Autópálya ***/>) | Geometria: konvex burok | A pontok burkának határán egymás melletti, különböző színű pontpár adja az egyenest | 3 | Magyarázat | ✅ kész |
| 3 | [Bekerítő háromszög](<3. Bekerítő háromszög **/>) | Szögrendezés, pont a háromszögben | A-ból és B-ből mért szögek szerinti rendezés, minimális pontok prefix-minimummal, legkisebb sorszámú jó pont. | 2 | Magyarázat | ✅ kész |
| 4 | [Csomópontok](<4. Csomópontok **/>) | Geometria: konvex burok | Két oldali konvex burok láncai jelölt élek, mohó intervallumlefedéssel kiválasztva. | 2 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 5 | [Épület](<5. Épület */>) | Téglalap-unió, lyukak | Sávonkénti söprés, megmaradó üres futamok DSU-val, kerület és terület összegzés | 1 | Mélyebb megértés | 🟡 nincs minta |
| 6 | [Épület kerülete](<6. Épület kerülete ***/>) | Sweep line, szegmentfa | Vízszintes és függőleges élek külön söprése, szegmensfa a lefedett szakaszok számára | 3 | Mélyebb megértés | ✅ kész |
| 7 | [Fák kivágása](<7. Fák kivágása **/>) | Pont poligonban | Ray casting (sugármetszés) egyszerű ortogonális poligonra | 2 | Magyarázat | ✅ kész |
| 8 | [Futárok](<8. Futárok */>) | Lineáris mozgás, találkozás | Pozíciókülönbség lineáris: előjelváltás vagy nulla az átfedő időintervallum végpontjain | 1 | Magyarázat | ✅ kész |
| 9 | [Háromszög](<9. Háromszög **/>) | Üres háromszög, q-pont | Séta az oq szakasz mentén üres háromszögeken, minimális beírt szögű csúcs választásával | 2 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 10 | [Háromszög kerítés](<10. Háromszög kerítés ***/>) | Geometria: dominanciaszámlálás | Szögek szerinti 2D dominanciaszámlálás Fenwick-fával, a csemetét tartalmazó háromszögekre. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 11 | [Házak](<11. Házak **/>) | Geometria: sugarak tengelymetszete | Balról jobbra haladva a jobb felső sarkok tengelymetszeteinek prefixmaximuma, egész számokkal összevetve. | 2 | Magyarázat | ✅ kész |
| 12 | [Hegy](<12. Hegy ***/>) | Geometria: láthatósági gráf | Láthatósági gráf BFS-e két szélső csúcs követésével, látótávolságok konvex burok érintőjével. | 3 | Mélyebb megértés | ✅ kész |
| 13 | [Kerítés](<13. Kerítés ***/>) | Geometria: összefüggő részek | Két DSU a H feletti és alatti határláncokra, a metszéspontok párosítása x szerint. | 3 | Mélyebb megértés | ✅ kész |
| 14 | [Lámpák](<14. Lámpák **/>) | Geometria: látóvonal, intervallumszúrás | Házanként a megvilágító lámpák intervalluma (érintő a konvex burokhoz), majd mohó szúrás. | 2 | Mélyebb megértés | ✅ kész |
| 15 | [Lefedő egyenesek](<15. Lefedő egyenesek **/>) | Geometria: egyenesek lefedése | Az első 4 pont 6 párja egyenesként, a maradék pontokra 2 egyenes ellenőrzése | 2 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 16 | [Négyszög alakú terület](<16. Négyszög alakú terület **/>) | Geometria: üres négyszög | Háromszögelés (x,y) söpréssel; cserélhető él két háromszöge üres konvex négyszöget ad. | 2 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 17 | [Park](<17. Park */>) | Geometria: háromszögelés | Teljes háromszögelés építése a burok átlóival és a belső pontok egyenkénti beszúrásával | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 18 | [Poligon](<18. Poligon **/>) | Geometria: konvex burok | A pontok konvex burkának irányított élei, amelyeken nincs más pont | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 19 | [Poligonok metszése](<19. Poligonok metszése ***/>) | Geometria: konvex sokszögek | Két lánc éleinek összefésülése x szerint, az átfedő élpárok metszésvizsgálatával | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 20 | [Szoborpark](<20. Szoborpark ***/>) | Szögtartomány, különbségtömb | Bal alsó sarok paraméterezése, szögtartományok különbségtömbbel, prefix-összeggel. | 3 | Mélyebb megértés | ✅ kész |
| 21 | [Telek](<21. Telek */>) | Szakasz és háromszög metszése | Szakasz és háromszög metszete egész számokkal: t-intervallum és előjelek alapján. | 1 | Magyarázat | ✅ kész |
| 22 | [Terv](<22. Terv **/>) | Intervallum-kiválasztás | Szögintervallumok, mohó intervallum-kiválasztás a jobb végpont szerint. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 23 | [Vágás](<23. Vágás */>) | Sokszög és egyenes metszése | Az AB szakasz és a sokszög éleinek metszéspontjait számoljuk, paritással. | 1 | Magyarázat | ✅ kész |
| 24 | [Zárt poligon készítése](<24. Zárt poligon készítése **/>) | Egyszerű poligon építése | Az LR egyenes két oldalán lévő láncok összefűzése: x-monoton, nem metsző poligon. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 25 | [Épület belső udvarai](<25. Épület belső udvarai ***/>) | Sweep és unió-keresés | Sweep sávonként üres futásokkal, szakasz-fával, csempékhez DSU-val a kerület és terület összegzésére. | 3 | Mélyebb megértés | 🟡 nincs minta |
| 26 | [Facsemeték bekerítése](<26. Facsemeték bekerítése ***/>) | Háromszögelés, maximális lefedés | Randomizált inkrementális háromszögelés legyezővel és DAG-pontlokalizációval; eredmény 2N−h−2. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 27 | [Háromszög](<27. Háromszög **/>) | Üres háromszög, szögrendezés | Legalsó pontból irányonként a legközelebbi pont; szomszédos irányok üres háromszöget alkotnak. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 28 | [Oszlopok](<28. Oszlopok */>) | Irányok, gcd egyszerűsítés | Az origóból nézve az egyszerűsített (gcd-vel osztott) irányok számának megszámlálása halmazzal. | 1 | Bevezetés | ✅ kész |
| 29 | [Épület elhagyása](<29. Épület elhagyása ***/>) | Gráf: BFS, téglalapok | Falak mentén átfedés-párosítás, fedett hossz alapján kijáratos szobák, BFS a legközelebbi kijáratig. | 3 | Magyarázat | ✅ kész |
| 30 | [Elválasztó egyenes](<30. Elválasztó egyenes ****/>) | Minkowski-összeg, szeparáció | A fehér és fekete burok különbségének (Minkowski-összeg) burka egész számokkal; origó-helyzet alapján normálvektor-jelöltek. | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 31 | [Pontok poligonban](<31. Pontok poligonban ****/>) | Geometria: pont a poligonban | Sugaras (ray casting) pont-poligon teszt egész aritmetikával, kérdésenként O(N·K) | 4 | Magyarázat | ✅ kész |
| 32 | [Négyzetek](<32. Négyzetek ***/>) | Geometria: látható négyzetek | Szögsöprés: a csúcsok szögei közti tartományok felezőpontjaiban a legközelebbi négyzet látszik | 3 | Magyarázat | ✅ kész |
| 33 | [Repterek](<33. Repterek ***/>) | Gráf: BFS, szegmensfa | BFS a nem látott pontokon, szegmensfával a két negyedsík kereséséhez. | 3 | Magyarázat | ✅ kész |
| 33 | [Repterek](<33. Repterek ****/>) | Gráf: BFS, kd-fa | BFS a (0,0) reptértől; a szomszédok NE/SW negyedsíkból gyűjtése kd-fából törléssel | 4 | Mélyebb megértés | 🟡 nincs minta |
| 34 | [Épület](<34. Épület ***/>) | Geometria: unió kerülete | Az unió kerülete: x- és y-irányú sweep, szakaszfa a lefedett szakaszok számával | 3 | Mélyebb megértés | ✅ kész |
| 35 | [Autópálya](<35. Autópálya ****/>) | Geometria: konvex burok | Konvex burok határán színváltó szomszédos pár adja az egyenest | 4 | Magyarázat | 🟡 kézi ellenőrzés |
| 36 | [Poligon](<36. Poligon/>) | Geometria: poligonút | Legyezős szögrendezés félsíkonként, az elfogyasztott oldal leválasztásával és visszalépéssel | 5 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 37 | [Négyszög](<37. Négyszög/>) | Geometria: konvex négyszög | Kis N-re négyesek, nagy N-re egy szinte egyenes előjel- és arányvizsgálata | 4 | Mélyebb megértés | ✅ kész |
| 38 | [Szuperhuszár](<38. Szuperhuszár/>) | Geometria: szögrendezés | Lépésvektorok kúpjának ellenőrzése: 2D-ben a szögrések legyenek mind 180 foknál kisebbek | 3 | Mélyebb megértés | ✅ kész |
| 39 | [Facsemete](<39. Facsemete/>) | Geometria: üres háromszög | Szögrendezés A körül, minimális üres (jobb, bal) fapár keresése szuffix-minimummal | 4 | Mélyebb megértés | ✅ kész |
| 40 | [Konvex négyszög](<40. Konvex négyszög/>) | Geometria: üres négyszög | Háromszögelés (x,y) söpréssel; két háromszögből álló cserélhető él üres konvex négyszöget ad. | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 41 | [Bekerítés konvex négyszöggel](<41. Bekerítés konvex négyszöggel/>) | Geometria: bekerítés | A célpontot tartalmazó üres háromszög kiegészítése a legközelebbi éltartománybeli ponttal konvex négyszöggé. | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 42 | [Szurikáta](<42. Szurikáta ****/>) | Láthatóság, bináris keresés | Eredeti látható lánc, lekérdezésenként bináris keresés a módosított indexek között. | 4 | Mélyebb megértés | ✅ kész |
| 43 | [Szakaszok](<43. Szakaszok/>) | Söprővonal, Fenwick-fa | X szerinti söpréssel, Fenwick-fával számoljuk a metsző vízszintes szakaszokat. | 3 | Magyarázat | ✅ kész |
| 44 | [Házak](<44. Házak/>) | Szögsöprés, láthatóság | Szögsöprés az origó körül, az alsó és bal élek legközelebbi metszésének nyilvántartása eseményekkel. | 4 | Mélyebb megértés | ✅ kész |
| 45 | [Várfalak száma](<45. Várfalak száma/>) | Unió-find, komponensek | Közös végpontú falak DSU-val való egyesítése, a komponensek számolása. | 3 | Magyarázat | ✅ kész |
| 46 | [Várfalak hossza](<46. Várfalak hossza/>) | Unió-find, shoelace-terület | Közös végpontú falak DSU-val csoportosítása; komponensenként hossz összeg, terület a rendezéshez. | 3 | Magyarázat | ✅ kész |
| 47 | [Úthálózatbővítés](<47. Úthálózatbővítés/>) | Láthatóság, szögsöprés | Szögsöprés A körül: irányonként a legközelebbi csomópont és a sugár legközelebbi útszakasza. | 5 | Mélyebb megértés | ✅ kész |
