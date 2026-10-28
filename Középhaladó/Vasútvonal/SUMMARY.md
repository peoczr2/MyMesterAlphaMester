# Vasútvonal – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 42 feladat · ✅ kész 42 · ❌ hibás 0 · 🟡 kézi 0 · 🟡 nincs minta/speciális 0 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Ameddig gazdaságossá válik](<1. Ameddig gazdaságossá válik */>) | Prefixösszeg | Utaslétszám prefixösszege, minden állomásig számolt profit, utolsó átmenet keresése | 1 | Magyarázat | ✅ kész |
| 2 | [Ameddig már nem gazdaságos](<2. Ameddig már nem gazdaságos */>) | Szuffixösszeg | Szakaszok eredményének hátulról történő összegzése, első negatív pont keresése. | 1 | Magyarázat | ✅ kész |
| 3 | [Csökkent a vonaton utazók száma](<3. Csökkent a vonaton utazók száma */>) | Számlálás | Lineáris bejárás, állomásonként a le > fel feltétel számlálása | 1 | Bevezetés | ✅ kész |
| 4 | [Csökkent az utasok száma](<4. Csökkent az utasok száma */>) | Keresés | Egy bejárás, az első olyan állomás keresése, ahol a leszállók száma nagyobb a felszállókénál | 1 | Bevezetés | ✅ kész |
| 5 | [Felszállók száma](<5. Felszállók száma */>) | Összegzés | Összegzés egy bejárásban: a felszállók számának összeadása | 1 | Bevezetés | ✅ kész |
| 6 | [Folyamatosan csökent az utasok száma](<6. Folyamatosan csökent az utasok száma */>) | Feltételes bejárás | Visszafelé bejárás Székesfehérvártól, megállás az első nem csökkenő állomásnál | 1 | Magyarázat | ✅ kész |
| 7 | [Folyamatosan nőtt az utasok száma](<7. Folyamatosan nőtt az utasok száma */>) | Feltételes bejárás | Elölről bejárás, az első olyan állomásnál megállás, ahol a felszállók száma nem nagyobb a leszállókénál | 1 | Bevezetés | ✅ kész |
| 8 | [Gazdaságos szomszédos állomáspárok](<8. Gazdaságos szomszédos állomáspárok */>) | Prefixösszeg | Futó utasszám egy bejárásban, szakaszonként a K·utasszám > M feltétel vizsgálata. | 1 | Bevezetés | ✅ kész |
| 9 | [Gazdaságos üzemeltetés Budapesttől](<9. Gazdaságos üzemeltetés Budapesttől */>) | Prefixösszeg | Futó bevétel és az útvonal kiadásának (V·(k−1)) összevetése állomásonként. | 1 | Magyarázat | ✅ kész |
| 10 | [Gazdaságos-e a vonat üzemeltetése](<10. Gazdaságos-e a vonat üzemeltetése */>) | Prefixösszeg | Összes bevétel (utas×szakasz) és összes kiadás szigorú összevetése egy bejárásban | 1 | Bevezetés | ✅ kész |
| 11 | [Legkevesebb ember fordult meg az állomáson](<11. Legkevesebb ember fordult meg az állomáson */>) | Minimumkeresés | Állomásonként le+fel összeg, minimum keresése egy bejárásban, döntetlenben a korábbi állomás | 1 | Bevezetés | ✅ kész |
| 12 | [Legkevesebb felszálló](<12. Legkevesebb felszálló */>) | Minimumkeresés | Felszállók minimuma egy bejárásban, az utolsó állomás kihagyásával, döntetlenben a korábbi | 1 | Bevezetés | ✅ kész |
| 13 | [Legkevesebb leszálló](<13. Legkevesebb leszálló */>) | Minimumkeresés | Lineáris bejárás, a legkisebb pozitív leszállószám keresése | 1 | Bevezetés | ✅ kész |
| 14 | [Legkevesebbel csökkent az utasok száma](<14. Legkevesebbel csökkent az utasok száma */>) | Feltételes kiválogatás | Lineáris bejárás, a változás (le - fel) legkisebb pozitív értékének keresése | 1 | Bevezetés | ✅ kész |
| 15 | [Legkevesebbel nőtt az utasok száma a vonaton](<15. Legkevesebbel nőtt az utasok száma a vonaton */>) | Feltételes kiválogatás | Lineáris bejárás, a változás (fel - le) legkisebb pozitív értékének keresése | 1 | Bevezetés | ✅ kész |
| 16 | [Legmesszebb lévő állomások – nem volt utas](<16. Legmesszebb lévő állomások – nem volt utas */>) | Prefixösszeg | Futó utasszám egy bejárásban, a leghosszabb nulla utasszámú szakasz keresése | 1 | Magyarázat | ✅ kész |
| 17 | [Legmesszebb lévő állomások – maximális létszám](<17. Legmesszebb lévő állomások – maximális létszám */>) | Leghosszabb összefüggő szakasz | Egy bejárás: a leghosszabb összefüggő, maximális létszámú szakasz keresése. | 1 | Bevezetés | ✅ kész |
| 18 | [Legmesszebb lévő állomáspár – folyamatosan voltak a vonaton](<18. Legmesszebb lévő állomáspár – folyamatosan voltak a vonaton */>) | Leghosszabb összefüggő szakasz | Egy bejárás: a leghosszabb összefüggő, pozitív létszámú szakasz keresése. | 1 | Bevezetés | ✅ kész |
| 19 | [Legtöbb leszálló az állomáson](<19. Legtöbb leszálló az állomáson */>) | Maximumkeresés | Lineáris maximumkiválasztás, egyenlőségnél a korábbi állomás marad. | 1 | Bevezetés | ✅ kész |
| 20 | [Legtöbbel csökkent az utasok száma a vonaton](<20. Legtöbbel csökkent az utasok száma a vonaton */>) | Minimumkeresés | Állomásonként a változás (fel - le) minimumának keresése egy bejárásban, döntetlenben a korábbi állomás | 1 | Bevezetés | ✅ kész |
| 21 | [Legtöbbel nőtt az utasok száma a vonaton](<21. Legtöbbel nőtt az utasok száma a vonaton */>) | Maximumkiválasztás | Állomásonként a változás (fel - le) maximumának keresése egy bejárásban, döntetlenben a korábbi állomás | 1 | Bevezetés | ✅ kész |
| 22 | [Legtöbben szálltak fel](<22. Legtöbben szálltak fel */>) | Maximumkiválasztás | Felszállók maximumának keresése egy bejárásban, döntetlenben a korábbi állomás | 1 | Bevezetés | ✅ kész |
| 23 | [Legtöbbet nőtt az utasok száma](<23. Legtöbbet nőtt az utasok száma */>) | Maximumkiválasztás | Állomásonként a változás (fel - le) maximumának keresése egy bejárásban, döntetlenben a korábbi állomás | 1 | Bevezetés | ✅ kész |
| 24 | [Leszállók és felszállók is voltak](<24. Leszállók és felszállók is voltak */>) | Feltételes számlálás | Egy bejárásban számolni azokat az állomásokat, ahol a leszállók és a felszállók száma is pozitív | 1 | Bevezetés | ✅ kész |
| 25 | [Leszállt-e mindenki](<25. Leszállt-e mindenki */>) | Szimuláció | Utasok számának követése egy bejárásban, az utolsó állomáson az érkezők és leszállók összevetése | 1 | Bevezetés | ✅ kész |
| 26 | [Meddig gazdaságos, ha lehet veszteséges szakasz](<26. Meddig gazdaságos, ha lehet veszteséges szakasz */>) | Prefixösszeg | Futó bevételösszeg és a Budapesttől mért szakaszok költsége, az utolsó gazdaságos állomás keresése egy bejárásban | 1 | Magyarázat | ✅ kész |
| 27 | [Mennyit fizettek az utasok?](<27. Mennyit fizettek az utasok? */>) | Összegzés | Az utas-szakasz párok összegének kiszámítása egy bejárásban, majd szorzás U-val | 1 | Bevezetés | ✅ kész |
| 28 | [Nem volt érdemes megállni](<28. Nem volt érdemes megállni */>) | Keresés | Lineáris bejárás, az első köztes állomás, ahol le és fel is nulla | 1 | Bevezetés | ✅ kész |
| 29 | [Nem volt felszálló](<29. Nem volt felszálló */>) | Keresés | Lineáris bejárás, az első állomás, ahol a felszállók száma nulla | 1 | Bevezetés | ✅ kész |
| 30 | [Nem volt leszálló](<30. Nem volt leszálló */>) | Keresés | Lineáris bejárás, az utolsó állomás, ahol a leszállók száma nulla | 1 | Bevezetés | ✅ kész |
| 31 | [Nem volt senki a vonaton](<31. Nem volt senki a vonaton */>) | Prefixösszeg | Futó létszám minden állomás után, az utolsó nem nulla létszámú állomás sorszáma plusz egy | 1 | Magyarázat | ✅ kész |
| 32 | [Nem volt senki a vonaton Budapesttől](<32. Nem volt senki a vonaton Budapesttől */>) | Prefixösszeg | Futó létszám, az első olyan állomás sorszáma, ahol a létszám nem nulla | 1 | Bevezetés | ✅ kész |
| 33 | [Nem volt utasforgalom](<33. Nem volt utasforgalom */>) | Feltételes számlálás | Lineáris bejárás, az állomások számlálása, ahol a leszállók és a felszállók száma is nulla | 1 | Bevezetés | ✅ kész |
| 34 | [Nőtt a vonaton utazók száma](<34. Nőtt a vonaton utazók száma */>) | Feltételes számlálás | Lineáris bejárás, az állomások számlálása, ahol a felszállók száma nagyobb a leszállókénál | 1 | Bevezetés | ✅ kész |
| 35 | [Több leszálló, mint felszálló](<35. Több leszálló, mint felszálló */>) | Feltételes számlálás | Egy bejárás, állomásonként a leszállók és felszállók összehasonlítása, a többen leszállók számlálása. | 1 | Bevezetés | ✅ kész |
| 36 | [Többen szálltak fel, mint az előző állomáson](<36. Többen szálltak fel, mint az előző állomáson */>) | Szomszédos elemek összehasonlítása | Egy bejárás, az előző állomás felszállóinak megjegyzése, az első olyan állomás keresése. | 1 | Bevezetés | ✅ kész |
| 37 | [Többen szálltak volna le, mint ahányan voltak](<37. Többen szálltak volna le, mint ahányan voltak */>) | Prefixösszeg, feltétel | Futó utaslétszám egy bejárásban, és minden állomáson összevetés a leszállók számával. | 1 | Magyarázat | ✅ kész |
| 38 | [Utasok száma nem változott](<38. Utasok száma nem változott */>) | Feltételes keresés | Egy bejárás, az első állomás keresése, ahol a leszállók és felszállók száma megegyezik. | 1 | Bevezetés | ✅ kész |
| 39 | [Vagy csak felszálló vagy csak leszálló](<39. Vagy csak felszálló vagy csak leszálló */>) | Feltételes számlálás | Állomásonként a leszállók és felszállók pozitív voltának összevetése egy bejárásban | 1 | Bevezetés | ✅ kész |
| 40 | [Vasút](<40. Vasút */>) | Szimuláció | Érkezéskori létszám és a leszállók összevetése egy bejárásban, ha volt utas a vonaton | 1 | Bevezetés | ✅ kész |
| 41 | [Veszteséges-e a vonat üzemeltetése](<41. Veszteséges-e a vonat üzemeltetése */>) | Prefixösszeg | Összes bevétel (utas×szakasz·K) és összes kiadás ((N-1)·M) összevetése egy bejárásban | 1 | Magyarázat | ✅ kész |
| 42 | [Vonaton utazók száma minden állomásra](<42. Vonaton utazók száma minden állomásra */>) | Prefixösszeg | Futó utasszám: minden állomáson levonni a leszállókat, majd hozzáadni a felszállókat | 1 | Bevezetés | ✅ kész |
