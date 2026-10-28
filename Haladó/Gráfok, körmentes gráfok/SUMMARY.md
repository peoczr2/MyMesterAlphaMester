# Gráfok, körmentes gráfok – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 28 feladat · ✅ kész 16 · ❌ hibás 0 · 🟡 kézi 9 · 🟡 nincs minta/speciális 3 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Állatkert](<1. Állatkert **/>) | Gráfok: fokszámok | Fokszámok számlálása élenként; zsákutca az a csúcs, amelynek fokszáma 1. | 2 | Bevezetés | 🟡 nincs minta |
| 2 | [Arany](<2. Arany */>) | Gráf: elérhetőség | Bejárás minden katalizátor-kizárással, a nélkülözhetetlen betűk gyűjtése | 1 | Bevezetés | ✅ kész |
| 3 | [Családfa](<3. Családfa */>) | Gráf: ősök | Gyermektelenekre visszafelé bejárt ősök számlálása; közös ős, ha mindegyiknél megjelenik | 1 | Bevezetés | ✅ kész |
| 4 | [Építkezés](<4. Építkezés */>) | Gráf: topologikus sorrend | Kahn-féle topologikus rendezés, szintek a leghosszabb előírás-lánc szerint | 1 | Bevezetés | ✅ kész |
| 5 | [Építkezési terv](<5. Építkezési terv */>) | Gráf: ütemezés | Legkorábbi napok javítása az előírások szerint, majd rendezett mohó ütemezés | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 6 | [Folyón átkelés](<6. Folyón átkelés */>) | Gráf: DP körmentes gráfon | Topologikus sorrendű DP: szigetenként a legnagyobb elérhető pénz, visszakövetéssel az útvonal | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 7 | [Kredit](<7. Kredit */>) | Gráf: kritikus út | Legkorábbi és legkésőbbi félév topologikus sorrendben; egyenlőségnél a tárgy kötött | 1 | Magyarázat | ✅ kész |
| 8 | [Mingrel](<8. Mingrel */>) | Gráf: topologikus sorrend | Szomszédos szavak első eltérő betűpárjából gráf, arra topologikus rendezés (Kahn) | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 9 | [Minimális házépítési idő](<9. Minimális házépítési idő **/>) | Gráf: leghosszabb út | Leghosszabb út irányított körmentes gráfon, élsúly k+1; kör esetén -1 | 2 | Magyarázat | ✅ kész |
| 10 | [Munkasorrend](<10. Munkasorrend **/>) | Topologikus rendezés | Három vállalkozó blokkjainak permutációja, majd Kahn-rendezés a korábbi blokk előnyben részesítésével. | 2 | Magyarázat | 🟡 kézi ellenőrzés |
| 11 | [Pontpárok közötti távolság](<11. Pontpárok közötti távolság */>) | Fák: pontpárok távolsága | Gyökértől mért távolságok, a távolság a két csúcs távolságának és a közös ős kétszeresének különbsége. | 1 | Magyarázat | 🟡 nincs minta |
| 12 | [Repülőút](<12. Repülőút */>) | DAG: kikerülhetetlen pontok | Átugrási ellenőrzés csúcsokra, vágásonkénti élszámlálás különbségi tömbbel. | 1 | Magyarázat | ✅ kész |
| 13 | [Síelő](<13. Síelő */>) | Gráf: körmentes, legrövidebb út | Topologikus sorrendű DP: legrövidebb és leghosszabb pálya, holtverseny a kezdőponttal | 1 | Bevezetés | ✅ kész |
| 14 | [Túra](<14. Túra **/>) | Gráf: elágazás nélküli szakasz | Kimenő élek láncolása, DP fordított topologikus sorrendben, holtverseny a kisebb kezdőponttal | 2 | Magyarázat | ✅ kész |
| 15 | [Utak száma](<15. Utak száma */>) | Gráf: utak száma | Dinamikus programozás topologikus sorrendben, maradékkal (mod 100000007) | 1 | Bevezetés | ✅ kész |
| 16 | [Építkezés](<16. Építkezés **/>) | Gráf: topologikus rendezés | Előre és hátra bejárás A-ból, illetve B-ből; a metszet elemszáma A és B nélkül | 2 | Magyarázat | ✅ kész |
| 17 | [Szabadtéri állatkert](<17. Szabadtéri állatkert ***/>) | Gráf: úthosszak | Élszámok bitsorozatos DP topologikus sorrendben, a K-hoz legközelebbi úthossz | 3 | Magyarázat | 🟡 nincs minta |
| 18 | [Építkezés kevés munkással](<18. Építkezés kevés munkással ****/>) | Gráf: ütemezés | Hu-algoritmus szintek szerint, a munkásszám bináris kereséssel | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 19 | [Akadálypálya](<19. Akadálypálya/>) | Gráf: csúcsvágás | Minimális csúcsvágás maximális folyammal, legfeljebb két csúcsig | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 20 | [Akadálypálya tervezés](<20. Akadálypálya tervezés/>) | Gráfok: rétegezett párosítás | BFS-rétegezés; a rétegek közti élek minimális lefedése párosítással (Hopcroft–Karp) | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 21 | [Házépítés](<21. Házépítés/>) | Gráfok: topologikus rendezés | A-elődök és B-utódok rögzítése, a köztes munkák topologikus sorrendje A és B között | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 22 | [Hálózat központja](<22. Hálózat központja */>) | Fa: excentricitás | Átmérő két végpontjától mért távolságok maximuma adja az excentricitást; három BFS | 1 | Magyarázat | ✅ kész |
| 23 | [Vasútvonal leghamarabb érkezéssel](<23. Vasútvonal leghamarabb érkezéssel/>) | Gráf: időfüggő út | Vonatok indulási sorrendben, állomásonkénti legkorábbi érkezés frissítése egy menetben | 2 | Bevezetés | ✅ kész |
| 24 | [Vasútvonal leghamarabb érkezés legkésőbbi indulással](<24. Vasútvonal leghamarabb érkezés legkésőbbi indulással/>) | Gráf: időzített utak | Előre: legkorábbi érkezés, hátra: állomásonként a legnagyobb jó indulási idő | 3 | Mélyebb megértés | ✅ kész |
| 25 | [Utazás](<25. Utazás ***/>) | Gráf: játékelmélet | Nyerő és vesztő városok visszafelé terjesztése körmentes gráfon | 3 | Mélyebb megértés | ✅ kész |
| 26 | [Hegymászó](<26. Hegymászó **/>) | Gráf: utak száma | Topologikus sorrendű DP: kezdőtáborokból elérhető útvonalak száma maradékkal | 2 | Magyarázat | ✅ kész |
| 27 | [Hegymászó](<27. Hegymászó/>) | Gráf: utak száma | Topologikus sorrendű DP: kezdőtáborokból elérhető útvonalak száma maradékkal | 2 | Magyarázat | ✅ kész |
| 28 | [Építkezés](<28. Építkezés ****/>) | Gráf: látványos sorrend | Blokkokra bontás, mohó bővítéshelyek intervallum-feltétellel, határidős (EDF) kiosztás | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
