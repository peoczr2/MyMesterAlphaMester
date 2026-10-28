# IOI ∕ CEOI Válogató 2021 – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 12 feladat · ✅ kész 9 · ❌ hibás 0 · 🟡 kézi 2 · 🟡 nincs minta/speciális 1 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Energiatakarékos ellenőrzés](<1. Energiatakarékos ellenőrzés ****/>) | Dinamikus programozás: fa | Fa-DP: részfánként a fény átvitele vagy a szülő lámpájának égve hagyása, lámpaszám szerint. | 4 | Mélyebb megértés | ✅ kész |
| 2 | [Maximum felosztás](<2. Maximum felosztás ****/>) | Kombinatorika, DP | Első B_i-előfordulás szerinti DP, a vágások tartományösszegei Fenwick-fával | 4 | Mélyebb megértés | ✅ kész |
| 3 | [Génsebész](<3. Génsebész/>) | Adatszerkezet: treap | Implicit treap betűnkénti darabszámokkal, split és merge műveletekkel | 4 | Magyarázat | 🟡 speciális |
| 4 | [Játék a síkon](<4. Játék a síkon ****/>) | Gráf: párosítás | Maximális párosítás (Kuhn), majd alternáló bejárás a kihagyható pontokra | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 5 | [Növekvő Ödön és a Másoló Varázsló](<5. Növekvő Ödön és a Másoló Varázsló ****/>) | DP: monoton sorozat | Megtartott elemek láncos DP, kétdimenziós lekérdezés kétszintű Fenwick-fával | 4 | Mélyebb megértés | ✅ kész |
| 6 | [Az óvodai lét elviselhetetlen könnyűsége #2](<6. Az óvodai lét elviselhetetlen könnyűsége #2 ****/>) | Dinamikus programozás | f(n)=1+min f(K·⌊n/K⌋); minden K-ra a változások követése, gyakorisági tömb és bitset minimum | 4 | Mélyebb megértés | ✅ kész |
| 7 | [Nemzetközi Rántott Hús Fesztivál](<7. Nemzetközi Rántott Hús Fesztivál ****/>) | Szimuláció: prefix-korlát | Egyensúly-prefixek, következő kisebb elem és prefix-korlátos M-választás szegmensfával | 4 | Mélyebb megértés | ✅ kész |
| 8 | [Turista járatok](<8. Turista járatok ****/>) | Gráf: blokkok, vágópontok | Blokkok (2-összefüggő komponensek) mélységi bejárással, blokk-vágópont fa BFS-sel, VAGY-jelzéssel | 4 | Mélyebb megértés | ✅ kész |
| 9 | [Vázsony vonatjegyet vásárol](<9. Vázsony vonatjegyet vásárol ****/>) | Gráf: legrövidebb utak | Dijkstra B-ből, azonos távolságú csúcsok DSU-val, leghosszabb súlyozott lánc DP-vel | 4 | Mélyebb megértés | ✅ kész |
| 10 | [Házak](<10. Házak ****/>) | Geometria: láthatóság | Szögszerinti sweep a ház két látható élére, rendezett halmazzal | 4 | Mélyebb megértés | ✅ kész |
| 11 | [Multiplikátoros telebabrátor](<11. Multiplikátoros telebabrátor ****/>) | Gráf: xor-távolság | Gyökértől vett xor-távolságok, bináris trie a legnagyobb xor-párhoz | 4 | Magyarázat | ✅ kész |
| 12 | [Építkezés](<12. Építkezés ****/>) | Gráf: topologikus rendezés | Blokkonkénti mohó ütemezés határidő szerinti prioritásos sorral, prefix-korlátokkal | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
