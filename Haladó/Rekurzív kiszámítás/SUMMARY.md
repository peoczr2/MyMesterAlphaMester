# Rekurzív kiszámítás – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 24 feladat · ✅ kész 21 · ❌ hibás 0 · 🟡 kézi 3 · 🟡 nincs minta/speciális 0 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Dobozok](<1. Dobozok **/>) | DP: leghosszabb lánc | Méretek rendezése, majd O(N²) leghosszabb-lánc DP a visszafejtéssel. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 2 | [Felbontás](<2. Felbontás **/>) | Bruteforce: kifejezés | Teljes keresés 3^8 jelkombinációra, előjeles összeg ellenőrzéssel | 2 | Bevezetés | ✅ kész |
| 3 | [Járda 1 – 1x1,1x2](<3. Járda 1 – 1x1,1x2 */>) | Rekurzió: Fibonacci | Utolsó lap szerinti rekurzió, Fibonacci-sor 64 bites egészekkel | 1 | Bevezetés | ✅ kész |
| 4 | [Járda 1 – 1x1,1x2,1x3](<4. Járda 1 – 1x1,1x2,1x3 */>) | Lineáris rekurzió | Háromtagú rekurzió: az utolsó lap 1, 2 vagy 3 hosszú, dp[n]=dp[n-1]+dp[n-2]+dp[n-3]. | 1 | Bevezetés | ✅ kész |
| 5 | [Járda 2 – 1x1,1x2](<5. Járda 2 – 1x1,1x2 */>) | Profil-DP: 2 soros járda | Oszloponkénti profil-DP két soros járdán, bitmaszk állapotokkal. | 1 | Magyarázat | ✅ kész |
| 6 | [Járda 2 – 1x2,1x3](<6. Járda 2 – 1x2,1x3 */>) | Profil-DP: 2 soros járda | Profil-DP két soros járdán, az 1×3 lap miatt három oszlopnyi előretekintéssel. | 1 | Magyarázat | ✅ kész |
| 7 | [Kép dekódolása](<7. Kép dekódolása **/>) | Quadtree: visszafejtés | Quadtree-kódok visszafejtése: a negyedek útját követve kitöltjük a négyzeteket. | 2 | Magyarázat | ✅ kész |
| 8 | [Kép kódolása](<8. Kép kódolása **/>) | Quadtree: kódolás | Quadtree-kódolás: homogén négyzetekhez útvonal és szín, különben rekurzió a négy negyedre. | 2 | Magyarázat | ✅ kész |
| 9 | [Robot](<9. Robot **/>) | 2D LIS, Fenwick-fa | Monoton lánc leghosszabb részsorozata (2D LIS) Fenwick-fával, a lépésszám-korláttal szűrve. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 10 | [Kifejezés](<10. Kifejezés ***/>) | Rekurzív elemzés, lineáris kifejezés | Lineáris együtthatók összegyűjtése, pozitív együtthatóhoz B, negatívhoz A. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 11 | [Hilbert-görbe](<11. Hilbert-görbe/>) | Térkitöltő görbe: rendezés | Hilbert-index kiszámítása negyedenként, rotációval; index szerint rendezés. | 3 | Magyarázat | ✅ kész |
| 12 | [Járda-L](<12. Járda-L ***/>) | DP: profilalapú lefedés | Oszloponkénti profil-DP: a két sor lefedettségi maszkjával, 64 állapottal. | 3 | Mélyebb megértés | ✅ kész |
| 13 | [JardaT](<13. JardaT ***/>) | DP: profil, T-tetromino | Ugyanaz a profil-DP, a két T-alakú elforgatással kiegészítve, mod 20200111. | 3 | Mélyebb megértés | ✅ kész |
| 14 | [Hanoi tornyai variáns](<14. Hanoi tornyai variáns ***/>) | Hanoi: rekurzív átrendezés | Rekurzió a legnagyobb, nem célpozícióban lévő korongtól; a kisebbek segédtoronyon. | 3 | Mélyebb megértés | ✅ kész |
| 15 | [Tornyok színes építőkockákból](<15. Tornyok színes építőkockákból/>) | Kombinatorika: rekurzió | Utolsó elem szerinti lineáris rekurzió T(n)=2T(n-1)+T(n-2), iteratív DP modulo | 2 | Magyarázat | ✅ kész |
| 16 | [Tornyok építőkockákból](<16. Tornyok építőkockákból */>) | Kombinatorika: rekurzió | Utolsó elem szerinti lineáris rekurzió T(n)=2T(n-1)+T(n-3), iteratív DP modulo | 1 | Bevezetés | ✅ kész |
| 17 | [Toronyépítés (1,1,1,2)](<17. Toronyépítés (1,1,1,2) */>) | Lineáris rekurzió | Utolsó elem szerinti lineáris rekurzió T(n)=3T(n-1)+T(n-2), iteratív DP modulo | 1 | Bevezetés | ✅ kész |
| 18 | [Toronyépítés (1,1,3,3)](<18. Toronyépítés (1,1,3,3) */>) | Lineáris rekurzió | Utolsó elem szerinti lineáris rekurzió T(n)=2T(n-1)+2T(n-3), iteratív DP modulo | 1 | Bevezetés | ✅ kész |
| 19 | [Toronyépítés (2,2,3,3)](<19. Toronyépítés (2,2,3,3) */>) | Lineáris rekurzió | Utolsó elem szerinti lineáris rekurzió T(n)=2T(n-2)+2T(n-3), iteratív DP modulo | 1 | Bevezetés | ✅ kész |
| 20 | [Különböző szélességű és magasságú lépcsők](<20. Különböző szélességű és magasságú lépcsők/>) | Dinamikus programozás | Prefixpozíciók és magasságok, DP az elérhető lépcsőkre (O(N^2)) | 3 | Magyarázat | ✅ kész |
| 21 | [Különböző szélességű lépcsők](<21. Különböző szélességű lépcsők/>) | Dinamikus programozás | Prefixpozíciók a szélességekből, összegző DP egységmagas lépcsőkre | 2 | Bevezetés | ✅ kész |
| 22 | [Fájlrendszer](<22. Fájlrendszer/>) | Fák, kombinatorika | Alulról felfelé összegzett fix/korlát alakok, stars-and-bars a szabad levelekre | 4 | Mélyebb megértés | ✅ kész |
| 23 | [Társasjáték](<23. Társasjáték/>) | Gráf: legrövidebb út | Hátulról előre DP az előrelépések DAG-ján, a kisebb távolság választásával | 1 | Bevezetés | ✅ kész |
| 24 | [Társasjáték visszalépéssel](<24. Társasjáték visszalépéssel/>) | Gráf: BFS | BFS egységsúlyú gráfon: a következő mező és az ugrómező a szomszédok | 2 | Magyarázat | ✅ kész |
