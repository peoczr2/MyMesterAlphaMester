# Programozási tételek: összeépítése – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 154 feladat · ✅ kész 147 · ❌ hibás 0 · 🟡 kézi 7 · 🟡 nincs minta/speciális 0 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Adott intervallumban rendezett környezetvédelmi világnapok helyszínei](<1. Adott intervallumban rendezett környezetvédelmi világnapok helyszínei **/>) | Szűrés, jelölés | Egyszeri beolvasás, az intervallumba eső rendezvények országainak jelölése. | 2 | Bevezetés | ✅ kész |
| 2 | [Árból egyértelműen következtethető utazások](<2. Árból egyértelműen következtethető utazások */>) | Számlálás, gyakoriság | Árak előfordulásának számlálása map-ben, a pontosan egyszer előforduló árak megszámolása. | 1 | Bevezetés | ✅ kész |
| 3 | [Átlag feletti légszennyezettségek](<3. Átlag feletti légszennyezettségek */>) | Átlag feletti elemek | Esti értékek összege, az átlag egész szorzással (E * N > összeg) való összehasonlítása. | 1 | Bevezetés | ✅ kész |
| 4 | [Egész héten helyettesíteni tudó tanár](<4. Egész héten helyettesíteni tudó tanár ****/>) | Halmazok, feltételes kiválasztás | Foglaltsági halmazok: szabad helyettes keresése, a napok részhalmaz-feltételével. | 4 | Mélyebb megértés | ✅ kész |
| 5 | [Egy melegebb település](<5. Egy melegebb település **/>) | Páronkénti összehasonlítás | Páronkénti összehasonlítás: van-e minden napon szigorúan hidegebb település | 2 | Bevezetés | ✅ kész |
| 6 | [Egy napon helyettesíteni tudó tanárok](<6. Egy napon helyettesíteni tudó tanárok ***/>) | Táblázat, keresés | Tanár óráinak gyűjtése, minden órához legkisebb szabad szakos tanár keresése a foglaltsági táblában | 3 | Magyarázat | ✅ kész |
| 7 | [Elég résztvevő a kihívás napján](<7. Elég résztvevő a kihívás napján */>) | Prefixösszeg | Futó összeg bejárás, az első küszöbátlépés sorszámának kiírása | 1 | Bevezetés | ✅ kész |
| 8 | [Előrejelzések átlaga legnagyobb](<8. Előrejelzések átlaga legnagyobb */>) | Maximumkiválasztás | Soronkénti összegzés, az eddigi legnagyobb összeg és sorszám követése szigorú összehasonlítással. | 1 | Bevezetés | ✅ kész |
| 9 | [Első útszakasz többszöri felújítással](<9. Első útszakasz többszöri felújítással */>) | Különbségtömb, ablak keresése | Különbségtömbbel számoljuk a felújítások számát km-enként, majd keressük az első 10 hosszú ablakot. | 1 | Magyarázat | ✅ kész |
| 10 | [Évek mikor több bor készült mint azelött](<10. Évek mikor több bor készült mint azelött */>) | Futó maximum | Futó maximum: a korábbi évek legnagyobb mennyiségénél nagyobb évek gyűjtése. | 1 | Bevezetés | ✅ kész |
| 11 | [Fagyos időszakok száma](<11. Fagyos időszakok száma */>) | Összefüggő szakaszok | Lineáris bejárás, átmenetek számolása negatív szakaszok kezdetére. | 1 | Bevezetés | ✅ kész |
| 12 | [Folyamatos fagy](<12. Folyamatos fagy */>) | Keresés: folytonos szakasz | Egy bejárás, futó számláló az egymás utáni fagyos napokra | 1 | Bevezetés | ✅ kész |
| 13 | [Folyamatos meleg az előrejelzésben](<13. Folyamatos meleg az előrejelzésben **/>) | Leghosszabb szakasz | Településenként futó számlálóval keressük a legtöbb egymás utáni K feletti napot. | 2 | Bevezetés | ✅ kész |
| 14 | [Legmelegebb település](<14. Legmelegebb település **/>) | Maximumkeresés, számlálás | Naponként az egyedül legmagasabb hőmérsékletű települést keressük, és a településenkénti nyerő napokat számoljuk. | 2 | Bevezetés | ✅ kész |
| 15 | [Gazdaságos-e a vonat üzemeltetése](<15. Gazdaságos-e a vonat üzemeltetése */>) | Összegzés: szakaszonkénti utasszám | Szakaszonkénti utasszámok összegzése, majd a bevétel és a költség összehasonlítása | 1 | Bevezetés | ✅ kész |
| 16 | [Gombaszedés](<16. Gombaszedés **/>) | Mohó kiválasztás, rendezés | Rendezés súly szerint, majd szimuláció a kapacitás és a Csiperke-szabály szerint. | 2 | Magyarázat | ✅ kész |
| 17 | [Igazságos edző](<17. Igazságos edző **/>) | Számlálás, gyakoriság | Posztonkénti számlálás, majd a minimális indulásszámú versenyzők kiválogatása. | 2 | Bevezetés | ✅ kész |
| 18 | [Királyok száma kiknek gyermeke nem volt király](<18. Királyok száma kiknek gyermeke nem volt király **/>) | Halmazok, szülő-gyerek kapcsolat | Két halmaz: van-e gyereke, és van-e királyként szereplő gyereke. | 2 | Bevezetés | ✅ kész |
| 19 | [Könyvbírálók](<19. Könyvbírálók ****/>) | Alsó korlát, ütemezés | Négy alsó korlát maximuma: fontos lánc, bíráló-összmunkák, legnagyobb könyv. | 4 | Mélyebb megértés | ✅ kész |
| 20 | [Könyvmásolatok eredeti szövege](<20. Könyvmásolatok eredeti szövege ***/>) | Többségi szavazás | Pozíciónkénti karaktergyakoriság-számlálás, többségi szavazással; ha nincs többség, #. | 3 | Magyarázat | ✅ kész |
| 21 | [Könyvmásolatok visszafejtése](<21. Könyvmásolatok visszafejtése ****/>) | Mohó szülőkeresés | Mohó szülőkeresés: a legkevesebb változtatással járó érvényes előző szöveg, a megváltozott pozíciók nyilvántartásával. | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 22 | [Különböző árú borok száma](<22. Különböző árú borok száma */>) | Halmaz, különböző elemek | Halmazba gyűjtött árak elemszámának meghatározása. | 1 | Bevezetés | ✅ kész |
| 23 | [Különböző életkorú dolgozók száma](<23. Különböző életkorú dolgozók száma */>) | Különböző elemek száma | Életkorok halmazba gyűjtése, a halmaz elemszáma a válasz. | 1 | Bevezetés | ✅ kész |
| 24 | [Lakások különböző alapterületeinek száma](<24. Lakások különböző alapterületeinek száma */>) | Különböző elemek száma | Alapterületek halmazba gyűjtése, a halmaz elemszáma a válasz. | 1 | Bevezetés | ✅ kész |
| 25 | [Lassú vonatok közt a leggyorsabb](<25. Lassú vonatok közt a leggyorsabb */>) | Feltételes minimumkeresés | Feltételes minimumkeresés egy menetben: a 120 percnél lassúbbak közül a legkisebb menetidő és sorszáma. | 1 | Bevezetés | ✅ kész |
| 26 | [Legdrágább közeli utazás ára](<26. Legdrágább közeli utazás ára */>) | Feltételes maximumkeresés | Feltételes maximumkeresés egy menetben: az 1000 kilométernél közelebbi utak legnagyobb ára. | 1 | Bevezetés | ✅ kész |
| 27 | [Leghosszabb állomásszakasz ahol a vonat nem állt meg](<27. Leghosszabb állomásszakasz ahol a vonat nem állt meg */>) | Leghosszabb folytonos szakasz | Érkezés–indulás összehasonlítás, leghosszabb megálló nélküli szakasz keresése egy menetben. | 1 | Magyarázat | ✅ kész |
| 28 | [Leghosszabb bankban tartózkodás](<28. Leghosszabb bankban tartózkodás **/>) | Asszociatív tömb | Kártyaszámonként a belépési idő tárolása map-ban, kilépéskor különbség, a nap végén bent lévők 24:00-ig. | 2 | Magyarázat | ✅ kész |
| 29 | [Leghosszabb egyszínű gyöngyökből álló szakasz](<29. Leghosszabb egyszínű gyöngyökből álló szakasz **/>) | Körkörös leghosszabb szakasz | Minden kezdőponttól az azonos színű futás hosszának megszámolása körkörös indexeléssel, a maximum tárolása. | 2 | Magyarázat | ✅ kész |
| 30 | [Leghosszabb emelkedő](<30. Leghosszabb emelkedő **/>) | Leghosszabb monoton szakasz | Két irányú lineáris bejárás, leghosszabb szigorúan monoton szakasz keresése. | 2 | Magyarázat | ✅ kész |
| 31 | [Leghosszabb időintervallumban dobogón elért helyezés](<31. Leghosszabb időintervallumban dobogón elért helyezés */>) | Leghosszabb feltételes szakasz | Lineáris bejárás, leghosszabb egymást követő legalább 3. helyezések sorozata. | 1 | Bevezetés | ✅ kész |
| 32 | [Leghosszabb időszakban folyamatos meleg](<32. Leghosszabb időszakban folyamatos meleg */>) | Leghosszabb feltételes szakasz | Lineáris bejárás, leghosszabb K-nál szigorúan melegebb egybefüggő szakasz. | 1 | Bevezetés | ✅ kész |
| 33 | [Leghosszabb intervallum estére romló légszennyeződésre](<33. Leghosszabb intervallum estére romló légszennyeződésre */>) | Leghosszabb feltételes szakasz | Lineáris bejárás, leghosszabb egybefüggő szakasz, ahol az esti érték nagyobb. | 1 | Bevezetés | ✅ kész |
| 34 | [Leghosszabb intervallum kevés őrrel a múzeumban](<34. Leghosszabb intervallum kevés őrrel a múzeumban **/>) | Intervallumok: különbségtömb | Különbségtömbbel napi őrszám, majd a kettőnél kevesebb őrös napok leghosszabb szakaszának keresése. | 2 | Magyarázat | ✅ kész |
| 35 | [Leghosszabb intervallumban nem védett falak száma](<35. Leghosszabb intervallumban nem védett falak száma */>) | Leghosszabb folytonos szakasz | Falankénti ellenőrzés a szomszédos őrhelypárokon, leghosszabb nem védett szakasz egy bejárásban. | 1 | Bevezetés | ✅ kész |
| 36 | [Leghosszabb intervallumban nem őrzött falak száma](<36. Leghosszabb intervallumban nem őrzött falak száma */>) | Leghosszabb folytonos szakasz | Falankénti ellenőrzés a szomszédos őrhelypárokon, leghosszabb nem őrzött szakasz egy bejárásban. | 1 | Bevezetés | ✅ kész |
| 37 | [Leghosszabb ismétlődő szakasz](<37. Leghosszabb ismétlődő szakasz ***/>) | Szövegek: LCP-táblázat | Minden kezdőpárra közös előtag LCP-táblázattal, a nem átfedő hosszt min(LCP, távolság) adja. | 3 | Magyarázat | ✅ kész |
| 38 | [Leghosszabb uralkodó dinasztia](<38. Leghosszabb uralkodó dinasztia **/>) | Maximális szakasz keresése | Szakaszok bontása a folytonos apa–fiú trónöröklés mentén, a leghosszabb szakasz kiválasztása. | 2 | Magyarázat | ✅ kész |
| 39 | [Legidősebb végzett hallgatók kora évenként](<39. Legidősebb végzett hallgatók kora évenként **/>) | Csoportos minimumkeresés | Csoportosítás végzési év szerint, évenkénti minimum (legkisebb születési év). | 2 | Magyarázat | ✅ kész |
| 40 | [Legjobb futóverseny helyezések száma](<40. Legjobb futóverseny helyezések száma */>) | Minimum és számlálás | Lineáris bejárás, a minimum és a számlálás egy menetben. | 1 | Bevezetés | ✅ kész |
| 41 | [Legjobb kilátó](<41. Legjobb kilátó ****/>) | Maximumkeresés: láthatóság | Minden szárazföldi pontból két irányban számoljuk a látható pontokat, meredekség-prefixmaximummal. | 4 | Mélyebb megértés | ✅ kész |
| 42 | [Legkedvezőbb málnavásárlás](<42. Legkedvezőbb málnavásárlás ***/>) | Mohó algoritmus: rendezés | Olcsóbbtól drágábbig rendezett termelők, napi kapacitásra töltve, a költség napi engedménnyel számolva. | 3 | Magyarázat | ✅ kész |
| 43 | [Legkevesebb idő megállás nélkül](<43. Legkevesebb idő megállás nélkül **/>) | Minimum: szakaszok hossza | Határpontok (0. perc, valódi megállások, végállomás) közti állómentes szakaszok minimuma egy bejárásban. | 2 | Bevezetés | ✅ kész |
| 44 | [Legkevesebb lyukasórájú tanár](<44. Legkevesebb lyukasórájú tanár ***/>) | Számlálás: lyukas órák | Tanáronként és naponként a legkisebb és legnagyobb óra közti üres órák összege, minimum kiválasztása. | 3 | Magyarázat | ✅ kész |
| 45 | [Legmesszebb lévő állomások, amelyek között nem volt utas](<45. Legmesszebb lévő állomások, amelyek között nem volt utas */>) | Prefixösszeg, leghosszabb futam | Állomásonkénti utasszám-számolás, majd leghosszabb nulla futam keresése egy bejárással. | 1 | Magyarázat | ✅ kész |
| 46 | [Legnagyobb különbség a min es max előrejelzések között](<46. Legnagyobb különbség a min es max előrejelzések között */>) | Minimum-maximum keresés | Soronkénti minimum és maximum követése egy bejárással, a legnagyobb különbségű sor kiválasztása. | 1 | Bevezetés | ✅ kész |
| 47 | [Legnagyobb tervbe betehető új szoba](<47. Legnagyobb tervbe betehető új szoba **/>) | Legnagyobb téglalap, hisztogram | Foglalt mezők különbségtömbbel, majd soronként legnagyobb téglalap veremmel a hisztogramon. | 2 | Mélyebb megértés | ✅ kész |
| 48 | [Legolcsóbb drága fenyőfa](<48. Legolcsóbb drága fenyőfa */>) | Feltételes minimumkeresés | Egy menetben a K-nál nagyobb árak közül a legkisebb ár és sorszámának követése. | 1 | Bevezetés | ✅ kész |
| 49 | [Legrosszabb kettesnél jobb tanuló](<49. Legrosszabb kettesnél jobb tanuló */>) | Minimumkeresés | Egymenetes minimumkeresés a legalább 3-as jegyek között, sorszámmal | 1 | Bevezetés | ✅ kész |
| 50 | [Legtöbb felhasználó a hálózatban](<50. Legtöbb felhasználó a hálózatban */>) | Eseménysorozat, szakaszok | Időrendi bejárás, bent lévők számának követése, legtöbbet tartalmazó szakaszok | 1 | Magyarázat | ✅ kész |
| 51 | [Legtöbb megfigyelt jármű egy időben](<51. Legtöbb megfigyelt jármű egy időben */>) | Gyakoriság számlálása | Azonos időpontú egymás utáni megfigyelések futamának hosszát maximalizáljuk | 1 | Bevezetés | ✅ kész |
| 52 | [Legtöbb rendszeridőt használó felhasználó](<52. Legtöbb rendszeridőt használó felhasználó ***/>) | Állapotkövetés, összegzés | Bejelentkezési állapot követése felhasználónként, sikeres be/ki párok időtartamainak összegzése | 3 | Magyarázat | ✅ kész |
| 53 | [Legtöbb tanár által tanított tantárgy](<53. Legtöbb tanár által tanított tantárgy **/>) | Mátrix, számlálás | Tantárgyanként a különböző tanárok megszámlálása egy táblázatban | 2 | Bevezetés | ✅ kész |
| 54 | [Legtöbb tipp](<54. Legtöbb tipp **/>) | Gyakoriság, rendezett map | Tippenként darabszám és első tippelő, majd a maximális darabszámú tippek kiírása | 2 | Bevezetés | ✅ kész |
| 55 | [Legtöbb ügyfél a bankban egyszerre](<55. Legtöbb ügyfél a bankban egyszerre */>) | Szakaszos összegzés, halmaz | Időszakok szakaszokra bontása, bentlévők halmazával; első maximális szakasz kiírása | 1 | Bevezetés | ✅ kész |
| 56 | [Legtöbbször ismétlődő szakasz](<56. Legtöbbször ismétlődő szakasz ****/>) | Karakterlánc: ismétlődés | Összes legalább 3 hosszú részszó nem átfedő előfordulásainak számlálása, legjobb kiválasztása | 4 | Magyarázat | ✅ kész |
| 57 | [Legvölgyesebb sziget](<57. Legvölgyesebb sziget ***/>) | Tömb: szigetek és völgyek | Szigetenként a völgyfutamok egyetlen bejárásos számlálása, a legtöbb völgyes sziget kiválasztása | 3 | Magyarázat | ✅ kész |
| 58 | [Nagy mennyiségben készített legdrágább bor](<58. Nagy mennyiségben készített legdrágább bor */>) | Maximumkeresés | Egy bejárás, feltételes maximumkeresés a nagy termésű években | 1 | Bevezetés | ✅ kész |
| 59 | [Növénytáblák száma](<59. Növénytáblák száma ****/>) | Mátrix: téglalapok | Maximális egyneműen kitöltött téglalapok számlálása, futamhosszakkal ellenőrizve | 4 | Mélyebb megértés | ✅ kész |
| 60 | [Összekevert sorrend](<60. Összekevert sorrend **/>) | Láncépítés, permutáció | Szomszédpárok gyűjtése a két szalag darabjaiból, majd a lánc bejárása a kezdőelemtől | 2 | Magyarázat | ✅ kész |
| 61 | [Pontozásos verseny végeredménye](<61. Pontozásos verseny végeredménye **/>) | Rendezés, összegzés | Pontszámok rendezése, a legkisebb és legnagyobb elhagyása, pontszám szerinti rendezés holtverseny-helyezéssel | 2 | Bevezetés | 🟡 kézi ellenőrzés |
| 62 | [Résztvevők száma kategóriánként a kihíváson](<62. Résztvevők száma kategóriánként a kihíváson */>) | Számlálás, kategorizálás | Lélekszám szerinti kategória meghatározása, és a részvevők összegzése kategóriánként | 1 | Bevezetés | ✅ kész |
| 63 | [Legkevesebb találkozás](<63. Legkevesebb találkozás ****/>) | Különbségtömb, intervallumok | Különbségtömb az érkezési időpontokra, a találkozók számának prefixösszege, minimum keresése a legkorábbi x-nél. | 4 | Magyarázat | ✅ kész |
| 64 | [Szigetek benépesítése](<64. Szigetek benépesítése **/>) | Lineáris bejárás, számlálás | Balról és jobbról egy-egy bejárás, a szigetek közötti tengerszakasz hossza legfeljebb T. | 2 | Bevezetés | ✅ kész |
| 65 | [Szólánc](<65. Szólánc **/>) | Láncolás, kezdőelem keresése | A kezdőszó az, amelynek kezdőbetűjére nincs végződő szó; utána a végbetű szerint láncolunk. | 2 | Bevezetés | ✅ kész |
| 66 | [Teaforgalmazók száma](<66. Teaforgalmazók száma */>) | Halmaz, egyedi elemek | Halmazba gyűjtjük a cégneveket, a végén a halmaz mérete adja a választ. | 1 | Bevezetés | ✅ kész |
| 67 | [Teljes sorozatok a lottón](<67. Teljes sorozatok a lottón **/>) | Mohó szakaszszámlálás | Mohó egyszeri bejárás, a különböző számok számlálása sorozatonként | 2 | Bevezetés | ✅ kész |
| 68 | [Új őrség küldése a Kínai Nagy Falra](<68. Új őrség küldése a Kínai Nagy Falra */>) | Szakaszok lefedése | Őrség nélküli szakaszok, szakaszonként floor(L/2) új őrség | 1 | Magyarázat | ✅ kész |
| 69 | [Vitorlás bajnokság végeredménye](<69. Vitorlás bajnokság végeredménye ****/>) | Rendezés, rangsor | Versenyzőnként pontok gyűjtése, legjobb L pont összege, többkulcsos rendezés | 4 | Mélyebb megértés | ✅ kész |
| 70 | [Vitorlás verseny kezdő napja](<70. Vitorlás verseny kezdő napja */>) | Keresés: összefüggő szakasz | Egy menetes bejárás futó számlálóval, az első K hosszú szakasz kezdete | 1 | Bevezetés | ✅ kész |
| 71 | [Drága beszerzések](<71. Drága beszerzések */>) | Prefixösszeg | Csökkenő ár szerinti prefixösszeg, az első felet elérő pozíció | 1 | Magyarázat | ✅ kész |
| 72 | [Győztes versenyzők](<72. Győztes versenyzők */>) | Tömbbejárás, jelölés | Logikai tömb jelöléssel: az 1-es helyezést elérő versenyzők | 1 | Bevezetés | ✅ kész |
| 73 | [Hőségriadó](<73. Hőségriadó ***/>) | Összefüggő szakaszok, távolság | Forró szakaszok egy menetben, a riadók közti legkisebb távolság | 3 | Magyarázat | ✅ kész |
| 74 | [Leghosszabb száraz időszak](<74. Leghosszabb száraz időszak **/>) | Leghosszabb összefüggő szakasz | Heti összegek számítása, majd egy bejárásban a leghosszabb folyamatos jó szakasz keresése | 2 | Bevezetés | ✅ kész |
| 75 | [Legszárazabb időszak](<75. Legszárazabb időszak **/>) | Csúszóablak, minimum | Napok számolása hetenként, majd csúszó ablak az N/2 hetes szakaszok összegére | 2 | Magyarázat | ✅ kész |
| 76 | [Legtöbb világcsúcs növekedés](<76. Legtöbb világcsúcs növekedés **/>) | Számlálás, maximum | Évenként számlálás: a szigorúan magasabb rekordok és az első rekord | 2 | Bevezetés | ✅ kész |
| 77 | [Legtovább szabad terem](<77. Legtovább szabad terem ***/>) | Tömb: szabad szakaszok | Foglalt napok jelölése termenként, majd a leghosszabb szabad szakasz keresése | 3 | Magyarázat | ✅ kész |
| 78 | [Magasugró világcsúcsok folyamatosan](<78. Magasugró világcsúcsok folyamatosan **/>) | Leghosszabb folytonos szakasz | Halmaz rendezi és szűri az éveket, majd egy bejárással keressük a leghosszabb folytonos szakaszt. | 2 | Magyarázat | ✅ kész |
| 79 | [Megbízható versenyzők](<79. Megbízható versenyzők **/>) | Szűrés, minimum-maximum | Versenyzőnkénti bejárás: sikertelen dobás keresése, majd minimum és maximum különbsége. | 2 | Bevezetés | ✅ kész |
| 80 | [Mindenhol pontot szerző versenyzők](<80. Mindenhol pontot szerző versenyzők */>) | Feltételes szűrés | Versenyzőnként az öt helyezés ellenőrzése: mindegyik 1 és K között kell legyen. | 1 | Bevezetés | ✅ kész |
| 81 | [Szabad nap nélküli termek](<81. Szabad nap nélküli termek **/>) | Rendezés, szomszédos elemek | Termenként rendezés után a szomszédos foglalások között keressük azt a párt, ahol a következő foglalás közvetlenül az előző után kezdődik. | 2 | Bevezetés | ✅ kész |
| 82 | [Pénzfeldobások](<82. Pénzfeldobások ***/>) | Gyakorisági tábla, sorozatok | Egy bejárással szériánként számoljuk a hosszokat gyakorisági tömbben, és a leggyakoribb hosszt választjuk. | 3 | Magyarázat | ✅ kész |
| 83 | [Fajok száma](<83. Fajok száma ****/>) | Eseményseprés, intervallumok | Eseményeket rendezve végigsöpörjük a fajszámot, és a maximumos szakaszok hosszait összegezzük. | 4 | Magyarázat | ✅ kész |
| 84 | [Születések](<84. Születések ****/>) | Csúszóablak, rendezés | Dátumokat egész kulccsá kódolunk, és rendezett kulcsokon 372 hosszú ablakban számoljuk a születéseket. | 4 | Mélyebb megértés | ✅ kész |
| 85 | [Globális felmelegedés](<85. Globális felmelegedés ***/>) | Maximumkiválasztás | Éves összegek összehasonlítása, visszafelé bejárás a növekvő szakaszhoz, napi maximum számolás | 3 | Magyarázat | ✅ kész |
| 86 | [Piac](<86. Piac ***/>) | Összegzés, rendezés, maximum | Kereskedőnkénti összegzés, termékenkénti maximum és rendezés | 3 | Magyarázat | ✅ kész |
| 87 | [Legtöbb hegycsúcs](<87. Legtöbb hegycsúcs */>) | Előtagösszeg, csúszóablak | Csúcsok előtagösszege, majd minden K hosszú ablak végigpróbálása | 1 | Bevezetés | ✅ kész |
| 88 | [DNS vizsgálat](<88. DNS vizsgálat **/>) | Szélsőérték, szöveg | Bázisonként a leghosszabb hiányzó szakasz, plusz egy | 2 | Magyarázat | ✅ kész |
| 89 | [Találkozások](<89. Találkozások ****/>) | Intervallumok metszése | Érkezési és távozási időpontokat külön rendezve, bináris kereséssel számoljuk minden ember találkozóit. | 4 | Magyarázat | ✅ kész |
| 90 | [Szomszédainál melegebb napok](<90. Szomszédainál melegebb napok ***/>) | Lokális maximumok | Egy bejárással gyűjtjük a csúcsokat, majd K egymás utáni csúcs legszűkebb ablakát keressük. | 3 | Magyarázat | ✅ kész |
| 91 | [Betűk intervalluma](<91. Betűk intervalluma ****/>) | Csúszóablak, utolsó előfordulás | Jobb végpontonként az R-beli betűk utolsó előfordulásainak minimuma adja a legrövidebb intervallumot. | 4 | Magyarázat | ✅ kész |
| 92 | [Legtöbb csúcsot tartalmazó terület](<92. Legtöbb csúcsot tartalmazó terület ****/>) | 2D prefixösszeg | Csúcsok előre jelölése, 2D prefixösszeg, a K osztópárjaihoz tartozó téglalapok bejárása. | 4 | Magyarázat | ✅ kész |
| 93 | [Legrövidebb szakasz](<93. Legrövidebb szakasz ****/>) | Csúszóablak | Csúszóablak: a jobb végpontot léptetjük, a bal végpontot szűkítjük, 26 elemű számlálóval. | 4 | Magyarázat | ✅ kész |
| 94 | [Mély pontok](<94. Mély pontok ****/>) | 2D prefixösszeg | Mély pontok előre jelölése, 2D prefixösszeg, a K osztópárjaihoz tartozó téglalapok bejárása. | 4 | Magyarázat | ✅ kész |
| 95 | [Hegycsúcsok](<95. Hegycsúcsok **/>) | Lokális maximumok | Csúcsok egy menetben való összegyűjtése, majd a szomszédos K-as csoportok távolságának minimuma. | 2 | Bevezetés | ✅ kész |
| 96 | [Ádám vagy Éva nyert többször?](<96. Ádám vagy Éva nyert többször? */>) | Számlálás, többségi döntés | Két számlálóval megszámoljuk az A és E karaktereket, és összevetjük őket | 1 | Bevezetés | ✅ kész |
| 97 | [Nemzetközi vonat állomásai](<97. Nemzetközi vonat állomásai **/>) | Időszámítás, éjfél-vizsgálat | Percekre váltott időtengely, modulo 1440 haladás; éjfélekre a megállás vagy szakasz vizsgálata | 2 | Magyarázat | ✅ kész |
| 98 | [Bűvös](<98. Bűvös **/>) | Mátrix: sor- és oszlopösszegek | Hibátlan sor összegéből kapott S alapján minden cellát kipróbálunk, és ellenőrizzük a sorokat, oszlopokat | 2 | Bevezetés | ✅ kész |
| 99 | [Időjárás előrejelzés](<99. Időjárás előrejelzés **/>) | Tömbbejárás több kérdésben | Három külön bejárás: futó számláló a fagyos napokra, szomszédos különbségek, 2N-szeres egész összevetés | 2 | Magyarázat | ✅ kész |
| 100 | [Kártyaleosztás értéke](<100. Kártyaleosztás értéke */>) | Összegzés, táblázat | Táblázatos értékkeresés a figurákra, a piros lapok értékének duplázásával. | 1 | Bevezetés | ✅ kész |
| 101 | [Lövészverseny eredményei](<101. Lövészverseny eredményei **/>) | Futó maximum és minimum | Futó maximum és minimum, versenyzőnként az előtte állók számlálása. | 2 | Magyarázat | ✅ kész |
| 102 | [Négyzetek összerakása](<102. Négyzetek összerakása */>) | Mohó algoritmus | Mohó: mindig a legnagyobb kirakható négyzet, a maradékra ismételve. | 1 | Bevezetés | ✅ kész |
| 103 | [Legnépszerűbb és legnépszerűtlenebb programozási nyelvek](<103. Legnépszerűbb és legnépszerűtlenebb programozási nyelvek */>) | Asszociatív tömb | Nyelvenként map-ban tárolt létszámok összevetése, a közös nyelvek összesített létszámának min/max keresése. | 1 | Bevezetés | ✅ kész |
| 104 | [Villamos statisztika](<104. Villamos statisztika ***/>) | Állapotkövetés | Utasszám-állapot végigkövetése állomásonként, a feltételek ellenőrzésével. | 3 | Magyarázat | ✅ kész |
| 105 | [Titkos karaván](<105. Titkos karaván ****/>) | Jelölőtömb, eltolás | Oázisonkénti fix eltolás, a tiltott indulási napok jelölése egy tömbben. | 4 | Mélyebb megértés | ✅ kész |
| 106 | [Nyereség](<106. Nyereség ****/>) | Maximális összegű szakasz | Prefixösszegek, a korábbi prefixösszegek minimumának nyilvántartása egy menetben | 4 | Bevezetés | ✅ kész |
| 107 | [Szabadnapok](<107. Szabadnapok ****/>) | Minimális lefedő intervallum | Rögzített kezdőnapra a legkisebb befejező nap, emberenként egy mutatóval, maximum-tömbbel | 4 | Magyarázat | ✅ kész |
| 108 | [Felhasználó azonosítás](<108. Felhasználó azonosítás ****/>) | Rendezés, közös előtag | Rendezés után a szomszédok legnagyobb közös előtagja, plusz egy | 4 | Magyarázat | ✅ kész |
| 109 | [Fényképezés adott időtartam alatt](<109. Fényképezés adott időtartam alatt ****/>) | Intervallum-metszés, prefixösszeg | Prefixösszegek: érkezések és távozások darabszámából minden kezdőpontra O(1) alatt | 4 | Magyarázat | ✅ kész |
| 110 | [Földrengések](<110. Földrengések */>) | Intervallumszámlálás | Jelölt kezdőnapok, intervallumba eső események számlálása bináris kereséssel. | 1 | Magyarázat | ✅ kész |
| 111 | [Hegycsúcsok](<111. Hegycsúcsok **/>) | Kétdimenziós prefixösszeg | Csúcsjelölés belső cellákra, kétdimenziós prefix-összeg, legjobb négyzet keresése. | 2 | Magyarázat | ✅ kész |
| 112 | [Hírterjedés](<112. Hírterjedés **/>) | Gráf: szélességi bejárás | Kezdő megkeresése bejövő él nélkül, majd szélességi bejárás a fán. | 2 | Magyarázat | ✅ kész |
| 113 | [Leghosszabb nyaralás](<113. Leghosszabb nyaralás **/>) | Kétmutatós módszer | Kétmutatós csúszóablak pozitív összegekkel, a P-t nem haladó leghosszabb szakasz | 2 | Bevezetés | ✅ kész |
| 114 | [Síkság](<114. Síkság ****/>) | Csúszóablak: monoton deque | Csúszóablak két monoton deque-kel követi a max-min különbséget; a legkisebb kezdőindex marad | 4 | Magyarázat | ✅ kész |
| 115 | [Leggyorsabb pénzkeresés](<115. Leggyorsabb pénzkeresés **/>) | Kétmutatós módszer | Kétmutatós csúszóablak pozitív fizetésekkel, a legalább P összegű legrövidebb szakasz | 2 | Bevezetés | ✅ kész |
| 116 | [Versenyzők](<116. Versenyzők ***/>) | Számlálás, küszöbérték-keresés | Minden egész ponthatárt kipróbálunk, a számlálásokat rendezett tömbön lower_bound adja | 3 | Magyarázat | ✅ kész |
| 117 | [Résztömb](<117. Résztömb **/>) | Szélsőérték-keresés | Előjel-paritás és abszolútérték alapú esetszétválasztás, lineáris bejárással | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 118 | [Kifejezés](<118. Kifejezés ***/>) | Kifejezés-kiértékelés | Verem a zárójelszintek előjel-szorzóihoz, együtthatók előjeles összegzése | 3 | Magyarázat | ✅ kész |
| 119 | [Kifejezés](<119. Kifejezés ***/>) | Kifejezés-kiértékelés | Verem a zárójelszintekhez, az egymás utáni előjelek szorzásával | 3 | Magyarázat | ✅ kész |
| 120 | [Rosszsorrend](<120. Rosszsorrend ***/>) | Keresés, prefixmaximum | Prefixmaximum és bináris keresés: minden elemhez a balról első nagyobb elemet keressük. | 3 | Magyarázat | ✅ kész |
| 121 | [Xor](<121. Xor ****/>) | Bitműveletek, xor maximalizálás | Legmagasabb eltérő bit szerinti bontás, alsó párok komplementálása, két jelölt közül a nagyobb. | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 122 | [Rosszsorrend](<122. Rosszsorrend ***/>) | Keresés, prefixmaximum | Prefixmaximum és bináris keresés: minden elemhez a balról első nagyobb elemet keressük. | 3 | Magyarázat | ✅ kész |
| 123 | [Eső](<123. Eső ***/>) | Prefixösszeg, intervallumkeresés | Prefixösszeg (±1 minden napra), a jobb végpontot minden bal végponthoz hátulról keressük. | 3 | Magyarázat | ✅ kész |
| 124 | [Ügyelet](<124. Ügyelet ***/>) | Csúszóablak (kétmutatós) | Csúszóablak, darabszám-tömb és számláló: a legrövidebb teljes lefedő intervallum. | 3 | Magyarázat | ✅ kész |
| 125 | [Szerencsejáték](<125. Szerencsejáték ***/>) | Távolságok gyakorisága | Utolsó előfordulás nyilvántartása, a távolságok darabszámának maximuma. | 3 | Bevezetés | ✅ kész |
| 126 | [Bánya](<126. Bánya ***/>) | Prefixösszeg (2D) | 2D prefixösszeg, minden téglalap végigpróbálása O(1) ellenőrzéssel. | 3 | Magyarázat | ✅ kész |
| 127 | [Sorsolás](<127. Sorsolás ***/>) | Távolságok gyakorisága | Utolsó előfordulás és első kezdőnap nyilvántartása, a hosszok darabszáma. | 3 | Magyarázat | ✅ kész |
| 128 | [Őrzés](<128. Őrzés ***/>) | Csúszóablak, számlálás | Csúszóablak: a leghosszabb szakasz, amelyben M-nél kevesebb különböző dolgozó őrzött. | 3 | Magyarázat | ✅ kész |
| 129 | [Legt�bb unoka](<129. Legt�bb unoka **/>) | Fa, gyermekek száma | Unokák száma: a gyermekek gyermekszámainak összege, minden emberre. | 2 | Bevezetés | ✅ kész |
| 130 | [Zenehallgat�s](<130. Zenehallgat�s **/>) | Előtagösszeg, keresés | Körmodulo (P-1) mod S, előtagösszeg és bináris keresés (upper_bound). | 2 | Magyarázat | ✅ kész |
| 131 | [Háromszögek](<131. Háromszögek ****/>) | Rendezés és bináris keresés | Háromszög-egyenlőtlenségek intervallumra alakítása, rendezés és két bináris keresés | 4 | Magyarázat | ✅ kész |
| 132 | [DNS](<132. DNS **/>) | Prefixösszeg, első előfordulás | Prefixös mérleg (2·darab − hossz), első előfordulások tömbje, O(N) betűnként | 2 | Mélyebb megértés | ✅ kész |
| 133 | [Kert](<133. Kert **/>) | Rendezés, többségi elem | Soronkénti rendezés, többségi szín ellenőrzése a futamhosszal, egymás melletti futamok számlálása | 2 | Bevezetés | ✅ kész |
| 134 | [Sivatag](<134. Sivatag ***/>) | Kétdimenziós prefixösszeg | Kétdimenziós különbségi tömb a esőzésekhez, 2D prefixösszeg a K×K négyzetekhez, O(N·M + E) | 3 | Magyarázat | ✅ kész |
| 135 | [Legátlagosabb testtömegű ember](<135. Legátlagosabb testtömegű ember/>) | Prefixösszeg, átlag | Korok szerinti prefixösszegek, az átlag-eltérés törtként, egész számokkal összehasonlítva. | 2 | Magyarázat | ✅ kész |
| 136 | [Versenyeredmények](<136. Versenyeredmények/>) | Rendezés, közös prefix | Azonosítók rendezése, egyedi prefix a két szomszédjával vett közös prefixből. | 3 | Magyarázat | ✅ kész |
| 137 | [Osztályok](<137. Osztályok/>) | Értéktartományok, futamok | Darabszám szerinti küszöbnövelés, a futamszám inkrementális karbantartása értékek törlésével. | 4 | Mélyebb megértés | ✅ kész |
| 138 | [Résztömb](<138. Résztömb/>) | Prefixösszeg, rendezés | Prefixösszegek rendezése, a legközelebbi szomszédos pár adja a minimumot. | 2 | Magyarázat | ✅ kész |
| 139 | [Osztályok](<139. Osztályok/>) | Rendezés: összefüggő szakaszok | Előforduló értékek összefüggő szakaszai adják az osztályokat; a K-adik legnagyobb rés a válasz. | 3 | Magyarázat | ✅ kész |
| 140 | [Két szálloda](<140. Két szálloda/>) | Előtagösszeg, optimalizálás | Határindex-bejárás: minden elválasztásra a két csoport legjobb szállodája előtagösszegekkel, O(N²)-ben. | 4 | Mélyebb megértés | ✅ kész |
| 141 | [Leghosszabb béke](<141. Leghosszabb béke/>) | Intervallumok, különbségtömb | Különbségtömbbel jelöljük a háborús napokat, majd a békés napok leghosszabb futamát keressük. | 2 | Bevezetés | ✅ kész |
| 142 | [Legtöbbször szomszédok](<142. Legtöbbször szomszédok/>) | Rendezett halmaz: szomszédok | Pontszámonkénti számlálók rendezett halmazzal: Ló előtti és utáni legközelebbi pontszám ugrásonként | 4 | Mélyebb megértés | ✅ kész |
| 143 | [Vásárlás](<143. Vásárlás/>) | Részsorozat: legkisebb összeg | Az A-nál vett szakasz: legkisebb összegű összefüggő részsorozat (Kadane) az árkülönbségekből | 2 | Magyarázat | ✅ kész |
| 144 | [TV szolgáltatók](<144. TV szolgáltatók/>) | Bináris keresés: konvex költség | Fix K hosszú szakasz, a költség konvex x-ben, bináris keresés a minimumra | 3 | Mélyebb megértés | ✅ kész |
| 145 | [Földvásárlás](<145. Földvásárlás/>) | Csúszóablak: összeg, számlálás | Csúszóablakos összegzés, a minimum és darabszáma egy bejárásban | 1 | Bevezetés | ✅ kész |
| 148 | [Gabonaraktár](<148. Gabonaraktár/>) | Súlyozott medián | Prefixösszegekkel minden helyre O(1) költség, majd a legkisebb kiválasztása | 3 | Magyarázás | ✅ kész |
| 149 | [Kép elemzés](<149. Kép elemzés/>) | Összefüggő komponensek | Fényességértékenként szélsőindexek, egymást követő értékek szakaszainak összegzése | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 150 | [Repülők indulása és érkezése](<150. Repülők indulása és érkezése/>) | Csúszóablak: legrövidebb szakasz | Csúszóablak fajtánkénti számlálóval, a legrövidebb teljes szakasz | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 151 | [Körutazás](<151. Körutazás/>) | Csúszóablak: legfeljebb K előfordulás | Kétmutatós csúszóablak városonkénti számlálóval | 2 | Magyarázat | ✅ kész |
| 152 | [Szálloda](<152. Szálloda/>) | Csúszóablak: összeg és minimum | Csúszóablakos összeg K telekre, a minimum és az összes minimális kezdőpozíció kiírása | 2 | Bevezetés | ✅ kész |
| 153 | [Vásárlás](<153. Vásárlás/>) | Kétmutatós bejárás | Két mutató a rendezett sorozatokon: minden i-hez a legkisebb j, amellyel az összeg eléri X-et. | 3 | Magyarázat | ✅ kész |
| 154 | [Két búzaraktár](<154. Két búzaraktár/>) | Prefixösszeg, szakaszok | Határpont-bejárás, szakaszonkénti optimum prefixösszegekkel. | 4 | Mélyebb megértés | ✅ kész |
| 155 | [Fénykép elemzés](<155. Fénykép elemzés/>) | Osztályok, befoglaló téglalap | Értékenként számolunk; a szomszédos előforduló fényességek egy osztályt alkotnak. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 156 | [Állás](<156. Állás/>) | Szegmensfa, söprővonal | Söprővonal: l csökkenésével tiltott intervallumok, szegmensfa range-add és legjobboldalibb nulla. | 3 | Mélyebb megértés | ✅ kész |
