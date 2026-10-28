# Elemi feladatok tömbökre – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 26 feladat · ✅ kész 24 · ❌ hibás 0 · 🟡 kézi 2 · 🟡 nincs minta/speciális 0 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Ábra](<1. Ábra **/>) | Tömb: szimmetria, szavazás | Befoglaló téglalap és a négy tükörkép többségi szavazása pontonként. | 2 | Magyarázat | ✅ kész |
| 2 | [Csokoládé automata](<2. Csokoládé automata **/>) | Összegzés, keresés | Fizetés 1, 2, majd 3 érmével sorban; az első találat a minimális érmeszám | 2 | Bevezetés | 🟡 kézi ellenőrzés |
| 3 | [Dátum](<3. Dátum */>) | Dátum: szökőévek | Napok számlálása 1901-től mod 7 léptetéssel, szökőév-szabállyal | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 4 | [Erősen páratlan számok](<4. Erősen páratlan számok */>) | Számjegyek: összegképzés | Számjegyösszeg ismételt képzése karakterláncként, paritás-ellenőrzéssel. | 1 | Magyarázat | ✅ kész |
| 5 | [Eszperantó számok](<5. Eszperantó számok */>) | Tömb: számnevek | Helyiértékek szerinti szétbontás, szorzószavak tömbből, speciális esetekkel. | 1 | Bevezetés | ✅ kész |
| 6 | [Francia számok](<6. Francia számok */>) | Elágazás: számnevek | Számnévtábla és esetszétválasztás a tízesek és egységek szerint. | 1 | Bevezetés | ✅ kész |
| 7 | [Hét napja](<7. Hét napja */>) | Dátum: maradékos számítás | Eltelt napok összegzése a hónapok hosszából, maradékképzés hét szerint. | 1 | Magyarázat | ✅ kész |
| 8 | [Játéktábla 1.](<8. Játéktábla 1. **/>) | Szimuláció: indexelés | A bábu (sor, hely) párját tartjuk nyilván, minden lépésnél index-képlettel frissítjük | 2 | Bevezetés | ✅ kész |
| 9 | [Játéktábla 2.](<9. Játéktábla 2. **/>) | Bináris fa: legrövidebb út | Csak lefelé lépések, a hely (p-1) bináris alakja adja a lépéseket | 2 | Magyarázat | ✅ kész |
| 10 | [Játéktábla 3.](<10. Játéktábla 3. ***/>) | Tömb: hármas számrendszer | A legrövidebb út a célsor mélysége; a célcsúcs indexének jegyeit tömb tárolja. | 3 | Magyarázat | ✅ kész |
| 11 | [Keresztrejtvény](<11. Keresztrejtvény **/>) | Tömb: rácsbejárás, számozás | Sorfolytonos bejárás számlálóval, a szókezdő kockák listákba gyűjtése. | 2 | Bevezetés | ✅ kész |
| 12 | [Kiszámoló](<12. Kiszámoló **/>) | Tömb: körszimuláció | Tömbös szimuláció: a K-adik gyerek indexe maradékos számítással, törléssel. | 2 | Bevezetés | ✅ kész |
| 13 | [Kocka](<13. Kocka **/>) | Gráf: szomszédság | Élek adjacencia-mátrixa, a bejárás szomszédos pároinak ellenőrzése | 2 | Magyarázat | ✅ kész |
| 14 | [Morze](<14. Morze */>) | Karakterkódolás, sztring | Kódtábla tömbben, betűnként kódolás, a szóközök kétszerezése | 1 | Bevezetés | ✅ kész |
| 15 | [Péntek 13](<15. Péntek 13 */>) | Dátumszámítás, maradék | Hónap 13. napja a január 1. utáni eltolással, hétnap maradékszámítással | 1 | Magyarázat | ✅ kész |
| 16 | [Rendezőpályaudvar](<16. Rendezőpályaudvar **/>) | Szimuláció: vágányok | Két vágány nyilvántartása, érkező kocsinként döntés, a hosszabb szerelvény indítása | 2 | Magyarázat | ✅ kész |
| 17 | [Számok betűkkel](<17. Számok betűkkel */>) | Szövegkezelés | Helyiérték-bontás (tízes és egyes), szótárak a nevekhez, a 100 külön eset | 1 | Bevezetés | ✅ kész |
| 18 | [Szűkszámok](<18. Szűkszámok ***/>) | Számrendszerek | Azonos jegyek futamai: a nagyobb jegy előtti futamot kivonjuk, egyébként összeadjuk | 3 | Magyarázat | ✅ kész |
| 19 | [Táblajáték szomszédok](<19. Táblajáték szomszédok ***/>) | Szomszédság a rácson | Eltolások bejárása; sarkos vagy oldalas távolság, körbeérés a C és D esetben | 3 | Magyarázat | ✅ kész |
| 20 | [Titkosított szó visszafejtése](<20. Titkosított szó visszafejtése */>) | Táblázatos kódolás | Kétkarakteres párok feldolgozása, és táblázat-keresés a sor- és oszlopbetű alapján. | 1 | Bevezetés | ✅ kész |
| 21 | [Hónapok első napjai](<21. Hónapok első napjai/>) | Dátumszámítás | A hónapok első napjának hétköznapját a hónap hosszával léptetve számoljuk végig. | 2 | Bevezetés | ✅ kész |
| 22 | [Bürokrácia](<22. Bürokrácia **/>) | Fordított sorrendű bejárás | Fordított sorrendben haladunk: egy törvény aktív, ha későbbi aktív törvény nem vonta vissza. | 2 | Magyarázat | ✅ kész |
| 23 | [Oszthatóság 17-tel](<23. Oszthatóság 17-tel **/>) | Oszthatósági szabály | Az utolsó számjegy ötszörösét kivonjuk a maradék számból, amíg az nem lesz negatív. | 2 | Magyarázat | ✅ kész |
| 24 | [Kártya](<24. Kártya **/>) | Tömbök: összegzés | Összeg és maradékos osztás: az összeg osztható-e N-nel, majd a többlet kiosztása | 2 | Bevezetés | ✅ kész |
| 25 | [Oszthatóság 31-gyel](<25. Oszthatóság 31-gyel **/>) | Oszthatóság: számjegyes szabály | Számjegyes redukció: az utolsó számjegy háromszorosának levonása, a köztes értékek kiírása | 2 | Magyarázat | ✅ kész |
| 26 | [Oszthatóság 37-tel](<26. Oszthatóság 37-tel **/>) | Oszthatóság: számjegyes szabály | Számjegyes redukció az utolsó számjegy 11-szeresének levonásával; az IGEN/NEM döntés az eredeti számból | 2 | Magyarázat | ✅ kész |
