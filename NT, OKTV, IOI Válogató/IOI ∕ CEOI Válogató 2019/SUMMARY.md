# IOI ∕ CEOI Válogató 2019 – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 17 feladat · ✅ kész 13 · ❌ hibás 0 · 🟡 kézi 3 · 🟡 nincs minta/speciális 1 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Termek](<1. Termek/>) | Fa: bejárási sorrend | Fa gyökértől felfelé lépkedés, ajtóállapotok, bal-előbb mélységi sorrend a közös ősig | 4 | Mélyebb megértés | ✅ kész |
| 2 | [Robotok összegyűjtése](<2. Robotok összegyűjtése/>) | Gráf: szinkronizáló szó | Állapotpárok visszafelé BFS-e: minden pár összevonható-e, ekkor van szinkronizáló szó | 4 | Mélyebb megértés | ✅ kész |
| 3 | [Hálózati átvitel](<3. Hálózati átvitel/>) | Gráf: legszélesebb út | Élek sebesség szerinti hozzáadása, inkrementális Dijkstra a K-költségen belül | 4 | Magyarázat | ✅ kész |
| 4 | [Lámpák](<4. Lámpák/>) | Lineáris egyenletrendszer GF(2) | Gauss-elimináció GF(2) felett, a szabad változók kombinációinak kipróbálásával a legkevesebb kapcsolás. | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 5 | [Banda szétválasztása](<5. Banda szétválasztása/>) | Gráf: artikulációs pontok | Artikulációs pontok keresése mélységi bejárással (low-érték), a részek száma és legnagyobb mérete alapján. | 3 | Magyarázat | ✅ kész |
| 6 | [Hercegek házassága](<6. Hercegek házassága/>) | Gráf: erősen összefüggő komponensek | Irányított gráf erősen összefüggő komponensei (Tarjan): a váltakozó körbe eső párok kiválasztása. | 4 | Mélyebb megértés | ✅ kész |
| 7 | [Keveset dolgozó vállalkozó](<7. Keveset dolgozó vállalkozó/>) | Dinamikus programozás: hátizsák | Dinamikus programozás a bevételre, minimális idővel; visszakövetéssel a kiválasztott munkák. | 2 | Bevezetés | ✅ kész |
| 8 | [Üdítő monopólium](<8. Üdítő monopólium/>) | Gráf: sugár, 0-1 BFS | Azonos italú összefüggő csoportok, 0-1 BFS minden csúcsból, minimális excentricitás | 4 | Mélyebb megértés | ✅ kész |
| 10 | [Segély](<10. Segély/>) | Korlátos elosztás | Prefixfeltételek (Hall-típusú) külön alsó és felső korlátra, rendezés és prefixösszegek után | 4 | Mélyebb megértés | ✅ kész |
| 11 | [Csatornák](<11. Csatornák/>) | Gráf: 0-1 BFS | Bináris keresés a szélességen, 0-1 BFS: legfeljebb egy keskeny csatorna | 3 | Magyarázat | ✅ kész |
| 12 | [Hálózattervezés](<12. Hálózattervezés/>) | Dinamikus programozás: intervallum | Intervallum-DP, élenkénti vágóköltség 2D prefixösszegekkel | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 13 | [Csavarok](<13. Csavarok/>) | Véletlen pivot, rekurzió | Véletlen pivot-csavar párja, majd a többi csavar és anya kettéosztása rekurzióval | 4 | Mélyebb megértés | 🟡 speciális |
| 14 | [Dominó](<14. Dominó/>) | Gráf: Euler-út | Gráf Euler-út feltétel, páratlan csúcsok párosítása, komponensek mohó összekötése | 5 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 15 | [Úttisztítás](<15. Úttisztítás/>) | Gráf: fák és körök | Komponensenkénti számolás, leveles lehúzással részfa-méretek, körös komponensek külön | 3 | Mélyebb megértés | ✅ kész |
| 16 | [Hilbert-görbe](<16. Hilbert-görbe/>) | Geometria: Hilbert-görbe | Hilbert-sorszám bitenkénti számítása, majd rendezés a sorszám szerint | 3 | Magyarázat | ✅ kész |
| 17 | [Játék](<17. Játék/>) | Mintaillesztés: Aho–Corasick | Aho–Corasick-automata a kombinációkra, dp a K gombnyomás állapotaira | 3 | Magyarázat | ✅ kész |
| 18 | [Fantasztikus feladat](<18. Fantasztikus feladat/>) | Számelmélet: prímosztók, intervallumok | Prímenként szomszédos párok intervallum-lefedése, módosításnál inkrementális frissítés | 4 | Mélyebb megértés | ✅ kész |
