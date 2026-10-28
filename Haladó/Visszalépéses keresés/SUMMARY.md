# Visszalépéses keresés – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 34 feladat · ✅ kész 19 · ❌ hibás 0 · 🟡 kézi 15 · 🟡 nincs minta/speciális 0 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Csoki](<1. Csoki ***/>) | Kombinatorikus visszalépés | Visszalépés Q elemű csoportokkal, a legkisebb hátralévő fajtából indulva, számlálók és korlátok alapján levágva. | 3 | Mélyebb megértés | ✅ kész |
| 2 | [Kirakó](<2. Kirakó ***/>) | Visszalépéses keresés, mohó | Mohó lépések: mindig a legnagyobb átfedésű elhelyezés; zsákutcánál visszalépés. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 3 | [Konferencia](<3. Konferencia */>) | Csoportosítás visszalépéssel | Visszalépés csökkenő sorrendben, zsákutcák memorizálásával | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 4 | [Megye](<4. Megye ***/>) | Gráf: színezés | Visszalépéses színezés, mindig a legkevesebb szabad színű színezetlen megye következik. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 5 | [Munka](<5. Munka **/>) | Hálózati folyam | Min-költségű maximális folyam a munkák és munkások hozzárendelésére. | 2 | Magyarázat | ✅ kész |
| 6 | [Ritmus](<6. Ritmus **/>) | Dinamikus programozás | Dinamikus programozás a sor prefixeire, visszakövetéssel a mintasorozat. | 2 | Bevezetés | 🟡 kézi ellenőrzés |
| 7 | [Sudoku 1](<7. Sudoku 1 */>) | Visszalépéses keresés | Visszalépéses keresés a 4x4-es sudoku összes szabályos kitöltésére, lexikografikus sorrendben. | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 8 | [Sudoku 2](<8. Sudoku 2 */>) | Visszalépéses keresés | Visszalépéses keresés: az összes szabályos sudoku-tábla felsorolása és a megadottal egyezők számlálása. | 1 | Bevezetés | ✅ kész |
| 9 | [Szoborpark](<9. Szoborpark **/>) | Gráf: egyszerű utak | DFS a bejárati csúcsból, bitmaszkos látogatottsággal; az Árpád-csúcs elérésekor egy utat számolunk. | 2 | Magyarázat | ✅ kész |
| 10 | [Ültetés](<10. Ültetés **/>) | Gráf: párosítás | Bipartit párosítás maximális folyammal (Dinic) a vendégek és az ülőhelyek között. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 11 | [Üvegválogatás](<11. Üvegválogatás */>) | Hozzárendelés: visszalépés | Visszalépés: fajtánként különböző láda, a helyben maradó darabszám maximalizálásával. | 1 | Bevezetés | ✅ kész |
| 12 | [Üzletek](<12. Üzletek */>) | Hozzárendelés: kapacitás | Visszalépés a legszűkebb üzlettel kezdve, pékségenként kapacitás-ellenőrzéssel. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 13 | [Tehenészet](<13. Tehenészet/>) | Bitmask DP, hozzárendelés kapacitással | Üzemenkénti részhalmaz-DP: dp[üzem][beosztott tehenészetek maszkja], részmaszk-felsorolás O(M·3^N) | – | Mélyebb megértés | ✅ kész |
| 14 | [Hátizsák probléma – sok kicsi tárgy](<14. Hátizsák probléma – sok kicsi tárgy/>) | DP, rekonstrukció | 0/1 hátizsák 1-D DP-vel (súly szerint visszafelé), visszafejtés N·K-s bittáblából | – | Bevezetés | ✅ kész |
| 15 | [Biztonságos leszállás](<15. Biztonságos leszállás/>) | Permutációk, ütemezés | Minden sorrend végigpróbálása; sorrendenként a páronkénti korlátok minimuma tört alakban, végül kerekítés másodpercre. | 3 | Magyarázat | ✅ kész |
| 16 | [Szókereső](<16. Szókereső/>) | Rácsbeli DFS, visszalépés | Visszalépéses DFS a rácson, a szó első betűjétől indulva; mezőnként legfeljebb egyszer lépünk. | 2 | Bevezetés | ✅ kész |
| 17 | [Iskolaválasztás](<17. Iskolaválasztás/>) | Hálózati folyam, hozzárendelés | Kapacitásos hozzárendelés: maximális folyam (Dinic) a tanulók és az iskolák hálózatán. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 18 | [L üzlet K pékség](<18. L üzlet K pékség/>) | Bitmask DP, hozzárendelés kapacitással | Pékségenkénti részhalmaz-DP: dp[pékség][kiszolgált üzletek maszkja], részmaszk-felsorolás O(K·3^L) | – | Mélyebb megértés | ✅ kész |
| 19 | [Munkásfelvétel maximált árral](<19. Munkásfelvétel maximált árral/>) | Bitmaszkos DP, hozzárendelés | Bitmaszkos DP a betöltött állások maszkja szerint, legolcsóbb költség, visszakövetéssel a kiosztás. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 20 | [Munkásfelvétel: N állás – N jelentkező](<20. Munkásfelvétel: N állás – N jelentkező/>) | Gráf: min-költségű folyam | Min-költségű folyam: forrás–munkás–állás–nyelő hálózat, a successive shortest path adja a minimális teljes párosítást. | 3 | Magyarázat | ✅ kész |
| 21 | [Munkásfelvétel: N állás – N jelentkező – backtrack](<21. Munkásfelvétel: N állás – N jelentkező – backtrack/>) | Visszalépéses keresés, párosítás | Munkásonként visszalépéses keresés, ágak nyesése Kuhn-féle teljes párosítás-ellenőrzéssel. | 3 | Magyarázat | ✅ kész |
| 22 | [Munkásfelvétel: N állás – N jelentkező, nem lehet mind felvenni](<22. Munkásfelvétel: N állás – N jelentkező, nem lehet mind felvenni/>) | Gráf: min-költségű folyam | Min-költségű folyam: maximális párosítás, ezen belül a legolcsóbb. | 3 | Magyarázat | ✅ kész |
| 23 | [N bástya](<23. N bástya/>) | Permutációk | Permutációk felsorolása lexikografikusan a std::next_permutation függvénnyel. | 2 | Bevezetés | 🟡 kézi ellenőrzés |
| 24 | [N vezér (összes megoldás)](<24. N vezér (összes megoldás)/>) | N vezér, visszalépés | Soronkénti visszalépés, oszlop- és átlójelölőkkel O(1) ütközésellenőrzéssel. | 3 | Magyarázat | ✅ kész |
| 25 | [N vezér (egy megoldás)](<25. N vezér (egy megoldás)/>) | N vezér, visszalépés | Ugyanaz a soronkénti visszalépés, az első megoldásnál azonnal leáll. | 2 | Bevezetés | 🟡 kézi ellenőrzés |
| 26 | [N-ből K az összes lehetséges sorrendben](<26. N-ből K az összes lehetséges sorrendben/>) | Variációk, visszalépés | Visszalépés a még nem használt számok növekvő próbálgatásával, jelölőtömbbel. | 3 | Bevezetés | ✅ kész |
| 27 | [N-ből K az összes lehetséges növekvő sorrendben](<27. N-ből K az összes lehetséges növekvő sorrendben/>) | Kombinációk generálása | Visszalépéses keresés, szigorúan növekvő elemválasztással | 2 | Bevezetés | ✅ kész |
| 28 | [Szóösszeadó fejtörő](<28. Szóösszeadó fejtörő/>) | Teljes keresés | Permutációk nyers erővel végigpróbálása, összegellenőrzéssel | 1 | Bevezetés | ✅ kész |
| 29 | [Az összes lehetséges speciális sorrend](<29. Az összes lehetséges speciális sorrend/>) | Permutációk generálása | Visszalépés: elem marad, vagy szomszédos pár cserél; tárolás nélküli kiírás | 2 | Magyarázat | ✅ kész |
| 30 | [Körmérkőzés új párosítása](<30. Körmérkőzés új párosítása/>) | Visszalépés: párosítás | Visszalépéses keresés: a legkisebb párosítatlan csapatot kötjük össze egy vele még nem játszott csapattal. | 2 | Bevezetés | 🟡 kézi ellenőrzés |
| 31 | [Svájci rendszerű körmérkőzés](<31. Svájci rendszerű körmérkőzés/>) | Bitmaskos DP: párosítás | Bitmaskos DP a párosítatlan csapatok halmazán, minimális pontkülönbség-összeggel. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 32 | [Banda szétválasztása](<32. Banda szétválasztása/>) | Visszalépés: rácsos kapcsolás | Az első sor mind 2^N mintájának kipróbálása, a többi sor kényszerített. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 33 | [Fesztivál](<33. Fesztivál/>) | Visszalépés: beosztás | Visszalépés a legkevesebb lehetőségű emberrel, kapacitáskorlátozással és üres helyszín-szimmetriával. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 34 | [Kirándulás](<34. Kirándulás/>) | Visszalépéses keresés | Visszalépéses keresés, sikertelen állapotok memorizálása, üres buszok szimmetriája. | 3 | Magyarázat | ✅ kész |
