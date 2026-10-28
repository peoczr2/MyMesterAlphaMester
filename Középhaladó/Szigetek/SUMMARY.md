# Szigetek – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 29 feladat · ✅ kész 29 · ❌ hibás 0 · 🟡 kézi 0 · 🟡 nincs minta/speciális 0 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [A második felében alacsonyabb csúcs volt?](<1. A második felében alacsonyabb csúcs volt? */>) | Minimumkeresés | Egy bejárás: az eddigi csúcsok minimumának nyilvántartása, második felben kisebb csúcs keresése. | 1 | Magyarázat | ✅ kész |
| 2 | [Alacsony szigetek](<2. Alacsony szigetek */>) | Feltételes szűrés | Szigetenként a maximum, a 100 m alatti magasságok gyűjtése listába | 1 | Bevezetés | ✅ kész |
| 3 | [Leghosszabb tengerszakasz hossza](<3. Leghosszabb tengerszakasz hossza */>) | Maximumkeresés | Egy bejárás futó számlálóval, a leghosszabb egymás utáni 0-sorozat keresése. | 1 | Bevezetés | ✅ kész |
| 4 | [Az első felében magasabb csúcs volt?](<4. Az első felében magasabb csúcs volt? */>) | Suffix-maximum | Csúcsok fordított bejárása, a későbbi csúcsok maximumának nyilvántartása. | 1 | Magyarázat | ✅ kész |
| 5 | [Csúcs nélküli sziget](<5. Csúcs nélküli sziget */>) | Tömb: szakaszok | Szigetek bejárása, belső elemek csúcs-ellenőrzése, első csúcsmentes sziget kiírása | 1 | Magyarázat | ✅ kész |
| 6 | [Egymáshoz legközelebbi szigetpár](<6. Egymáshoz legközelebbi szigetpár */>) | Tömb: minimumkeresés | Szigetek gyűjtése, szomszédos szigetpárok távolságának minimuma, korábbi pár előnyben | 1 | Magyarázat | ✅ kész |
| 7 | [Egyre keskenyebb szigetek?](<7. Egyre keskenyebb szigetek? */>) | Tömb: monotonitás | Szigetek hosszainak szomszédos összehasonlítása szigorú csökkenésre | 1 | Bevezetés | ✅ kész |
| 8 | [Egyre magasabb szigetek?](<8. Egyre magasabb szigetek? */>) | Tömb: monotonitás | Szigetek csúcsmagasságainak szomszédos összehasonlítása szigorú növekedésre | 1 | Bevezetés | ✅ kész |
| 9 | [Egyre szélesebb szigetek?](<9. Egyre szélesebb szigetek? */>) | Összefüggő szakaszok | Egy bejárás: a szigetek szakaszait keressük, és a szélességek szigorú növekedését ellenőrizzük. | 1 | Magyarázat | ✅ kész |
| 10 | [Hegycsúcsok magasságai](<10. Hegycsúcsok magasságai */>) | Feltételes szűrés | Egy bejárás: a három egymást követő mérés feltételének szűrése, a csúcsok magasságainak kiírása. | 1 | Bevezetés | ✅ kész |
| 11 | [Legelszigeteltebb sziget](<11. Legelszigeteltebb sziget */>) | Maximumkeresés | Szigetenként a két oldali legközelebbi szárazföld távolságának minimuma, ennek maximuma. | 1 | Magyarázat | ✅ kész |
| 12 | [Leginkább középen lévő sziget](<12. Leginkább középen lévő sziget */>) | Minimumkeresés | Szigetenként a két part közül a kisebb távolság az óceán közepétől; ennek minimuma. | 1 | Magyarázat | ✅ kész |
| 13 | [Legkisebb szintkülönbségű sziget](<13. Legkisebb szintkülönbségű sziget */>) | Minimumkeresés | Szigetenként egy bejárás: a legnagyobb és a legkisebb mérés különbsége, ennek minimuma. | 1 | Bevezetés | ✅ kész |
| 14 | [Leglaposabb csúcsú sziget](<14. Leglaposabb csúcsú sziget */>) | Minimumkeresés | Szigetenként a csúcsok legkisebb meredeksége (a két oldal nagyobb különbsége), és ennek minimuma. | 1 | Magyarázat | ✅ kész |
| 15 | [Leglaposabb partú sziget](<15. Leglaposabb partú sziget */>) | Minimumkeresés | Szigetenként a két part közül a kisebb meredekség (a parti mérés magassága), ennek minimuma. | 1 | Magyarázat | ✅ kész |
| 16 | [Legmagasabb csúcs](<16. Legmagasabb csúcs */>) | Maximumkeresés | Egy bejárás: a három egymást követő mérés feltételének szűrése, a legmagasabb csúcs keresése. | 1 | Bevezetés | ✅ kész |
| 17 | [Legmagasabb csúcsú sziget](<17. Legmagasabb csúcsú sziget */>) | Maximumkeresés | Szakaszonként belső csúcsok keresése, a legmagasabb csúcs szigetének partjai | 1 | Magyarázat | ✅ kész |
| 18 | [Legmélyebb völgyű sziget](<18. Legmélyebb völgyű sziget */>) | Minimumkeresés | Szigetenként prefix- és suffix-maximum, a legmélyebb völgy szigetének partjai | 1 | Magyarázat | ✅ kész |
| 19 | [Legmeredekebb csúcsú sziget](<19. Legmeredekebb csúcsú sziget */>) | Maximumkeresés | Csúcs meredeksége: magasság mínusz a kisebbik szomszéd, legmeredekebb csúcs keresése | 1 | Magyarázat | ✅ kész |
| 20 | [Legszélesebb síkság szigeten](<20. Legszélesebb síkság szigeten */>) | Futamkeresés | Szigetenként egy bejárás: az egyenlő pozitív mérések leghosszabb futamának keresése. | 1 | Magyarázat | ✅ kész |
| 21 | [Legszélesebb sziget](<21. Legszélesebb sziget */>) | Maximumkeresés | Egy bejárás: a szigetek szélességének (a két part közti mérésszámnak) maximumának keresése. | 1 | Bevezetés | ✅ kész |
| 22 | [Legvölgyesebb sziget](<22. Legvölgyesebb sziget */>) | Prefix- és suffixmaximum | Szigetenként prefix- és suffix-maximum tömbökkel a völgyek számlálása, a legtöbb völgyű sziget keresése. | 1 | Magyarázat | ✅ kész |
| 23 | [Magas szigetek](<23. Magas szigetek */>) | Feltételes szűrés | Egy bejárás: szigetenként a legmagasabb pont, az 1000 m-nél magasabbak szűrése és sorban gyűjtése. | 1 | Bevezetés | ✅ kész |
| 24 | [Meredekebbek a bal oldali partok?](<24. Meredekebbek a bal oldali partok? */>) | Feltételes számlálás | Szigetenként a bal és a jobb part magasságának összehasonlítása, két számlálóval. | 1 | Bevezetés | ✅ kész |
| 25 | [Minden sziget legmagasabb pontja csúcs?](<25. Minden sziget legmagasabb pontja csúcs? */>) | Lokális maximum | Szigetenként a legmagasabb pontok ellenőrzése: mindegyik csúcs-e a szomszédai alapján. | 1 | Magyarázat | ✅ kész |
| 26 | [Szigetek teljes hossza](<26. Szigetek teljes hossza */>) | Szakaszok összegzése | Egy bejárás: a kontinenshez nem tartozó nem nulla szakaszok hosszának összegzése. | 1 | Bevezetés | ✅ kész |
| 27 | [Szigeteken lévő hegycsúcsok magasságai](<27. Szigeteken lévő hegycsúcsok magasságai */>) | Lokális maximum és szűrés | Egy bejárás: a szigeteken belüli, 500 m-nél magasabb csúcsok szűrése a szomszédok alapján. | 1 | Magyarázat | ✅ kész |
| 28 | [Tengerszakaszok teljes hossza](<28. Tengerszakaszok teljes hossza */>) | Feltételes számlálás | Egy bejárás, a 0 magasságú mérések összeszámolása. | 1 | Bevezetés | ✅ kész |
| 29 | [Van két egyforma szélességű sziget?](<29. Van két egyforma szélességű sziget? */>) | Halmazos ellenőrzés | Szigetek szélességének (partok indexkülönbsége) halmazba gyűjtése, duplikáció keresése. | 1 | Magyarázat | ✅ kész |
