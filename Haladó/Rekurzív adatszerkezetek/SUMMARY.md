# Rekurzív adatszerkezetek

Részben feldolgozott batch. Az alábbi táblában a már megoldott feladatok szerepelnek.

Skála: a nehézség 1-től 5-ig terjed, ahol 1 = nagyon alap, 5 = kifejezetten nehéz.

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | Aranyalma | Fa-DP | részfa DP, választás legfeljebb K csomóponttal | 3 | Magyarázat | ✅ kész |
| 2 | Árvízvédelem | Rendezett fa, mohó | 2N-1 szakaszra bontott bináris fa komponensekre vágása | 4 | Mélyebb megértés | ✅ kész |
| 3 | Banda átszervezése | Fa, átmérő | bruteforce áthelyezés + Euler/segment tree | 3 | Magyarázat | ✅ kész |
| 4 | Beépített ügynök | Fa, hierarchia | DFS részfaméret, gyökér gyerekei közül választás | 2 | Bevezetés | ✅ kész |
| 5 | Család | Családfa | szülő-táblák, rokoni lekérdezések | 2 | Bevezetés | ✅ kész |
| 6 | Családfa | Fa, generációk | BFS szintszámlálás | 1 | Bevezetés | ✅ kész |
| 7 | Csatornatakarító | Fa, útfedés | nagy csövek láncai, levél-startok | 3 | Magyarázat | ✅ kész |
| 8 | DNS ismétlődés | String, ablak | 4-es kódolás, csúszó ablak | 1 | Bevezetés | ✅ kész |
| 9 | DNS kezdőszeletek | Trie, string | trie-alapú prefixszámlálás | 2 | Bevezetés | ✅ kész |
| 10 | DNS legtöbbször előforduló kezdőszelet | Trie, prefix | prefix-hashmap / számlálás | 1 | Bevezetés | ✅ kész |
| 11 | Fa elágazásai | String, fa-parszolás | rekurzív parser, elágazásszám | 2 | Bevezetés | ✅ kész |
| 12 | Fa magassága | String, fa-parszolás | rekurzív parser, magasság és lánchossz | 2 | Bevezetés | ✅ kész |
| 13 | Fa zárójelezéssel | String, bináris fa | rekurzív parser, háromértékes DP | 2 | Magyarázat | ✅ kész |
| 14 | Faágak letörése | Fa, egyensúly | postorder prunings, ágbontás | 3 | Magyarázat | ✅ kész |
| 15 | Fában leghosszabb út | Fa, átmérő | két BFS a fa átmérőjére | 2 | Bevezetés | ✅ kész |
| 16 | Farajz | Bináris fa, fa-parszolás | levelek számlálása a zárójelezett fában | 1 | Bevezetés | ✅ kész |
| 17 | Favágás | Bináris fa, DP | exact K vágásos fa-DP, részfák összefésülése | 4 | Mélyebb megértés | ✅ kész |
| 18 | Fenyőfa zárójelezéssel | String, fa-parszolás | rekurzív parser, magasság és súly | 2 | Bevezetés | ✅ kész |
| 19 | Folyók | Irányított fa | fordított/original DFS elérhetőség | 2 | Bevezetés | ✅ kész |
| 20 | Folyók összefolyása | Irányított fa, LCA | szülőláncok összehasonlítása | 2 | Bevezetés | ✅ kész |
| 21 | Harmadolás | Fa, generációk | depth-alapú számlálás | 1 | Bevezetés | ✅ kész |
| 22 | Jelentés | Fa, mélység | BFS mélységmaximum | 1 | Bevezetés | ✅ kész |
| 23 | Kamionok | Fa, útösszeg | DFS gyökértől levélig maximális útösszeg | 1 | Bevezetés | ✅ kész |
| 24 | Kémek | Fa, mélység | gyökér, fokszám, legmélyebb csúcs | 1 | Bevezetés | ✅ kész |
| 25 | Kémszervezet | Fa, szintek | BFS szintszámlálás | 1 | Bevezetés | ✅ kész |
| 26 | Képlet | Kifejezésfa, DP | teljesen zárójelezett kifejezés, egy operátor flipje | 2 | Magyarázat | ✅ kész |
| 27 | Képzés | Fa, DP | gyökérre kényszerített minimum csúcsfedés visszaépítéssel | 3 | Magyarázat | ✅ kész |
| 28 | Kiegyensúlyozott keresőfa | Bináris fa, konstrukció | méretre kiegyensúlyozott fa építése, inorder értékadás | 2 | Magyarázat | ✅ kész |
| 29 | Kieséses csapatverseny | Erdő, részfák | kieséses erdő, fokszámok és részfaméretek | 2 | Magyarázat | ✅ kész |
| 30 | Kieséses verseny | Erdő, részfák | kieséses erdő, győzelemszámok és részfaméretek | 2 | Magyarázat | ✅ kész |
| 31 | Lovak | DAG, útszámlálás | topologikus útszám-DP az ősökre és teljes utakra | 3 | Mélyebb megértés | ✅ kész |
| 32 | Őrhangyák | Fa, mohó | legmélyebb őrizetlen élhez a K-adik ős választása | 4 | Mélyebb megértés | ✅ kész |
| 33 | Raktár | Fa, részfaösszeg | raktárba gyökerezett fa, élkapacitással korlátos részfa-hozzájárulás | 2 | Magyarázat | ✅ kész |
| 34 | Sereg | Fa, inkrementális statisztika | éves belépések mellett mélység-, levél- és fokszámkarbantartás | 3 | Magyarázat | ✅ kész |
| 35 | Szállítás | Fa, DP | nettó részfatöbblet és újrahasznosítható kamionok száma | 4 | Mélyebb megértés | ✅ kész |
| 36 | Titkos társaság | Bináris fa, DP | legmélyebb elég nagy tökéletes bináris részfa keresése | 3 | Magyarázat | ✅ kész |
| 37 | Titkos társaság 1 | Bináris fa, részfák | üres A/B helyek számlálása részfánként | 1 | Bevezetés | ✅ kész |
| 38 | Titkos társaság 2 | Fa, részfák | sorszámozott gyerekhelyek üres pozícióinak részfaösszege | 2 | Bevezetés | ✅ kész |
| 39 | Titkos társaság 3 | Fa, LCA | részfaméret, ős-leszármazott reláció és távolság | 2 | Magyarázat | ✅ kész |
| 40 | Titkos társaság 4 | Fa, átmérő | részfaméret, csúcstávolság és két BFS-es átmérő | 2 | Magyarázat | ✅ kész |
| 41 | Trópusi fa | Bináris fa, kanonizálás | normál és tükrözött részfaazonosítók összehasonlítása | 4 | Mélyebb megértés | ✅ kész |
| 42 | Túra | Erdő, szülőlánc | közös downstream pont keresése és láncpozíció-jelölés | 1 | Bevezetés | ✅ kész |
| 43 | Újság | Fa, részfák | részfaméret, mélység és legmélyebb közös ős | 1 | Bevezetés | ✅ kész |
| 44 | Ügynökök lecserélése | Fa, DP | részfa-lefedéses fa-knapsack legalább fél szervezetre | 4 | Mélyebb megértés | ✅ kész |
| 45 | Üzenetek | Fa-parszolás, string | zárójeles fa egyszeri parzolása fokszámra, mélységre, levelekre | 1 | Bevezetés | ✅ kész |
| 46 | Üzletek | Fa, DP | pozitív gyerekrészfák megtartása élköltséggel gyökerezett DP-ben | 3 | Magyarázat | ✅ kész |
| 47 | Vállalat – utasítások K lépésben | Fa, mélység | K mélységű csúcsok kigyűjtése bináris fában | 1 | Bevezetés | ✅ kész |
| 48 | Vállalat – üzenet az igazgatónak | Fa, mélység | K távolságra levő csúcsok kigyűjtése szülőlistából | 1 | Bevezetés | ✅ kész |
| 49 | Vasút | Fa, láncok | leghosszabb lefelé induló egygyerekes szakasz keresése | 2 | Magyarázat | ✅ kész |
| 50 | Titkos társaság alcsoport | Bináris fa, DP | legmélyebb elég nagy tökéletes bináris részfa keresése | 3 | Magyarázat | ✅ kész |
| 51 | Bináris fa magassága és szélessége | Bináris fa, parszolás | zárójeles bináris fa magassága és szintszélessége | 1 | Bevezetés | ✅ kész |
| 52 | Fa magassága és szélessége | Fa, parszolás | általános zárójeles fa magassága és szintszélessége | 1 | Bevezetés | ✅ kész |
| 53 | Farajz | Bináris fa, fa-parszolás | levelek számlálása zárójelezett fában | 2 | Bevezetés | ⏳ függőben |
| 54 | Körök | Funkcionális gráf, ciklusok | Kahn-levágás + reverse DFS a cikluskomponensekre | 3 | Magyarázat | ✅ kész |
| 55 | Titkos küldemény | Fa, mélység | ősök lánca + részfánkénti mélységszámlálás Euler-idővel | 3 | Magyarázat | ✅ kész |
| 56 | Konverzió | String, parszolás | veremmel épített fa + minimális zárójelezés precedencia szerint | 2 | Bevezetés | ✅ kész |
| 57 | Banda | Fa-DP | maximum független halmaz visszaépítéssel | 3 | Magyarázat | ✅ kész |
| 58 | DNS vizsgálat | String, automata, mohó | Aho-Corasick + intervallumfedés greedy | 4 | Mélyebb megértés | ✅ kész |
| 59 | Családfa | Fa, BFS | mélységszámítás a gyökértől, legmélyebb leszármazottak kigyűjtése | 1 | Bevezetés | ✅ kész |
| 60 | Fa szélső pontjai | Fa, szintek | szintenkénti első és utolsó csúcs kigyűjtése BFS-sel | 1 | Bevezetés | ✅ kész |
| 61 | Vizitúra | Fa, átmérő | két bejárásos fa-átmérő súlyozott éleken | 2 | Magyarázat | ✅ kész |
| 62 | Szigetek | Fa, kombinatorika | részfák sorrendjeinek számlálása multinomialis DP-vel | 3 | Magyarázat | ✅ kész |
| 63 | Közös ősök | LCA, bináris emelés | legközelebbi közös ős lekérdezések | 3 | Magyarázat | ✅ kész |
| 64 | Közös ősök száma | LCA, bináris emelés | LCA mélységéből közös ősök száma | 2 | Magyarázat | ✅ kész |
| 65 | Részfák | Bináris fa, kanonizálás | részfa-hash/azonosító alapú egyezés | 3 | Magyarázat | ✅ kész |
| 66 | Szótár | Trie, prefixszámolás | beszúrási sorrend szerinti prefixösszegzés | 4 | Mélyebb megértés | ✅ kész |
| 67 | Átfedő intervallumok | Szegmensfa, lazy | 10-es ciklusú szegmensfa forgatással | 4 | Mélyebb megértés | ✅ kész |
| 68 | Párhuzamos kiszámítás | Fa-DP, párhuzam | kritikus út + műveletszám / idő | 3 | Magyarázat | ✅ kész |
| 69 | Közös főnök | LCA, fa | legközelebbi közös főnök speciális szülő-szabállyal | 3 | Magyarázat | ✅ kész |
| 70 | Találós kérdések | Fa, DFS | címkefrekvencia a kérdésfán | 2 | Bevezetés | ✅ kész |
| 71 | Csővezetés | Fa, részfa | célcsapok ősútjainak uniója | 1 | Bevezetés | ✅ kész |
| 72 | Csapok zárása | Fa, részfa | célmentes maximális részfák lezárása | 2 | Bevezetés | ✅ kész |
| 77 | Tornyok | Szegmensfa, intervallum | jobb oldali láthatósági intervallumok offline fedése | 4 | Mélyebb megértés | ✅ kész |
| 81 | Útadó | Fa, súlyozás | élhasználati számok szerinti adóoptimalizálás | 3 | Magyarázat | ✅ kész |
| 90 | Kulcsember | Fa, centroid | centroid keresés maximális komponens minimalizálásával | 2 | Bevezetés | ✅ kész |
| 92 | Titkos tömb | Permutáció, stack | next greater tömb visszaállítása preorderrel | 3 | Magyarázat | ✅ kész |
| 93 | Legtávolabbi leszármazott | Fa, mélység | DFS mélységmaximum | 1 | Bevezetés | ✅ kész |
| 94 | Különböző katicák | Fa-DP, intervallum | paritásos intervallum-DP és visszaépítés | 4 | Mélyebb megértés | ✅ kész |

## Batch állapot
- **Elkészült feladatok**: 1–52, 54–77, 81, 90, 92–94
- **Függő feladat**: 53
- **Megjegyzés**: 53-at a kérésnek megfelelően átmenetileg kihagytuk.