# Verseny – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 25 feladat · ✅ kész 25 · ❌ hibás 0 · 🟡 kézi 0 · 🟡 nincs minta/speciális 0 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Átlagosnál erősebb versenyek](<1. Átlagosnál erősebb versenyek/>) | Átlagok összehasonlítása | Verseny-átlagok összehasonlítása a globális átlaggal, egész számos szorzással. | 2 | Magyarázat | ✅ kész |
| 2 | [Csak egy versenyen indultak](<2. Csak egy versenyen indultak/>) | Számlálás, szűrés | Tanulónként megszámoljuk az indulásokat, és kiválogatjuk azokat, akiknél pontosan 1. | 1 | Bevezetés | ✅ kész |
| 3 | [Egyéni rangsorok](<3. Egyéni rangsorok/>) | Rendezés, szűrés | Versenyenként szűrés, majd rendezés pont szerint csökkenőn, sorszám szerint növekvőn | 2 | Bevezetés | ✅ kész |
| 4 | [Eredménytelen versenyek](<4. Eredménytelen versenyek/>) | Keresés, logikai jelző | Versenyenkénti logikai jelző: senki nem érte el a minimumot | 1 | Bevezetés | ✅ kész |
| 5 | [Versenyek győztesei rangsora](<5. Versenyek győztesei rangsora/>) | Maximumkiválasztás, rendezés | Versenyenként a maximumot keressük, győzelmeket számolunk, majd a győzteseket rendezzük. | 2 | Magyarázat | ✅ kész |
| 6 | [Versenyek győztesei](<6. Versenyek győztesei/>) | Maximumkiválasztás | Versenyenként a maximumot keressük, és a maximumot elérő tanulókat egy jelölő tömbben megjelöljük. | 2 | Bevezetés | ✅ kész |
| 7 | [Kieső győztesek](<7. Kieső győztesek/>) | Feltételes halmazszűrés | Versenyenként a győzteseket meghatározzuk, majd minden győztesre ellenőrizzük, van-e másik, minimumot nem elérő verseny. | 3 | Magyarázat | ✅ kész |
| 8 | [Legalább egy versenyben elérték a minimális pontszámot](<8. Legalább egy versenyben elérték a minimális pontszámot/>) | Feltételes szűrés | Minden tanulóra és versenyre összevetjük a pontot a minimummal; elég egy találat. | 1 | Bevezetés | ✅ kész |
| 9 | [Legalább egy versenyben indultak](<9. Legalább egy versenyben indultak/>) | Halmaz, logikai tömb | Logikai tömbben megjelölni a résztvevőket, majd sorszám szerint kiírni | 1 | Bevezetés | ✅ kész |
| 10 | [Legnépesebb versenyek](<10. Legnépesebb versenyek/>) | Számlálás, maximum | Versenyenként a minimumot elérők megszámolása, majd a maximumot elérő versenyek kiválasztása. | 1 | Bevezetés | ✅ kész |
| 11 | [Legszorosabb versenyek](<11. Legszorosabb versenyek/>) | Minimum és maximum | Versenyenként a minimumot elértek pontjainak max-min különbsége, majd a legkisebb különbség kiválasztása. | 2 | Magyarázat | ✅ kész |
| 12 | [Legtöbb holtverseny](<12. Legtöbb holtverseny/>) | Rendezés, csoportosítás | Versenyenként rendezés után az azonos pontszámú csoportok méretének összege. | 3 | Magyarázat | ✅ kész |
| 13 | [Legtöbb versenyben győztesek](<13. Legtöbb versenyben győztesek/>) | Számlálás, maximum | Versenyenként a legnagyobb pontot elérők győznek (döntetlennel együtt), a győzelmeket tanulónként számoljuk. | 2 | Magyarázat | ✅ kész |
| 14 | [Mindenhol elérték a minimális pontszámot](<14. Mindenhol elérték a minimális pontszámot/>) | Szűrés, feltételek | Versenyenként kiszűrjük, akik nem indultak vagy nem érték el a minimumot; ami marad, az megfelel. | 1 | Bevezetés | ✅ kész |
| 15 | [Minden versenyen kiestek](<15. Minden versenyen kiestek/>) | Szűrés, feltételek | Tanulónként megjegyezzük, hogy valahol elérte-e a minimumot; a többiek, a nem induló tanulók is, bekerülnek. | 1 | Bevezetés | ✅ kész |
| 16 | [Minimális pont alatt nem voltak](<16. Minimális pont alatt nem voltak/>) | Szűrés, feltételek | Indultak-e és volt-e minimum alatti eredményük: csak az indult és sosem maradt alatta. | 2 | Magyarázat | ✅ kész |
| 17 | [Nehéz versenyek](<17. Nehéz versenyek/>) | Feltételes számlálás | Versenyenként megszámoljuk a minimum alatt maradókat, és a 2·k ≥ i feltétellel szűrünk. | 2 | Bevezetés | ✅ kész |
| 18 | [Nem csak összetettben győzött](<18. Nem csak összetettben győzött/>) | Maximum és szűrés | Versenyenként maximumkeresés, az összetettben a szűrt tanulók összpontszámának maximuma. | 3 | Magyarázat | ✅ kész |
| 19 | [Sehol sem győztek](<19. Sehol sem győztek/>) | Halmazműveletek és szűrés | Győztesek halmazának kiszámítása, majd az indulók és a győztesek különbsége. | 3 | Magyarázat | ✅ kész |
| 20 | [Nem induló győztesek](<20. Nem induló győztesek/>) | Verseny | Versenyenkénti maximumkeresés, győzelem- és indulásszámlálás tanulónként | 2 | Bevezetés | ✅ kész |
| 21 | [Összetett holtverseny](<21. Összetett holtverseny/>) | Verseny | Értékelhető tanulók összpontszáma, pontszámonkénti számlálás, helyezés = 1 + nála jobbak száma | 3 | Magyarázat | ✅ kész |
| 22 | [Versenyben nem értékelhetők](<22. Versenyben nem értékelhetők/>) | Verseny | Versenyenkénti teljesítés-számlálás, a nem teljesítő tanulók sorszámainak kiírása | 1 | Bevezetés | ✅ kész |
| 23 | [Összetett rangsor](<23. Összetett rangsor/>) | Verseny | Értékelhető tanulók összpontszáma, rendezés csökkenő pontszám, növekvő sorszám szerint | 2 | Bevezetés | ✅ kész |
| 24 | [Egyetlen versenyben sem győztek](<24. Egyetlen versenyben sem győztek/>) | Maximumkeresés és összegzés | Versenyenkénti maximum és összetett összeg, majd a nem nyertesek kiírása | 3 | Magyarázat | ✅ kész |
| 25 | [Volt holtverseny](<25. Volt holtverseny/>) | Maximumkeresés, számlálás | Versenyenként a minimumot elérők maximumának számlálása | 2 | Bevezetés | ✅ kész |
