# Programozási tételek: minimum, maximum számítás – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 91 feladat · ✅ kész 84 · ❌ hibás 0 · 🟡 kézi 6 · 🟡 nincs minta/speciális 1 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Előrejelzések maximuma legnagyobb](<1. Előrejelzések maximuma legnagyobb */>) | Maximumkeresés | Soronkénti maximum számítása, majd egy menetes maximumkiválasztás a települések között. | 1 | Bevezetés | ✅ kész |
| 2 | [Gyanús hőmérsékletek](<2. Gyanús hőmérsékletek */>) | Maximumkiválasztás: szomszédok | Belső mérések eltérése a szomszédok átlagától, egész számokkal (kétszeres eltérés), maximumkiválasztás. | 1 | Magyarázat | ✅ kész |
| 3 | [Legdrágább lakás](<3. Legdrágább lakás */>) | Maximumkiválasztás: sorszám | Egy menetes maximumkiválasztás az árra, szigorú összehasonlítással. | 1 | Bevezetés | ✅ kész |
| 4 | [Legfiatalabban végzett hallgató](<4. Legfiatalabban végzett hallgató */>) | Maximumkiválasztás: életkor | Diplomázáskori életkor (végzés éve − születési év) minimumának kiválasztása | 1 | Bevezetés | ✅ kész |
| 5 | [Leghidegebb hőmérséklet a Balatonon](<5. Leghidegebb hőmérséklet a Balatonon */>) | Minimumkiválasztás | Egy menetes minimumkiválasztás a beolvasás közben. | 1 | Bevezetés | ✅ kész |
| 6 | [Leghidegebb nap](<6. Leghidegebb nap */>) | Minimumkiválasztás | Minimumkeresés egy bejárással, az első mérés kezdőértékkel | 1 | Bevezetés | ✅ kész |
| 7 | [Leghosszabb intervallum mikor senki sem közlekedett](<7. Leghosszabb intervallum mikor senki sem közlekedett */>) | Maximumkiválasztás | Szomszédos időpontok különbségének maximuma, egyetlen bejárással | 1 | Bevezetés | ✅ kész |
| 8 | [Legidősebb dolgozó](<8. Legidősebb dolgozó */>) | Maximumkiválasztás | Lineáris maximumkiválasztás: egyenlő kornál a korábbi sorszám marad | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 9 | [Legidősebb ember](<9. Legidősebb ember */>) | Maximumkiválasztás | Egy menetes minimumkiválasztás az (év, hónap, nap) dátumok egyetlen számmá alakított kulcsával | 1 | Bevezetés | ✅ kész |
| 10 | [Legjobb idejű futóverseny eredmény helyezése](<10. Legjobb idejű futóverseny eredmény helyezése */>) | Minimumkeresés | Időeredmény átszámítása másodpercre, majd egy menetes minimumkiválasztás a versenyek között. | 1 | Bevezetés | ✅ kész |
| 11 | [Legkisebb bortermésű év](<11. Legkisebb bortermésű év */>) | Minimumkeresés | Egy menetes minimumkiválasztás: az eddigi legkisebb mennyiség és a sorszám nyilvántartása. | 1 | Bevezetés | ✅ kész |
| 12 | [Legkisebb különbség a min es max hőmérséklet között](<12. Legkisebb különbség a min es max hőmérséklet között */>) | Minimumkeresés | Napi különbség (max − min) számítása, majd egy menetes minimumkiválasztás. | 1 | Bevezetés | ✅ kész |
| 13 | [Legkorábbi környezetvédelmi világnap](<13. Legkorábbi környezetvédelmi világnap */>) | Minimumkiválasztás | Egy menetes minimumkiválasztással az évszám szerint; az ország sorszámát tároljuk, 0 esetén kérdőjel. | 1 | Bevezetés | ✅ kész |
| 14 | [Legközelebbi események](<14. Legközelebbi események */>) | Szomszédos különbségek minimuma | Rendezett adatoknál a szomszédos évek különbségének minimumát keressük; egyenlőnél az első pár marad. | 1 | Magyarázat | ✅ kész |
| 15 | [Legmelegebb nap](<15. Legmelegebb nap */>) | Maximumkiválasztás | Egy menetes maximumkeresés indexszel, szigorú összehasonlítással, így az első előfordulás marad. | 1 | Bevezetés | ✅ kész |
| 16 | [Legmesszebbi település Kukutyintól](<16. Legmesszebbi település Kukutyintól */>) | Maximumkiválasztás | Egy menetes maximumkeresés a Kukutyintól mért távolság szerint, szigorú összehasonlítással az első marad. | 1 | Bevezetés | ✅ kész |
| 17 | [Legnagyobb hórétegű sípálya](<17. Legnagyobb hórétegű sípálya */>) | Maximumkiválasztás: sorszám | Egyszeri bejárás, menet közben az eddigi legnagyobb érték és sorszám nyilvántartása. | 1 | Bevezetés | ✅ kész |
| 18 | [Legnagyobb hőmérsékletváltozás két nap között](<18. Legnagyobb hőmérsékletváltozás két nap között */>) | Maximumkiválasztás: párok | Szomszédos párok bejárása, mindkét keresztkülönbség abszolút értékének maximuma. | 1 | Magyarázat | ✅ kész |
| 19 | [Legnagyobb különbség a min es max hőmérséklet között](<19. Legnagyobb különbség a min es max hőmérséklet között */>) | Maximumkiválasztás: különbség | Napi maximum és minimum különbségét számoljuk, és a legnagyobbat keressük, holtversenynél az elsőt. | 1 | Bevezetés | ✅ kész |
| 20 | [Legnagyobb lélekszámú helység a Kihívás napján](<20. Legnagyobb lélekszámú helység a Kihívás napján */>) | Maximumkiválasztás | Maximumkiválasztás egy bejárásban: a legnagyobb lélekszám sorszámának és résztvevőinek nyilvántartása. | 1 | Bevezetés | ✅ kész |
| 21 | [Legnagyobb mennyiségű teavásárlás](<21. Legnagyobb mennyiségű teavásárlás */>) | Maximumkiválasztás | Maximumkiválasztás egy bejárásban, a legnagyobb egyedi mennyiség sorszámának követésével. | 1 | Bevezetés | ✅ kész |
| 22 | [Legnagyobb mértékben nőtt légszennyeződés](<22. Legnagyobb mértékben nőtt légszennyeződés */>) | Maximális különbség | Napi különbség (este − reggel) maximuma egy bejárásban, 0 kezdőértékkel. | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 23 | [Legrövidebb útfelújítás](<23. Legrövidebb útfelújítás */>) | Minimumkiválasztás | Minden felújítás hosszának (V − K + 1) minimuma egy bejárásban. | 1 | Magyarázat | ✅ kész |
| 24 | [Legszennyezettebb nap](<24. Legszennyezettebb nap */>) | Maximumkiválasztás | Egy menetes maximumkiválasztás a nap sorszámával, szigorú összehasonlítással. | 1 | Bevezetés | ✅ kész |
| 25 | [Legtöbb eső-egy-nap](<25. Legtöbb eső-egy-nap */>) | Maximumkiválasztás | Egy menetes maximumkiválasztás: az eddigi legnagyobb mennyiség és a nap sorszáma, szigorú összehasonlítással. | 1 | Bevezetés | ✅ kész |
| 26 | [Legtöbb megfigyelt jármű egy helyen](<26. Legtöbb megfigyelt jármű egy helyen */>) | Számlálás: maximum | Helyenkénti számláló tömb, majd a legnagyobb számláló keresése, egyenlőségnél a kisebb sorszámmal. | 1 | Bevezetés | ✅ kész |
| 27 | [Legtöbbször lefényképezett terület műholdról](<27. Legtöbbször lefényképezett terület műholdról */>) | Különbségi tömb: 2D | Imos-módszer: 2D különbségi tömb a téglalapok sarkaival, majd összegzés és a maximum keresése. | 1 | Magyarázat | ✅ kész |
| 28 | [Legvastagabb jég a Balatonon](<28. Legvastagabb jég a Balatonon */>) | Maximumkiválasztás: sorszám | Egy menetes maximumkiválasztás a nap sorszámával, szigorú összehasonlítással. | 1 | Bevezetés | ✅ kész |
| 29 | [Leggyorsabb áradás](<29. Leggyorsabb áradás ***/>) | Szakaszok: legközelebbi pár | Szakaszok gyűjtése kategóriánként, majd egy menetes legközelebbi pár keresés. | 3 | Mélyebb megértés | ✅ kész |
| 30 | [Maximális egyedszámú helységek](<30. Maximális egyedszámú helységek */>) | Maximumkiválasztás: sorszám | Fajonként külön maximumkiválasztás soronkénti beolvasással, a helység sorszámát tárolva. | 1 | Bevezetés | 🟡 nincs minta |
| 31 | [Maximális utasszám a villamoson](<31. Maximális utasszám a villamoson */>) | Prefixösszeg, maximum | Lineáris bejárás: futó utaslétszám, minden állomás után a maximum frissítése. | 1 | Bevezetés | ✅ kész |
| 32 | [Múzeumban leghosszabb ideig szolgálatban lévő őr](<32. Múzeumban leghosszabb ideig szolgálatban lévő őr */>) | Maximumkiválasztás | Lineáris bejárás: a zárt intervallum hosszának (U − E + 1) maximumát tartjuk nyilván. | 1 | Bevezetés | ✅ kész |
| 33 | [Utazási iroda legtávolabbi városa](<33. Utazási iroda legtávolabbi városa */>) | Maximumkiválasztás, döntetlen | Lineáris bejárás, a legnagyobb távolság és a hozzá tartozó legkisebb ár nyilvántartása. | 1 | Bevezetés | ✅ kész |
| 34 | [Legnagyobb hőmérséklet eltérés](<34. Legnagyobb hőmérséklet eltérés */>) | Csúszóablak, max-min | Fix hosszú (7) csúszóablak: minden szakasz max−min különbsége, egyenlőségnél a korábbi kezdőnap. | 1 | Bevezetés | ✅ kész |
| 35 | [Földrengések](<35. Földrengések */>) | Maximumkiválasztás | Időpontok másodpercre váltása, szomszédos különbségek maximuma és minimuma. | 1 | Bevezetés | ✅ kész |
| 36 | [Ideális lakás](<36. Ideális lakás **/>) | Maximumkiválasztás | Anti-érték minimumának kiválasztása egy menetben, döntetlennél ár szerint. | 2 | Magyarázat | ✅ kész |
| 37 | [Kalapácsvető verseny győztese](<37. Kalapácsvető verseny győztese ***/>) | Maximumkiválasztás | Versenyzők dobásainak csökkenő rendezése, lexikografikus maximum, holtverseny kiírása. | 3 | Magyarázat | ✅ kész |
| 38 | [Legcsapadékosabb hét](<38. Legcsapadékosabb hét **/>) | Maximumkiválasztás | Hetenkénti összegzés és maximumkiválasztás, egyenlőségnél a korábbi hét marad. | 2 | Bevezetés | ✅ kész |
| 39 | [Rendezvénysorozat legelfoglaltabb napja](<39. Rendezvénysorozat legelfoglaltabb napja **/>) | Maximumkiválasztás: prefixösszeg | Különbségi tömb a foglalások kezdő- és végnapjára, majd prefixösszeg-bejárás | 2 | Magyarázat | ✅ kész |
| 40 | [Legnagyobb dobások](<40. Legnagyobb dobások */>) | Maximumkiválasztás: soronként | Soronkénti maximumkiválasztás, 0 kezdőértékkel a sikertelen dobások kiszűrésére | 1 | Bevezetés | ✅ kész |
| 41 | [Üzemanyag tartály mérete](<41. Üzemanyag tartály mérete */>) | Maximumkiválasztás: szint-követés | Egyszeri bejárás: fogyasztás levonása, tankolás hozzáadása, a legnagyobb szint követése | 1 | Bevezetés | ✅ kész |
| 42 | [Legnagyobb haszon](<42. Legnagyobb haszon */>) | Maximumkiválasztás, feltétel | Feltételes maximumkiválasztás egy menetben: csak a 2. héten többet fogyó termékek hasznát vizsgáljuk. | 1 | Bevezetés | ✅ kész |
| 43 | [Távoli bolygó](<43. Távoli bolygó/>) | Különbségtömb, prefixösszeg | Különbségtömb (+1 születéskor, −1 halálozás után), prefix összeggel az élők maximuma. | 2 | Magyarázat | ✅ kész |
| 44 | [Szobafoglalások](<44. Szobafoglalások/>) | Különbségtömb, intervallumok | Félnyílt [K, V) intervallumok különbségtömbje, prefix összeggel az éjszakánkénti foglaltság maximuma. | 2 | Magyarázat | ✅ kész |
| 45 | [Autópálya](<45. Autópálya/>) | Szomszédos párok, irányított számlálás | Autónként első–utolsó észlelés időkülönbsége, szomszédos irányított párok számlálása, maximum kiválasztása. | 3 | Magyarázat | ✅ kész |
| 46 | [Születések](<46. Születések/>) | Intervallumkeresés, számlálás | Évenkénti darabszám-tömb; kezdőévenként a legrövidebb felet lefedő intervallum; majd a leghosszabb üres szakasz. | 3 | Magyarázat | ✅ kész |
| 47 | [Autópálya](<47. Autópálya/>) | Minimumkiválasztás csoportonként | Autónkénti észlelési idők, szakaszonként és irányonként a legkisebb menetidő kiválasztása. | 3 | Magyarázat | ✅ kész |
| 48 | [Napszámosok](<48. Napszámosok/>) | Összegzés, maximumkiválasztás | Keresetek (V−K+1)·B összegzése; a legtöbbet kereső egy menetben, holtversenyben a több napot dolgozó. | 2 | Bevezetés | ✅ kész |
| 49 | [Osztályzatok](<49. Osztályzatok/>) | Maximumkiválasztás csoportonként | Osztályzatonként egy maximum, a pontszámot a négy ponthatárhoz hasonlítva. | 2 | Bevezetés | ✅ kész |
| 50 | [Kihalt állatok](<50. Kihalt állatok/>) | Prefixösszeg | Különbségi tömb: minden faj intervallumának határait jelöljük, prefixösszeggel számoljuk az éveket. | 2 | Magyarázat | ✅ kész |
| 51 | [Születésnapok](<51. Születésnapok/>) | Dátumszámítás | Dátumok napsorszámra váltása, a névnap távolsága három év közül, globális minimum. | 3 | Magyarázat | ✅ kész |
| 52 | [Sikertelen napok](<52. Sikertelen napok/>) | Prefixmaximum | Sikeres (rekord) napok szakaszolása, a leghosszabb sikertelen szakasz egy menetben. | 2 | Bevezetés | ✅ kész |
| 53 | [Sikeres sorozatok](<53. Sikeres sorozatok/>) | Futó maximum | Egyszeri bejárás, futó maximum és futó sorozathossz. | 2 | Bevezetés | ✅ kész |
| 54 | [Játékállások](<54. Játékállások/>) | Pontszámok, maximum | Pontszámtömb frissítése, minden játszma után maximumkeresés és kiírás. | 2 | Bevezetés | ✅ kész |
| 55 | [Fogadások](<55. Fogadások/>) | Maximum, rendezett halmaz | Rendezett halmaz pénz szerint, pénzösszegek darabszámával. | 4 | Magyarázat | 🟡 kézi ellenőrzés |
| 56 | [Vizsga](<56. Vizsga/>) | Intervallumok, ablak | Befejezési időpontok ablakszámlálása, rések és összevont foglalt blokkok maximuma. | 3 | Magyarázat | ✅ kész |
| 57 | [Maximális növekedés](<57. Maximális növekedés/>) | Minimum-maximum keresés | Következő kisebb elem veremmel, a tartomány maximumának összevonásával | 3 | Mélyebb megértés | ✅ kész |
| 58 | [Hideg és meleg napok](<58. Hideg és meleg napok/>) | Prefixösszeg, számlálás | Hideg -1, meleg +1 előjelezés, majd az egyenlegek gyakoriságának számlálása | 3 | Magyarázat | ✅ kész |
| 59 | [Ügyelet](<59. Ügyelet/>) | Számlálás, leghosszabb szakasz | Napi gyakorisági tömb, majd egy bejárással a leghosszabb lefedett szakasz keresése | 2 | Bevezetés | ✅ kész |
| 60 | [Földrengések](<60. Földrengések/>) | Intervallumok, rendezés | Intervallumok egy listába gyűjtése, rendezés, balról jobbra haladó maximális rés keresése. | 2 | Bevezetés | ✅ kész |
| 61 | [Két csoportra osztás](<61. Két csoportra osztás/>) | Szomszédos különbség | Pontszámok jelölőtömbbel, szomszédos előfordulók különbségének maximuma. | 2 | Bevezetés | ✅ kész |
| 62 | [Rövid földrengések](<62. Rövid földrengések/>) | Időpontok, szabad percek | Időpontok rendezése, a közöttük lévő szabad percek maximuma. | 1 | Bevezetés | ✅ kész |
| 63 | [Határőrök](<63. Határőrök/>) | Különbségi tömb, prefixösszeg | Különbségi tömb (prefixösszeg), leghosszabb nem nulla szakasz, majd maximális nap keresése a szakaszon belül. | 3 | Magyarázat | ✅ kész |
| 64 | [Földrengésmentes időszak](<64. Földrengésmentes időszak/>) | Intervallumok, rések maximuma | Intervallumok kezdőperc szerinti rendezése, majd a két intervallum közötti szabad percek maximuma. | 3 | Magyarázat | ✅ kész |
| 65 | [Közeli legmelegebb nap](<65. Közeli legmelegebb nap/>) | Csúszóablak, maximumkiválasztás | Csúszóablak-maximum monoton deque-kel, indexekkel, O(N) időben. | 2 | Magyarázat | ✅ kész |
| 66 | [Völgy](<66. Völgy ***/>) | Monoton verem, völgyek | Csökkenő monoton verem, kivételkor völgy-párok képzése; a legnagyobb r-l a válasz. | 3 | Mélyebb megértés | ✅ kész |
| 67 | [Gyros](<67. Gyros **/>) | Erőforrás-elosztás, maximum | Végigpróbáljuk a vegyes gyrosok számát; a többi típus ebből független, egyszerű képlettel adódik. | 2 | Magyarázat | ✅ kész |
| 68 | [Dinnyeárusok](<68. Dinnyeárusok/>) | Mohó párosítás | Mohó párosítás: emberek balról jobbra, mindenkinek a legkisebb szabad elérhető árushely | 3 | Magyarázat | ✅ kész |
| 69 | [Macskák](<69. Macskák/>) | Prefixösszeg, minimalizálás | K-t végigpróbálva, két prefix-számlálóval számoljuk a rosszul besorolt macskákat; egyenlőségnél a nagyobb K marad | 3 | Magyarázat | ✅ kész |
| 70 | [Speciális számok kódolása](<70. Speciális számok kódolása/>) | Prefixösszeg | Prefixösszegekből az első számjegy legkisebb és legnagyobb megengedett értéke | 2 | Bevezetés | ✅ kész |
| 71 | [Szomszédok](<71. Szomszédok/>) | Szomszédos elemek | Két egymás utáni A közötti szakaszok B-darabszámainak maximuma, A-nként egy bejárással | 3 | Magyarázat | ✅ kész |
| 72 | [Kétértékű szelet](<72. Kétértékű szelet/>) | Csúszó ablak | Csúszó ablak legfeljebb két különböző értékkel, darabszám-tömbbel | 2 | Magyarázat | ✅ kész |
| 73 | [Számok kódolása](<73. Számok kódolása/>) | Előtagösszeg, kódolás | Előtagösszeg minimuma és maximuma adja a kezdő számjegy érvényes tartományát | 3 | Mélyebb megértés | ✅ kész |
| 74 | [Szomszédok](<74. Szomszédok/>) | Szomszédos elemek | Két egymás utáni A közötti szakasz darabszám-előtagösszege, B-nként maximum | 3 | Magyarázat | ✅ kész |
| 75 | [Háromértékű szelet](<75. Háromértékű szelet/>) | Csúszóablak: különböző értékek | Csúszóablak, számláló-map, legfeljebb három különböző értékkel | 4 | Magyarázat | ✅ kész |
| 76 | [Világcsúcsok közötti legnagyobb időkülönbség](<76. Világcsúcsok közötti legnagyobb időkülönbség */>) | Maximumkiválasztás | Szomszédos sorok évkülönbségének maximumkiválasztása egy menetben | 1 | Bevezetés | ✅ kész |
| 77 | [Szélsőséges időjárás](<77. Szélsőséges időjárás ***/>) | Csúszóablak: min és max | Csúszóablak két monoton deque-kel, a szélső értékek tartására | 3 | Magyarázat | ✅ kész |
| 78 | [Szélsőséges időjárás](<78. Szélsőséges időjárás/>) | Csúszóablak: min és max | Csúszóablak két monoton deque-kel, a szélső értékek tartására | 3 | Magyarázat | ✅ kész |
| 79 | [Kamionok](<79. Kamionok/>) | Mohó ütemezés | Határidő szerinti rendezés és kör-alapú mohó kiosztás, a kamionok 2S napos ciklusban járnak | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 80 | [Ablak az óceánra](<80. Ablak az óceánra/>) | Monoton verem | Legnagyobb téglalap hisztogramban monoton veremmel, magasság = mélység − 1 | 3 | Magyarázat | ✅ kész |
| 81 | [Csapatverseny](<81. Csapatverseny/>) | Szimuláció prioritási sorral | Szimuláció prioritási sorral: a szabad csapatok közül a legjobb vezetőhöz csatlakozás | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 82 | [Freskó a sziklafalon](<82. Freskó a sziklafalon/>) | Maximum, bejárás | Magasságonként a leghosszabb elég magas szakasz keresése, a szegélyek levonásával. | 3 | Magyarázat | ✅ kész |
| 83 | [Legnagyobb szintkülönbség](<83. Legnagyobb szintkülönbség/>) | Prefix minimum | Balról jobbra haladva az eddigi minimum és a legnagyobb különbség nyilvántartása. | 2 | Bevezetés | ✅ kész |
| 84 | [Táncverseny](<84. Táncverseny/>) | Prioritási sor, szimuláció | Prioritási sorral szimulált párválasztás: a legjobb szabad fiú, egyenlőségnél a korábbi. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 85 | [Steak](<85. Steak/>) | Rendezés, maximum | Rendezés csökkenő sorrendbe, a végső fok maximum A_j + j - 1 alakban. | 2 | Mélyebb megértés | ✅ kész |
| 86 | [Tóparti búzaföldek](<86. Tóparti búzaföldek/>) | Körkörös maximális szakasz | Kétszer leírt sorozat, prefixösszegek és csúszó minimum (monoton deque) a legjobb körbe érő szakaszra. | 3 | Mélyebb megértés | ✅ kész |
| 87 | [Ismétlődés sorozatban](<87. Ismétlődés sorozatban/>) | Utolsó előfordulás | Értékenkénti utolsó előfordulás tárolása, a szomszédos előfordulások távolságának maximuma szigorú összehasonlítással. | 2 | Bevezetés | ✅ kész |
| 88 | [Lift felfelé](<88. Lift felfelé/>) | Különbségi tömb: maximum | Különbségi tömb a szállási és célemeletekre, majd prefixösszeg-bejárás a maximális utasszámhoz. | 2 | Magyarázat | ✅ kész |
| 89 | [Tóparti földek vásárlása](<89. Tóparti földek vásárlása/>) | Körkörös maximális szakasz | Birtokonként K*B_i - A_i érték, majd körbe érő szakasz maximuma csúszó minimummal (monoton deque). | 3 | Mélyebb megértés | ✅ kész |
| 90 | [Lift felfelé és lefelé](<90. Lift felfelé és lefelé/>) | Intervallumok és különbségi tömb | Irányonként különbségi tömb a szakaszokon, a két menet maximumának nagyobbika | 2 | Magyarázat | ✅ kész |
| 91 | [Csökkenés és növekedés](<91. Csökkenés és növekedés/>) | Monoton részsorozatok | Az elemeket egyesével generálva két futó szakaszhossz-számlálóval követjük a monoton szakaszokat | 3 | Magyarázat | ✅ kész |
