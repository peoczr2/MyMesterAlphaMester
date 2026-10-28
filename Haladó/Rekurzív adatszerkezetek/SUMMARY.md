# Rekurzív adatszerkezetek – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 93 feladat · ✅ kész 64 · ❌ hibás 0 · 🟡 kézi 18 · 🟡 nincs minta/speciális 11 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Aranyalma](<1. Aranyalma ***/>) | Fa: dinamikus programozás | Fa-DP részfánként, a megtartott csomópontok számával indexelve, összefésüléssel. | 3 | Mélyebb megértés | ✅ kész |
| 2 | [Árvízvédelem](<2. Árvízvédelem ***/>) | Rendezett fa, mohó | 2N-1 szakaszra bontott bináris fa komponensekre vágása | 3 | Mélyebb megértés | ✅ kész |
| 3 | [Banda átszervezése](<3. Banda átszervezése ***/>) | Fa: részfa-áthelyezés | Összes (x, y) áthelyezés kipróbálása; új magasság Euler-sorrendű szegmensfával. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 4 | [Beépített ügynök](<4. Beépített ügynök */>) | Fa: mélység, részfa-méret | Legkisebb mélységű szabad helyű tag; holtversenyben a több leszármazottal rendelkező. | 1 | Bevezetés | ✅ kész |
| 5 | [Család](<5. Család */>) | Családfa: rokonsági kapcsolatok | Szülői táblából közvetlen ellenőrzés: testvérek, féltestvérek, apai ág bejárása, unokatestvérek a szülők testvéreinek gyermekeiként. | 1 | Bevezetés | ✅ kész |
| 6 | [Családfa](<6. Családfa */>) | Fa: szintenkénti bejárás | BFS a gyökértől: a szintenkénti létszám maximuma és minimuma (a gyökér szintje kizárva). | 1 | Bevezetés | ✅ kész |
| 7 | [Csatornatakarító](<7. Csatornatakarító **/>) | Fa: erdő levelei | Nagy szakaszok erdejének levelei indulnak robotot, a lánc hosszát felfelé számoljuk. | 2 | Magyarázat | ✅ kész |
| 8 | [DNS ismétlődés](<8. DNS ismétlődés ***/>) | Hash: csúszóablak | Csúszóablak K hosszú részsztringekre, négyes számrendszerű kulccsal és gyakoriságszámlálással. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 9 | [DNS kezdőszeletek](<9. DNS kezdőszeletek ***/>) | Trie, kezdőszelet | Trie-ba építjük a szekvenciákat; minden szekvencia útján összeadjuk a bemeneti végpontok számát. | 3 | Magyarázat | ✅ kész |
| 10 | [DNS legtöbbször előforduló kezdőszelet](<10. DNS legtöbbször előforduló kezdőszelet ***/>) | Gyakoriság számlálás | Hash-tábla: az első K karakter előfordulásainak számlálása, a legnagyobb kiválasztása. | 3 | Magyarázat | ✅ kész |
| 11 | [Fa elágazásai](<11. Fa elágazásai */>) | Fa: rekurzív feldolgozás | Rekurzív leírás-feldolgozás: zárójelpárok számolása, közben a gyerekszám maximuma. | 1 | Bevezetés | ✅ kész |
| 12 | [Fa magassága](<12. Fa magassága */>) | Fa: rekurzív feldolgozás | Rekurzív bejárás: a magasság a lánchossz és a legmagasabb gyermek összege, a leghosszabb lánc külön. | 1 | Magyarázat | ✅ kész |
| 13 | [Fa zárójelezéssel](<13. Fa zárójelezéssel */>) | Bináris fa: rekurzív elemzés | Rekurzív elemzés: magasság, tömeg és elágazásszám egy bejárásban, bináris szerkezettel. | 1 | Magyarázat | ✅ kész |
| 14 | [Faágak letörése](<14. Faágak letörése ***/>) | Fa: alulról felfelé bejárás | Postorder bejárás: részfánként a nagyobb oldal letörése, amíg az egyensúly helyreáll. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 15 | [Fában leghosszabb út](<15. Fában leghosszabb út ***/>) | Fa: átmérő | BFS-sel a fa átmérője; a kör hossza átmérő + 1. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 17 | [Favágás](<17. Favágás ***/>) | Bináris fa, DP | exact K vágásos fa-DP, részfák összefésülése | 3 | Mélyebb megértés | ✅ kész |
| 18 | [Fenyőfa zárójelezéssel](<18. Fenyőfa zárójelezéssel */>) | Fa: súlyozott összeg | Mélységenkénti darabszámok súlya 2^(H−d), nagy számok Horner-sémával. | 1 | Magyarázat | ✅ kész |
| 19 | [Folyók](<19. Folyók */>) | Gráf: bejárás | Két bejárás: a fordított élek mentén a források, az eredetin a szennyezés. | 1 | Bevezetés | ✅ kész |
| 20 | [Folyók összefolyása](<20. Folyók összefolyása */>) | Fa: közös ős | Mélységek kiegyenlítése, majd együtt felfelé lépkedés az első közös csúcsig. | 1 | Magyarázat | ✅ kész |
| 21 | [Harmadolás](<21. Harmadolás */>) | Fa: mélység, levelek | A megtartott pénz nevezőjének kitevője mélységből és levélségből adódik. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 22 | [Jelentés](<22. Jelentés */>) | Gráf: BFS és mélység | BFS a gyökértől: minden dolgozó mélysége, a legmélyebb csúcs keresése a legkisebb sorszámmal. | 1 | Bevezetés | ✅ kész |
| 23 | [Kamionok](<23. Kamionok */>) | Fa: részfák és levelek | Részfánként a termelés és a levelek számának hányadosa; a válasz ezek felfelé kerekített maximuma. | 1 | Mélyebb megértés | ✅ kész |
| 24 | [Kémek](<24. Kémek */>) | Fa: fokszám és mélység | Főnök: a felettes nélküli csúcs; legtöbb beosztott: fokszámlálás; legmesszebb: BFS a főnöktől. | 1 | Bevezetés | ✅ kész |
| 25 | [Kémszervezet](<25. Kémszervezet **/>) | Gráf: BFS szintek | BFS-sel szintenként számoljuk a tagokat, a legtöbb tagú legkisebb szintet adjuk. | 2 | Magyarázat | 🟡 nincs minta |
| 26 | [Képlet](<26. Képlet ***/>) | Kifejezésfa: DP | Veremmel felépített kifejezésfa; minden részre a legnagyobb és legkisebb elérhető érték (egy jelváltás). | 3 | Mélyebb megértés | ✅ kész |
| 27 | [Képzés](<27. Képzés **/>) | Fa: DP, csúcsfedés | Minimális csúcsfedés fán: kétállapotú DP (képzésen van / nincs), a gyökér is szabadon választható. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 28 | [Kiegyensúlyozott keresőfa](<28. Kiegyensúlyozott keresőfa **/>) | Bináris keresőfa | Méret szerinti rekurzív felezés, majd inorder bejárással az 1..N értékek kiosztása. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 29 | [Kieséses csapatverseny](<29. Kieséses csapatverseny */>) | Erdő, részfák | kieséses erdő, fokszámok és részfaméretek | 1 | Magyarázat | ✅ kész |
| 30 | [Kieséses verseny](<30. Kieséses verseny */>) | Erdő, részfák | kieséses erdő, győzelemszámok és részfaméretek | 1 | Magyarázat | ✅ kész |
| 31 | [Lovak](<31. Lovak ***/>) | DAG, útszámlálás | topologikus útszám-DP az ősökre és teljes utakra | 3 | Mélyebb megértés | ✅ kész |
| 32 | [Őrhangyák](<32. Őrhangyák ***/>) | Fa, mohó | legmélyebb őrizetlen élhez a K-adik ős választása | 3 | Mélyebb megértés | ✅ kész |
| 33 | [Raktár](<33. Raktár */>) | Fa, részfaösszeg | raktárba gyökerezett fa, élkapacitással korlátos részfa-hozzájárulás | 1 | Magyarázat | ✅ kész |
| 34 | [Sereg](<34. Sereg **/>) | Fa, inkrementális statisztika | éves belépések mellett mélység-, levél- és fokszámkarbantartás | 2 | Magyarázat | ✅ kész |
| 35 | [Szállítás](<35. Szállítás **/>) | Fa, DP | nettó részfatöbblet és újrahasznosítható kamionok száma | 2 | Mélyebb megértés | ✅ kész |
| 36 | [Titkos társaság](<36. Titkos társaság **/>) | Bináris fa, DP | legmélyebb elég nagy tökéletes bináris részfa keresése | 2 | Magyarázat | 🟡 nincs minta |
| 37 | [Titkos társaság 1](<37. Titkos társaság 1 */>) | Bináris fa, részfák | üres A/B helyek számlálása részfánként | 1 | Bevezetés | ✅ kész |
| 38 | [Titkos társaság 2](<38. Titkos társaság 2 */>) | Fa: részfa-összegzés | Szabad gyerekhelyek összegzése részfánként, a bejárás fordított sorrendjében. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 39 | [Titkos társaság 3](<39. Titkos társaság 3 **/>) | Fa, LCA | részfaméret, ős-leszármazott reláció és távolság | 2 | Magyarázat | ✅ kész |
| 40 | [Titkos társaság 4](<40. Titkos társaság 4 **/>) | Fa, átmérő | részfaméret, csúcstávolság és két BFS-es átmérő | 2 | Magyarázat | ✅ kész |
| 41 | [Trópusi fa](<41. Trópusi fa ***/>) | Bináris fa, kanonizálás | normál és tükrözött részfaazonosítók összehasonlítása | 3 | Mélyebb megértés | ✅ kész |
| 42 | [Túra](<42. Túra */>) | Erdő, szülőlánc | közös downstream pont keresése és láncpozíció-jelölés | 1 | Bevezetés | ✅ kész |
| 43 | [Újság](<43. Újság */>) | Fa, részfák | részfaméret, mélység és legmélyebb közös ős | 1 | Bevezetés | ✅ kész |
| 44 | [Ügynökök lecserélése](<44. Ügynökök lecserélése **/>) | Fa, DP | részfa-lefedéses fa-knapsack legalább fél szervezetre | 2 | Mélyebb megértés | ✅ kész |
| 45 | [Üzenetek](<45. Üzenetek */>) | Fa-parszolás, string | zárójeles fa egyszeri parzolása fokszámra, mélységre, levelekre | 1 | Bevezetés | ✅ kész |
| 46 | [Üzletek](<46. Üzletek **/>) | Fa: dinamikus programozás | Fa-DP gyökérből: egy részfát csak akkor kötünk be, ha hozzájárulása pozitív. | 2 | Mélyebb megértés | ✅ kész |
| 47 | [Vállalat – utasítások K lépésben](<47. Vállalat – utasítások K lépésben */>) | Fa: mélységi bejárás | Bejárás az igazgatótól, a K mélységben lévő munkatársak gyűjtése. | 1 | Bevezetés | ✅ kész |
| 48 | [Vállalat – üzenet az igazgatónak](<48. Vállalat – üzenet az igazgatónak */>) | Fa, mélység | K távolságra levő csúcsok kigyűjtése szülőlistából | 1 | Bevezetés | ✅ kész |
| 49 | [Vasút](<49. Vasút ***/>) | Fa, láncok | leghosszabb lefelé induló egygyerekes szakasz keresése | 3 | Magyarázat | 🟡 nincs minta |
| 50 | [Titkos társaság alcsoport](<50. Titkos társaság alcsoport ***/>) | Bináris fa, DP | legmélyebb elég nagy tökéletes bináris részfa keresése | 3 | Magyarázat | 🟡 nincs minta |
| 51 | [Bináris fa magassága és szélessége](<51. Bináris fa magassága és szélessége ***/>) | Bináris fa, parszolás | zárójeles bináris fa magassága és szintszélessége | 3 | Bevezetés | ✅ kész |
| 52 | [Fa magassága és szélessége](<52. Fa magassága és szélessége ***/>) | Fa, parszolás | általános zárójeles fa magassága és szintszélessége | 3 | Bevezetés | ✅ kész |
| 54 | [Körök](<54. Körök/>) | Funkcionális gráf, ciklusok | Kahn-levágás + reverse DFS a cikluskomponensekre | – | Magyarázat | ✅ kész |
| 55 | [Titkos küldemény](<55. Titkos küldemény/>) | Fa, mélység | ősök lánca + részfánkénti mélységszámlálás Euler-idővel | – | Magyarázat | ✅ kész |
| 56 | [Konverzió](<56. Konverzió/>) | String, parszolás | veremmel épített fa + minimális zárójelezés precedencia szerint | – | Bevezetés | ✅ kész |
| 57 | [Banda](<57. Banda/>) | Fa-DP | maximum független halmaz dp0/dp1-gyel, rekurzió nélkül (S[i] < i: i = N..1 sorrend), visszaépítés szigorú dp1 > dp0 szabállyal (= hivatalos kimenet) | – | Magyarázat | ✅ kész |
| 58 | [DNS](<58. DNS/>) | String, automata, mohó | Aho-Corasick + intervallumfedés greedy | – | Mélyebb megértés | ✅ kész |
| 59 | [Családfa](<59. Családfa/>) | Fa, BFS | mélységszámítás a gyökértől, legmélyebb leszármazottak kigyűjtése | – | Bevezetés | ✅ kész |
| 60 | [Fa szélső pontjai](<60. Fa szélső pontjai/>) | Fa: szintenkénti bejárás | Szintenkénti BFS balról jobbra: minden szint első és utolsó csúcsa, unióban. | 2 | Bevezetés | 🟡 kézi ellenőrzés |
| 61 | [Vizitúra](<61. Vizitúra/>) | Fa, átmérő | két bejárásos fa-átmérő súlyozott éleken | – | Magyarázat | ✅ kész |
| 62 | [Szigetek](<62. Szigetek/>) | Fa, kombinatorika | részfák sorrendjeinek számlálása multinomialis DP-vel | – | Magyarázat | ✅ kész |
| 63 | [Közös ősök](<63. Közös ősök/>) | LCA, bináris emelés | legközelebbi közös ős lekérdezések | – | Magyarázat | ✅ kész |
| 64 | [Közös ősök száma](<64. Közös ősök száma/>) | LCA, bináris emelés | LCA mélységéből közös ősök száma | – | Magyarázat | ✅ kész |
| 65 | [Részfák](<65. Részfák/>) | Fa: részfa-azonosítás | Kanonikus azonosító (címke, bal és jobb gyerek azonosítója) minden részfára, hash-halmazban keresve. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 66 | [Szótár](<66. Szótár/>) | Trie, prefixszámolás | beszúrási sorrend szerinti prefixösszegzés | – | Mélyebb megértés | ✅ kész |
| 67 | [Átfedő intervallumok](<67. Átfedő intervallumok/>) | Szegmensfa, lazy | 10-es ciklusú szegmensfa forgatással | – | Mélyebb megértés | ✅ kész |
| 68 | [Párhuzamos kiszámítás](<68. Párhuzamos kiszámítás/>) | Fa: párhuzamos végrehajtás | Határidő-korlát: t-ig esedékes műveletek száma legfeljebb t·P; az idő a gyökér magassága. | 3 | Mélyebb megértés | ✅ kész |
| 69 | [Közös főnök](<69. Közös főnök/>) | Fa: legközelebbi közös ős | LCA bináris emeléssel, majd a közvetlen főnök kiválasztása, ha az egyik dolgozó a másiké | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 70 | [Találós kérdések](<70. Találós kérdések/>) | Fa, DFS | címkefrekvencia a kérdésfán | – | Bevezetés | ✅ kész |
| 71 | [Csővezetés](<71. Csővezetés/>) | Fa, részfa | célcsapok ősútjainak uniója | – | Bevezetés | ✅ kész |
| 72 | [Csapok zárása](<72. Csapok zárása/>) | Fa, részfa | célmentes maximális részfák lezárása | – | Bevezetés | ✅ kész |
| 73 | [Fantasztikus feladat](<73. Fantasztikus feladat/>) | Mozgó ablak, prímtényezők | Mozgó ablak prímtényező-számlálókkal, frissítésnél az érintett ablakok lokális újraszámolása | 3 | Mélyebb megértés | ✅ kész |
| 74 | [Robotok összegyűjtése](<74. Robotok összegyűjtése/>) | Bináris fa: bejárási sorrend | Ajtónyitottság szerinti elérhetőség; a bejárási sorrend az útvonal lexikografikus összehasonlítása. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 75 | [Társaság](<75. Társaság ***/>) | Fa, bináris keresés | Bináris keresés a várakozási időre, alulról felfelé mohó kijelölés. | 3 | Mélyebb megértés | ✅ kész |
| 76 | [Járatok](<76. Járatok **/>) | Fabejárás, koordináták | Rácskoordináták számítása fabejárással, oszloponként a legmélyebb terem kiválasztása | 2 | Magyarázat | ✅ kész |
| 77 | [Tornyok](<77. Tornyok ****/>) | Szegmensfa, intervallum | jobb oldali láthatósági intervallumok offline fedése | 4 | Mélyebb megértés | ✅ kész |
| 78 | [Barlangrendszer](<78. Barlangrendszer **/>) | Gráfbejárás, koordináták | BFS koordinátákkal, bejárt termek jelölésével, oszloponként a legmagasabb terem | 2 | Magyarázat | ✅ kész |
| 79 | [Színes fa](<79. Színes fa ***/>) | Fa, színezés | A legkisebb levélmélység adja a színek számát; színezés mélység szerint. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 80 | [Szállítás](<80. Szállítás ***/>) | Fa, láncfelbontás | A fa leghosszabb utas láncokra bontása, a K leghosszabb lánc összege. | 3 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 81 | [Útadó](<81. Útadó/>) | Fa, súlyozás | élhasználati számok szerinti adóoptimalizálás | – | Magyarázat | 🟡 nincs minta |
| 81 | [Útadó](<81. Útadó ***/>) | Fa, élek súlyozása | Él-együttható 2·s·(N−s), majd átrendezési párosítás a maximumhoz. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 82 | [Dinamikus rendezett minta](<82. Dinamikus rendezett minta/>) | Rendezett halmaz, treap | Kulcs szerinti treap részfa-méretekkel: beszúrás, k-adik elem és rang logaritmikus időben | 3 | Magyarázat | 🟡 speciális |
| 83 | [Dinamikus rendezett minta törléssel](<83. Dinamikus rendezett minta törléssel/>) | Rendezett halmaz, törlés | Kulcs szerinti treap: Adat csak a hiányzó elemet szúrja be, törlés split-tel | 3 | Magyarázat | 🟡 speciális |
| 84 | [Művelatek sorozattal](<84. Művelatek sorozattal/>) | Sorozat, implicit treap | Implicit treap részfa-méretekkel; beszúrás és törlés split-merge műveletekkel | 3 | Magyarázat | 🟡 speciális |
| 85 | [Intervallumok](<85. Intervallumok/>) | Intervallumok, metszéskeresés | Treap (l,r) szerint, részfánként legnagyobb jobb véggel a metszéskereséshez | 3 | Magyarázat | 🟡 speciális |
| 86 | [Pont a legtöbb intervallumban](<86. Pont a legtöbb intervallumban/>) | Lefedettség, prefixmaximum | Események prefixösszege treapben, részfánként legnagyobb prefixösszeg és helye | 3 | Magyarázat | 🟡 speciális |
| 87 | [Génsebész](<87. Génsebész/>) | Implicit treap, DNS-sorozat | Implicit treap karakterszámlálókkal: beszúrás, csere, kivágás és részszámlálás | 4 | Magyarázat | 🟡 speciális |
| 88 | [Legközelebbi közös anya és apa](<88. Legközelebbi közös anya és apa/>) | Családfa: közös ős | Anyai és apai ág felmenőinek metszete, BFS-sel legkisebb távolságú ősanya és ősapa | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 89 | [Legközelebbi közös ős](<89. Legközelebbi közös ős/>) | Családfa: közös ős | Anyai és apai ág felmenőinek metszete, BFS-sel legközelebbi közös ős | 2 | Magyarázat | ✅ kész |
| 90 | [Kulcsember](<90. Kulcsember/>) | Fa, centroid | centroid keresés maximális komponens minimalizálásával | – | Bevezetés | ✅ kész |
| 91 | [Csoportbontás](<91. Csoportbontás/>) | Fa: levélszámlálás | Levélszámok a részfákban; törléskor a gyerek-részfák és a felső komponens levélszámaiból a minimum. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 92 | [Titkos tömb](<92. Titkos tömb/>) | Permutáció, stack | next greater tömb visszaállítása preorderrel | – | Magyarázat | ✅ kész |
| 93 | [Legtávolabbi leszármazott](<93. Legtávolabbi leszármazott/>) | Fa, mélység | DFS mélységmaximum | – | Bevezetés | ✅ kész |
| 94 | [Különböző katicák](<94. Különböző katicák/>) | Fa: dinamikus programozás | Paritásrögzítés és alulról felfelé intervallumszűkítés, majd felülről lefelé visszaépítés | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
