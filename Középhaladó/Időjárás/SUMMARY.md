# Időjárás – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 37 feladat · ✅ kész 35 · ❌ hibás 0 · 🟡 kézi 2 · 🟡 nincs minta/speciális 0 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Az átlag kisebb a minimum és maximum átlagánál](<1. Az átlag kisebb a minimum és maximum átlagánál/>) | Átlag és szélsőértékek | Soronként egy bejárás: összeg, minimum, maximum; a feltétel szorzással: 2·összeg < M·(min+max). | 2 | Magyarázat | ✅ kész |
| 2 | [Átlagosan legmelegebb település](<2. Átlagosan legmelegebb település/>) | Mátrix: összegek maximuma | Soronként összegzés, a legnagyobb összeg és sorszám követése egy bejárásban. | 1 | Bevezetés | ✅ kész |
| 3 | [Települések átlagosnál több melegebb nappal](<3. Települések átlagosnál több melegebb nappal/>) | Átlaghoz viszonyítás | Településenként összeg, majd az átlag feletti és alatti napok megszámolása | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 4 | [Hamarabb kezdődik a felmelegedés](<4. Hamarabb kezdődik a felmelegedés/>) | Szomszédos elemek összevetése | Első csökkenés utáni első növekedés napja, egyedi legkorábbi kezdet keresése | 3 | Magyarázat | ✅ kész |
| 5 | [Előző napnál hűvösebb napok](<5. Előző napnál hűvösebb napok/>) | Szomszédos elemek összevetése | Napi hőmérsékletek balról jobbra összevetése az előző nappal, a csökkenő napok jelölése. | 2 | Bevezetés | ✅ kész |
| 6 | [Leghűvösebb települések legmelegebb napjai](<6. Leghűvösebb települések legmelegebb napjai/>) | Napi minimumok maximuma | Napi minimumok tömbben, majd a legnagyobb napi minimumot elérő napok kiválasztása. | 3 | Magyarázat | ✅ kész |
| 7 | [Legkisebb ingadozású települések](<7. Legkisebb ingadozású települések/>) | Maximum–minimum különbség | Soronkénti maximum és minimum, különbségük tömbben, majd a legkisebb különbség kiválasztása. | 2 | Bevezetés | ✅ kész |
| 8 | [Legmelegebb napok](<8. Legmelegebb napok/>) | Globális maximum napjai | Napi maximumok a beolvasás közben, majd a globális maximumot elérő napok kiírása. | 1 | Bevezetés | ✅ kész |
| 9 | [Legmelegebb települések](<9. Legmelegebb települések/>) | Maximumkeresés | Soronkénti maximum beolvasás közben, majd a globális maximummal egyező sorok gyűjtése | 2 | Bevezetés | 🟡 kézi ellenőrzés |
| 10 | [Legmelegebb települések leghidegebb napjai](<10. Legmelegebb települések leghidegebb napjai/>) | Mátrix: szélsőértékek | Az országos maximumot elérő települések sorában a saját minimumnapok megjelölése, majd a jelölt napok kiírása. | 3 | Mélyebb megértés | ✅ kész |
| 11 | [Legszélsőségesebb települések](<11. Legszélsőségesebb települések/>) | Mátrix: szélsőérték-különbség | Soronként egy bejárás a legnagyobb és legkisebb érték különbségéhez, majd a maximális különbségű települések kiírása. | 2 | Bevezetés | ✅ kész |
| 12 | [Legtöbb helyen maximális hőmérsékletű napok](<12. Legtöbb helyen maximális hőmérsékletű napok/>) | Mátrix: oszlopszámlálás | Az országos maximumot egyezően elért értékek számlálása naponként, majd a legnagyobb darabszámú napok kiírása. | 2 | Magyarázat | ✅ kész |
| 13 | [Legtöbbször legmelegebb települések](<13. Legtöbbször legmelegebb települések/>) | Mátrix: napi maximumok | Naponként megkeressük az aznapi maximumot, és minden településnél számoljuk a maximumot elérő napok számát. | 2 | Magyarázat | ✅ kész |
| 14 | [Legváltozatosabb települések](<14. Legváltozatosabb települések/>) | Mátrix: irányváltások | Soronként a nem nulla napi különbségek előjelét követjük, és számoljuk az előjelváltásokat. | 3 | Magyarázat | ✅ kész |
| 15 | [Legváltozóbb települések](<15. Legváltozóbb települések/>) | Mátrix: maximális változás | Soronként a szomszédos napok közti abszolút különbségek maximuma, majd a legnagyobbat elérő települések kiírása. | 2 | Bevezetés | ✅ kész |
| 16 | [Sem maximum, sem minimum](<16. Sem maximum, sem minimum/>) | Mátrix: napi szélsőértékek | Naponkénti szélsőértékek kiszámítása, majd a soha szélsőértéket nem elérő települések kiírása. | 2 | Magyarázat | ✅ kész |
| 17 | [Fagyos napok száma szerinti sorrend](<17. Fagyos napok száma szerinti sorrend/>) | Mátrix: oszlopok számlálása | Napi számlálás a negatív értékekre, majd rendezés a számláló szerint csökkenően. | 2 | Bevezetés | ✅ kész |
| 18 | [Napi maximumok száma szerinti sorrend](<18. Napi maximumok száma szerinti sorrend/>) | Mátrix: napi maximumok | Napi maximum keresése, településenként a maximumot elérő napok számlálása, majd rendezés. | 2 | Magyarázat | ✅ kész |
| 19 | [Az átlagnál melegebb napok száma szerinti sorrend](<19. Az átlagnál melegebb napok száma szerinti sorrend/>) | Mátrix: átlag feletti számlálás | Soronkénti összeg, majd egész-összehasonlítás (M·h > összeg) alapján napok számlálása és rendezés. | 3 | Magyarázat | ✅ kész |
| 20 | [Minden településen melegebb van](<20. Minden településen melegebb van/>) | Szűrés napok között | Egy bejárás, napokhoz tartozó igaz/hamis jelző, az előző napi értékkel való összevetés | 2 | Bevezetés | ✅ kész |
| 21 | [Mindenhol meleg napok](<21. Mindenhol meleg napok/>) | Feltétel minden elemre | Egy bejárás, naponként logikai jelző, nem pozitív érték kizárja a napot | 1 | Bevezetés | ✅ kész |
| 22 | [Mindig fagyos települések](<22. Mindig fagyos települések/>) | Feltétel minden elemre | Soronként egy bejárás, egy nem negatív érték kizárja a települést | 1 | Bevezetés | ✅ kész |
| 23 | [Másnál melegebb település](<23. Másnál melegebb település/>) | Bitset: halmazmetszet | Naponkénti csoportosítás, bitsetek metszése az összes napra | 3 | Magyarázat | ✅ kész |
| 24 | [Minden nap meleg települések](<24. Minden nap meleg települések/>) | Feltétel minden elemre | Soronként egy bejárás, logikai jelző a nem pozitív érték kizárására | 1 | Bevezetés | ✅ kész |
| 25 | [Másnál melegebb nap](<25. Másnál melegebb nap/>) | Bitset: halmazmetszet | Településenként hőmérséklet szerinti csoportosítás, napokra bitset-metszet | 3 | Magyarázat | ✅ kész |
| 26 | [Nagy változású települések](<26. Nagy változású települések/>) | Szomszédos elemek különbsége | Soronként egy bejárás, az előző nappal való abszolút különbség vizsgálata | 1 | Bevezetés | ✅ kész |
| 27 | [Sokáig hidegebbé váló települések](<27. Sokáig hidegebbé váló települések/>) | Egymás utáni csökkenések | Soronként egy bejárás, futó számláló az egymás utáni csökkenések hosszára | 2 | Bevezetés | ✅ kész |
| 28 | [Sokáig melegebbé váló települések](<28. Sokáig melegebbé váló települések/>) | Egymás utáni növekedések | Soronként egy bejárás, futó számláló az egymás utáni növekedések hosszára | 2 | Bevezetés | ✅ kész |
| 29 | [Sokáig meleg települések](<29. Sokáig meleg települések/>) | Küszöb feletti sorozat | Soronként egy bejárás, futó számláló a 30 fok feletti napok sorozatának hosszára | 2 | Bevezetés | ✅ kész |
| 30 | [Sok településen meleg napok](<30. Sok településen meleg napok/>) | Oszlopok számlálása | Oszloponként számláló a 30 fokot elérő települések számára, majd 2·db ≥ N feltétel | 2 | Bevezetés | ✅ kész |
| 31 | [Nagyon hideg település](<31. Nagyon hideg település/>) | Átlag és minimum összevetése | Beolvasás közben összeg és minimum, az átlag összevetése M·min alakban, egész számokon | 2 | Magyarázat | ✅ kész |
| 32 | [Települések átlag szerinti sorrendje](<32. Települések átlag szerinti sorrendje/>) | Rendezés egyedi összehasonlítóval | Összegek a beolvasás közben, majd egyedi összehasonlítóval rendezés (összeg csökkenő, sorszám növekvő) | 2 | Bevezetés | ✅ kész |
| 33 | [A települések legalább felében melegedő napok](<33. A települések legalább felében melegedő napok/>) | Szomszédos elemek összevetése | Soronként szomszédos elemek összevetése, napi számláló, a feltétel 2·db ≥ N egész számokon | 2 | Bevezetés | ✅ kész |
| 34 | [Kis maximumú település](<34. Kis maximumú település/>) | Maximum és átlag összevetése | Beolvasás közben maximum és összeg, a maximum összevetése az átlaggal szorzással (max·M < összeg) | 2 | Magyarázat | ✅ kész |
| 35 | [Nagyon meleg település](<35. Nagyon meleg település/>) | Minimum és maximum összevetése | Minimum és maximum a beolvasás közben, majd páronkénti összevetés a többi településsel | 2 | Magyarázat | ✅ kész |
| 36 | [Település valamikor minimális hőmérséklettel](<36. Település valamikor minimális hőmérséklettel/>) | Napi minimum kiválasztása | Napi minimumok meghatározása a mátrixból, majd a minimumot elérő települések jelölése | 2 | Bevezetés | ✅ kész |
| 37 | [Település valamikor maximális hőmérséklettel](<37. Település valamikor maximális hőmérséklettel/>) | Napi maximum kiválasztása | Napi maximumok meghatározása a mátrixból, majd a maximumot elérő települések jelölése | 2 | Bevezetés | ✅ kész |
