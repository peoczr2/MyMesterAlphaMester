# Gráfok, szélességi bejárás – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 85 feladat · ✅ kész 45 · ❌ hibás 0 · 🟡 kézi 36 · 🟡 nincs minta/speciális 4 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [2x2-es robot](<1. 2x2-es robot ***/>) | Gráf: súlyozott legrövidebb út | Állapot a robot bal felső sarka; Dial-algoritmus (költség 1–3) a legrövidebb útra | 3 | Magyarázat | ✅ kész |
| 2 | [6x6-os solitaire](<2. 6x6-os solitaire **/>) | Gráf: BFS állapottér | Szélességi bejárás a két korong rendezett állapotterén, visszafejtés szülőmutatókkal. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 3 | [80 nap alatt a Föld körül](<3. 80 nap alatt a Föld körül ***/>) | Gráf: legrövidebb út | Dijkstra (város, fordulatszám) állapotokon, a hosszúsági elmozdulás nyomon követésével | 3 | Mélyebb megértés | ✅ kész |
| 4 | [Ádám és Éva](<4. Ádám és Éva */>) | Gráf: szélességi bejárás | Két szélességi bejárás (Ádámtól és Évától), majd a minimális távolságú város kiválasztása | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 5 | [Adott ponton átmenő legrövidebb kör](<5. Adott ponton átmenő legrövidebb kör **/>) | Gráf: BFS | Többforrású BFS a P szomszédjaiból, a két különböző forrást összekötő él adja a kört | 2 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 6 | [Akadálypálya](<6. Akadálypálya ***/>) | Gráf: súlyozott legrövidebb út | Súlyozott legrövidebb út (Dijkstra) a (cella, sínállás) állapotokon | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 7 | [Állatkert](<7. Állatkert ***/>) | Gráf: legrövidebb utak száma | Szélességi bejárás, minden csúcshoz a legrövidebb utak számának összegzése a szomszédokból. | 3 | Magyarázat | ✅ kész |
| 8 | [Anyagmozgató robot](<8. Anyagmozgató robot ***/>) | Gráf: BFS | Állapot-BFS (sor, oszlop, irány): előre lépés és fordulás egyaránt 1 másodperc. | 3 | Magyarázat | ✅ kész |
| 9 | [Autók](<9. Autók ***/>) | Gráf: szélességi bejárás | BFS (pozíció, sebesség) állapotokon, cellánkénti előszámolt szabad szakaszokkal | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 10 | [Bolha](<10. Bolha **/>) | Gráf: funkcionális gráf | Ugrási funkcionális gráf; szintenkénti összegek long path decomposition-nel, ciklusokon paritás | 2 | Mélyebb megértés | 🟡 nincs minta |
| 11 | [Csapat](<11. Csapat */>) | Gráf: kétszínezés | Gráf kétszínezése szélességi bejárással (BFS) | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 12 | [Csatorna](<12. Csatorna ***/>) | Gráf: komponensek (DSU) | Élszűrés (A > R) után DSU komponensek; S komponensének élei és további komponensek száma | 3 | Magyarázat | ✅ kész |
| 13 | [Csoport](<13. Csoport ***/>) | Gráf: kétszínezés | Paritásos unió-keresés (DSU) a barát/ellenség feltételekre | 3 | Magyarázat | ✅ kész |
| 14 | [Egér és macska](<14. Egér és macska/>) | Gráf: BFS időkorláttal | Két szélességi bejárás (macska, egér); az egér csak ott léphet, ahol előbb ér | 3 | Magyarázat | ✅ kész |
| 15 | [Falak](<15. Falak ***/>) | Rács: szélességi bejárás | Cellákra bontás, zárt falak lefedése, szélességi bejárás a szélig | 3 | Magyarázat | ✅ kész |
| 16 | [Falvakban üzletek](<16. Falvakban üzletek **/>) | Fa: dinamikus programozás | Fa-DP: részfánként két állapot (van/nincs üzlet), visszafejtés fentről | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 17 | [Futár](<17. Futár */>) | Gráf: többforrású BFS | Többforrású szélességi bejárás a kezdővárosokból, majd a távolságok K-val való összevetése. | 1 | Bevezetés | ✅ kész |
| 18 | [Futó a sakktáblán](<18. Futó a sakktáblán **/>) | Gráf: BFS a sakktáblán | Szélességi bejárás a táblán: átlós csúszás az első bábuig, B részben az első bábu leütése. | 2 | Magyarázat | ✅ kész |
| 19 | [Gráf színező verseny](<19. Gráf színező verseny **/>) | Szimuláció, FIFO sorok | Két FIFO sor szimulációja: a legrégebbi pont legkisebb festetlen szomszédja, egyezésnél fehér. | 2 | Magyarázat | ✅ kész |
| 20 | [Hálózat átmérője](<20. Hálózat átmérője */>) | Gráf: fa átmérője | Két szélességi bejárás a fában: a legtávolabbi csúcsból indítva kapjuk az átmérőt. | 1 | Bevezetés | ✅ kész |
| 21 | [Hatszög](<21. Hatszög ***/>) | Gráf: BFS koordinátákkal | Hatszög-koordináták (i,j,k) szerinti szélességi bejárás csak azonos magasságú mezőkön. | 3 | Magyarázat | ✅ kész |
| 22 | [Kanyarodó villamos](<22. Kanyarodó villamos ***/>) | Gráf: BFS állapotokon | Állapot: (sor, oszlop, belépési oldal); szélességi bejárás az elemek összekötésein. | 3 | Magyarázat | ✅ kész |
| 23 | [Karaván](<23. Karaván **/>) | Gráf: időzített élek | Napról napra haladó bejárás: legkorábbi érkezés, legrövidebb időtartam és fordított legkésőbbi indulás. | 2 | Magyarázat | ✅ kész |
| 24 | [Két Mérőkanna](<24. Két Mérőkanna */>) | Gráf: szélességi bejárás | Szélességi bejárás a két kanna vízmennyiségének (a, b) állapotain | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 25 | [Kommandó](<25. Kommandó ***/>) | Gráf: legrövidebb út | Dijkstra a (trikócsere, országok száma) párokon, színváltásonként 1 költséggel | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 26 | [Körút](<26. Körút ***/>) | Gráf: szélességi bejárás | BFS K-ból ágcímkékkel, a legrövidebb K-n átmenő kör megkeresése | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 27 | [Labirintus](<27. Labirintus **/>) | Gráf: szélességi bejárás | Szélességi bejárás (mező, kapcsolóparitás) állapotokon | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 28 | [Mérőkannák](<28. Mérőkannák */>) | Állapottér-keresés | Állapottér (a, b) szélességi bejárása a lépések visszakövetésével | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 29 | [Modul](<29. Modul **/>) | Gráf: bejárás | Függőségi gráf előre- és visszirányú bejárása, szerzők halmaza | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 30 | [Mozi](<30. Mozi ***/>) | Állapottér-keresés | Elrendezések (permutációk) szélességi bejárása szomszédos cserékkel | 3 | Magyarázat | ✅ kész |
| 31 | [Nincs kimérhető tej](<31. Nincs kimérhető tej */>) | Állapottér bejárása | Szélességi bejárás a három kanna állapotain; a negyedik kanna tartalma a maradék | 1 | Magyarázat | 🟡 nincs minta |
| 32 | [Összefüggő hálózat](<32. Összefüggő hálózat */>) | Gráf: komponensek | Komponensek BFS-sel, a komponensek legkisebb csomópontjainak összekötése láncban | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 33 | [Pontok gráfon](<33. Pontok gráfon ***/>) | Gráf: határ és terület | Legkisebb összefüggő terület, amelynek határa nem nagyobb nála; BFS és három pontos Steiner-fa | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 34 | [Raktár](<34. Raktár */>) | Gráf: fa átmérője | Fa átmérője: két BFS a szabad mezők között | 1 | Magyarázat | ✅ kész |
| 35 | [Randi](<35. Randi */>) | Gráf: szélességi bejárás | Szélességi bejárás az R találkahelyből, a járatok irányát megfordítva. | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 36 | [Robotváros](<36. Robotváros ***/>) | Gráf: szélességi bejárás | Állapotgráf szélességi bejárása, a fordulást szögek döntik el (J/B). | 3 | Mélyebb megértés | ✅ kész |
| 37 | [Robotverseny](<37. Robotverseny ***/>) | Gráf: szélességi bejárás | Időegységenkénti szélességi bejárás, a szomszédos robotok blokkolásával. | 3 | Mélyebb megértés | ✅ kész |
| 38 | [Senki nem ismer senkit](<38. Senki nem ismer senkit */>) | Gráf: független halmaz | Legfeljebb öt nagy fokú csúcs összes részhalmaza, a többi csúcs utak és körök összegeként. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 39 | [Solitaire](<39. Solitaire **/>) | Állapottér: szélességi bejárás | Szélességi bejárás a három korong rendezett hármasaiból álló állapottérben | 2 | Magyarázat | ✅ kész |
| 40 | [Számítógépes hálózat](<40. Számítógépes hálózat ***/>) | Gráf: 0-1 szélességi bejárás | 0-1 szélességi bejárás a részhálózat-váltások költségével, szülőmutatókon visszafelé úttal | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 41 | [Sziget](<41. Sziget ***/>) | Rács: vízszint-szimuláció | Szélről számolt kritikus szint (minimax út), vízszint-szimuláció szélességi bejárással | 3 | Mélyebb megértés | ✅ kész |
| 42 | [Szójáték](<42. Szójáték **/>) | Gráf: BFS | Szélességi bejárás szógráfon: egy betű csere, B szabálynál betű írása a végére | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 43 | [Szolga](<43. Szolga ***/>) | Gráf: több forrású BFS | Több forrású szélességi bejárás; minden csomópont a bejárásban őt elérő szülőjének küldi a kérést | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 44 | [Szögletes villamos](<44. Szögletes villamos ***/>) | Gráf: legrövidebb út | Forgatás nélkül szélességi bejárás, forgatással Dijkstra a cellákon (élsúly 1 + forgatások száma) | 3 | Magyarázat | ✅ kész |
| 45 | [Találka](<45. Találka */>) | Gráf: BFS | Két szélességi bejárás (A-ból, B-ből); a találkozási város a max(dA, dB) minimuma | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 46 | [Találka2](<46. Találka2 */>) | Gráf: szélességi bejárás | Két szélességi bejárás, esetszétválasztás és szülő-tömbös útvonal-visszaállítás | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 47 | [Tárcsás játék](<47. Tárcsás játék ***/>) | Állapottér-keresés | Szélességi bejárás az (mező, lépésszám mod 4) állapottéren, a tárcsák forgatásával | 3 | Magyarázat | ✅ kész |
| 48 | [Tejeskanna](<48. Tejeskanna ***/>) | Állapottér-keresés | Szélességi bejárás a két kanna mennyiségének állapotterén, A és B literes áttöltésekkel | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 49 | [Tejkimérés négy kannával](<49. Tejkimérés négy kannával */>) | Állapottér-keresés | Szélességi bejárás a három kanna állapottérén, a kényszerített öntési szabállyal | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 50 | [Térkép](<50. Térkép ***/>) | Gráf: BFS | Országgráf BFS a hosszhoz, 0-1 BFS a határ-ellenőrzéshez a rácson | 3 | Magyarázat | ✅ kész |
| 51 | [Utcák behajtani tilos táblákkal](<51. Utcák behajtani tilos táblákkal ***/>) | Gráf: BFS | BFS a rácson, a tiltott irányított éleket kihagyva, útvonal visszakövetéssel | 3 | Bevezetés | ✅ kész |
| 52 | [Utcák kötelező haladási irány táblákkal](<52. Utcák kötelező haladási irány táblákkal ***/>) | Gráf: BFS | BFS állapottérben (csomópont, érkezési irány), megengedett kimenő irányok maszkkal | 3 | Magyarázat | ✅ kész |
| 53 | [Városok](<53. Városok ***/>) | Gráf: rácsos legrövidebb út | Három Dijkstra-futás más lépésköltséggel, a városok területe 2-es mezőkön át számolt BFS-sel. | 3 | Magyarázat | ✅ kész |
| 54 | [Vasút](<54. Vasút ***/>) | Gráf: szélességi bejárás | Vonalak mint csúcsok szélességi bejárása; az átszállások száma a felhasznált vonalak számából adódik. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 55 | [Bolha](<55. Bolha ***/>) | Gráf: funkcionális gráf | Legközelebbi szomszéd mutatók; fák hosszú-út felbontása, körökön maradékosztályok szerinti összeg. | 3 | Mélyebb megértés | 🟡 nincs minta |
| 56 | [Tiltott városok 2](<56. Tiltott városok 2 **/>) | Gráf: szélességi bejárás | Két szélességi bejárás, saját tiltott városokkal; a legkisebb távolságösszegű közös város keresése. | 2 | Bevezetés | ✅ kész |
| 57 | [Tiltott városok 3](<57. Tiltott városok 3 **/>) | Gráf: BFS | Két szélességi bejárás, majd a legkisebb max(dA, dE) értékű város kiválasztása | 2 | Bevezetés | ✅ kész |
| 58 | [Ügynök útja](<58. Ügynök útja ***/>) | Fa: átmérő | Fa átmérőjének két BFS-sel, majd zárt képlet a bejárható városokra | 3 | Mélyebb megértés | ✅ kész |
| 59 | [Cukrászok](<59. Cukrászok ***/>) | Gráf: háromszögek | Háromszögek keresése fokszám szerinti irányítással, a maximumok összegzése | 3 | Magyarázat | ✅ kész |
| 60 | [Labor](<60. Labor ***/>) | Részösszegek modulo K | Részlegesen töltött edények összege modulo K bitsettel; a 0 és a K feltétele külön. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 61 | [Országok](<61. Országok/>) | Gráf: szélességi bejárás | Évenkénti szélességi bejárás; ha egy szabad ország agresszív szomszédai különböző tulajdonosúak, örökre szabad marad. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 62 | [Csatornák](<62. Csatornák/>) | Gráf: legszélesebb út | Csökkenő sorrendű diszjunkt halmazok adják a szélességet, majd BFS a küszöbön. | 2 | Magyarázat | ✅ kész |
| 63 | [DNS vizsgálat](<63. DNS vizsgálat/>) | Gráf: levélnyesés, BFS | Levélnyesés a városmag megtalálására, majd többforrásos BFS a tanyák hozzárendelésére. | 3 | Magyarázat | ✅ kész |
| 64 | [Szigetek száma](<64. Szigetek száma/>) | Gráf: szélességi bejárás | Szélességi bejárás (BFS) 8 irányban, a zöld komponensek számolása. | 1 | Bevezetés | ✅ kész |
| 65 | [Legnagyobb sziget](<65. Legnagyobb sziget/>) | Gráf: szélességi bejárás | Szélességi bejárás 8 irányban, a legnagyobb komponens cellaszámának meghatározása. | 1 | Bevezetés | ✅ kész |
| 66 | [Futárszolgálat](<66. Futárszolgálat/>) | Fa: legrövidebb séta | A kötelező városok Steiner-fájának élei kétszer, a végpontok közti út egyszer: 2·W − D. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 67 | [Hálózat kettéosztás](<67. Hálózat kettéosztás/>) | Lineáris algebra: GF(2) | Paritási feltétel GF(2) lineáris egyenletrendszerként, Gauss-eliminációval. | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 68 | [Bástya a sakktáblán](<68. Bástya a sakktáblán/>) | Gráf: szélességi bejárás | Szélességi bejárás szakaszonként: egy lépésben a teljes szabad sor- vagy oszlopszakasz elérhető. | 3 | Magyarázat | ✅ kész |
| 69 | [Futó a sakktáblán](<69. Futó a sakktáblán/>) | Gráf: szélességi bejárás | Szélességi bejárás szakaszonként, átlós irányban: egy lépésben a teljes szabad átlószakasz elérhető. | 3 | Magyarázat | ✅ kész |
| 70 | [Repülési esetek](<70. Repülési esetek/>) | Gráf: komponensek | Komponensenként szorzás: fa esetén V, egy körös komponensben 2, kétélű körnél 1 lehetőség. | 3 | Mélyebb megértés | ✅ kész |
| 72 | [Sípályák](<72. Sípályák/>) | Gráf: DAG, bitmaszk | Körmentes gráf: célhelyek bitmaszkja topologikus sorrendben, starthelyenként számolva | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 73 | [Tom és Jerry 1](<73. Tom és Jerry 1 ***/>) | Gráf: idő-korlátos bejárás | Tom 2-es élekre korlátozott távolságai, majd Dijkstra-szerű visszafelé számolás az egérlyuktól | 3 | Mélyebb megértés | ✅ kész |
| 74 | [Hírvivők csoportosítása](<74. Hírvivők csoportosítása **/>) | Unió-keresés, csoportosítás | Manhattan-távolságok rendezése, Kruskal-típusú összevonás DSU-val, a csoportszám K alá csökkenéséig | 2 | Magyarázat | ✅ kész |
| 75 | [Pletyka](<75. Pletyka ***/>) | Gráf: séták paritása | BFS a (diák, paritás) párok gráfján, a napi létszámok prefixösszeggel | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 76 | [Egyirányú utcák](<76. Egyirányú utcák **/>) | Gráf: irányított BFS | BFS az irányított rácson, a szülőtömbből visszafelé rakjuk össze az utat | 2 | Bevezetés | ✅ kész |
| 77 | [Legközelebbi szigetek](<77. Legközelebbi szigetek **/>) | Rács: többforrású BFS | Minden szigetből többforrású BFS a rácson, így a szigetpárok legkisebb távolsága | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 78 | [Legelszigeteltebb sziget](<78. Legelszigeteltebb sziget **/>) | Rács: többforrású BFS | Szigetenként többforrású BFS, a legközelebbi másik sziget távolságainak maximuma | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 79 | [Üzletlánc](<79. Üzletlánc ****/>) | Gráf: BFS | Két BFS a két raktárból, majd mohó kiosztás a dA−dB különbség szerint rendezve. | 4 | Magyarázat | 🟡 kézi ellenőrzés |
| 80 | [Matekbolha](<80. Matekbolha/>) | Gráf: BFS | Min: BFS a karaktergráfon; max: zárójelcsoportonként DP a két x között. | 4 | Mélyebb megértés | ✅ kész |
| 81 | [Távoli városok](<81. Távoli városok/>) | Gráf: artikulációs pont | Mélységi bejárás, low-érték: a főváros–kikötő fa-úton elválasztó csúcs keresése. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 82 | [Járások](<82. Járások */>) | Gráf: szélességi bejárás | Többforrású szélességi bejárás; egyenlő távolságnál a kisebb sorszámú központ nyer | 1 | Magyarázat | 🟡 nincs minta |
| 83 | [Tom és Jerry 3](<83. Tom és Jerry 3/>) | Gráf: fa, üldözéses játék | Átmérő-feltétel és a Jerry számára biztonságos szobák legtávolabbi távolsága | 4 | Mélyebb megértés | ✅ kész |
| 84 | [Testnevelés óra](<84. Testnevelés óra/>) | Gráf: topologikus rendezés | Topologikus rendezés (Kahn), egyértelműség-ellenőrzés szomszédos párokra | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 85 | [Vizeskannák](<85. Vizeskannák/>) | Állapottér-keresés | BFS az állapotokon (első két kanna vize), legkevesebb átöntés | 2 | Bevezetés | ✅ kész |
| 86 | [Sportos nyaralás](<86. Sportos nyaralás/>) | Gráf: komponensek | Két DSU a komponensekhez, majd a (bicikli, vízi) komponens-párok csoportméretéből | 2 | Magyarázat | ✅ kész |
