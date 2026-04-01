# Kombinatorikai algoritmusok – oktatási összefoglaló

> Batch mód: a 21–40 tartományhoz kész C++ megoldás tartozik.

Skála:
- **Nehézség 1–5**: 1 = nagyon alap, 5 = nagyon összetett
- **Órai cél**: `Bevezetés` / `Magyarázat` / `Mélyebb megértés`

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 21 | Válogatás | Brute force, permutáció | Minden ládadisztibúció kipróbálása, maximális bent hagyott mennyiség keresése | 2 | Magyarázat | ✅ kész |
| 22 | Verseny | Partíciók, DP | Különböző tagú partíciók száma 1D dinamikával | 3 | Magyarázat | ✅ kész |
| 23 | Zár | Állapottér, minimális lépésszám | Három tárcsa irányválasztása, 2^3 lehetőség kipróbálása | 2 | Magyarázat | ✅ kész |
| 24 | Akadályverseny | Eulerian számok | Alternáló permutációk Entringer-DP-vel | 4 | Mélyebb megértés | ✅ kész |
| 25 | Épület színezések száma 2 | DP, automata | 3 állapotú színezési rekurzió modulo számolással | 2 | Magyarázat | ✅ kész |
| 26 | Épület színezések száma 3 | DP, automata | 3 állapotú színezési rekurzió eltérő átmenetmátrixszal | 2 | Magyarázat | ✅ kész |
| 27 | Ügyességi verseny | Eulerian számok | Pontosan K emelkedés számolása klasszikus Eulerian rekurzióval | 3 | Magyarázat | ✅ kész |
| 28 | Permutáció kódolása | Fenwick-fa, inverziók | Prefixben korábbi nagyobb elemek száma gyors összegezéssel | 2 | Bevezetés | ✅ kész |
| 29 | Sorrend | Eulerian számok | Középső Eulerian szám kiszámítása modulo 2017 | 3 | Magyarázat | ✅ kész |
| 30 | Idegen DNS | DP, korlátozott átmenetek | 5 állapotú lánc-DP tiltott szomszédpárokkal | 2 | Magyarázat | ✅ kész |
| 31 | Azonosítók | Kombináció-rangolás | Lexikografikus sorszám és visszaépítés binomiális együtthatókkal | 3 | Magyarázat | ✅ kész |
| 32 | Ajándékozás | Partíciók, DP | N összegű partíciók száma legfeljebb M taggal | 3 | Magyarázat | ✅ kész |
| 33 | Gyémántok | Partíciók, tiltott ismétlés | Különböző tagú partíciók száma 1D DP-vel | 3 | Magyarázat | ✅ kész |
| 34 | Csapatösszeállítás | Kombinációs szomszédok | Lexikografikus következő és előző kombináció ciklikus kezeléssel | 2 | Magyarázat | ✅ kész |
| 35 | Növény | Rekurzív szimuláció | Csúszóösszeges szaporodási rekurzió és élő-egyedszám | 3 | Mélyebb megértés | ✅ kész |
| 36 | Virágok | Rekurzív szimuláció | Ugyanaz a növekedési rekurzió, csak az összes élő virágra | 2 | Magyarázat | ✅ kész |
| 37 | Elrendezés | Catalan-szám | 2×N standard Young-tábla száma, Catalan-rekurzióval | 2 | Magyarázat | ✅ kész |
| 38 | Leosztások | Trie-sorrend, lexikografikus szomszéd | Multihalmazos variáció következő eleme prefixfa-logikával | 4 | Mélyebb megértés | ✅ kész |
| 39 | Multihalmaz variációi | Trie-sorrend, ciklikus szomszédok | Előző és következő variáció multihalmazra, ciklikus bejárással | 4 | Mélyebb megértés | ✅ kész |
| 40 | Táblás játék | Skyline, matching DP | Nem támadó bábuk száma oszlopmagasságokra bontott rekurzív DP-vel | 5 | Mélyebb megértés | ✅ kész |

## Batch állapot
- **Elkészült C++ megoldások**: 21–40
- **Következő batch javaslat**: nincs

# Kombinatorikai algoritmusok – oktatási összefoglaló

> Batch mód: az 1–20. feladatok elkészültek C++ megoldással.

| # | Feladat | Röviden használt módszer / algoritmus | Állapot |
|---|---|---|---|
| 1 | Azonosító kód | Következő lexikografikus permutáció | ✅ kész |
| 2 | Befektetés | Zeckendorf-szerű Fibonacci felbontás | ✅ kész |
| 3 | Beosztás | Kompozíciók rangja / unrankje | ✅ kész |
| 4 | Birtokfelosztás | Kompozíciók unrankelése | ✅ kész |
| 5 | Dekódolás | Inverziós kód visszaalakítása Fenwick-fával | ✅ kész |
| 6 | Fák száma | Catalan-szám | ✅ kész |
| 7 | Halmazok sorrendje | Colex jellegű halmaz-unrank | ✅ kész |
| 8 | Hibás lépcsők | Lépésszám + pozíció DP | ✅ kész |
| 9 | Kincselosztás | Partíció-rangolás és szomszédok | ✅ kész |
| 10 | Következő azonosító | Következő lexikografikus permutáció | ✅ kész |
| 11 | Lépcsők | Összegző DP | ✅ kész |
| 12 | Nyúl | Korosztályos szimuláció, mod 1 000 000 | ✅ kész |
| 13 | Osztály részhalmazai | Binomiális unrank bitmintára | ✅ kész |
| 14 | Örökösök | Partíciók számlálása | ✅ kész |
| 15 | Róka | Korosztályos szimuláció, mod 1 000 000 | ✅ kész |
| 16 | Sorrend | Inklúzió-exklúzió tiltott szomszédságokra | ✅ kész |
| 17 | Sorrend-változás | Monomer-dimer generálás | ✅ kész |
| 18 | Számzár | Szorzat, rossz tárcsa, bitmask DP | ✅ kész |
| 19 | Színezés | Fibonacci-jellegű DP és unrank | ✅ kész |
| 20 | Társasjáték | Reflektált lépés DP | ✅ kész |

## Batch állapot
- **Elkészült C++ megoldások**: 1–20
- **Következő batch javaslat**: nincs
