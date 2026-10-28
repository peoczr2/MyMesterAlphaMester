# Gráfok, legrövidebb utak – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 34 feladat · ✅ kész 20 · ❌ hibás 0 · 🟡 kézi 11 · 🟡 nincs minta/speciális 3 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Adott élen átmenő utak](<1. Adott élen átmenő utak ***/>) | Gráf: élen átmenő utak | Kétszeri szélességi bejárás minden kezdőpontból: a teljes gráfban és az uv él nélkül | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 2 | [Bányászrobot](<2. Bányászrobot */>) | Gráf: rácsgráf, legrövidebb út | Dijkstra a cellarácson: szabad cellába lépés 1, falba lépés F időegységgel. | 1 | Magyarázat | ✅ kész |
| 3 | [Futár](<3. Futár **/>) | Gráf: Dijkstra | Dijkstra a kezdő városból; a válasz a legnagyobb elérhető távolság. | 2 | Bevezetés | 🟡 nincs minta |
| 4 | [Hálózat1](<4. Hálózat1 */>) | Gráf: legszélesebb út | Élek csökkenő sávszélesség szerinti összevonása DSU-val, A és B összekötésekor kiírás | 1 | Bevezetés | ✅ kész |
| 5 | [V-kódolás](<5. V-kódolás/>) | Szöveg: V-alakú bejárás | A karakter indexéből kiszámított sor szerinti gyűjtés, majd a sorok összefűzése | 1 | Bevezetés | ✅ kész |
| 6 | [Kanna](<6. Kanna */>) | Gráf: legrövidebb út | Állapotgráf Dijkstra-val, teljes öntésekkel; A-beli mennyiségenként a legkisebb idő | 1 | Magyarázat | ✅ kész |
| 7 | [Kastély](<7. Kastély */>) | Gráf: rácsgráf | Rácsgráf Dijkstra-val: az átlós (rejtekajtós) lépés plusz R költséggel | 1 | Bevezetés | ✅ kész |
| 8 | [Legnagyobb átviteli sebességű útvonal](<8. Legnagyobb átviteli sebességű útvonal **/>) | Gráf: minimax út | Élek csökkenő sebesség szerint DSU-val összevonva; az első összekötéskor a sebesség a válasz | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 9 | [Raktár](<9. Raktár */>) | Fa: újragyökerezés | Fa gyökerezése, részfa-súlyok, gyökércsere-képlettel minden csúcs költsége | 1 | Mélyebb megértés | ✅ kész |
| 10 | [Repülőút](<10. Repülőút ***/>) | Gráf: menetrend szerinti út | Dijkstra a legkorábbi érkezési időkkel, a járatok napi ciklusát mod 1440 számolva | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 11 | [Szállítás](<11. Szállítás */>) | Gráf: legszélesebb út | Maximális feszítőerdő: utak csökkenő sorrendben, DSU, majd szélességi bejárás az erdőben | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 12 | [Szállítás kétféle szempont](<12. Szállítás kétféle szempont */>) | Gráf: két szempontos út | Legnagyobb szűk keresztmetszet unió-kereséssel, majd legkevesebb élű út szélességi bejárással | 1 | Magyarázat | ✅ kész |
| 13 | [Térkép](<13. Térkép */>) | Gráf: legrövidebb út | Dijkstra a rácson, indexelt bináris halommal és csökkentési kulccsal. | 1 | Magyarázat | ✅ kész |
| 14 | [Túra](<14. Túra */>) | Gráf: legrövidebb út, útvonal | Dijkstra, a belépő lépések betűit tárolva Q-ból visszafelé rakjuk ki az utat. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 15 | [Turista](<15. Turista */>) | Gráf: legrövidebb út, rács | Dijkstra (idő, szakaszszám) páros kulccsal, 64 bites csomagolással. | 1 | Magyarázat | ✅ kész |
| 16 | [Út városok elkerülésével](<16. Út városok elkerülésével **/>) | Gráf: legrövidebb út, csúcsköltség | Dijkstra csúcsköltséggel: elsődlegesen az elkerülendő városok, másodlagosan a városok száma. | 2 | Magyarázat | ✅ kész |
| 17 | [Vám](<17. Vám */>) | Gráf: csúcssúlyozott legrövidebb út | Dijkstra-algoritmus csúcsokra súlyozva, a célvárosban nem fizetett vám kivonásával. | 1 | Magyarázat | 🟡 nincs minta |
| 18 | [Repülőút menetrenddel](<18. Repülőút menetrenddel ***/>) | Gráf: időfüggő legrövidebb út | Dijkstra a legkorábbi érkezési időkkel, átszállásnál a napi menetrend szerinti következő indulással. | 3 | Mélyebb megértés | 🟡 nincs minta |
| 19 | [Tűzoltó](<19. Tűzoltó ***/>) | Gráf: többforrású legrövidebb út | Többforrású Dijkstra az állomásokról, az elődláncon visszafelé követve az útvonalat. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 20 | [Egér és macska](<20. Egér és macska ***/>) | Gráf: legrövidebb utak | Dijkstra a macska idejeivel, majd az egér Dijkstrája csak olyan pontokon, ahol még nincs a macska. | 3 | Magyarázat | ✅ kész |
| 21 | [Szállítás](<21. Szállítás ***/>) | Gráf: szűk keresztmetszet | Uniós-kereső a legnagyobb súlyhoz, majd szélességi bejárás a legkevesebb városon át. | 3 | Magyarázat | ✅ kész |
| 22 | [Autóbusz](<22. Autóbusz/>) | Gráf: negatív élek | Negatív élekkel Bellman–Ford, a haszon a legkisebb összköltség ellentettje. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 24 | [Fizetős utak](<24. Fizetős utak/>) | Gráf: legrövidebb utak | 0-1 szélességi bejárás deque-val, az előzők alapján visszafejtett úttal | 2 | Magyarázat | ✅ kész |
| 25 | [Leggyorsabb szállítás](<25. Leggyorsabb szállítás/>) | Gráf: Dijkstra | Dijkstra két kulccsal: a legrövidebb hossz, azon belül a legnagyobb szűk keresztmetszet | 2 | Magyarázat | ✅ kész |
| 26 | [Vasútállomások](<26. Vasútállomások/>) | Gráf: időfüggő utak | Menetrendi csúcsokon Dijkstra, átszállási várakozólánccal, lexikografikus (költség, indulás) kulccsal | 3 | Mélyebb megértés | ✅ kész |
| 28 | [Csatornák](<28. Csatornák/>) | Gráf: legszélesebb út | Bináris keresés a szélességen, kétállapotú BFS a kiszélesítés felhasználásával. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 29 | [Séta minél biztonságosabban](<29. Séta minél biztonságosabban **/>) | Rács: 0-1 BFS | Világos mezők bejelölése, majd 0-1 BFS a sötét mezők számával súlyozva. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 30 | [Tom és Jerry2](<30. Tom és Jerry2 ****/>) | Gráf: vágópontok, blokkok | Blokkfelbontás a lyukból gyökerezve, vágópontok ellenőrzése Tom- és Jerry-távolsággal. | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 31 | [Jegesmedve](<31. Jegesmedve ***/>) | Gráf: unió-keresés | Elérhető halak DSU-val napról napra, Hall-feltétel alapján min(nap + halak) | 3 | Mélyebb megértés | ✅ kész |
| 32 | [Egyirányú utcák megfordítása](<32. Egyirányú utcák megfordítása **/>) | Gráf: legrövidebb út | Dijkstra két költséggel: megfordítások száma, majd út hossza | 2 | Magyarázat | ✅ kész |
| 33 | [Vázsony vonatjegyet vásárol](<33. Vázsony vonatjegyet vásárol ****/>) | Gráf: legrövidebb út, DP | Dijkstra a célból, azonos távolságú csoportok DSU-val, lánc-DP a csoportok között | 4 | Mélyebb megértés | ✅ kész |
| 34 | [Rácsháló gráf](<34. Rácsháló gráf/>) | Gráf: BFS, átmérő | Új élek után minden pontból BFS, az átmérő kiírása | 2 | Bevezetés | 🟡 kézi ellenőrzés |
| 35 | [Ciklikus rácsháló gráf](<35. Ciklikus rácsháló gráf/>) | Gráf: BFS, átmérő | Új él után minden csúcsból BFS, a legnagyobb távolság (átmérő) kiírása | 2 | Bevezetés | ✅ kész |
| 36 | [Hálózati átvitel](<36. Hálózati átvitel/>) | Gráf: szűk keresztmetszet | Legfeljebb h élen elérhető legnagyobb sebesség: lépésenkénti DP a szűk keresztmetszetre | 3 | Magyarázat | ✅ kész |
