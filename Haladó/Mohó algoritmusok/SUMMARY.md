# Mohó algoritmusok – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 82 feladat · ✅ kész 46 · ❌ hibás 0 · 🟡 kézi 34 · 🟡 nincs minta/speciális 2 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [ABC Ládapakolás](<1. ABC Ládapakolás */>) | Láncfedés, Dilworth-tétel | Dilworth-tétel: a leghosszabb A*B*C* részsorozat hossza, O(N) DP három állapottal. | 1 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 2 | [Alkatrészgyártás](<2. Alkatrészgyártás ***/>) | Mohó: ütemezés | Gyártási idő szerinti csökkenő sorrend, előkészítési prefixösszeggel | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 3 | [Alkatrészt gyűjtő robot](<3. Alkatrészt gyűjtő robot **/>) | Dilworth, láncfedés | Mohó láncfedés nemcsökkenő oszlopsorozatokkal, multiset-tel. | 2 | Mélyebb megértés | ✅ kész |
| 4 | [Asztalok](<4. Asztalok ***/>) | Intervallumok, mohó | időbeli söprés + távozás szerinti min-kupac: a legkorábban távozó vendég távozásakor új asztal a legkorábban távozó legfeljebb K jelenlévővel | 3 | Magyarázat | ✅ kész |
| 5 | [Autó](<5. Autó */>) | Szimuláció, mohó | a tesztek szerinti értelmezés: tankolások a megadott sorrendben, legrövidebb elég előtag (elakadáskor a következő tankolás bevonása) | 1 | Bevezetés | ✅ kész |
| 6 | [Bíróság büntetéssel](<6. Bíróság büntetéssel ***/>) | Határidő, min-kupac | Határidő szerinti bejárás min-kupaccal; a legkisebb díjú ügy kiesik, DSU a szabad napra | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 7 | [Dominó](<7. Dominó ***/>) | Dinamikus programozás | DP a lánc két végpontjára (10x10 tábla), dominónként átmenetekkel. | 3 | Magyarázat | ✅ kész |
| 8 | [Fadöntés](<8. Fadöntés ***/>) | Mohó: láncreakció, intervallumfedés | Láncreakció-végpontok balról jobbra, majd mohó intervallumfedés. | 3 | Mélyebb megértés | ✅ kész |
| 9 | [Fénykép](<9. Fénykép **/>) | Mohó: intervallum-lefogás | A legkorábban távozó lefedetlen vendég távozása előtti utolsó pillanatban fotózunk, és a lefedett vendégeket kihagyjuk. | 2 | Magyarázat | ✅ kész |
| 10 | [Fényképész a rendezvényen](<10. Fényképész a rendezvényen ***/>) | Intervallumok, mohó | legkésőbbi fotó (min U-1 a hátralévőkre), kihívásonként T hosszú ablak és legfeljebb D kép; hátulról minimum + prefix összeg | 3 | Magyarázat | ✅ kész |
| 11 | [Fényképész-menetek](<11. Fényképész-menetek ***/>) | Intervallum-lefedés | Mohó: a legkorábban távozó lefedetlen vendég távozási idejétől indul új menet. | 3 | Magyarázat | ✅ kész |
| 12 | [Gépek](<12. Gépek **/>) | Határidős ütemezés | Prefix-korlát adja a gépszámot; a munkákat határidő szerint, a legkésőbbi szabad napra ütemezzük (DSU). | 2 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 13 | [Hangosítás](<13. Hangosítás ***/>) | Dinamikus programozás | Napi maximális nem átfedő rendezvényszám (befejezési idő szerinti mohó), majd DP az előrefizetési blokkokon. | 3 | Mélyebb megértés | ✅ kész |
| 14 | [Hegy](<14. Hegy ***/>) | Hall-feltétel, suffix-összeg | Suffix-összegek hányadosának minimuma (Hall-feltétel). | 3 | Magyarázat | ✅ kész |
| 15 | [Intervallumok](<15. Intervallumok ***/>) | Intervallumgráf, domináló halmaz | Mohó: a legkisebb jobb végű nem dominált intervallum legjobb végű szomszédát választjuk. | 3 | Mélyebb megértés | ✅ kész |
| 16 | [Kemping](<16. Kemping **/>) | Mohó: intervallum-ütemezés | Végidő szerinti rendezés, a legkésőbb felszabaduló faházhoz rendelés multihalmazzal | 2 | Magyarázat | ✅ kész |
| 17 | [Koncert](<17. Koncert ***/>) | Mohó: párosítás | Jobb végpont szerinti rendezés, a legkisebb szabad hely foglalása DSU-val | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 19 | [Konténeroszlopok](<19. Konténeroszlopok **/>) | Mohó: láncfelbontás | Legkisebb, x-nél nem kisebb tetejű oszlop választása, bitmezős keresés | 2 | Magyarázat | ✅ kész |
| 20 | [Ládák balról jobbra](<20. Ládák balról jobbra **/>) | Mohó: láncfelbontás | Legkisebb, x-nél nagyobb legbelső méretű csomag választása multihalmazzal | 2 | Magyarázat | ✅ kész |
| 21 | [Ládapakolás](<21. Ládapakolás ***/>) | Mohó, szakaszokra bontás | A leghosszabb egyhegyű, különböző méretű szakaszt vágjuk le balról, mohón. | 3 | Mélyebb megértés | ✅ kész |
| 22 | [Ládapakolás egymásba](<22. Ládapakolás egymásba **/>) | Láncolt lista, mohó törlés | Értékben és pozícióban is szomszédos halmok egyesítése mohó törléssel, láncolt listákkal. | 2 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 23 | [Lefedés](<23. Lefedés ***/>) | Mohó, intervallumok lefedése | Rések mohó elvágása a legnagyobb pozitív nettó nyereségűnél, lusta kupaccal. | 3 | Mélyebb megértés | ✅ kész |
| 24 | [Legnagyobb hasznú munkák](<24. Legnagyobb hasznú munkák ***/>) | Ütemezés határidőkkel | Határidő szerinti mohó kiválasztás minimum-kupaccal, majd napok DSU-val történő hozzárendelése. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 25 | [Legtöbb vírus](<25. Legtöbb vírus ***/>) | Különbségi tömb, intervallumok | Különbségi tömb: minden vírushoz a kedvező kezdőidők szakasza, prefixösszeggel végigjárva. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 26 | [Lift-menetek](<26. Lift-menetek ***/>) | Különbségi tömb, alsó korlát | Szintközönkénti terhelés különbségi tömbbel, irányonként ceil(terhelés/K) menet, a maximum. | 3 | Mélyebb megértés | ✅ kész |
| 27 | [Mekk Elek](<27. Mekk Elek **/>) | Mohó: határidős ütemezés | Határidő szerinti rendezés, legkésőbbi szabad napra helyezés DSU-val. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 28 | [Mekk Elek munkái](<28. Mekk Elek munkái **/>) | Intervallum-ütemezés | Befejezési idő szerinti rendezés, mohó kiválasztás zárt intervallumokkal. | 2 | Bevezetés | 🟡 kézi ellenőrzés |
| 29 | [Minél több fénykép](<29. Minél több fénykép ***/>) | Kupac, szimuláció | Időben haladó szimuláció, minimum-kupac a távozási idők szerint. | 3 | Magyarázat | ✅ kész |
| 30 | [Minibusz](<30. Minibusz ***/>) | Intervallum-kiválasztás kapacitással | Utasok szerinti rendezés, aktív halmaz, a legkésőbb célba érő utas elengedése. | 3 | Mélyebb megértés | ✅ kész |
| 31 | [Mozi](<31. Mozi ***/>) | Intervallum-párosítás, DSU | Felső határ szerinti rendezés, legkisebb szabad pont DSU-val. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 32 | [Munkák](<32. Munkák **/>) | Ütemezés: határidők | Határidő szerinti rendezés, majd a kumulált idő és a határidő különbségének maximuma. | 2 | Magyarázat | ✅ kész |
| 33 | [Olimpiai láng](<33. Olimpiai láng ***/>) | Intervallumlefedés | Mohó intervallumlefedés: mindig a legtávolabbra érő, elérhető futót választjuk. | 3 | Magyarázat | ✅ kész |
| 34 | [Olimpiai staféta](<34. Olimpiai staféta/>) | Intervallumlefedés | Mohó intervallumlefedés prioritási sorral: az elérhető futók közül a legtovább érőt választjuk. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 35 | [Páros fotózás](<35. Páros fotózás ***/>) | Intervallum-párosítás | Távozás szerinti feldolgozás, párosítás a legkorábban távozó, még bent lévő párosítatlan vendéggel. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 36 | [Rendezvény](<36. Rendezvény **/>) | Intervallumütemezés | Befejezési idő szerinti mohó; a szabad terem közül a később felszabaduló kapja az előadást. | 2 | Magyarázat | ✅ kész |
| 37 | [Rúd darabolás](<37. Rúd darabolás */>) | Huffman-fa | Huffman-stratégia: a két legkisebb darab összevonása min-heapben, a fa preorder bejárással kiírva. | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 38 | [Sejtek](<38. Sejtek ***/>) | Intervallum-söprés | Elpusztulási idő szerinti söprés, multisetben a K. legnagyobb keletkezési idő adja E-t. | 3 | Magyarázat | ✅ kész |
| 39 | [Strázsa](<39. Strázsa ***/>) | Intervallum-lefedés | Mohó láncolás: mindig a legtovább érő, már elkezdett jelentkezőt választjuk. | 3 | Magyarázat | ✅ kész |
| 40 | [Számok intervallumba](<40. Számok intervallumba ***/>) | Dinamikus programozás | Dinamikus programozás a szomszédos hézagokon: nem egymás melletti, maximális összegű vágáshalmaz. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 41 | [Szemtanúk](<41. Szemtanúk ***/>) | Intervallum-stabbing | Mohó stabbing: a legkorábbi lefedetlen eseményhez a legkésőbb távozó lefedő vendéget választjuk. | 3 | Magyarázat | ✅ kész |
| 42 | [Szilveszteri tévézés](<42. Szilveszteri tévézés **/>) | Intervallum-ütemezés | Befejezési idő szerinti mohó kiválasztás: mindig a legkorábban végződő, még elkezdhető filmet vesszük. | 2 | Bevezetés | 🟡 kézi ellenőrzés |
| 43 | [Termek](<43. Termek **/>) | Intervallumok színezése | Kezdési idő szerinti söprés, minimumkupac a termek szabadulási idejével; csak teli esetén nyitunk újat. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 44 | [Tópart](<44. Tópart ***/>) | Mohó: körös intervallumütemezés | Kör egyenessé vágása, ugrótábla (bináris emelés) és mohó intervallumválasztás. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 45 | [Ütemezés](<45. Ütemezés ***/>) | Mohó: ütemezés határidővel | Határidő szerinti rendezés, és a leghosszabb elem eldobása túlcsordulás esetén. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 46 | [Vasút](<46. Vasút */>) | Mohó: megállók kiválasztása | Mohó bejárás balról, az utolsó állomás előtti megállót a T(N)-K határig keresve. | 1 | Bevezetés | ✅ kész |
| 47 | [Vendégség](<47. Vendégség **/>) | Prefixösszeg: találkozások | A találkozások száma a nem találkozók darabszámából adódik prefix- és szuffixösszeggel. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 48 | [Vizirendőr](<48. Vizirendőr **/>) | Mohó: intervallumlefedés | Az első lefedetlen településhez a folyásirányban legtávolabbi, még elérhető állomást választjuk. | 2 | Magyarázat | ✅ kész |
| 49 | [WiFi](<49. WiFi **/>) | Mohó: pontlefedés | Balról jobbra, az első lefedetlen házhoz a hatótávolságon belül legjobbra eső házra telepítünk. | 2 | Bevezetés | ✅ kész |
| 50 | [Zenekar](<50. Zenekar **/>) | Intervallum-párosítás | Határidő (u) szerinti rendezés, majd a legkorábbi szabad nap kiválasztása DSU-val. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 51 | [Alvállalkozó](<51. Alvállalkozó */>) | Ütemezés: határidők | Határidő szerinti bejárás: munkát vállalunk, ha a (k+1). napra még belefér. | 1 | Bevezetés | ✅ kész |
| 52 | [Beruházás](<52. Beruházás **/>) | Ütemezés: vállalkozók | Alsó korlát: K = max ceil(db(H≤d)/d), majd a határidő szerint sorban kiosztjuk a helyeket. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 53 | [Hegymászó visszafelé is](<53. Hegymászó visszafelé is ****/>) | Mohó szimuláció: visszaút | Felvétel a szabad hely szerint, a táborban K_{i-1} tartalékot hagyunk, szükség esetén a hátizsákból. | 4 | Mélyebb megértés | ✅ kész |
| 54 | [Csoportképek](<54. Csoportképek ***/>) | Intervallumok, mohó | időbeli söprés + távozás szerinti min-kupac: a távozó vendég a K legkorábban távozó jelenlévővel kerül képre (K<=2-re optimális, K>=3-ra a szerzői mohó, nem mindig optimális) | 3 | Magyarázat | 🟡 nincs minta |
| 55 | [Hegymászó](<55. Hegymászó **/>) | Mohó: minimum megállás | Az oda-vissza utat egy sorozatba fűzzük, és mindig a legtávolabbi táborig megyünk pihenés nélkül. | 2 | Magyarázat | ✅ kész |
| 56 | [Minimális tankolás szám](<56. Minimális tankolás szám */>) | Tankolás: prioritási sor | Prioritási sor: ha nem érünk a következő kútig vagy a célig, a legnagyobb tankolást vesszük. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 57 | [Ütemezés](<57. Ütemezés ***/>) | Ütemezés, határidő | Moore–Hodgson: határidő szerint haladva, max-kupaccal a leghosszabb esemény kiejtése | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 58 | [Múzeum](<58. Múzeum ***/>) | Intervallum-hozzárendelés | Két független intervallum-hozzárendelés (sor és oszlop), mohó, jobb végpont szerinti kupaccal | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 59 | [Konténer pakolás](<59. Konténer pakolás ***/>) | Mohó: torony-számlálás | Jobbról balra mohó torony-számlálás, méretenként és szabad helyenként nyilvántartva | 3 | Mélyebb megértés | 🟡 nincs minta |
| 60 | [Konténer átpakolás](<60. Konténer átpakolás ***/>) | Konténer-mozgatás | Jobbról balra mohó toronyválasztás, a mozgatások fa-bejárással sorrendezve | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 61 | [Asztalok](<61. Asztalok **/>) | Intervallum-csoportosítás | Távozás szerinti mohó: közös időpontos asztal, legfeljebb K vendéggel | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 62 | [Munkagépek](<62. Munkagépek/>) | Prefixösszeg-korlát | Gépszám: a határidő-prefixek alsó korlátjainak maximuma. | 2 | Bevezetés | ✅ kész |
| 63 | [Csapatépítés](<63. Csapatépítés/>) | Intervallumlefedés | Balról jobbra mohó lefedés max-kupaccal, ugrással a fedhetetlen pontoknál. | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 64 | [Tanúk](<64. Tanúk/>) | Pontfedés intervallumokkal | Pontfedés: időrendi bejárás, a legtovább maradó vendég választása max-kupaccal. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 65 | [Filmgyártás](<65. Filmgyártás/>) | Pontfedés, kettős célfüggvény | Maximális lefedés, azon belül minimális filmesszám: időrendi pontfedés max-kupaccal. | 3 | Magyarázat | ✅ kész |
| 66 | [Kereskedő](<66. Kereskedő/>) | Prefixmaximum, tie-break | Rögzített x-hez prefixmaximum a B[y]-Ky értékekre, majd tie-breakkel a legjobb pár. | 3 | Magyarázat | ✅ kész |
| 67 | [Határidős ütemezés](<67. Határidős ütemezés/>) | Határidős ütemezés | Határidő szerint haladva a leghosszabb munka kiejtése max-kupaccal (Moore–Hodgson). | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 68 | [Segély](<68. Segély/>) | Bináris keresés | Bináris keresés a D különbségre, minden prefixre alsó korlát ellenőrzése. | 3 | Mélyebb megértés | ✅ kész |
| 69 | [Jelzőlámpák](<69. Jelzőlámpák/>) | Láncfedés (Dilworth) | Rendezés után mohó láncbontás: minden pont a legnagyobb még jó láncába kerül. | 3 | Magyarázat | ✅ kész |
| 70 | [Utazásszervezés](<70. Utazásszervezés */>) | Intervallum-ütemezés | Mohó elfogadás kezdőnap szerint, prioritási sorral a foglalt idegenvezetőkről. | 1 | Magyarázat | ✅ kész |
| 71 | [Fasor](<71. Fasor **/>) | Csúszóablakos maximum | Két irányú csúszóablakos maximum, az első olyan fa keresése. | 2 | Magyarázat | ✅ kész |
| 72 | [Ládapakolás raktárban](<72. Ládapakolás raktárban ***/>) | Dinamikus programozás | DP az alapok számával, az utolsó torony jobb végpozíciója szerint. | 3 | Mélyebb megértés | ✅ kész |
| 73 | [Részekre](<73. Részekre */>) | Mohó: láncfelbontás | Mohó láncillesztés: a legnagyobb, x-nél kisebb végű láncra fűzés (multiset). | 1 | Magyarázat | ✅ kész |
| 74 | [Kamionok](<74. Kamionok **/>) | Mohó: kamionütemezés | Kapacitásfüggvény adja a kamionszámot; min-heap a legkorábbi érkezésekhez. | 2 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 75 | [Robotok](<75. Robotok **/>) | Mohó: láncfedés | Mohó láncfedés: a legnagyobb, a ponté alatti oszlopú láncra fűzés, multisettel. | 2 | Magyarázat | ✅ kész |
| 76 | [Tevafarm](<76. Tevafarm ***/>) | Fa dinamikus programozás | Fa-DP: vagy a csúcsot választjuk (részfája tiltott), vagy a gyerek-részfákat optimalizáljuk. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 77 | [Óvoda](<77. Óvoda ***/>) | Mohó: kapacitáskiosztás | Szerepenként a legnagyobb sírásúak maradnak, a túlfoglalást és az üres szerepeket korrigálva. | 3 | Mélyebb megértés | ✅ kész |
| 78 | [Ügyelet](<78. Ügyelet **/>) | Mohó: intervallumlefedés | Időben haladva, lefedettség 2 alá esésekor a leghosszabb ideig élő jelentkező (max-heap). | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 79 | [Többszörös összefésülés](<79. Többszörös összefésülés/>) | Mohó: optimális összefésülés | Mindig a két legkisebb sorozatot egyesítjük, min-heappel (Huffman-stratégia). | 2 | Magyarázat | ✅ kész |
| 80 | [Tejeskocsik](<80. Tejeskocsik/>) | Sorozat darabolása, mohó | mindig a leghosszabb jó szakasz (összeg <= K, időtáv <= T); azonos idejű párnál a nagyobb beférő tétel marad a kocsiban | – | Bevezetés | ✅ kész |
| 81 | [Tűzijáték](<81. Tűzijáték/>) | Mohó: távolságkorlátos kiválasztás | A telephelytől mindkét irányban a legközelebbi még megengedett településsel haladunk. | 1 | Bevezetés | ✅ kész |
| 82 | [Vállalkozó](<82. Vállalkozó/>) | Mohó: határidős ütemezés | Határidő szerint rendezve elfogadunk egy munkát, ha a prefix-kapacitás még belefér. | 2 | Magyarázat | ✅ kész |
| 83 | [Zárójelek](<83. Zárójelek/>) | Mohó: zárójelezés rendezése | Nemnegatív összegűek mn szerint, negatívak (sum-mn) szerint rendezve, majd szimulációval ellenőrzünk. | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
