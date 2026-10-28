# Gráfok, feszítőfák – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 11 feladat · ✅ kész 6 · ❌ hibás 0 · 🟡 kézi 5 · 🟡 nincs minta/speciális 0 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Csővezeték](<1. Csővezeték */>) | Minimális feszítőfa | Prim-algoritmus, a finomítók egy csomópontba vonva | 1 | Magyarázat | ✅ kész |
| 2 | [Ellenséges Városok](<2. Ellenséges Városok */>) | Maximális feszítőfa | Kruskal csökkenő sorrendben, unió-find, maximális feszítőfa | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 3 | [Gyár](<3. Gyár */>) | Feszítőfa: Kruskal | Gyárak összevonása egy csúccsá, majd Kruskal-algoritmus a minimális feszítőfára. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 4 | [Hálózat kiépítés](<4. Hálózat kiépítés */>) | Feszítőfa: inkrementális frissítés | Minimális feszítőfa újraszámolása hetente: az előző fa éleiből és az új élből, Kruskal-algoritmussal. | 1 | Magyarázat | ✅ kész |
| 5 | [Járásközpont](<5. Járásközpont */>) | Legrövidebb utak: Floyd-Warshall | Floyd-Warshall legrövidebb utak, majd a lakosokkal súlyozott távolságösszeg minimuma. | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 6 | [Kereskedők](<6. Kereskedők */>) | Feszítőfa: járások összevonása | Járások városait ingyen összekötjük, majd Kruskal-algoritmussal választjuk az ajánlatokat. | 1 | Magyarázat | ✅ kész |
| 7 | [Malmokból szállítás](<7. Malmokból szállítás */>) | Gráf: feszítőfa | Kruskal a malmok összevonásával, szélességi bejárás a szülőkhöz | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 8 | [Terek közötti utak](<8. Terek közötti utak */>) | Gráf: feszítőfa | Kruskal a meglévő utak előzetes összevonásával (DSU), számlálórendezéssel | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 9 | [Villamosítás](<9. Villamosítás ***/>) | Gráf: feszítőfa | Kruskal súlyonként; él akkor jön szóba, ha végpontjai még nem összekötöttek | 3 | Mélyebb megértés | ✅ kész |
| 10 | [Autóbusz](<10. Autóbusz ***/>) | Feszítőfa: kizárható élek | Kruskal csoportonként, élek kizárása összefüggőség alapján | 3 | Mélyebb megértés | ✅ kész |
| 11 | [Vasútépítés](<11. Vasútépítés/>) | Steiner-fa, legrövidebb utak | Steiner-pont három Dijkstra-futásból, legolcsóbb utak egyesítése | 3 | Magyarázat | ✅ kész |
