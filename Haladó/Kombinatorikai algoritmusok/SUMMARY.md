# Kombinatorikai algoritmusok – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 61 feladat · ✅ kész 54 · ❌ hibás 0 · 🟡 kézi 5 · 🟡 nincs minta/speciális 2 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Azonosító kód](<1. Azonosító kód ***/>) | Permutáció: következő elem | Következő lexikografikus permutáció a std::next_permutation-nel, kódonként egy hívás. | 3 | Bevezetés | 🟡 kézi ellenőrzés |
| 2 | [Befektetés](<2. Befektetés ***/>) | Zeckendorf-felbontás | Mohó Zeckendorf-felbontás: a legnagyobb Fibonacci-számtól, nincs két egymást követő év. | 3 | Mélyebb megértés | ✅ kész |
| 3 | [Beosztás](<3. Beosztás ***/>) | Kompozíciók, rangsorolás | Kompozíciók rangja binomiális összegekkel, az előző és következő unrankeléssel. | 3 | Mélyebb megértés | ✅ kész |
| 4 | [Birtokfelosztás](<4. Birtokfelosztás ***/>) | Kompozíciók, unrankelés | Vágások száma C(N−1, K−1), lexikografikus unrankelés csökkenő első résszel | 3 | Magyarázat | ✅ kész |
| 5 | [Dekódolás](<5. Dekódolás ***/>) | Inverziós kód, Fenwick-fa | Jobbról balra: az i-edik szám a még szabad számok (i−b_i)-edik legkisebbje, Fenwick-fával. | 3 | Magyarázat | ✅ kész |
| 6 | [Fák száma](<6. Fák száma ***/>) | Catalan-számok | Catalan-szám iteratív kiszámítása: C(k+1) = C(k)·2(2k+1)/(k+2). | 3 | Magyarázat | ✅ kész |
| 7 | [Halmazok sorrendje](<7. Halmazok sorrendje ***/>) | Binomiális rangsorolás | Legnagyobb elem szerinti csoportosítás, binomiális együtthatókkal N-től lefelé haladva. | 3 | Mélyebb megértés | ✅ kész |
| 8 | [Hibás lépcsők](<8. Hibás lépcsők ***/>) | Dinamikus programozás | DP lépésszám és pozíció szerint; hibás fokon 0, az átmenet az előző K fokot összegzi. | 3 | Magyarázat | ✅ kész |
| 9 | [Kincselosztás](<9. Kincselosztás ***/>) | Partíciók, rangsorolás | Partíciószámláló DP, unrankelés csoportonként, rangból következő és előző felosztás. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 10 | [Következő azonosító](<10. Következő azonosító **/>) | Permutáció: lexikografikus sorrend | Következő permutáció: jobbról az első növekedési pont, csere, majd megfordítás. | 2 | Bevezetés | ✅ kész |
| 11 | [Lépcsők](<11. Lépcsők **/>) | Dinamikus programozás: összegzés | Összegző DP: dp[i] az i lépcsőre feljutási módok száma, dp[i] = dp[i-1]+…+dp[i-K]. | 2 | Bevezetés | ✅ kész |
| 12 | [Nyúl](<12. Nyúl **/>) | Szimuláció, moduláris aritmetika | Korosztályonkénti szimuláció: évente az újszülöttek száma, majd a korosztályok léptetése, MOD-dal. | 2 | Magyarázat | ✅ kész |
| 13 | [Osztály részhalmazai](<13. Osztály részhalmazai ***/>) | Kombinatorika: rangsorolás | Fordított rangsorolás: a legnagyobb bittől binomiális együtthatókkal döntünk a tagságról. | 3 | Magyarázat | ✅ kész |
| 14 | [Örökösök](<14. Örökösök **/>) | Partíciószám: pontosan K tag | Partíció-rekurzió: dp[n][k] = dp[n-1][k-1] + dp[n-k][k], a legkisebb tag szerint bontva. | 2 | Magyarázat | ✅ kész |
| 15 | [Róka](<15. Róka **/>) | Szimuláció: korosztályok | Korosztályonkénti darabszámok évenkénti léptetése, újszülöttek = szaporodó korúak összege, MOD szerint. | 2 | Bevezetés | ✅ kész |
| 16 | [Sorrend](<16. Sorrend **/>) | Inklúzió-exklúzió | Inklúzió-exklúzió: j tiltott pár összevonása, (N-j)! sorrend, binomiálisok Pascal-háromszöggel. | 2 | Magyarázat | ✅ kész |
| 17 | [Sorrend-változás](<17. Sorrend-változás ***/>) | Permutáció, generálás | Szomszédos cserék rekurzív generálása, a darabszám Fibonacci-szám. | 3 | Mélyebb megértés | ✅ kész |
| 18 | [Számzár](<18. Számzár */>) | Bitmaszkos DP | Szorzat, a legkisebb tárcsa elhagyása, és bitmaszkos DP a különböző számjegyű kódokra. | 1 | Magyarázat | ✅ kész |
| 19 | [Színezés](<19. Színezés ***/>) | Rangsorolás, DP | Folytatások száma DP-vel, a K-adik sorozat elemenkénti kiválasztása (unrank). | 3 | Magyarázat | ✅ kész |
| 20 | [Társasjáték](<20. Társasjáték ***/>) | Dinamikus programozás | DP a dobásszámra és a mezőre, a túllépés visszatükrözésével. | 3 | Magyarázat | ✅ kész |
| 21 | [Válogatás](<21. Válogatás **/>) | Permutáció: hozzárendelés | Összes permutáció kipróbálása, a helyben maradó üvegek maximalizálásával. | 2 | Bevezetés | ✅ kész |
| 22 | [Verseny](<22. Verseny */>) | Partíció: különböző tagok | Különböző tagú felbontások számolása 0/1 hátizsák-DP-vel, BigInt-tel. | 1 | Magyarázat | ✅ kész |
| 23 | [Zár](<23. Zár ***/>) | Körkörös tárcsák: minimális lépésszám | Tárcsánként a két forgásirány távolsága, az irányok 2^3 kombinációja, maximumok összege. | 3 | Mélyebb megértés | ✅ kész |
| 24 | [Akadályverseny](<24. Akadályverseny ***/>) | Alternáló permutációk | Alternáló permutációk száma: 2·E_N, az Entringer-háromszöggel számolt Euler-féle zigzag-szám. | 3 | Mélyebb megértés | 🟡 nincs minta |
| 25 | [Épület színezések száma 2](<25. Épület színezések száma 2 **/>) | Dinamikus programozás: állapotok | Három állapotú lineáris DP az utolsó emelet színe szerint, modulo 20160109. | 2 | Bevezetés | ✅ kész |
| 26 | [Épület színezések száma 3](<26. Épület színezések száma 3 **/>) | Dinamikus programozás | Három állapotú DP az utolsó szín szerint, a három érték mindig egyenlő. | 2 | Magyarázat | ✅ kész |
| 27 | [Ügyességi verseny](<27. Ügyességi verseny **/>) | Eulerian számok | Eulerian-rekurzió a legnagyobb elem beszúrásával, az emelkedések számára. | 2 | Magyarázat | 🟡 nincs minta |
| 28 | [Permutáció kódolása](<28. Permutáció kódolása ***/>) | Fenwick-fa, inverziók | Fenwick-fával számoljuk a prefixben a kisebb-egyenlő elemeket, O(N log N). | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 29 | [Sorrend](<29. Sorrend/>) | Eulerian számok | Eulerian-szám középső értéke az emelkedés-rekurzióval, modulo 2017. | 2 | Magyarázat | ✅ kész |
| 30 | [Idegen DNS](<30. Idegen DNS/>) | Dinamikus programozás | Utolsó betű szerinti 5 állapotú DP, nagy egész összeadással. | 2 | Bevezetés | ✅ kész |
| 31 | [Azonosítók](<31. Azonosítók/>) | Kombinatorika: sorszámozás | Lexikografikus sorszámozás binomiális együtthatókkal, majd visszaépítés a célsorszámból. | 3 | Mélyebb megértés | ✅ kész |
| 32 | [Ajándékozás](<32. Ajándékozás/>) | Dinamikus programozás: partíció | Partíciók számolása DP-vel, a csomagméret szerinti külső ciklussal. | 2 | Magyarázat | ✅ kész |
| 33 | [Gyémántok](<33. Gyémántok/>) | Dinamikus programozás: partíció | Különböző részekre bontások számolása 0-1 hátizsák típusú DP-vel. | 2 | Magyarázat | ✅ kész |
| 34 | [Csapatösszeállítás](<34. Csapatösszeállítás/>) | Kombinatorika: következő kombináció | Lexikografikus következő és előző kombináció keresése a jobb szélső elem módosításával. | 3 | Magyarázat | ✅ kész |
| 35 | [Növény](<35. Növény/>) | Rekurzió: csúszóablak | Csúszóablakos rekurzió prefixösszegekkel, az élő darabszám inkrementális frissítése. | 2 | Magyarázat | ✅ kész |
| 36 | [Virágok](<36. Virágok/>) | Rekurzió: csúszóablak | Csúszóablakos rekurzió prefixösszegekkel, az X. évi élő darabszám frissítése. | 3 | Magyarázat | ✅ kész |
| 37 | [Elrendezés](<37. Elrendezés/>) | Catalan-számok | Zárójelezések (Dyck-utak) számolása, Catalan-rekurzióval O(N²) időben | 2 | Magyarázat | ✅ kész |
| 38 | [Leosztások](<38. Leosztások/>) | Lexikografikus rákövetkező | Prefixfa-bejárás: bővítés a legkisebb kártyával, különben visszalépés a legkisebb nagyobb betűre | 2 | Magyarázat | ✅ kész |
| 39 | [Multihalmaz variációi](<39. Multihalmaz variációi/>) | Lexikografikus rákövetkező | Prefixfa-bejárás: rákövetkező és előző variáció visszalépéssel, prefixenkénti darabszámokkal | 3 | Magyarázat | ✅ kész |
| 40 | [Táblás játék](<40. Táblás játék/>) | Rekurzív DP, konvolúció | Legalacsonyabb oszlop szerinti rekurzív felbontás, sávonkénti képlet és konvolúció | 4 | Mélyebb megértés | ✅ kész |
| 41 | [Permutációk](<41. Permutációk/>) | Verem, Dyck-szavak | Veremmel kódolt Dyck-szó, rákövetkező Dyck-szó és visszaalakítás veremmel | 4 | Mélyebb megértés | ✅ kész |
| 42 | [Rózsafüzér permutáció](<42. Rózsafüzér permutáció/>) | Lexikografikus permutáció | Az 1 nélküli sorozat next_permutation-je; ha nincs, az első elem növelése. | 3 | Magyarázat | ✅ kész |
| 43 | [Szavak](<43. Szavak/>) | Szavak sorrendje | Betűszámlálás: bővítés, hátulról növelés; előző: utolsó betű csökkentése vagy elhagyása. | 3 | Mélyebb megértés | ✅ kész |
| 44 | [Következő közeli elrendezés](<44. Következő közeli elrendezés/>) | Közeli permutációk | Közeli permutáció 0/1 bitsorozat (nincs két szomszédos 1), következő bitsorozat lexikografikus sorrendben. | 3 | Magyarázat | ✅ kész |
| 45 | [Előző és következő közeli elrendezés](<45. Előző és következő közeli elrendezés/>) | Közeli permutációk | Bitkódolás; előző: utolsó 1-es törlése és váltakozó kitöltés; következő: jobbról első 0 növelése. | 3 | Magyarázat | ✅ kész |
| 46 | [Euler](<46. Euler **/>) | Eulerian-számok | Eulerian-rekurzió: E(n,k) = (k+1)E(n-1,k) + (n-k)E(n-1,k-1), modulo 20191019. | 2 | Magyarázat | ✅ kész |
| 47 | [Ritka számok](<47. Ritka számok/>) | Ritka bináris számok | Ritka bináris számok következője és előzője bitszintű módosítással, vezető nullával. | 2 | Magyarázat | ✅ kész |
| 48 | [Előző és következő ülés sorrend](<48. Előző és következő ülés sorrend/>) | Kombinációk lexikografikus sorrendje | Következő/előző kombináció: a jobbról első módosítható elem léptetése, a jobb oldali rész alaphelyzetbe állítása. | 3 | Magyarázat | ✅ kész |
| 49 | [Kirándulás sorrend](<49. Kirándulás sorrend/>) | Bitmaszkos DP, legrövidebb utak | Floyd–Warshall távolságok, majd bitmaszkos DP a városok sorrendjére, visszaút a lakóhelyre. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 50 | [Kígyózó szavak](<50. Kígyózó szavak ***/>) | Rangsorolás, prefixfa | Prefixfa bejárása: a betűnként számolt részfák méretével léptetünk a K-adik szóhoz. | 3 | Mélyebb megértés | ✅ kész |
| 51 | [Lassú szöveg](<51. Lassú szöveg ***/>) | Lexikografikus szomszéd, prefixfa | Utolsó betű szomszédos cseréje, majd az előző szónál maximális, a következőnél minimális folytatás. | 3 | Mélyebb megértés | ✅ kész |
| 52 | [Örökség](<52. Örökség ***/>) | Partíciószám, DP | Partíciószámolás zsákprobléma-szerű DP-vel: K darab, 1 és M közötti részre bontás, összeg N. | 3 | Magyarázat | ✅ kész |
| 53 | [Számlexikon](<53. Számlexikon ****/>) | Bináris keresés, lexikografikus rang | Bináris keresés N-re, Q_{N,K} számlálása prefixek intervallumaival. | 4 | Mélyebb megértés | ✅ kész |
| 54 | [Lassú permutáció](<54. Lassú permutáció **/>) | Sztring, lexikografikus sorrend | Közvetlen szomszédkeresés: utolsó módosítható pozíció, a maradék szélső betűkkel. | 2 | Magyarázat | ✅ kész |
| 55 | [Örökösök](<55. Örökösök ***/>) | Hátizsák-DP, részhalmazok | Különböző értékű K-elemű részhalmazok számolása hátizsák-DP-vel. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 56 | [Inverzió](<56. Inverzió **/>) | Fenwick-fa, inverziók | Jobbról balra haladva Fenwick-fa prefix-maximummal a legtávolabbi kisebb társ. | 2 | Magyarázat | ✅ kész |
| 57 | [Maximum felosztás](<57. Maximum felosztás ****/>) | DP, intervallumok, bináris keresés | Szakaszok az utolsó B_i-előfordulással; a DP-réteg intervallum-darabokként, prefixösszegekkel. | 4 | Mélyebb megértés | ✅ kész |
| 58 | [Szomszédos számok](<58. Szomszédos számok/>) | Számrendszer, lexikografikus rendezés | Jobbról balra az első módosítható jegy, a maradék összeget a szélső jegyekkel töltjük ki. | 3 | Magyarázat | ✅ kész |
| 59 | [Ciklikusan szomszédos számok](<59. Ciklikusan szomszédos számok/>) | Összegkötött számok sorrendje | Lexikografikus szomszéd keresése fix jegyösszeggel: jobbról első megváltoztatható jegy, a maradék összeg szétosztása. | 3 | Mélyebb megértés | ✅ kész |
| 60 | [Következő szám azonos számú 1-es bittel](<60. Következő szám azonos számú 1-es bittel/>) | Bitműveletek: következő szám | Bitműveletes léptetés: a legalsó 1-es blokk fölötti 0 bit 1-re állítása, alatta újrarendezés. | 2 | Magyarázat | ✅ kész |
| 61 | [Autókódolás](<61. Autókódolás/>) | Bitműveletek: előző és következő | Következő: 60-as bittrükk; előző: az alsó 1-esek fölötti 1 bit csökkentése. | 3 | Magyarázat | ✅ kész |
