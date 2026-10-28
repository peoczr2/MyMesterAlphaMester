# Programozási tételek: sorozatszámítás – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 29 feladat · ✅ kész 25 · ❌ hibás 0 · 🟡 kézi 2 · 🟡 nincs minta/speciális 2 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Első teaforgalmazó összes eladott mennyisége](<1. Első teaforgalmazó összes eladott mennyisége */>) | Feltételes összegzés | Lineáris bejárás, az első elem neve alapján feltételes összegzés. | 1 | Bevezetés | ✅ kész |
| 2 | [Horgászverseny - halfajták mennyisége](<2. Horgászverseny - halfajták mennyisége */>) | Sorozatszámítás: oszlopösszeg | Oszloponkénti összegzés egy K hosszú tömbben, soronként beolvasva | 1 | Bevezetés | ✅ kész |
| 3 | [Horgászverseny - horgász halai](<3. Horgászverseny - horgász halai */>) | Sorozatszámítás: sorösszeg | Soronkénti összegzés belső ciklussal, a külső ciklus a horgászokon megy. | 1 | Bevezetés | ✅ kész |
| 4 | [Lakosságszám](<4. Lakosságszám */>) | Csoportonkénti összegzés | Megyénkénti összegzés map-pel, a megyék bemeneti megjelenési sorrendjét vektorban tartva. | 1 | Bevezetés | ✅ kész |
| 5 | [Legnagyobb térfogat](<5. Legnagyobb térfogat */>) | Sorozatszámítás: összegzés | Lineáris bejárás, a kockák köbeinek összegzése. | 1 | Bevezetés | ✅ kész |
| 6 | [Menetrend](<6. Menetrend */>) | Sorozatszámítás: logikai ÉS | Oszloponkénti logikai ÉS: egy 1-es tömb, amelyet minden 0 elem nullára állít. | 1 | Bevezetés | ✅ kész |
| 7 | [Nyersanyagköltség](<7. Nyersanyagköltség */>) | Sorozatszámítás: szorzatösszeg | Egységárak tömbben, a receptsorok egységár·darabszám szorzatainak összegzése. | 1 | Bevezetés | ✅ kész |
| 8 | [Összes esőzés mennyisége](<8. Összes esőzés mennyisége */>) | Sorozatszámítás: összegzés | Lineáris bejárás, a napi mérések összegzése egyetlen változóban. | 1 | Bevezetés | ✅ kész |
| 9 | [Összes utas száma a villamoson](<9. Összes utas száma a villamoson */>) | Összegzés | Lineáris bejárás, a felszállók számának összegzése egyetlen változóban. | 1 | Bevezetés | ✅ kész |
| 10 | [Összterület](<10. Összterület */>) | Összegzés | Lineáris bejárás, a szélességek négyzetének összegzése. | 1 | Bevezetés | 🟡 nincs minta |
| 11 | [Összterület négyzetekkel](<11. Összterület négyzetekkel */>) | Összegzés | Lineáris bejárás, a szélességek négyzetének összegzése. | 1 | Bevezetés | 🟡 nincs minta |
| 12 | [Összterület téglalapokkal](<12. Összterület téglalapokkal */>) | Összegzés | Lineáris bejárás, téglalapok területének (szélesség·hosszúság) összegzése. | 1 | Bevezetés | ✅ kész |
| 13 | [Pénzfelvételek összege](<13. Pénzfelvételek összege */>) | Feltételes összegzés | Lineáris bejárás, a pénzfelvételi (-2 jelű) események összegzése. | 1 | Bevezetés | ✅ kész |
| 14 | [Sikertelen napokon fogott halak száma](<14. Sikertelen napokon fogott halak száma */>) | Feltételes összegzés | Lineáris bejárás, feltételes összegzés a K-nál kisebb napokon. | 1 | Bevezetés | ✅ kész |
| 15 | [Tervbe nem tartozó falak összhossza](<15. Tervbe nem tartozó falak összhossza */>) | Különbségtömb | Oldalankénti különbségtömb, a lefedett mezők levonása a kerületből. | 1 | Magyarázat | ✅ kész |
| 16 | [Benzinmaradék](<16. Benzinmaradék **/>) | Összegzés | Mérleg: kezdő benzin plusz tankolások, mínusz a teljes fogyasztás. | 2 | Bevezetés | ✅ kész |
| 17 | [Foglalt napok száma](<17. Foglalt napok száma **/>) | Sorozatszámítás: összegzés | Foglalt napok összegzése termenként: a foglalás hossza U−E+1, tömbbe gyűjtve | 2 | Bevezetés | ✅ kész |
| 18 | [Heti eső mennyisége](<18. Heti eső mennyisége */>) | Sorozatszámítás: sorösszeg | Soronkénti összegzés belső ciklussal, a külső ciklus a heteken megy végig | 1 | Bevezetés | ✅ kész |
| 19 | [Olimpiai kvalifikáció összpontszáma](<19. Olimpiai kvalifikáció összpontszáma ***/>) | Sorozatszámítás: pontozás | Helyezésenkénti pontszám képlettel (2·(K−h)+1), versenyzőnként összegezve | 3 | Magyarázat | ✅ kész |
| 20 | [Leértékelés haszna](<20. Leértékelés haszna ***/>) | Sorozatszámítás: összegzés | Termékenként összegezzük a két hét bevételét és hasznát, majd kiírjuk a különbséget. | 3 | Bevezetés | ✅ kész |
| 21 | [Almaszállítás](<21. Almaszállítás/>) | Kétmutatós módszer | Kétmutatós csúszóablak: a pozitív súlyok miatt a legrövidebb K összegű szakasz egy menetben megtalálható. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 22 | [Kerékpárverseny](<22. Kerékpárverseny/>) | Kétmutatós módszer | Kétmutatós csúszóablak: a pozitív távolságok miatt a legrövidebb K hosszúságú szakasz egy menetben megtalálható. | 2 | Magyarázat | ✅ kész |
| 23 | [Középső életkorú](<23. Középső életkorú/>) | Gyakoriság-tömb | Gyakoriság-tömb a korokra, majd a kumulált darabszámokból a (N+1)/2. elem megkeresése. | 2 | Magyarázat | ✅ kész |
| 24 | [Középső születésnapú](<24. Középső születésnapú/>) | Gyakorisági tömb, medián | Naponkénti gyakorisági tömb, halmozott összeg a középső pozícióig. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 25 | [Gázvezeték](<25. Gázvezeték/>) | Gráf: láncok, minimum | Láncok bejárása a lelőhelyektől, a szakaszkapacitások minimuma a fogyasztóig. | 2 | Magyarázat | ✅ kész |
| 26 | [Áruszállítás](<26. Áruszállítás/>) | Előtag-összeg, minimum | Előtag-összegekkel minden k-ra O(1)-ben a két kamion terhelésének maximuma. | 2 | Magyarázat | ✅ kész |
| 27 | [Vízvezeték](<27. Vízvezeték/>) | Gráf: láncok, szimuláció | Lánconként követjük a vizet: a szakasz kapacitása és a városok F-es levonása korlátoz. | 3 | Magyarázat | ✅ kész |
| 28 | [Szállítás](<28. Szállítás/>) | Prefixösszeg | Előtag-összegekkel O(1) bevétel minden központi raktárra, majd a maximum minimalizálása. | 3 | Magyarázat | ✅ kész |
| 29 | [Több konzolt kiadó gyártó](<29. Több konzolt kiadó gyártó */>) | Csoportonkénti összegzés | Gyártónként konzolszámok összegzése, majd a két megadott gyártó összehasonlítása. | 1 | Bevezetés | ✅ kész |
