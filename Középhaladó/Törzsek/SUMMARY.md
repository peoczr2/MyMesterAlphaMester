# Törzsek – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 45 feladat · ✅ kész 39 · ❌ hibás 0 · 🟡 kézi 6 · 🟡 nincs minta/speciális 0 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Adott századi háborúk](<1. Adott századi háborúk/>) | Intervallumok: összegzés | Intervallum-átfedés szűrése, majd a háborúk teljes hosszának összegzése. | 2 | Bevezetés | ✅ kész |
| 2 | [Békés évek](<2. Békés évek */>) | Intervallumok: eseménypont-bejárás | Eseménypont-bejárás rendezett map-pel: nulla számlálójú évek kiírása | 1 | Magyarázat | ✅ kész |
| 3 | [Békés törzs](<3. Békés törzs */>) | Halmaz: részvétel | Háborúban szereplő törzsek halmazba gyűjtése, majd az első nem szereplő sorszám keresése. | 1 | Bevezetés | ✅ kész |
| 4 | [Békés törzsek](<4. Békés törzsek */>) | Jelölő tömb: érintetlen elemek | Jelölő tömb a háborúban részt vevő törzsekről, a jelöletlen sorszámok kiírása. | 1 | Bevezetés | ✅ kész |
| 5 | [Csak egy ellenfél](<5. Csak egy ellenfél */>) | Halmazok: különböző elemek | Törzsenkénti halmaz a különböző ellenfelekről, majd az egy elemű halmazú törzs keresése. | 1 | Magyarázat | ✅ kész |
| 6 | [Csak egyszer háborúzó törzs](<6. Csak egyszer háborúzó törzs */>) | Számlálás: gyakoriság | Törzsenkénti háborúszámláló, az első pontosan egyet számláló törzs keresése. | 1 | Bevezetés | ✅ kész |
| 7 | [Egészében adott századi háborúk száma](<7. Egészében adott századi háborúk száma */>) | Intervallumok: tartalmazás | Két évszámhatár a századra, majd lineáris bejárás a teljes egészében beeső háborúkra. | 1 | Bevezetés | ✅ kész |
| 8 | [Egy évnél rövidebb](<8. Egy évnél rövidebb */>) | Számlálás: egyezés | Lineáris bejárás, a kezdő és a befejező év egyezésének számlálása. | 1 | Bevezetés | ✅ kész |
| 9 | [Egy törzs adott évszázadba eső háborúi összeideje](<9. Egy törzs adott évszázadba eső háborúi összeideje */>) | Intervallumok: metszet, összegzés | Háborúnként a századba eső évek metszetének hosszát összegezzük, az S törzs háborúira. | 1 | Bevezetés | ✅ kész |
| 10 | [Egy törzs adott századi háborúi](<10. Egy törzs adott századi háborúi */>) | Megszámolás | Lineáris bejárás: a törzs részvételének és az évszázadbeli átfedésnek egyidejű ellenőrzése. | 1 | Bevezetés | ✅ kész |
| 11 | [Egy törzs háborúi](<11. Egy törzs háborúi */>) | Megszámolás | Lineáris bejárás, feltétel szerinti számlálás. | 1 | Bevezetés | ✅ kész |
| 12 | [Egy törzs háborús évei egy évszázadban](<12. Egy törzs háborús évei egy évszázadban */>) | Intervallumok: évek egyesítése | Jelölőtömb a századi évekre, a közös évek egyszeri számlálása. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 13 | [Egy törzs leghosszabb békés időszaka](<13. Egy törzs leghosszabb békés időszaka */>) | Intervallumok, rések keresése | Kezdés szerint rendezés, majd a legnagyobb szabad szakasz keresése a legkésőbbi befejezés alapján. | 1 | Magyarázat | ✅ kész |
| 14 | [Egy törzs leghosszabb háborúja](<14. Egy törzs leghosszabb háborúja */>) | Keresés, maximum | Lineáris bejárás, a kérdezett törzs háborúi közül a leghosszabb keresése. | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 15 | [Egy törzs legrövidebb háborúja](<15. Egy törzs legrövidebb háborúja */>) | Keresés, minimum | Lineáris bejárás, a kérdezett törzs háborúi közül a legrövidebb keresése. | 1 | Bevezetés | ✅ kész |
| 16 | [Egy törzs legrövidebb háborús időszaka](<16. Egy törzs legrövidebb háborús időszaka */>) | Intervallum-összevonás | Kezdés szerint rendezés, átfedő háborúk összevonása, a legrövidebb összevont időszak keresése. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 17 | [Első békés év](<17. Első békés év */>) | Intervallumok: eseménypont-bejárás | Eseménypont-bejárás rendezett map-pel: az első nulla számlálójú év | 1 | Magyarázat | ✅ kész |
| 18 | [Első év, amikor csak egy háború volt](<18. Első év, amikor csak egy háború volt */>) | Intervallumok: eseménypont-bejárás | Eseménypont-bejárás rendezett map-pel: az első egyes számlálójú év | 1 | Magyarázat | ✅ kész |
| 19 | [Gyakori háborúk](<19. Gyakori háborúk */>) | Számlálás, összehasonlítás | Háborúk számlálása évszázadonként a kezdő év alapján, majd összehasonlítás | 1 | Bevezetés | ✅ kész |
| 20 | [Háború a századfordulón](<20. Háború a századfordulón */>) | Intervallumok: évszázad-határ | Kezdő és befejező év századának összehasonlítása, az első eltérő háború sorszáma. | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 21 | [Háború együttes ideje adott században](<21. Háború együttes ideje adott században */>) | Intervallumok: összegzés | A háborúkat a megadott századra vágjuk, és a metszetük éveit (végpontokkal) összegezzük. | 1 | Bevezetés | ✅ kész |
| 22 | [Háború nélkül](<22. Háború nélkül */>) | Intervallumok: rések keresése | Kezdés szerint rendezés, átfedő intervallumok egyesítése, a lefedetlen évek számolása a teljes időszakból. | 1 | Magyarázat | ✅ kész |
| 23 | [Háborús évek száma adott században](<23. Háborús évek száma adott században */>) | Intervallumok: évek egyesítése | A századra vágott háborús intervallumok egyesítése, az egyesített évek számának összege. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 24 | [Háborúzó törzsek](<24. Háborúzó törzsek */>) | Halmaz: egyedi elemek száma | Századonként halmazba gyűjtjük a háborúk törzseit, ha kezdő- vagy befejező év esik a századba. | 1 | Magyarázat | ✅ kész |
| 25 | [Három évszázad háborúi](<25. Három évszázad háborúi */>) | Számlálás: évszázadokra bontva | Háborúnként, századonként egyszer ellenőrizzük a kezdő- vagy befejező évet, és számlálót növelünk. | 1 | Bevezetés | ✅ kész |
| 26 | [Kinek volt több háborúja](<26. Kinek volt több háborúja */>) | Számlálás, összehasonlítás | Minden törzs háborúit megszámoljuk, majd a két kérdezett törzs számát összehasonlítjuk. | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 27 | [Legellenségeseb törzs](<27. Legellenségeseb törzs */>) | Halmaz: különböző ellenségek száma | Törzsenként halmazba gyűjtjük a különböző ellenségeket, majd a legnagyobb halmazú törzset keressük. | 1 | Magyarázat | ✅ kész |
| 28 | [Legháborgóbb év](<28. Legháborgóbb év */>) | Eseménypont-bejárás | Háborúk kezdő- és záró eseményeinek rendezése, majd a legtöbb egyidejű háború keresése eseménypont-bejárással. | 1 | Magyarázat | ✅ kész |
| 29 | [Leghosszab haborus idoszak](<29. Leghosszab haborus idoszak */>) | Intervallumok: összevonás | Háborús intervallumok rendezése és összevonása, majd a leghosszabb összevont szakasz keresése. | 1 | Magyarázat | ✅ kész |
| 30 | [Leghosszabb béke](<30. Leghosszabb béke */>) | Intervallumok: rések | Háborús intervallumok összevonása, majd a két szomszédos szakasz közti leghosszabb rés keresése. | 1 | Magyarázat | ✅ kész |
| 31 | [Leghosszabb háború](<31. Leghosszabb háború */>) | Keresés, maximum | Lineáris bejárás, az eddigi leghosszabb háború egy változóban, egyenlőségnél a korábbi kezdéssel. | 1 | Bevezetés | ✅ kész |
| 32 | [Legkevésbé ellenséges törzs](<32. Legkevésbé ellenséges törzs */>) | Halmaz, egyedi elemek | Törzsenkénti halmaz a különböző ellenségekről, minimum keresés a nem üres halmazok között. | 1 | Magyarázat | ✅ kész |
| 33 | [Legkevesebbet háborúzó törzs](<33. Legkevesebbet háborúzó törzs */>) | Megszámolás, minimum | Számláló tömb törzsenként, minimum keresés a nem nulla értékek között. | 1 | Bevezetés | ✅ kész |
| 34 | [Legnagyobb ellenségek](<34. Legnagyobb ellenségek */>) | Map, párok számlálása | Párok számlálása map-pel, rendezett sorszámpárral, a legnagyobb darabszám keresése. | 1 | Magyarázat | ✅ kész |
| 35 | [Legrövidebb béke](<35. Legrövidebb béke */>) | Intervallumok: rések | Kezdés szerint rendezés, az eddigi legkésőbbi befejezés követése, legrövidebb pozitív rés. | 1 | Magyarázat | ✅ kész |
| 36 | [Legrövidebb háború](<36. Legrövidebb háború */>) | Intervallumok: minimum | Egyetlen bejárás, a legrövidebb háború kiválasztása hossz, majd kezdő év szerint. | 1 | Bevezetés | ✅ kész |
| 37 | [Legrövidebb, 10 évnél hosszabb háború](<37. Legrövidebb, 10 évnél hosszabb háború */>) | Intervallumok: szűrés, minimum | Háborúk szűrése 10 évnél hosszabbakra, majd a legrövidebb kiválasztása egy bejárásban. | 1 | Bevezetés | ✅ kész |
| 38 | [Legtöbb ellenfél](<38. Legtöbb ellenfél */>) | Halmaz: különböző ellenfelek száma | Törzsenként halmazba gyűjtjük az ellenfeleket, a legnagyobb halmazú törzset keressük. | 1 | Magyarázat | ✅ kész |
| 39 | [Legtöbb törzs](<39. Legtöbb törzs */>) | Intervallumok: átfedés számolása | Kezdő- és befejező események rendezett bejárása, a legalább Y aktív háborús évek összegzése. | 1 | Magyarázat | ✅ kész |
| 40 | [Mindenkivel ellenséges törzs](<40. Mindenkivel ellenséges törzs */>) | Halmaz: különböző partnerek | Törzsenként halmaz az ellenfelekről, az első olyan törzs keresése, amelynek N-1 ellenfele van. | 1 | Magyarázat | ✅ kész |
| 41 | [Nem békés törzsek](<41. Nem békés törzsek */>) | Jelölő tömb: érintett elemek | Jelölő tömb a háborúban részt vevő törzsekről, a megjelölt sorszámok kiírása. | 1 | Bevezetés | ✅ kész |
| 42 | [Öt évnél hosszabb](<42. Öt évnél hosszabb */>) | Intervallumok: hossz szerinti számlálás | Lineáris bejárás: a háború hossza (kezdő- és befejező évvel együtt) összevetése O-val. | 1 | Bevezetés | ✅ kész |
| 43 | [Részben adott századi háborúk száma](<43. Részben adott századi háborúk száma */>) | Intervallumok: átfedés | Lineáris bejárás: a háború átfedi-e a megadott század évtartományát. | 1 | Bevezetés | ✅ kész |
| 44 | [Több háború](<44. Több háború */>) | Intervallumok: eseménypont-bejárás | Évenkénti változási események rendezett map-ben, a legalább Y-os szakaszok hosszának összegzése. | 1 | Magyarázat | ✅ kész |
| 45 | [Több törzs](<45. Több törzs */>) | Intervallumok: eseménypont-bejárás | Törzsenkénti aktív háborúszámláló és eseménypont-bejárás: legalább Y különböző törzs szakaszai. | 1 | Magyarázat | ✅ kész |
