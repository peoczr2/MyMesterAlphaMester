# Gráfok, mélységi bejárás – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 81 feladat · ✅ kész 22 · ❌ hibás 0 · 🟡 kézi 46 · 🟡 nincs minta/speciális 13 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Ádám és Éva kirándul](<1. Ádám és Éva kirándul/>) | Folyam: csúcsdiszjunkt utak | Csúcskapacitásos maximális folyam: két csúcsdiszjunkt út Évából Ádámig és a célig. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 2 | [Biztonsági szolgálat](<2. Biztonsági szolgálat */>) | Gráf: kétszeresen összefüggő komponensek | Kétszeresen összefüggő blokkok (Tarjan) és az A–B út a blokk-vágópont fán. | 1 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 3 | [Bűnöző elfogása](<3. Bűnöző elfogása */>) | Gráf: mélységi bejárás, irányítás | Mélységi bejárás: minden utca oda-vissza, az ősökhöz vezető utcákat az ős oldaláról járja be. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 4 | [Csomópontok körökben](<4. Csomópontok körökben **/>) | Gráf: hidak, élösszefüggőség | Hidak keresése, komponensfa, levelek DFS-sorrendben párosítva a minimális bővítéshez. | 2 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 5 | [Duplán elérhető pontok](<5. Duplán elérhető pontok */>) | Gráf: hidak, kétélű összefüggőség | Tarjan-féle kétélű-összefüggő komponensek egy mélységi bejárással; a központ komponense a válasz. | 1 | Magyarázat | ✅ kész |
| 6 | [Elárasztás](<6. Elárasztás */>) | Min-max bejárás, vízgyűjtés | Min-max Dijkstra a szegélyről, majd BFS a forrásból: a vízszint min(lefolyási szint, forrásszint). | 1 | Mélyebb megértés | 🟡 nincs minta |
| 7 | [Elfogó](<7. Elfogó */>) | Gráfok: körök, zsákutcák | Zsákutca- és körellenőrzés minden csúcs kihagyásával, topologikus rendezéssel | 1 | Magyarázat | ✅ kész |
| 8 | [Erősen összefüggővé alakítás](<8. Erősen összefüggővé alakítás ***/>) | Gráf: erős komponensek | Erős komponensek Kosaraju-val; a nyelő- és a forráskomponens közé húzott él zárja a kört. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 9 | [Futár mindenhova](<9. Futár mindenhova */>) | Gráf: mélységi bejárás | Mélységi fa visszaugró élekkel, bejárás visszalépésekkel és kijárat-számítással | 1 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 10 | [Hálózat](<10. Hálózat */>) | Gráf: elérhetőség | Két BFS K-ból: az élek irányában és fordítva; a különbségük a válasz. | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 11 | [Hálózat kitüntetett csomóponttal](<11. Hálózat kitüntetett csomóponttal **/>) | Gráf: távolság, elérhetőség | BFS K-ból az élek mentén (legfeljebb T+1 élig) és fordítva; a két halmaz metszete. | 2 | Magyarázat | 🟡 nincs minta |
| 12 | [Hálózat hiányzó vonal](<12. Hálózat hiányzó vonal **/>) | Gráf: erősen összefüggő komponensek | Erősen összefüggő komponensek (Tarjan): a komponensek láncának kezdő és záró csúcsa adja a P,Q párt. | 2 | Mélyebb megértés | 🟡 nincs minta |
| 13 | [Hálózat kezdőpont](<13. Hálózat kezdőpont ***/>) | Gráf: erős komponensek | Erősen összefüggő komponensek (Tarjan), forráskomponensek száma, k−1 új él láncban. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 14 | [Hírek](<14. Hírek ***/>) | Gráf: elérhetőség, bitsorozat | Erős komponensek, komponensenkénti elérési bitsorozatok, források párjainak uniója. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 15 | [Hírlánc](<15. Hírlánc ***/>) | Gráf: erős komponensek | Erős komponensek, a befutó élek nélküli komponensek száma; mindegyikbe egy tanuló. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 16 | [Járások](<16. Járások */>) | Gráf: szélességi bejárás | Központonként szélességi bejárás (BFS), minden település a legközelebbi központhoz kerül. | 1 | Bevezetés | 🟡 nincs minta |
| 17 | [Kannák](<17. Kannák */>) | Gráf: állapottér-keresés | Állapottér-bejárás (BFS) a három kanna tartalmán; a negyedik kanna a maradékot tartalmazza. | 1 | Magyarázat | 🟡 nincs minta |
| 18 | [Képtár](<18. Képtár **/>) | Gráf: mélységi bejárás | Mélységi bejárás a szomszédok óramutató szerinti sorrendjében, a szülő után kezdve. | 2 | Magyarázat | 🟡 nincs minta |
| 19 | [Két út](<19. Két út ***/>) | Folyam: csúcsdiszjunkt utak | Csúcsszétbontásos folyam: két csúcsdiszjunkt út 1-ből U-ba és V-be. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 20 | [Két út hálózatban](<20. Két út hálózatban ***/>) | Gráf: csúcsdiszjunkt utak | Csúcsok felbontása, kétegységnyi folyam két BFS-növeléssel | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 21 | [Koncert](<21. Koncert ***/>) | Gráf: feszítőfa | Komponensenként feszítőfa, a fán kívüli él a gyökérhez, a többi csúcs a szülőélét kapja | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 22 | [Körben lévő pontok](<22. Körben lévő pontok **/>) | Gráf: erős komponensek | Tarjan-algoritmus: erősen összefüggő komponensek, hurokéllel kiegészítve | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 23 | [Körön kívüli pontok](<23. Körön kívüli pontok **/>) | Gráf: hidak | Mélységi bejárás, hidak keresése tin és low értékekkel | 2 | Magyarázat | ✅ kész |
| 24 | [Körséta](<24. Körséta **/>) | Gráf: Euler-körút | Egyetlen-úti fa, visszaélek egyszeri használata, fa-élek számolt ismétlésével Euler-körút. | 2 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 25 | [Központ kialakítás](<25. Központ kialakítás ***/>) | Gráf: erős komponensek | Kosaraju-féle erős komponensek; a bejövő él nélküli komponensekbe egy-egy új él a központból. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 26 | [Központi raktár](<26. Központi raktár **/>) | Gráf: erős komponensek | A régi raktár törlése, erős komponensek, forrás-komponensek száma mínusz egy új út. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 27 | [Kritikus csomópontok](<27. Kritikus csomópontok ***/>) | Gráf: artikulációs pont | Mélységi bejárás low-értékekkel, az A-B fa-úton a kritikus csúcsok gyűjtése. | 3 | Mélyebb megértés | 🟡 nincs minta |
| 28 | [Kritikus ellenőrző pontok](<28. Kritikus ellenőrző pontok **/>) | Gráf: dominátorok | Dominátorfa (Lengauer–Tarjan): B dominátorai, azaz a B-ből A-ig vezető idom-lánc csúcsai. | 2 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 29 | [Kritikus pontok](<29. Kritikus pontok ***/>) | Gráf: artikulációs pontok | A-ból mélységi bejárás, low-értékek; a B-ig vezető fa-úton v kritikus, ha low[c] ≥ disc[v]. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 30 | [Ládák sorbarendezése](<30. Ládák sorbarendezése **/>) | Gráf: Euler-kör, rendezés | Rosszul álló ládák élek; komponensenként Euler-kör, minden k hosszú körre k+1 mozgatás. | 2 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 31 | [Legkevesebb végpont](<31. Legkevesebb végpont **/>) | Gráf: erősen összefüggő komponensek | Erősen összefüggő komponensek (Tarjan), majd a nyelő komponensekből egy-egy pont. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 32 | [Biztonság](<32. Biztonság ***/>) | Gráf: blokkok és vágópontok | Blokkok és vágópontok Hopcroft–Tarjan-bejárással; az A–B út blokkjainak pontjai, A és B nélkül. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 33 | [Mindenhova legyen út](<33. Mindenhova legyen út ***/>) | Gráf: erősen összefüggő komponensek | Forrás komponensek száma eggyel kevesebb új él, láncba fűzve egy r pontból. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 34 | [Mindenhova vezessen út](<34. Mindenhova vezessen út **/>) | Gráf: erősen összefüggő komponensek | Nyelő komponensek száma eggyel kevesebb új él, láncba fűzve egy R pont felé. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 35 | [Négykannás öntögetés](<35. Négykannás öntögetés */>) | Gráf: állapottér-keresés | Állapottér szélességi bejárása a négy kanna tartalmával, a negyedik kanna értékeinek gyűjtése. | 1 | Magyarázat | 🟡 nincs minta |
| 36 | [Nincs odaút](<36. Nincs odaút **/>) | Gráf: elérhetőség | Két bejárás P-ből: élek irányában és fordítva; a halmazok különbsége a válasz. | 2 | Bevezetés | 🟡 kézi ellenőrzés |
| 37 | [Nincs visszaút](<37. Nincs visszaút **/>) | Gráf: elérhetőség | Két bejárás P-ből, élek irányában és fordítva; az elsőből kivonjuk a másodikat. | 2 | Bevezetés | 🟡 kézi ellenőrzés |
| 38 | [Oda-vissza független út megadása](<38. Oda-vissza független út megadása ***/>) | Folyam: csúcsdiszjunkt utak | Csúcsdiszjunkt utak: maximális folyam csúcsok szétbontásával, két szélességi augmentálással. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 39 | [Oda-vissza független utak](<39. Oda-vissza független utak ***/>) | Gráf: blokkok, kétszeres összefüggőség | Tarjan-féle blokkbontás élveremmel: a gyökérnél záródó, legalább kétélű blokkok csúcsai. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 40 | [Összefüggő egyirányú hálózat](<40. Összefüggő egyirányú hálózat ***/>) | Gráf: erős összefüggőség | Erős komponensek Tarjan-algoritmussal, befok-kifok alapján a forrás és a nyelő összekötése. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 41 | [Park](<41. Park **/>) | Gráf: mélységi bejárás | Bármely feszítőfa Euler-bejárása: minden csúcs legfeljebb gyerekszám+1-szer szerepel. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 42 | [Raktár](<42. Raktár ***/>) | Gráf: hidak, mélységi bejárás | Mélységi bejárás, low-link hidak: jó csúcs, ha út minden éle híd | 3 | Magyarázat | 🟡 nincs minta |
| 43 | [Tájékozódási verseny](<43. Tájékozódási verseny **/>) | Gráf: kikerülhetetlen pontok | Csúcsonkénti kihagyásos bejárás: elérhető-e a cél a csúcs nélkül | 2 | Bevezetés | 🟡 nincs minta |
| 44 | [Út legfeljebb egy kritikus szakasszal](<44. Út legfeljebb egy kritikus szakasszal */>) | Gráf: 0-1 BFS | 0-1 BFS: minden csúcsig a legkevesebb kritikus él, jó ha legfeljebb egy | 1 | Magyarázat | 🟡 nincs minta |
| 45 | [Út mindenhova két pontból](<45. Út mindenhova két pontból ***/>) | Gráf: erősen összefüggő komponensek | Erősen összefüggő komponensek, minden forrásból egy kezdőpont | 3 | Mélyebb megértés | 🟡 nincs minta |
| 46 | [Utcák egyirányúsítása](<46. Utcák egyirányúsítása ***/>) | Gráf: hidak és irányítás | Hidak keresése (Tarjan low-link) mélységi bejárással, a fa- és visszaélek irányításával. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 47 | [Utcaseprő](<47. Utcaseprő */>) | Gráf: Euler-kör | Euler-kör az utcák két irányú élekre bontott gráfjában, Hierholzer-algoritmussal. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 48 | [Ültetés](<48. Ültetés ***/>) | Dinamikus programozás gráfon | Lineáris erdő legnagyobb súlyú kiválasztása a kérés-gráfon: fa-DP és körös DP. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 50 | [Ádám és Éva közös kirándulása](<50. Ádám és Éva közös kirándulása ***/>) | Folyam: csúcsdiszjunkt utak | Csúcsszétbontásos maximális folyam: két csúcsdiszjunkt út Évából Ádámig és a célig. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 51 | [Kritikus összekötések](<51. Kritikus összekötések ****/>) | Gráf: hidak, fa átmérője | Hidak és kétélű komponensek Tarjan-algoritmussal; a komponensfa átmérőjének két végpontja a válasz. | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 52 | [Közösségi háló](<52. Közösségi háló ***/>) | Gráf: erős komponensek, bitsorozat | Erős komponensek, komponensenkénti elérési bitsorozat VAGY-egyesítéssel; a legkisebb számú elérés keresése. | 3 | Mélyebb megértés | ✅ kész |
| 53 | [Két hivatal](<53. Két hivatal ***/>) | Gráf: szélességi bejárás | Szélességi bejárás szintjeinek paritása adja az A/B jelölést; izolált település esetén NEM. | 3 | Magyarázat | 🟡 nincs minta |
| 54 | [Hálózat](<54. Hálózat ***/>) | Gráf: hídélek | Hídélek keresése Tarjan-féle low-értékkel; R-ből bejárásban minden hídlánc végéhez egy visszazáró él. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 55 | [Legyen minden pár között út](<55. Legyen minden pár között út ****/>) | Gráf: erős összefüggőség | Erősen összefüggő komponensek; forrás–nyelő párok összekötése, elérési halmazok bitsorozatban. | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 56 | [Biztonság](<56. Biztonság ***/>) | Gráf: kétszeresen összefüggő | Az A–B virtuális élt tartalmazó kétszeresen összefüggő komponens csúcsai (élveremmel, Tarjan). | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 58 | [Hálózat felezés](<58. Hálózat felezés/>) | Fa DP, részfa-vágás | Gyökerezett fa DP: a legfelső csúcsonként, méretenként a minimális határ-élszám, zsákprobléma-szerű összevonással. | 4 | Mélyebb megértés | ✅ kész |
| 59 | [Kémek](<59. Kémek/>) | Artikulációs pontok, DFS | DFS low-értékekkel: a csúcs törlése utáni komponensszámot számoljuk, az artikulációs pontokat keressük. | 3 | Magyarázat | ✅ kész |
| 60 | [Séta](<60. Séta/>) | Gráf: erősen összefüggő komponensek | Erősen összefüggő komponensek (Tarjan) és DP a komponensek DAG-ján | 4 | Mélyebb megértés | ✅ kész |
| 61 | [Sípálya](<61. Sípálya/>) | Gráf: Dilworth-tétel | Dilworth-tétel: antilánc a síkbeli rendben, felezőpontokkal, leghosszabb csökkenő részsorozat | 3 | Mélyebb megértés | ✅ kész |
| 62 | [Pálya ellenőrzés](<62. Pálya ellenőrzés/>) | Gráf: Dilworth-tétel | Dilworth-tétel: antilánc a síkbeli elérhetőségi rendben, két mélységi bejárással, leghosszabb csökkenő részsorozat | 4 | Mélyebb megértés | ✅ kész |
| 63 | [Programgráf](<63. Programgráf/>) | Gráf: mélységi bejárás | Mélységi bejárás: visszamutató élek és kétkimenetű csúcsok száma | 2 | Magyarázat | ✅ kész |
| 64 | [Karavánok](<64. Karavánok/>) | Gráf: mélységi bejárás | Mélységi bejárás utolsó gyökere mint jelölt, majd BFS-ek a gráfon és a fordított élekkel. | 3 | Magyarázat | ✅ kész |
| 65 | [Hercegek házassága](<65. Hercegek házassága/>) | Gráf: erősen összefüggő komponensek | Tarjan-algoritmus a herceg-gráf erősen összefüggő komponenseire; kedvelt pár akkor marad, ha egy komponensben van. | 4 | Mélyebb megértés | ✅ kész |
| 66 | [Úttisztítás](<66. Úttisztítás/>) | Gráf: összeszámlálás | Fa: részfa-méretekkel súlyozott élösszeg; körös: levéllehámozás és a kör két iránya. | 3 | Mélyebb megértés | ✅ kész |
| 67 | [Keveset dolgozó vállalkozó](<67. Keveset dolgozó vállalkozó/>) | Dinamikus programozás: hátizsák | Dinamikus programozás a bevételre levágva, minimális munkaidővel; visszakövetéssel a munkák. | 2 | Bevezetés | ✅ kész |
| 68 | [Hilbert-görbe](<68. Hilbert-görbe/>) | Rendezés: Hilbert-görbe | Hilbert-sorszám bitenkénti kiszámolása, majd rendezés a sorszám szerint | 3 | Magyarázat | ✅ kész |
| 70 | [Kontroll](<70. Kontroll ****/>) | Gráfok: maximális folyam | Minimális csúcs-vágás maximális folyammal, csúcsbontással (Dinic) | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 71 | [Erőművek](<71. Erőművek ****/>) | Gráf: hidak, részfák | Hidak keresése, hídfa részfa-összegei, merge sort fával legközelebbi párkeresés | 4 | Mélyebb megértés | ✅ kész |
| 72 | [Útépítés](<72. Útépítés ****/>) | Gráf: párosítás | Rácspontok páros gráfja, maximális párosítás Hopcroft–Karp-pal | 4 | Magyarázat | 🟡 kézi ellenőrzés |
| 73 | [Kaktuszgráf](<73. Kaktuszgráf **/>) | Gráf: mélységi bejárás | Mélységi bejárás, a visszaélek által lezárt körök hosszának maximuma | 2 | Magyarázat | ✅ kész |
| 74 | [Elfogás](<74. Elfogás ****/>) | Gráf: blokkok, vágópontok | Blokkfelbontás (Tarjan), U-ból mélységi fa, V-t tartalmazó blokkok alatti csúcsok | 4 | Mélyebb megértés | ✅ kész |
| 75 | [Egyirányú egyensúly](<75. Egyirányú egyensúly ***/>) | Gráf: Euler-séta, irányítás | Fiktív csúcs a páratlan fokúakhoz, majd zárt Euler-sétákkal irányítás. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 76 | [Játék a síkon](<76. Játék a síkon ****/>) | Játékelmélet: párosítás | Kuhn-féle maximális párosítás, majd BFS a nem fedett csúcsokból páros hosszú váltakozó úton. | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 77 | [Turista járatok](<77. Turista járatok ****/>) | Gráf: blokkok, összefüggőség | Blokkbontás (Tarjan élverem) és a DFS-fán lefelé terjesztett látványosság-jelző. | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 78 | [Multiplikátoros telebabrátor](<78. Multiplikátoros telebabrátor ****/>) | Bináris trie: XOR-maximum | Gyökértől vett XOR-értékek, és bináris trie a legnagyobb XOR-ú pár keresésére. | 4 | Magyarázat | 🟡 kézi ellenőrzés |
| 79 | [Logisztikai központ](<79. Logisztikai központ/>) | Gráf: fa, átmérő | Átmérő két végpontjából mért távolságok; excentricitás = max(d_a, d_b), minimum keresése. | 3 | Magyarázat | ✅ kész |
| 80 | [Hálózatjavítás](<80. Hálózatjavítás/>) | Gráf: körök, DFS | Egyetlen erős komponens; DFS-visszaél vagy fabeli él, topologikus rendezés, vágásszámlálás. | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 81 | [Városok](<81. Városok/>) | Párosítás, élefedés | Minimális élefedés sor–oszlop páros gráfban: csúcsok száma − maximális párosítás. | 4 | Mélyebb megértés | ✅ kész |
| 82 | [Hegyi levegő](<82. Hegyi levegő/>) | Gráf: minimax út | Kruskal-rekonstrukciós fa és LCA a minimax útra | 4 | Magyarázat | ✅ kész |
| 83 | [Dinók](<83. Dinók/>) | Gráf: erős összefüggőség | Különbségi egyenlőtlenségek gráfja, erős komponensek és potenciálok | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 84 | [Testvérvárosok](<84. Testvérvárosok/>) | Fa: centroid-felbontás | Centroid-felbontás, maradékok számlálása modulo K | 4 | Mélyebb megértés | ✅ kész |
