# Szimuláció – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 36 feladat · ✅ kész 31 · ❌ hibás 0 · 🟡 kézi 5 · 🟡 nincs minta/speciális 0 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Automata](<1. Automata ***/>) | Állapotszimuláció | Parancsok sorrendi végigvitele, pozíció és irány frissítése. | 3 | Bevezetés | ✅ kész |
| 2 | [Autómentés](<2. Autómentés ***/>) | Szimuláció | Lépésenkénti forgalomszimuláció, a mentő útja BFS-sel, visszafelé rekonstruálva | 3 | Mélyebb megértés | ✅ kész |
| 3 | [Autóút járdával](<3. Autóút járdával **/>) | Forgalmi szimuláció, Időbeli események | Időlépéses útszakasz-szimuláció lámpafázissal és ütközéskorláttal | 2 | Magyarázat | ✅ kész |
| 4 | [Bábuk ütközése 1](<4. Bábuk ütközése 1 */>) | Szimuláció, Mozgás | Egydimenziós mozgás és szélső visszafordulás lépésenként | 1 | Bevezetés | ✅ kész |
| 5 | [Bábuk ütközése 2](<5. Bábuk ütközése 2 */>) | Szimuláció, Ütközés | Kétbábus ütközés kezelése előző állapotból | 1 | Bevezetés | ✅ kész |
| 6 | [Bábuk ütközése 3](<6. Bábuk ütközése 3 */>) | Szimuláció, Vektormozgás | Kétdimenziós mozgás visszapattanással és állapotfrissítéssel | 1 | Magyarázat | ✅ kész |
| 7 | [Életjáték](<7. Életjáték */>) | Celluláris automata, Rácsszimuláció | Generációnkénti tábla-másolás és szomszédszámlálás | 1 | Magyarázat | ✅ kész |
| 8 | [Hangya az egységkockán](<8. Hangya az egységkockán ***/>) | Rácsmodell, Állapotgép | Állapotalapú léptetés térbeli orientációval és látogatásszámlálással | 3 | Magyarázat | ✅ kész |
| 9 | [Hangya nyolcszögeken](<9. Hangya nyolcszögeken ***/>) | Szimuláció: rácsbolyongás | Mezőtípusos szimuláció, a különböző érintett négyzetek halmaza, látogatásszámlálás map-pel | 3 | Magyarázat | ✅ kész |
| 10 | [Hangya tizenkétszögeken](<10. Hangya tizenkétszögeken ***/>) | Geometriai szimuláció, rácsmodell | Állapotgépes bejárás tizenkétszög-rácson, lapok látogatásszámának hash-táblában tartásával. | 3 | Mélyebb megértés | ✅ kész |
| 11 | [Huszár](<11. Huszár */>) | Tábla, Bejárás | Huszár-lépések állapotgépes követése | 1 | Bevezetés | ✅ kész |
| 12 | [Huszár lépésszám](<12. Huszár lépésszám */>) | Gráf, BFS | Huszárlépések számának szélességi bejárása | 1 | Bevezetés | ✅ kész |
| 13 | [Metró](<13. Metró */>) | Sorok, eseményszimuláció | Utasok darabszámos időléptetéses szimulációja, K-val eltolt érkezési tömbbel. | 1 | Magyarázat | ✅ kész |
| 14 | [Metróállomás](<14. Metróállomás ***/>) | Többszereplős szimuláció, sorok | Két mozgólépcső és a metró darabszámos időléptetéses szimulációja. | 3 | Mélyebb megértés | ✅ kész |
| 15 | [Őrök](<15. Őrök */>) | Intervallumok, Szimuláció | Őrhatókörök időbeli követése és lefedettségvizsgálat | 1 | Magyarázat | ✅ kész |
| 17 | [Vonatok szemben](<17. Vonatok szemben */>) | Eseményszimuláció, találkozás | Két vonat közös percenkénti szimulációja, szakaszfoglaltság követésével. | 1 | Magyarázat | ✅ kész |
| 18 | [Benzinkút](<18. Benzinkút ***/>) | Sorok, Terheléselosztás | Sorhossz alapú tankolási/feltöltési szimuláció | 3 | Magyarázat | ✅ kész |
| 19 | [Körforgalom](<19. Körforgalom/>) | Közlekedési szimuláció, Diszkrét esemény | Körforgalmi belépés/kilépés külön leképezésekkel és időzített áthaladással | – | Mélyebb megértés | ✅ kész |
| 20 | [Ügyfélkapu](<20. Ügyfélkapu/>) | Szimuláció: sorbanállás | Érkezési sorrend szerinti szimuláció prioritásos sorral (ügyintézési idő, érkezés, sorszám). | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 21 | [Várólista](<21. Várólista/>) | Sor, FIFO | Egyszerű várólista-szimuláció érkezési sorrenddel | – | Bevezetés | ✅ kész |
| 22 | [Vonatok](<22. Vonatok/>) | Szimuláció: vonatforgalom | Eseményvezérelt szimuláció szakaszonként prioritásos sorral (készenlét, irány, sorszám). | 2 | Magyarázat | ✅ kész |
| 23 | [Vonatok 1-2 vágánnyal](<23. Vonatok 1-2 vágánnyal/>) | Szimuláció: vonatforgalom | Eseményvezérelt szimuláció szakaszkapacitással (vágányszám), prioritásos sorral. | 3 | Mélyebb megértés | ✅ kész |
| 24 | [Vizitúra](<24. Vizitúra/>) | Mohó: visszafelé számolás | Hátulról számolt igények, előre haladva csak a hiány felvétele; előtte elérhetőség-szimuláció. | 2 | Magyarázat | ✅ kész |
| 25 | [Ütemezés azonos futási idővel](<25. Ütemezés azonos futási idővel/>) | Ütemezés, Körbeforgó sor | Körkörös feladatfeldolgozás azonos futási időkre | – | Magyarázat | ✅ kész |
| 26 | [Hegymászó](<26. Hegymászó/>) | Mohó: készletezés | Felfelé mohó felvétel a visszaútra szükséges tartalékkal; csúcsra és elérhetőségre külön ellenőrzés. | 3 | Mélyebb megértés | ✅ kész |
| 27 | [Ütemezés különböző futási idővel](<27. Ütemezés különböző futási idővel/>) | Ütemezés, Prioritási sor | Legrövidebb hátralévő idejű feladat kiválasztása prioritási sorral | – | Magyarázat | ✅ kész |
| 28 | [Ügyfélszolgálat](<28. Ügyfélszolgálat **/>) | Szimuláció: ügyfélszolgálat | Eseményvezérelt szimuláció: FIFO sor, a legkisebb sorszámú szabad pult min-heapből. | 2 | Magyarázat | ✅ kész |
| 29 | [Nemzetközi Rántott Hús Fesztivál](<29. Nemzetközi Rántott Hús Fesztivál ****/>) | Prefixösszeg, monoton verem | Monoton verem a járható végpontokhoz, szakaszminimum a legtöbb hús kiszámításához | 4 | Mélyebb megértés | ✅ kész |
| 30 | [Bábuk ütközése visszapattanással](<30. Bábuk ütközése visszapattanással/>) | Szimuláció: ütközés | Idősoros szimuláció, falnál egy irány előjelének megfordítása, páronkénti ütközésvizsgálat | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 31 | [Bábuk ütközése átlósan](<31. Bábuk ütközése átlósan/>) | Szimuláció: ütközés | Idősoros szimuláció, a falnál mindkét irány megfordul, ütközés: azonos vagy másik bábu mezőjére lépés | 3 | Magyarázat | ✅ kész |
| 32 | [Orvos](<32. Orvos/>) | Sorbanállás, FIFO | FIFO kezdési idő (max(érkezés, előző befejezés)), jelenlévők száma érkezés/befejezés összefésüléssel | 1 | Bevezetés | ✅ kész |
| 33 | [Posta](<33. Posta/>) | Eseményalapú szimuláció | Eseményalapú szimuláció közös FIFO sorral, ügyintézők befejezési idejét prioritási sor tartja | 2 | Magyarázat | ✅ kész |
| 34 | [Úthálózat szimuláció](<34. Úthálózat szimuláció/>) | Szimuláció: forgalmi lámpák | Autónkénti szimuláció, lámpafázis-várakozás és a célhoz közelebbi irány választása | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 35 | [Sejtautomata síkon](<35. Sejtautomata síkon/>) | Sejtautomata: 2D rács | Lépésenkénti szimuláció 3×3 környezet 9 bites maszkjával és szabálytáblázattal, a szélső cellák mindig fehérek | 3 | Magyarázat | ✅ kész |
| 36 | [Sejtautomata](<36. Sejtautomata/>) | Sejtautomata: 1D | Kétpufferes szimuláció 5 bites mintázat-maszkkal és szabálytáblázattal | 2 | Bevezetés | 🟡 kézi ellenőrzés |
| 37 | [Sejtautomata-2](<37. Sejtautomata-2/>) | Sejtautomata: általános sugár | Kétpufferes szimuláció 2L+1 bites mintázat-maszkkal és szabálytáblázattal | 2 | Magyarázat | 🟡 kézi ellenőrzés |
