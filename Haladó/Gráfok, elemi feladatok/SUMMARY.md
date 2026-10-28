# Gráfok, elemi feladatok – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 47 feladat · ✅ kész 36 · ❌ hibás 0 · 🟡 kézi 11 · 🟡 nincs minta/speciális 0 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Állatkert](<1. Állatkert */>) | Gráf: fokszám | Fokszámok számolása élenként, majd egy bejárás a fokszám-1 csúcsok és a maximum keresésére. | 1 | Bevezetés | ✅ kész |
| 2 | [Bandák](<2. Bandák */>) | Gráf: bandák, komponensek | Komponensek bejárása; tagonként a kihagyással újraszámolt komponensek, fokszámok és teljes gráf ellenőrzése. | 1 | Magyarázat | ✅ kész |
| 3 | [Baráti lánc](<3. Baráti lánc */>) | Gráf: Hamilton-kör | Pósa-féle forgatásokkal bővített út, amely 1-ből indulva Hamilton-kört ad. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 4 | [Barátok](<4. Barátok */>) | Gráf: összefüggő komponensek | Unió-keresés (DSU): a barátpárokat egyesítjük, majd a komponenseket sorszám szerint írjuk ki. | 1 | Bevezetés | ✅ kész |
| 5 | [Csapatverseny](<5. Csapatverseny */>) | Gráf: irányított kör | Irányított gráf: kölcsönös párok, befok 0 csúcsok, 3+ hosszú kör bejárással. | 1 | Magyarázat | ✅ kész |
| 6 | [Csoportok](<6. Csoportok */>) | Gráf: unió-keresés | Legszimpatikusabb (pozitív maximum) él, unió-keresés; a komponensek a csoportok. | 1 | Bevezetés | ✅ kész |
| 7 | [Ember](<7. Ember */>) | Gráf: fa, fokszámok | Gyerekek száma; unokák száma a gyermekek gyermekszámainak összegeként; egy bejárás. | 1 | Bevezetés | ✅ kész |
| 8 | [Falu](<8. Falu */>) | Gráf: legrövidebb utak | Fokszámok (zsákfalvak, maximum); minden csúcsból Dijkstra a legközelebbi nem szomszédos párhoz. | 1 | Magyarázat | ✅ kész |
| 9 | [Falvak](<9. Falvak */>) | Gráf: fokszám, élsúlyok | Zsákfalutól az elágazásig tartó út összege; fokszám-maximum; a csúcsok legrövidebb élének maximuma. | 1 | Magyarázat | ✅ kész |
| 10 | [Hálózat átmérője](<10. Hálózat átmérője */>) | Fa: átmérő | Szülő-gyerek sorrend miatt fordított sorrendű bejárás, csúcsonként a két leghosszabb ág összege. | 1 | Magyarázat | ✅ kész |
| 11 | [Hálózat központja](<11. Hálózat központja */>) | Fa: központ | Két szélességi bejárással megkeressük az átmérő végpontjait, a központ az átmérő felénél van. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 12 | [Hír a legtöbb tanulónak](<12. Hír a legtöbb tanulónak */>) | Gráf: BFS elérhetőség | Irányított gráf, minden tanulóból BFS, a legtöbb elérhető tanuló közül a legkisebb sorszám. | 1 | Bevezetés | ✅ kész |
| 13 | [Hírek](<13. Hírek */>) | Gráf: elérhetőség | Tranzitív lezárás bitsetekkel (Warshall), majd párok és sorok számlálása. | 1 | Magyarázat | ✅ kész |
| 14 | [Hírek visszaérése](<14. Hírek visszaérése */>) | Gráf: függvénygráf, körök | Bejövő fok szerinti levágás (Kahn-szerűen); a megmaradt csúcsok a körökön vannak. | 1 | Magyarázat | ✅ kész |
| 15 | [Hírlánc](<15. Hírlánc */>) | Gráf: topologikus sorrend | Topologikus sorrendben haladva minden ember a bejövő élek forrásainak egyedi többségi hírét fogadja el. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 16 | [Ismerősök](<16. Ismerősök */>) | Gráf: közös ismerős | Ismerőslisták bitsetben, páronként metszet és egyenlőség ellenőrzése. | 1 | Bevezetés | ✅ kész |
| 17 | [Ismerősök2](<17. Ismerősök2 */>) | Gráf: közös ismerős | Szomszédsági bitsetek metszete, illetve azonos szomszédsági halmaz ellenőrzése párokra. | 1 | Bevezetés | ✅ kész |
| 18 | [Kockavilág](<18. Kockavilág */>) | Szimuláció: kockatorony | Sorban építjük a tornyot: a rajta lévő kockákat felülről lebontjuk, majd az i. kockát ráhelyezzük. | 1 | Magyarázat | ✅ kész |
| 19 | [Konténer rendezés](<19. Konténer rendezés */>) | Gráf: komponensek, rendezés | Rossz pozíciók száma plusz a színgráf összefüggő komponenseinek száma (DSU). | 1 | Mélyebb megértés | ✅ kész |
| 20 | [Legelszigeteltebb falu](<20. Legelszigeteltebb falu */>) | Gráf: legközelebbi szomszéd | Minden faluhoz a rá illeszkedő utak minimumát tároljuk, majd a maximumot keressük. | 1 | Bevezetés | ✅ kész |
| 21 | [Legnagyobb átviteli sebesség](<21. Legnagyobb átviteli sebesség */>) | Gráf: maximin út | Élek csökkenő sebesség szerinti Union-Find egyesítése; P és Q összekötésekor megvan az érték. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 22 | [Mikulás](<22. Mikulás */>) | Gráf: permutáció, módosítás | Többszörösen célzott tanulók felesleges éleit átirányítjuk a senki által nem célzott tanulókhoz, ciklikus párosítással. | 1 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 23 | [Régiók](<23. Régiók */>) | Gráf: komponensek | Szélességi bejárás a legfeljebb T távolságú települések között; a komponensek adják a régiókat. | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 24 | [Rémhír](<24. Rémhír */>) | Gráf: be- és kimenő fok | Be- és kimenő élek számlálása irányított gráfon, duplikátumok szűrésével. | 1 | Bevezetés | ✅ kész |
| 25 | [Szállítás](<25. Szállítás */>) | Gráf: csúcstípusok fokszámból | Fokszámokból csúcstípusok (termelő, raktározó, árusító) meghatározása, majd szomszédság-ellenőrzés. | 1 | Magyarázat | ✅ kész |
| 26 | [Telephely](<26. Telephely */>) | Gráf: legrövidebb utak, excentricitás | Floyd-Warshall minden csúcspárra, majd a legkisebb excentricitású csúcs kiválasztása. | 1 | Magyarázat | ✅ kész |
| 27 | [Város](<27. Város */>) | Geometria: háromszögelés, határél | Élek számlálása a háromszögekből: pontosan egy háromszögben szereplő él a határél. | 1 | Magyarázat | ✅ kész |
| 28 | [Körutak](<28. Körutak/>) | Gráf: hidak, körök | Tarjan-féle hidkeresés DFS-sel; a nem híd élek végpontjai körúton vannak. | 2 | Magyarázat | ✅ kész |
| 29 | [Legnépszerűbb tagok](<29. Legnépszerűbb tagok/>) | Gráf: függvénygráf, körök | Függvénygráf: minden csúcsból egy él indul, így a körök egy bejárással megtalálhatók. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 30 | [Zsákfalvak](<30. Zsákfalvak/>) | Gráf: láncok, fokszám | Zsákfaluból indulva fokszám-2 csúcsokon át követjük az utat, és megszámoljuk az élek számát. | 2 | Bevezetés | ✅ kész |
| 31 | [Karavánok találkozása](<31. Karavánok találkozása/>) | Gráf: útvonal-szimuláció | Karavánok útjának időbeli szimulálása, oázisonként a köztes érkezések páronkénti összevetése. | 3 | Magyarázat | ✅ kész |
| 32 | [Oázisok szállásai](<32. Oázisok szállásai/>) | Gráf: útvonal-szimuláció, maximum | Karavánok útjának szimulálása, oázisonként az éjszakánkénti különböző karavánok maximuma. | 3 | Magyarázat | ✅ kész |
| 33 | [Leghosszabb kör](<33. Leghosszabb kör/>) | Gráf: funkcionális gráf | Funkcionális gráf bejárása, a lépésszámok különbségéből a körök hossza. | 2 | Bevezetés | ✅ kész |
| 34 | [Telephelyek](<34. Telephelyek/>) | Gráf: Steiner-fa, Floyd–Warshall | Középpont-keresés: minden csúcsra a három legrövidebb út összköltsége, Floyd–Warshall távolságokkal. | 3 | Mélyebb megértés | ✅ kész |
| 35 | [Központ](<35. Központ/>) | Gráf: legszélesebb utak | Floyd-Warshall-szerű max-min számítás, majd a leglassabban elért csúcs sebességének maximuma. | 2 | Magyarázat | ✅ kész |
| 36 | [Hálózat tesztelés](<36. Hálózat tesztelés/>) | Gráf: unió-keresés, fordított idő | Élek visszaadása fordított sorrendben DSU-val, komponensenként a csúcslistákkal. | 4 | Magyarázat | 🟡 kézi ellenőrzés |
| 37 | [Körmérközés](<37. Körmérközés/>) | Gráf: turnamenti sorrend | Beszúrásos módszer: az új versenyző a végére kerül, majd előrébb cserélgetjük. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 38 | [Függvény minimális periódushossza](<38. Függvény minimális periódushossza/>) | Gráf: függvénygráf, ciklus | Bejárás kezdőpontonként, csúcsonként jegyzett bejárás-azonosítóval; a legrövidebb ciklus kiírása. | 2 | Magyarázat | ✅ kész |
| 39 | [Repülés](<39. Repülés/>) | Gráf: hidak, körök | Hidkeresés mélységi bejárással; a nem híd élek végpontjai körön vannak, a többi csúcsot számoljuk. | 2 | Magyarázat | ✅ kész |
| 40 | [Függvény periódushossza](<40. Függvény periódushossza/>) | Gráf: függvénygráf | Funkcionális gráf: körök levágással, a körbe jutás távolsága a levágás fordított sorrendjében. | 3 | Magyarázat | ✅ kész |
| 41 | [Parti](<41. Parti **/>) | Gráf: iteratív levágás | Legnagyobb megfelelő részhalmaz: a kevesebb mint két javaslatot kapó tagokat iteratívan kihúzzuk. | 2 | Magyarázat | ✅ kész |
| 42 | [Hálózati biztonság](<42. Hálózati biztonság **/>) | Gráfok: K-mag | Fokszám-alapú hámozás: a K-nál kisebb fokú csúcsok törlése sorban, amíg lehet | 2 | Magyarázat | ✅ kész |
| 43 | [Két csoport](<43. Két csoport ***/>) | Gráfok: kétszínezés | Lokális javítás: aki csoportjában legalább két nem kedvelt társ van, átvált a másik csoportba | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 44 | [Átvágás](<44. Átvágás/>) | Fák: fokszámok | Bambusz: levelek száma − 2; csillag: N−1 mínusz legnagyobb fok | 3 | Mélyebb megértés | ✅ kész |
| 45 | [Túra](<45. Túra/>) | Fák: legkisebb összegű út | Fa DP: legkisebb összegű, legalább két csúcsú út gyökerezett bejárással | 2 | Magyarázat | ✅ kész |
| 46 | [Pletykálkodás](<46. Pletykálkodás/>) | Gráf: feszítőfa | C4-kör négy csúcsának négy hívása, a többi csúcs BFS-fa mentén (2N-4); C4 nélkül feszítőfa (2N-3). | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 47 | [Mágikus sorozat](<47. Mágikus sorozat/>) | Z-függvény inverze | Balról jobbra: Z-szakasz másolása, különben a legkisebb nem tiltott érték. | 3 | Magyarázat | ✅ kész |
