# Programozási tételek: megszámolás – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 99 feladat · ✅ kész 96 · ❌ hibás 0 · 🟡 kézi 3 · 🟡 nincs minta/speciális 0 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Állatértékesítés](<1. Állatértékesítés */>) | Megszámolás | Kumulált bevétel növekedéseinek számlálása, az előző érték kezdetben 0. | 1 | Bevezetés | ✅ kész |
| 2 | [Balaton befagyott napjainak száma](<2. Balaton befagyott napjainak száma */>) | Megszámolás: feltétel | Egyetlen végigolvasás, a pozitív vastagságú mérések számlálása | 1 | Bevezetés | ✅ kész |
| 3 | [Bináris alak 1-esei](<3. Bináris alak 1-esei */>) | Számjegyek számlálása | Maradékos osztással (2-vel) kinyert számjegyek 1-eseinek számlálása. | 1 | Bevezetés | ✅ kész |
| 4 | [Délben bankban lévő ügyfelek száma](<4. Délben bankban lévő ügyfelek száma **/>) | Megszámolás: halmaz | Időrendi szimuláció halmazzal: belépés beszúr, kilépés töröl, X:00-ig | 2 | Magyarázat | ✅ kész |
| 5 | [Esős napok száma](<5. Esős napok száma */>) | Feltételes számlálás | Lineáris bejárás: a pozitív csapadékmérések napjainak számlálása. | 1 | Bevezetés | ✅ kész |
| 6 | [Fagyos napok száma](<6. Fagyos napok száma */>) | Feltételes számlálás | Lineáris bejárás: a 0 foknál hidegebb mérések számlálása. | 1 | Bevezetés | ✅ kész |
| 7 | [Fagyos napok száma az előrejelzésben](<7. Fagyos napok száma az előrejelzésben */>) | Megszámolás | Egyszeri bejárás, a napi legkisebb hőmérséklet 0-nál kisebb voltának számlálása. | 1 | Bevezetés | ✅ kész |
| 8 | [Futamok száma](<8. Futamok száma **/>) | Megszámolás: futamok | Egy bejárás: az előjelváltásoknál új futam kezdődik, a határelem mindkettőhöz tartozik. | 2 | Magyarázat | ✅ kész |
| 9 | [Idős és alacsony fizetésűek száma](<9. Idős és alacsony fizetésűek száma/>) | Feltételes számlálás | Egyetlen bejárás, két feltétel együttes teljesülésének számlálása. | 1 | Bevezetés | ✅ kész |
| 10 | [Idősebb emberek száma](<10. Idősebb emberek száma */>) | Megszámolás | Életkor számítása a születésnap figyelembevételével, majd feltételes számlálás. | 1 | Magyarázat | ✅ kész |
| 11 | [Ismétlődők](<11. Ismétlődők **/>) | Megszámolás | Pozíciónként ellenőrizzük, van-e egyező elem a következő K elemben, és azt számoljuk. | 2 | Bevezetés | ✅ kész |
| 12 | [Járművek száma adott időintervallumban](<12. Járművek száma adott időintervallumban */>) | Megszámolás | Egyetlen menetben számoljuk azokat a megfigyeléseket, amelyek órája X és Y közé esik. | 1 | Bevezetés | ✅ kész |
| 13 | [Javított futóeredmények száma](<13. Javított futóeredmények száma */>) | Megszámolás | Az időeredményt másodpercre váltjuk, és egy menetben számoljuk a javulások számát az előzőhöz képest. | 1 | Magyarázat | ✅ kész |
| 14 | [Jegyek](<14. Jegyek */>) | Megszámolás | Darabszám-tömb: minden jegy értékéhez egy számlálót növelünk egy menetben. | 1 | Bevezetés | ✅ kész |
| 15 | [Jelenlévők](<15. Jelenlévők */>) | Megszámolás | Egy menetben minden vendégre ellenőrizzük, hogy a K. percben jelen van-e, és számoljuk. | 1 | Bevezetés | ✅ kész |
| 16 | [Két évszám közötti események száma](<16. Két évszám közötti események száma **/>) | Megszámolás | Egy menetben beolvassuk az eseményeket, és számoljuk azokat, amelyek évszáma a két határ közé esik. | 2 | Bevezetés | ✅ kész |
| 17 | [Műholddal kétszer lefényképezett területek](<17. Műholddal kétszer lefényképezett területek **/>) | Megszámolás: rácsfedés | Kétdimenziós különbségi tömb és prefixösszeg, a pontosan kétszer fedett cellák számolása | 2 | Magyarázat | ✅ kész |
| 18 | [Kissé szeles napok száma](<18. Kissé szeles napok száma */>) | Megszámolás: feltétel | Egyetlen végigolvasás, a 0-nál nagyobb, M-nél kisebb sebességek számlálása | 1 | Bevezetés | ✅ kész |
| 19 | [Közös territóriummal rendelkező madarak](<19. Közös territóriummal rendelkező madarak **/>) | Megszámolás: tartalmazás | Négyzetek sarokkoordinátáinak összehasonlítása, minden madárra az összes többi madárral | 2 | Bevezetés | ✅ kész |
| 20 | [Kukutyinhoz közelebb lévő települések száma](<20. Kukutyinhoz közelebb lévő települések száma */>) | Megszámolás: feltétel | Egyszeri bejárás, minden sorban a K < P feltétel ellenőrzése és számlálás. | 1 | Bevezetés | ✅ kész |
| 21 | [Lakatlan territóriumok száma](<21. Lakatlan territóriumok száma **/>) | Megszámolás: rácsfedés | Minden rácspont ellenőrzése: fedi-e valamelyik territórium, és a fedetlenek számlálása. | 2 | Magyarázat | ✅ kész |
| 22 | [Leghosszabb növekvő szakaszok száma](<22. Leghosszabb növekvő szakaszok száma */>) | Megszámolás: szakaszok | Balról jobbra haladó bejárás: a legtovább növekvő szakaszokat levágva, legalább kételemű szakaszok számlálása. | 1 | Magyarázat | ✅ kész |
| 23 | [Légszennyezettségmérő javításainak száma](<23. Légszennyezettségmérő javításainak száma */>) | Megszámolás: állapotváltás | Az előző és a mai nap értékét párban nézzük; 0-ról pozitívra váltás a javítás. | 1 | Bevezetés | ✅ kész |
| 24 | [Meleg napok száma](<24. Meleg napok száma */>) | Megszámolás | Egyetlen menetben, beolvasás közben számoljuk a K-nál nagyobb méréseket. | 1 | Bevezetés | ✅ kész |
| 25 | [Múzeum szolgálatában lévő őrök száma napi leosztásban](<25. Múzeum szolgálatában lévő őrök száma napi leosztásban **/>) | Megszámolás, prefixösszeg | Különbségtömb: kezdőnapon +1, a végét követő napon -1, majd prefixösszeg. | 2 | Magyarázat | ✅ kész |
| 26 | [Nagy hőingadozású napok száma](<26. Nagy hőingadozású napok száma */>) | Megszámolás | Naponként a maximum és minimum különbségét vizsgáljuk, és számoljuk a legalább 10 fokosakat. | 1 | Bevezetés | ✅ kész |
| 27 | [Nyelvórán egyesek száma](<27. Nyelvórán egyesek száma */>) | Megszámolás | Beolvasás közben egy számlálóval megszámoljuk az 1-es osztályzatokat. | 1 | Bevezetés | ✅ kész |
| 28 | [Olcsó és egyben nagy lakások száma](<28. Olcsó és egyben nagy lakások száma */>) | Feltételes számlálás | Feltételes számlálás: egy beolvasás, két feltétel együttes teljesülése. | 1 | Bevezetés | ✅ kész |
| 29 | [Órát tartó tanárok száma naponként](<29. Órát tartó tanárok száma naponként **/>) | Megszámolás: egyedi párok | Logikai táblázat (nap, tanár) jelöléssel, majd soronkénti megszámolás. | 2 | Magyarázat | ✅ kész |
| 30 | [Őrzött falak száma](<30. Őrzött falak száma */>) | Szomszédos párok számlálása | Szomszédos elempárok bejárása egy ciklusban, logikai VAGY feltétellel. | 1 | Bevezetés | ✅ kész |
| 31 | [Őrzött szakaszok száma a Kínai Nagy Falon](<31. Őrzött szakaszok száma a Kínai Nagy Falon */>) | Összefüggő szakaszok számlálása | Lineáris bejárás a falakon: az őrzött szakaszok kezdeteinek számlálása. | 1 | Magyarázat | ✅ kész |
| 32 | [Összes játékkonzol száma](<32. Összes játékkonzol száma **/>) | Gyakorisági számlálás | Generációnkénti számláló, majd a 2·db ≥ N feltétel ellenőrzése. | 2 | Magyarázat | ✅ kész |
| 33 | [Összes műholddal lefényképezett terület](<33. Összes műholddal lefényképezett terület **/>) | Téglalapok lefedése | Kétdimenziós differencia-tömb, prefixösszeg és a lefedett rácspontok számlálása. | 2 | Mélyebb megértés | ✅ kész |
| 34 | [Romló légszennyeződési értékek](<34. Romló légszennyeződési értékek */>) | Szomszédos párok számlálása | Szomszédos napok összehasonlítása egy bejárásban, két feltétel ÉS-kapcsolatával. | 1 | Bevezetés | ✅ kész |
| 35 | [Sötétben maradt helyek](<35. Sötétben maradt helyek **/>) | Megszámolás: rács bejelölése | Lámpánként a négyzet bejelölése logikai rácsban, szélnél levágva; utána a jelöletlen mezők számlálása. | 2 | Magyarázat | ✅ kész |
| 36 | [Szabadnapos tanárok száma](<36. Szabadnapos tanárok száma **/>) | Megszámolás: egyedi párok | Logikai táblázat (nap, tanár) jelöléssel, majd napokra bontott megszámolás. | 2 | Magyarázat | ✅ kész |
| 37 | [Számpárok száma](<37. Számpárok száma */>) | Párok számlálása | Páronkénti ellenőrzés két egymásba ágyazott ciklussal, i<j feltétel mellett. | 1 | Bevezetés | ✅ kész |
| 38 | [Szélcsendes napok száma](<38. Szélcsendes napok száma */>) | Feltételes számlálás | Egyetlen végigolvasás, a nulla sebességű napok számlálása. | 1 | Bevezetés | ✅ kész |
| 39 | [Tejárak](<39. Tejárak */>) | Megszámolás | Lineáris bejárás, minden ár összevetése a [P,Q] intervallummal | 1 | Bevezetés | ✅ kész |
| 40 | [Teljes útfelújítás](<40. Teljes útfelújítás **/>) | Megszámolás: tömb jelölés | Logikai tömb jelölése kilométerenként, a jelöletlenek megszámolása | 2 | Bevezetés | ✅ kész |
| 41 | [Tervbe betehető szobák száma](<41. Tervbe betehető szobák száma ***/>) | Megszámolás: rácsos terület | Rács a házról, a szabad területek bal felső mezőinek megszámolása | 3 | Mélyebb megértés | ✅ kész |
| 42 | [Tervbe nem tartozó falszakaszok száma égtájanként](<42. Tervbe nem tartozó falszakaszok száma égtájanként **/>) | Lefedetlen szakaszok számlálása | Oldalankénti különbségtömbös lefedettség, majd a lefedetlen futamok számlálása. | 2 | Mélyebb megértés | ✅ kész |
| 43 | [Több konzolt kiadó gyártó](<43. Több konzolt kiadó gyártó */>) | Gyártónkénti összegzés | Gyártónkénti összegzés tömbben, majd a két összeg összehasonlítása. | 1 | Bevezetés | ✅ kész |
| 44 | [Többször ugyanott rendezett környezetvédelmi világnapok](<44. Többször ugyanott rendezett környezetvédelmi világnapok **/>) | Gyakorisági számlálás | Darabszám-tömb a rendezvényekhez, a legalább kétszer előfordulók megszámlálása. | 2 | Magyarázat | ✅ kész |
| 45 | [Ugró értékek](<45. Ugró értékek */>) | Szomszédos párok számlálása | Szomszédos elemek különbségének egy bejárásban történő ellenőrzése. | 1 | Bevezetés | ✅ kész |
| 46 | [Utas nélküli állomásszakaszok száma](<46. Utas nélküli állomásszakaszok száma */>) | Prefixösszeg | Utasok számának futó összege (felszállók mínusz leszállók), a nulla egyenlegű állomásközök számlálása. | 1 | Bevezetés | ✅ kész |
| 47 | [Védett falak száma](<47. Védett falak száma */>) | Szomszédos párok | Lineáris bejárás: a két szomszédos őrhelyen is őrséget tartalmazó párok számlálása. | 1 | Bevezetés | ✅ kész |
| 48 | [Védett szakaszok száma a Kínai Nagy Falon](<48. Védett szakaszok száma a Kínai Nagy Falon **/>) | Összefüggő szakaszok | Lineáris bejárás: a védett falak közül azok számlálása, amelyek előtt nem áll védett fal. | 2 | Magyarázat | ✅ kész |
| 49 | [Végzettek születési dátumai évszakokra lebontva](<49. Végzettek születési dátumai évszakokra lebontva **/>) | Feltételes számlálás | Hónap alapján elágazással választjuk ki az évszakot, és a megfelelő számlálót növeljük. | 2 | Bevezetés | ✅ kész |
| 50 | [Viharos napok száma](<50. Viharos napok száma */>) | Feltételes számlálás | Lineáris bejárás: a 100 km/óránál nagyobb szélsebességű napok számlálása. | 1 | Bevezetés | ✅ kész |
| 51 | [Olimpiai kvalifikáció indulók száma](<51. Olimpiai kvalifikáció indulók száma */>) | Oszloponkénti számlálás | Oszloponkénti számlálás: versenyenként egy számláló, a nem nulla helyezéseket növeljük. | 1 | Magyarázat | ✅ kész |
| 52 | [Lakás kategóriák](<52. Lakás kategóriák **/>) | Intervallumok szerinti számlálás | Kategóriaindex számítása (terület egész osztása tízzel, legfeljebb 19), majd a számlálótömb növelése. | 2 | Magyarázat | ✅ kész |
| 53 | [Sikeres dobások száma](<53. Sikeres dobások száma */>) | Megszámolás: feltétel | Versenyzőnként a hat dobás végigolvasása, a nem -1 értékek számlálása | 1 | Bevezetés | ✅ kész |
| 54 | [Személyi számok](<54. Személyi számok ***/>) | Megszámolás: dátum | Születési dátumok tömbbe gyűjtése nemenként, a napok bejárásával a szökőnap figyelembevételével | 3 | Magyarázat | ✅ kész |
| 55 | [Világcsúcs beállítások száma](<55. Világcsúcs beállítások száma */>) | Szomszédos elemek | Egyszeri végigolvasás, a szomszédos azonos magasságok számlálása | 1 | Bevezetés | ✅ kész |
| 56 | [Világcsúcsok közötti legnagyobb időkülönbség](<56. Világcsúcsok közötti legnagyobb időkülönbség */>) | Maximumkiválasztás: szomszédos elemek | Egyszeri végigolvasás, a szomszédos évek különbségének maximuma | 1 | Bevezetés | ✅ kész |
| 57 | [Turistaház](<57. Turistaház ***/>) | Szabad szakaszok számlálása | Összefüggő szabad szakaszok bejárása, szakaszonként a maradék napok korlátozzák a meghosszabbítást. | 3 | Magyarázat | ✅ kész |
| 58 | [Vitorlásverseny](<58. Vitorlásverseny/>) | Szabad szakaszok számlálása | Szeles szakaszok bejárása, szakaszonként a versenyszám és a maradék napok alapján. | 3 | Magyarázat | ✅ kész |
| 59 | [Rendezőpályaudvar](<59. Rendezőpályaudvar ***/>) | Számlálás és rendezés | Városonkénti számlálás, majd szabad hely szerinti rendezés, az első három város kiírása. | 3 | Magyarázat | ✅ kész |
| 60 | [Hajók](<60. Hajók ***/>) | Megszámolás: csoportosítás | Városonkénti darabszám, hajók és szabad hely képlettel, majd rendezés | 3 | Magyarázat | ✅ kész |
| 61 | [Földrengések](<61. Földrengések ***/>) | Megszámolás: állapotgép | Egyszeri bejárás: az utórengés-feltétel az utolsó mérés idejével és a földrengés erősségével | 3 | Magyarázat | ✅ kész |
| 62 | [Visszhang](<62. Visszhang ***/>) | Megszámolás: állapotgép | Egyszeri bejárás: az előző nem nulla mérés idejével és erősségével, visszhangok számlálása | 3 | Magyarázat | ✅ kész |
| 63 | [Csoportképek](<63. Csoportképek ****/>) | Megszámolás: prefixösszeg | Differenciatömbbel a létszám, prefixösszeggel a képes időpontok, videónként két kivonással | 4 | Mélyebb megértés | ✅ kész |
| 64 | [Csoportképek](<64. Csoportképek/>) | Differenciatömb, prefixösszeg | Differenciatömb és prefixösszeg a létszámhoz, majd prefixösszeg a képes időpontokra. | 2 | Magyarázat | ✅ kész |
| 65 | [Véletlenszám ellenőrzés](<65. Véletlenszám ellenőrzés ****/>) | Szomszédos előfordulások | Szomszédos előfordulási párok, értékenkénti prefixösszeg és M×M-es maximumtábla. | 4 | Mélyebb megértés | ✅ kész |
| 66 | [Pontozásos verseny](<66. Pontozásos verseny ***/>) | Gyakorisági tömb | Gyakorisági tömb 1–100 pontszámokra, sorban haladva az addig kisebb pontszámok összege. | 3 | Bevezetés | ✅ kész |
| 67 | [Szerencsés napok](<67. Szerencsés napok ****/>) | Intervallumok számlálása | Szerencsés (+1) és szerencsétlen (−1) napok jelölése, prefixösszeg, végpontpárok kettős ciklusban. | 4 | Magyarázat | ✅ kész |
| 68 | [Versenyeredmények](<68. Versenyeredmények ****/>) | Prefixösszeg | Prefixösszegek, minden érték-párra a szomszédos előfordulások közti maximális rés táblázatban. | 4 | Magyarázat | ✅ kész |
| 69 | [Dinnyeárus](<69. Dinnyeárus ***/>) | Megszámolás | Előzetes és utólagos számlálás, a 100-nál nem nagyobb árak tömbjével. | 3 | Bevezetés | ✅ kész |
| 70 | [Ismétlődő karakterek részsorozatban](<70. Ismétlődő karakterek részsorozatban ****/>) | Mohó kiválasztás | Mohó betűnkénti építés, a folytatást betűnkénti felső korláttal ellenőrizve. | 4 | Mélyebb megértés | ✅ kész |
| 71 | [Kerítés](<71. Kerítés ***/>) | Megszámolás: festés-szimuláció | Lécenkénti szimuláció: darabszám és az utolsó két festés színe | 3 | Magyarázat | ✅ kész |
| 72 | [Versenypárok kialakítása](<72. Versenypárok kialakítása **/>) | Megszámolás: párosítás | Színenként számolás, két független párosítási típus minimumának összege | 2 | Bevezetés | ✅ kész |
| 73 | [Falfestés](<73. Falfestés ***/>) | Megszámolás: rácsszimuláció | Cellánkénti szimuláció rácson: darabszám és az utolsó két festés színe | 3 | Magyarázat | ✅ kész |
| 74 | [Telekocsi](<74. Telekocsi **/>) | Megszámolás: csoportosítás | Célvárosonként a minimum: autók férőhelye és az utasok száma | 2 | Bevezetés | ✅ kész |
| 75 | [Morze](<75. Morze */>) | Morze-kód dekódolás | Öt karakteres blokkokra bontás, minden blokk összevetése a számjegyek kódtáblázatával | 1 | Bevezetés | ✅ kész |
| 76 | [Kövek](<76. Kövek **/>) | Prefixösszeg | Átlagtól való eltérések prefixösszege, a nem nulla prefixek számlálása | 2 | Magyarázat | ✅ kész |
| 77 | [Kerítés](<77. Kerítés/>) | Megszámolás: állapotgép | Léckénként az utolsó festés színének nyilvántartása, az utolsó két festés összevetése | 2 | Magyarázat | ✅ kész |
| 78 | [Versenypárok kialakítása](<78. Versenypárok kialakítása/>) | Párok számlálása | Két független párfajta (zöld–piros és piros–zöld) külön min-értéke, ezek összege | 2 | Bevezetés | ✅ kész |
| 79 | [Generátor](<79. Generátor ***/>) | Megszámolás: prefixösszeg | Értékenkénti prefixösszegek, lekérdezésenként az előforduló értékek megszámolása. | 3 | Magyarázat | ✅ kész |
| 80 | [Falfestés](<80. Falfestés/>) | Megszámolás: rácsszimuláció | Kőnként az utolsó két festés színének követése rácson. | 2 | Magyarázat | ✅ kész |
| 81 | [Telekocsi](<81. Telekocsi/>) | Megszámolás: csoportosítás | Városonként a minimum: az autók 3-szoros férőhelye és az utasok száma. | 2 | Bevezetés | ✅ kész |
| 82 | [Véletlenszámok](<82. Véletlenszámok ***/>) | Prefixösszeg | Értékenkénti prefixösszeg, az intervallumban nulla előfordulású értékek számlálása | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 83 | [Különböző értékek](<83. Különböző értékek ***/>) | Prefixösszeg | Előforduló értékek jelölése, prefixösszeg az értéktartományon | 3 | Bevezetés | 🟡 kézi ellenőrzés |
| 84 | [Különböző értékek](<84. Különböző értékek/>) | Prefixösszeg | Előforduló értékek jelölése, prefixösszeg az értéktartományon | 1 | Bevezetés | ✅ kész |
| 85 | [Pillanatnyilag megelőzöttek](<85. Pillanatnyilag megelőzöttek **/>) | Gyakorisági tömb | Pontszámonkénti darabszámok tömbje, minden versenyzőnél a kisebb pontszámok összegzése | 2 | Magyarázat | ✅ kész |
| 86 | [Előállítások száma orgonasíp elrendezésben](<86. Előállítások száma orgonasíp elrendezésben ***/>) | Megszámolás: párok összege | Balról jobbra haladva a K - x értékű korábbi elemek számának összegzése gyakorisági táblával | 3 | Magyarázat | ✅ kész |
| 87 | [Különböző és ismétlődő értékek](<87. Különböző és ismétlődő értékek ***/>) | Megszámolás: prefixösszeg | Két prefixösszeg-tömb (különböző értékek, összes húzás), ismétlődés: összes mínusz különböző | 3 | Magyarázat | ✅ kész |
| 88 | [Pillanatnyilag helyezés](<88. Pillanatnyilag helyezés **/>) | Megszámolás: rangsorolás | Korábbi, nála jobb és azonos pontszámok darabszámának lekérdezése Fenwick-fával | 2 | Magyarázat | ✅ kész |
| 89 | [Színezés](<89. Színezés **/>) | Megszámolás: szakaszhatárok | Szomszédos eltérő színű párok száma V; a válasz ceil(V/2), egy átszínezés után O(1) frissítés | 2 | Mélyebb megértés | ✅ kész |
| 90 | [Vetélkedő](<90. Vetélkedő ***/>) | Megszámolás: csoportosítás | Karakterenként rendezett azonosító kulcsként, map-ben előfordulások számolása, a páratlan darabszámú csapat kiválasztása. | 3 | Magyarázat | ✅ kész |
| 91 | [Előállítások száma](<91. Előállítások száma **/>) | Megszámolás: párok | Gyakorisági tömb: értékpárok számolása, az azonos értékek n(n-1)/2 párral. | 2 | Magyarázat | ✅ kész |
| 92 | [Málna](<92. Málna/>) | Prefixösszeg: paritás | Prefixösszegek paritása: páros párok számolása paritásonként egy bejárásban. | 2 | Magyarázat | ✅ kész |
| 93 | [Székek](<93. Székek/>) | Megszámolás: ciklusok | Rosszul ülők száma plusz a legalább kétszékes körök száma | 3 | Magyarázat | ✅ kész |
| 94 | [Áruszállítás](<94. Áruszállítás/>) | Prefixösszeg | Különbségtömb a szakaszok lefedettségére, nulla értékű szakaszok számlálása | 2 | Magyarázat | ✅ kész |
| 95 | [Egykorúak](<95. Egykorúak/>) | Dátumszámítás, naptár | Dátumok napsorszámra alakítása, összevetés 365 nappal | 2 | Bevezetés | ✅ kész |
| 96 | [Tükörtojás](<96. Tükörtojás/>) | Megszámolás: szakaszhatárok | Prefixfordítás: a szomszédos eltérések számlálása | 3 | Magyarázat | ✅ kész |
| 97 | [Áruszállítás üres szakaszai](<97. Áruszállítás üres szakaszai/>) | Intervallumok lefedése | Különbségtömbbel jelöljük a lefedett szakaszokat, majd a lefedetlen futamok kezdeteit számoljuk. | 3 | Magyarázat | ✅ kész |
| 98 | [Síugró verseny](<98. Síugró verseny/>) | Helyezések gyakorisága | Lineáris bejárás: ugrásonként számoljuk a nála szigorúan jobb pontszámúak számát, és ebből a helyezést. | 2 | Bevezetés | ✅ kész |
| 99 | [Szálloda](<99. Szálloda/>) | Szomszédok a rangsorban | Lineáris bejárás, futás közben a Hó Eduárdhoz legközelebbi felső és alsó pontszám karbantartása. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
