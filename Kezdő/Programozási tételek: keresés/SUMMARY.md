# Programozási tételek: keresés – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 32 feladat · ✅ kész 31 · ❌ hibás 0 · 🟡 kézi 1 · 🟡 nincs minta/speciális 0 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [A nap mikor nem volt kapás](<1. A nap mikor nem volt kapás */>) | Lineáris keresés | Lineáris bejárás, az első nulla értékű elem keresése | 1 | Bevezetés | ✅ kész |
| 2 | [Azonos évben születtek](<2. Azonos évben születtek */>) | Keresés | Páronkénti összehasonlítás két egymásba ágyazott ciklussal | 1 | Bevezetés | ✅ kész |
| 3 | [Azonos pont egymás mellett](<3. Azonos pont egymás mellett */>) | Lineáris keresés | Lineáris bejárás a szomszédos elemek összehasonlításával. | 1 | Bevezetés | ✅ kész |
| 4 | [Első öt év alatt végzett hallgató](<4. Első öt év alatt végzett hallgató */>) | Lineáris keresés | Lineáris bejárás, a kezdés és a végzés évének különbségére épülő feltétel | 1 | Bevezetés | ✅ kész |
| 5 | [Feleltetés](<5. Feleltetés */>) | Feltételes keresés | Két sorban alkalmazott lineáris bejárás, az átlag tizedesjegyét egész számokkal számolva | 1 | Magyarázat | ✅ kész |
| 6 | [Gyorsabb vonat az előzőnél](<6. Gyorsabb vonat az előzőnél */>) | Szomszédos elemek | Lineáris bejárás, szomszédos menetidők összehasonlítása | 1 | Bevezetés | ✅ kész |
| 7 | [Képek](<7. Képek */>) | Mátrix: eltérések keresése | Négy irány független bejárása, oszlopok és sorok teljes egyezésének vizsgálatával | 1 | Magyarázat | ✅ kész |
| 8 | [Két azonos figurájú lap](<8. Két azonos figurájú lap */>) | Szomszédos elemek | Lineáris bejárás, szomszédos lapok figuráinak összehasonlítása | 1 | Bevezetés | ✅ kész |
| 9 | [Két azonos színű lap](<9. Két azonos színű lap */>) | Szomszédos elemek | Lineáris bejárás, szomszédos lapok színeinek összehasonlítása | 1 | Bevezetés | ✅ kész |
| 10 | [Korcsolyázós nap a Balatonon](<10. Korcsolyázós nap a Balatonon */>) | Szomszédos elemek | Szomszédos napok párjainak egyetlen bejárásos vizsgálata | 1 | Bevezetés | ✅ kész |
| 11 | [Lehűlés napja](<11. Lehűlés napja */>) | Szomszédos elemek | Előző napi minimum tárolása, egyetlen bejárás | 1 | Bevezetés | ✅ kész |
| 12 | [Memóriajáték](<12. Memóriajáték */>) | Sztring, részsorozat | Közös előtag hossza és mohó részsorozat-egyeztetés két mutatóval | 1 | Magyarázat | ✅ kész |
| 13 | [Metró átszállás](<13. Metró átszállás ***/>) | Gráf: legrövidebb út | Gráf 0-1 BFS-sel a legkevesebb megállóra, majd vonalankénti szakaszok összevonása | 3 | Mélyebb megértés | ✅ kész |
| 14 | [Műhold](<14. Műhold */>) | Mátrix: eltérések keresése | Pixelenkénti összehasonlítás, az eltérések szélső indexei | 1 | Bevezetés | ✅ kész |
| 15 | [Olcsó fenyőfa](<15. Olcsó fenyőfa */>) | Keresés: lineáris | Lineáris keresés az első K-nál olcsóbb elemre | 1 | Bevezetés | ✅ kész |
| 16 | [Őr nélküli nap a múzeumban](<16. Őr nélküli nap a múzeumban */>) | Prefixösszeg: intervallumok | Különbségtömb és prefixösszeg a napi lefedettség számítására | 1 | Magyarázat | ✅ kész |
| 17 | [Sípálya ahol vastag a hó](<17. Sípálya ahol vastag a hó */>) | Keresés | Lineáris keresés az első legalább 100 cm-es sípályára | 1 | Bevezetés | ✅ kész |
| 18 | [Székesfehérvári vonat](<18. Székesfehérvári vonat */>) | Keresés | Lineáris keresés a kezdőállomásról induló vonat feltételével | 1 | Magyarázat | ✅ kész |
| 19 | [Szövegkereső](<19. Szövegkereső **/>) | Keresés | Két minta párhuzamos bejárása visszalépéses kereséssel, memoizálással | 2 | Mélyebb megértés | ✅ kész |
| 20 | [Végállomás Fonyód előtt](<20. Végállomás Fonyód előtt */>) | Keresés | Lineáris bejárás, az utolsó megfelelő végállomás-sor megjegyzése, megállás Fonyódnál | 1 | Bevezetés | ✅ kész |
| 21 | [Csökkenő benzin](<21. Csökkenő benzin **/>) | Keresés | Egy bejárás, a tankban levő benzin nyilvántartása kútról kútra | 2 | Bevezetés | ✅ kész |
| 22 | [Jegy a határon](<22. Jegy a határon **/>) | Keresés | Függvénnyel számolt jegy, minden hallgatóra egy-egy lépéses javítás kipróbálása | 2 | Magyarázat | ✅ kész |
| 23 | [Nagy és drága lakás](<23. Nagy és drága lakás */>) | Keresés | Egy bejárás, az első olyan lakás keresése, amely mindkét feltételt teljesíti | 1 | Bevezetés | ✅ kész |
| 24 | [Utolsó sikeres dobás](<24. Utolsó sikeres dobás */>) | Keresés: utolsó előfordulás | Soronként végigmegyünk a dobásokon, és az utolsó nem -1 dobás sorszámát tároljuk. | 1 | Bevezetés | ✅ kész |
| 25 | [Utolsó világcsúcsmentes év](<25. Utolsó világcsúcsmentes év */>) | Keresés: halmaz | A világcsúcs-években halmazt építünk, és a legújabb évtől visszafelé az első rekordmentes évet keressük. | 1 | Magyarázat | ✅ kész |
| 26 | [Ponthatárok](<26. Ponthatárok/>) | Keresés: határok | Legkisebb, legfeljebb L-es csökkentés, amelynél az új határ alatti pontszám senkinél sincs meg. | 2 | Magyarázat | ✅ kész |
| 27 | [Távoli bolygó DNS-e](<27. Távoli bolygó DNS-e/>) | Keresés: gyakoriság | A sorozatot K-hosszú darabokra bontjuk, és a darabok gyakorisági táblázatait hasonlítjuk össze. | 2 | Magyarázat | ✅ kész |
| 28 | [Legközelebbi szomszédok út mentén](<28. Legközelebbi szomszédok út mentén/>) | Legközelebbi szomszédok | Bináris keresés a legkisebb költségű K+1 hosszú szakaszra. | 3 | Mélyebb megértés | ✅ kész |
| 29 | [Közeli városok a tóparton](<29. Közeli városok a tóparton/>) | Körkörös szomszédkeresés | Körkörös szakasz-keresés bináris kereséssel, a sorozat háromszoros kiterjesztésével. | 4 | Mélyebb megértés | ✅ kész |
| 30 | [Tippek](<30. Tippek **/>) | Bináris keresés | Bináris keresés (lower_bound) és a két szomszédos jelölt összehasonlítása. | 2 | Magyarázat | ✅ kész |
| 31 | [Birtok vásárlás](<31. Birtok vásárlás/>) | Kétmutatós keresés | Rendezett tömb, a legnagyobb területtől visszafelé kétmutatós párkeresés | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 32 | [Örökség](<32. Örökség/>) | Négy elem összege | Rendezett tömb, két elem rögzítése után kétmutatós párkeresés nyesésekkel | 3 | Magyarázat | ✅ kész |
