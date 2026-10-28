# Számelméleti algoritmusok – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 59 feladat · ✅ kész 55 · ❌ hibás 0 · 🟡 kézi 3 · 🟡 nincs minta/speciális 1 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [6174](<1. 6174 */>) | Számjegyes iteráció, keresés | Számjegyek csökkenő és növekvő rendezése, kivonás ismétlése; a legkisebb azonos lépésszámú szám keresése. | 1 | Bevezetés | ✅ kész |
| 2 | [Abszolút prímek](<2. Abszolút prímek ***/>) | Prímek, permutációk | Prímszita, majd a jelölt permutációinak prímvizsgálata next_permutation-nel. | 3 | Magyarázat | ✅ kész |
| 3 | [Armstrong számok](<3. Armstrong számok */>) | Számjegyek hatványösszege | Számjegy-multihalmazok rekurzív felsorolása, hatványösszeg ellenőrzése. | 1 | Bevezetés | ✅ kész |
| 4 | [Barátságos számok](<4. Barátságos számok */>) | Osztóösszeg, szita | Osztóösszeg-szita, majd a kölcsönös párok kiírása | 1 | Bevezetés | ✅ kész |
| 5 | [Bitművelet](<5. Bitművelet */>) | Sorozatok, bitek | Átlós felsorolás visszafejtése, majd az AND és OR értékek bináris kiírása. | 1 | Magyarázat | ✅ kész |
| 6 | [Boldog számok](<6. Boldog számok */>) | Szimuláció, ciklusdetektálás | Minden szám szimulálása a négyzetösszeg-átalakítással, ciklusdetektálással. | 1 | Bevezetés | ✅ kész |
| 7 | [Diofantoszi egyenlet](<7. Diofantoszi egyenlet ***/>) | Diofantoszi egyenlet | gcd-szűrés, majd a moduláris inverzzel kapott legkisebb x és a nemnegatív y ellenőrzése. | 3 | Magyarázat | ✅ kész |
| 8 | [Egyes számok](<8. Egyes számok */>) | Digitális gyök | A számjegyösszeg 9-cel osztott maradékának ellenőrzése, egyszeri összegzéssel. | 1 | Bevezetés | ✅ kész |
| 9 | [Egységtört](<9. Egységtört **/>) | Számelmélet: egységtörtek | Mohó egyiptomi törtbontás: mindig a legkisebb 1/d tag levonása, gcd-s egyszerűsítéssel. | 2 | Magyarázat | ✅ kész |
| 10 | [Erősen összetett számok](<10. Erősen összetett számok */>) | Osztók száma, szita | Szita: minden szám osztószámának kiszámolása, majd a futó maximumot meghaladó számok kiírása. | 1 | Magyarázat | ✅ kész |
| 11 | [Erősen páratlan számok](<11. Erősen páratlan számok **/>) | Számjegyösszeg-lánc | Számjegyösszeg-lánc követése: egyjegyű páratlan végeredmény IGEN, az első páros összeg NEM. | 2 | Magyarázat | ✅ kész |
| 12 | [Faktoriális számrendszer](<12. Faktoriális számrendszer */>) | Számrendszer-átváltás | Átváltás maradékos osztással (2, 3, 4, ...), visszafelé a számjegyek (k+1)! súlyú összege. | 1 | Magyarázat | ✅ kész |
| 13 | [Hatványmaradék](<13. Hatványmaradék */>) | Moduláris aritmetika | Ciklus-keresés: 1 mod B-től indulva ismételt szorzás A-val mod B, az első ismétlésnél megállunk. | 1 | Bevezetés | ✅ kész |
| 14 | [Hatványozás](<14. Hatványozás */>) | Nagy számok | 10^9 alapú nagy szám ismételt szorzása kis számmal, átvitel kezelésével. | 1 | Magyarázat | ✅ kész |
| 15 | [Hofstadter](<15. Hofstadter */>) | Szimuláció: sorozat | Közvetlen szimuláció, jelölőtömbbel a legkisebb szabad szám keresésével. | 1 | Bevezetés | ✅ kész |
| 16 | [Kiszámolós játék](<16. Kiszámolós játék **/>) | Szimuláció: Josephus | Vektoros Josephus-szimuláció, az index a kiesett elem helyén marad. | 2 | Bevezetés | ✅ kész |
| 17 | [Közös prímosztók](<17. Közös prímosztók ***/>) | Prímtényezős felbontás | Próbaosztásos prímfaktorizáció, majd két mutatós összefésülés. | 3 | Magyarázat | ✅ kész |
| 18 | [Lkkt](<18. Lkkt ***/>) | Prímtényezős számlálás | Prímenkénti kitevőszámlálás Π(2e+1) formulával, szitával. | 3 | Mélyebb megértés | ✅ kész |
| 19 | [Lnko](<19. Lnko ***/>) | Legnagyobb közös osztó | Gcd(2^N−1, 2^M−1)=2^gcd(N,M)−1 azonosság, nagy szám 10^9-es alapon. | 3 | Magyarázat | ✅ kész |
| 20 | [Mókusok](<20. Mókusok */>) | Többszörösök, számlálás | Ugráshosszonként a többszörösök számlálása, majd 0 és maximális darabszámú kövek kiírása. | 1 | Bevezetés | ✅ kész |
| 21 | [Nagyonprímek](<21. Nagyonprímek */>) | Prímek, DFS keresés | Balról jobbra DFS, csak prím prefixeket bővítünk 1, 3, 7, 9 számjegyekkel. | 1 | Magyarázat | ✅ kész |
| 22 | [Negatív számrendszer](<22. Negatív számrendszer **/>) | Számrendszer-átváltás | Ismételt osztás -10 alapra, negatív maradék korrigálásával; visszaváltás Horner-sémával. | 2 | Magyarázat | ✅ kész |
| 23 | [Négyzetszám nem osztó](<23. Négyzetszám nem osztó */>) | Szitálás intervallumon | Négyzetszám többszöröseinek megjelölése prímekre szitálva az intervallumban; a megjelöletlen számok kiírása. | 1 | Bevezetés | ✅ kész |
| 24 | [Összes prímosztó](<24. Összes prímosztó */>) | Faktorizálás | Próbaosztásos faktorizálás, minden osztó prím egyszeri kiírásával. | 1 | Bevezetés | ✅ kész |
| 25 | [Pierce](<25. Pierce */>) | Törtek rendezése | Az összes p/q tört felsorolása, egész számos összehasonlítással rendezve. | 1 | Bevezetés | ✅ kész |
| 26 | [P-ig nem osztott](<26. P-ig nem osztott */>) | Kínai maradéktétel | Lcm-modulusú maradékos egyenlet megoldása kiterjesztett euklideszi algoritmussal. | 1 | Magyarázat | ✅ kész |
| 27 | [Prímtényezős faktoriális](<27. Prímtényezős faktoriális */>) | Legendre-képlet | Legendre-képlet: a prímkitevők összegzése egész osztásokkal. | 1 | Magyarázat | ✅ kész |
| 28 | [Prímtényezős felbontás](<28. Prímtényezős felbontás */>) | Prímtényezős felbontás | Próbaosztás a négyzetgyökig, a végén maradt szám prím. | 1 | Bevezetés | ✅ kész |
| 29 | [Részosztó](<29. Részosztó */>) | Számjegyek, résztringek | Minden folytonos résztringet megvizsgálunk, a 0-val kezdődőket kihagyva, hossz szerint csökkenően. | 1 | Bevezetés | ✅ kész |
| 30 | [Sajátszámok](<30. Sajátszámok */>) | Számjegyösszeg, keresés | Csak M körüli generátor-ablak vizsgálata, n + számjegyösszeg(n) előállítások jelölése. | 1 | Magyarázat | ✅ kész |
| 31 | [Számrendszer](<31. Számrendszer */>) | Számrendszerek | Minden 2..A+1 alap számjegyösszegét maradékos osztással kiszámítjuk. | 1 | Bevezetés | ✅ kész |
| 32 | [Szerencsés](<32. Szerencsés */>) | Szita, szerencsés számok | Szita, ahol a lépésköz mindig a következő megmaradt szám (upper_bound). | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 33 | [Tükörkép](<33. Tükörkép */>) | Számjegyes DP | Számjegyenként 0–2 értékek, négyzetösszeg legfeljebb 9, lexikografikus DFS zsákutca-táblázattal. | 1 | Mélyebb megértés | ✅ kész |
| 34 | [Zeckendorf](<34. Zeckendorf */>) | Mohó algoritmus | Mohó választás a legnagyobb nem nagyobb Fibonacci-számmal, majd a tagok növekvő sorrendben való kiírása. | 1 | Magyarázat | ✅ kész |
| 35 | [Oszthatóság](<35. Oszthatóság */>) | Maradékszámítás | Karakterenkénti maradékszámítás 19, 29 és 551 modulusra, az eredmények soronként gyűjtve. | 1 | Bevezetés | ✅ kész |
| 36 | [Nagy szám kis prímosztói](<36. Nagy szám kis prímosztói **/>) | Prímosztók | Karakterenkénti maradékszámítás a 2 és 40 közötti 12 prímre, a találatok növekvő sorrendben. | 2 | Bevezetés | 🟡 nincs minta |
| 37 | [Irányítószámok](<37. Irányítószámok ***/>) | Számelméleti konstrukció | Projektív sík egyeneseinek prímszorzatai, egyedi címke-prímmel megkülönböztetve | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 38 | [Kártyakeverés](<38. Kártyakeverés ***/>) | Permutáció hatványozása | A duplakeverés négyzetre emelés; a 2^S kitevő modulo N inverzével visszafelé hatványozás | 3 | Magyarázat | ✅ kész |
| 39 | [Számok](<39. Számok ***/>) | Diofantikus egyenlet | Lnko-val leosztás, majd moduláris inverzzel a legkisebb nemnegatív y kiszámítása | 3 | Magyarázat | ✅ kész |
| 40 | [Euler](<40. Euler/>) | Euler-féle phi függvény | Prímtényezős bontás, minden p prímre az eredmény ans -= ans/p módosítása (Euler-féle phi). | 2 | Magyarázat | ✅ kész |
| 41 | [Faktoriális vége](<41. Faktoriális vége/>) | Faktoriális, prímek | Legendre-formula: az N! ötös prímtényezőinek száma: N/5 + N/25 + ... | 1 | Bevezetés | ✅ kész |
| 42 | [Nem négyzetmentes számok](<42. Nem négyzetmentes számok/>) | Szita, négyzetmentesség | Szita: minden p-re a p^2 többszöröseit megjelöljük, majd megszámoljuk a jelölteket. | 2 | Magyarázat | ✅ kész |
| 43 | [Számok előállítása](<43. Számok előállítása/>) | Maradékgráf, bitkészlet | Maradékosztályok a legkisebb érme szerint, blokkonkénti bitkészlet-szita Dijkstra helyett. | 4 | Mélyebb megértés | ✅ kész |
| 44 | [Ritka szám](<44. Ritka szám/>) | Fibonacci, bináris számok | Fibonacci-számlálás bithosszonként, majd greedy bitépítés a sorszám alapján. | 3 | Magyarázat | ✅ kész |
| 45 | [Páratlan számok](<45. Páratlan számok/>) | Bitműveletek, popcount | A számokat sorban végignézzük, és a páratlan popcountúakat számoljuk az i-edikig. | 1 | Bevezetés | ✅ kész |
| 46 | [Számok előállítása](<46. Számok előállítása/>) | Maradékgráf, bitkészlet | Maradékosztályok a legkisebb érme szerint, blokkonkénti bitkészlet-szita Dijkstra helyett. | 3 | Mélyebb megértés | ✅ kész |
| 47 | [Kastély](<47. Kastély/>) | Legnagyobb közös osztó | Kastélyonként az összes oldalhossz legnagyobb közös osztója (gcd-lánc). | 1 | Bevezetés | ✅ kész |
| 48 | [Börtön](<48. Börtön/>) | Számelmélet: osztók | Osztók paritása: pontosan a tökéletes négyzetek maradnak nyitva; ezeket sorban kiírjuk. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 49 | [Páros számok](<49. Páros számok/>) | Bitműveletek: popcount | Sorban végigmegyünk a számokon, és a popcount paritása alapján számolunk. | 1 | Bevezetés | ✅ kész |
| 50 | [Számok összege](<50. Számok összege/>) | Kétmutatós módszer | Rendezett sorozatban rögzített elem mellett kétmutatós keresés a maradék párra. | 2 | Magyarázat | ✅ kész |
| 51 | [Szám előállítási lehetőségei](<51. Szám előállítási lehetőségei/>) | Kétpontos módszer | Rögzített első elem, két mutató a rendezett maradék részen. | 2 | Magyarázat | ✅ kész |
| 52 | [Lineáris kombináció](<52. Lineáris kombináció/>) | Számelmélet: lineáris kombináció | Floor-sum számlálás bináris kereséssel, a felbontás moduló-inverzzel. | 4 | Mélyebb megértés | ✅ kész |
| 53 | [Sokszögszámok](<53. Sokszögszámok/>) | Zárt képlet | Zárt képlet az N-szögszámra, modulo 1 000 000. | 1 | Bevezetés | ✅ kész |
| 54 | [Terem](<54. Terem/>) | Euklideszi algoritmus | Euklideszi algoritmus hányadosösszege; egyforma lapokhoz a gcd. | 2 | Magyarázat | ✅ kész |
| 55 | [Középpontos sokszögszámok](<55. Középpontos sokszögszámok/>) | Számelmélet: képletek | Zárt képlet, a háromszögszám-jellegű részt szorzás előtt modulózzuk. | 1 | Bevezetés | ✅ kész |
| 56 | [K-osztható párok](<56. K-osztható párok/>) | Maradékosztályok | Maradékosztályok számlálása, párosítás r és K-r között. | 2 | Magyarázat | ✅ kész |
| 57 | [Térfogat](<57. Térfogat/>) | Osztók, faktorizálás | Osztóhármasok végigpróbálása, a legkisebb különbségű kiválasztása. | 2 | Magyarázat | ✅ kész |
| 58 | [Számjegy keverés](<58. Számjegy keverés/>) | Mohó stratégia, számjegyek | Mohó csökkentés a legnagyobb számjeggyel; a kölcsönzések alsó korlátja L(L-1)/2. | 3 | Mélyebb megértés | ✅ kész |
| 59 | [Házszámok](<59. Házszámok/>) | Bináris keresés, számlálás | Bináris keresés a válaszra, számjegyek helyiértékenkénti számlálásával ellenőrizve. | 3 | Mélyebb megértés | ✅ kész |
