# Interaktív feladatok, kétszemélyes játékok – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 11 feladat · ✅ kész 0 · ❌ hibás 0 · 🟡 kézi 0 · 🟡 nincs minta/speciális 11 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Dominó](<1. Dominó ***/>) | Játékelmélet: minimax | Szakasz-állapot (i, j, bal és jobb szél) és memoizált minimax a büntetőpont-különbségre | 3 | Mélyebb megértés | 🟡 speciális |
| 2 | [Egy kavicshalom](<2. Egy kavicshalom ***/>) | Játékelmélet: Fibonacci-nim | Fibonacci-nim: a kavicsok Zeckendorf-felbontásának legkisebb tagját vesszük el | 3 | Mélyebb megértés | 🟡 speciális |
| 3 | [Fizetős játék](<3. Fizetős játék ***/>) | Interaktív: minimax | Minimax-DP intervallumokon: f(a,b) = min_x P(x) + max(f(a,x), f(x+1,b)). | 3 | Mélyebb megértés | 🟡 speciális |
| 4 | [Két játékos egy bábuval](<4. Két játékos egy bábuval ***/>) | Játékelmélet: rácsos minimax | Visszafelé számolt minimax-DP két táblázattal, a bábu helye szerint. | 3 | Magyarázat | 🟡 speciális |
| 5 | [Kitalálós játék fizetéssel](<5. Kitalálós játék fizetéssel ***/>) | Interaktív: zsetonos keresés | Intervallum-DP a biztos sikerhez szükséges zsetonszámra, a minimumot adó kérdéssel. | 3 | Mélyebb megértés | 🟡 speciális |
| 6 | [Kitalálós játék hibakorláttal](<6. Kitalálós játék hibakorláttal ***/>) | Interaktív: keresés hibákkal | Kérdésszám-korlát binomiális összegből (S(q,t) = sum C(q,i)2^i), intervallum-felosztással. | 3 | Mélyebb megértés | 🟡 speciális |
| 7 | [Számok elvétele](<7. Számok elvétele ***/>) | Játékelmélet: DP | Hátulról számolt DP a maximális pontkülönbségre, az első lépés az optimális L. | 3 | Mélyebb megértés | 🟡 speciális |
| 8 | [Mankala](<8. Mankala ***/>) | Játékelmélet: minimax | Teljes minimax-keresés a játékállapotokon, a kavics-szétosztás szimulálásával. | 3 | Magyarázat | 🟡 speciális |
| 9 | [Kincskereső játék](<9. Kincskereső játék ***/>) | Interaktív: centroid-keresés | Centroid-keresés: minden kérdés a részfa súlypontjára, így a jelöltek felezése. | 3 | Mélyebb megértés | 🟡 speciális |
| 10 | [Kavicsos játék](<10. Kavicsos játék ***/>) | Játékelmélet: Wythoff-játék | Wythoff-játék: vesztes pozíciók (a_k, b_k) mex-konstrukcióval, lépés a legközelebbi vesztes pozícióba | 3 | Magyarázat | 🟡 speciális |
| 11 | [Grundy játék](<11. Grundy játék ***/>) | Játékelmélet: Sprague–Grundy | Grundy-értékek mex-szel, minden lépésben xor-nullázó felosztás táblázatból | 3 | Mélyebb megértés | 🟡 speciális |
