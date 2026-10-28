# IOI ∕ CEOI Válogató 2018 – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 18 feladat · ✅ kész 9 · ❌ hibás 0 · 🟡 kézi 9 · 🟡 nincs minta/speciális 0 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Fizetős utak](<1. Fizetős utak/>) | Gráf: legrövidebb út | 0-1 BFS a fizetős élek számával súlyozva, szülőmutatókból az útvonal visszaállítása | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 2 | [Futárszolgálat](<2. Futárszolgálat/>) | Fa: minimális séta | Steiner-részfa élei, a részfa átmérőjének kétszeres bejárásából levonva | 4 | Magyarázat | 🟡 kézi ellenőrzés |
| 3 | [Szuperhuszár](<3. Szuperhuszár/>) | Geometria: konvex burok | Szögrendezés a lépésvektorokra; az origó nyerhető, ha nincs 180 foknál nagyobb rés | 3 | Mélyebb megértés | ✅ kész |
| 4 | [Leggyorsabb szállítás](<4. Leggyorsabb szállítás/>) | Gráf: legrövidebb út | Dijkstra (távolság, teherbírás) párral, elődök tárolásával az út visszaállításához | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 5 | [Sűrű részsorozat](<5. Sűrű részsorozat/>) | Intervallumfedés, csúszóablak | Csúszóablak-minimum adja a maximumot, utána mohó intervallumfedés a legkevesebb pozícióval | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 6 | [Zárkód](<6. Zárkód/>) | Gráf: Euler-kör | De Bruijn-gráf Euler-köre Hierholzer-algoritmussal, legrövidebb nyitó sorozat. | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 7 | [Találkozó](<7. Találkozó/>) | Dinamikus programozás: rácsút | Négy sarokból számolt DP-tábla, két útvonal-elrendezés a találkozási mezőnél. | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 8 | [Permutációk](<8. Permutációk/>) | Kombinatorika: Dyck-szavak | Veremmel kiadható permutáció zárójelsorozata, Dyck-szó rákövetkezője. | 4 | Mélyebb megértés | ✅ kész |
| 9 | [Hálózat kettéosztás](<9. Hálózat kettéosztás/>) | Lineáris egyenletrendszer GF(2) | Csúcsonként paritás-egyenlet, GF(2) Gauss-elimináció bitekkel. | 4 | Mélyebb megértés | 🟡 kézi ellenőrzés |
| 10 | [Vásárlások](<10. Vásárlások/>) | Dinamikus programozás: bitmask | Napokon végigmenő bitmask-DP a megvett termékek halmazával, visszakövetéssel a napok | 3 | Magyarázat | 🟡 kézi ellenőrzés |
| 11 | [Telephelyek](<11. Telephelyek/>) | Gráf: Steiner-fa | Minden csúcsból Dijkstra, a három telephelyre vezető utak uniója közül a legolcsóbb | 4 | Magyarázat | 🟡 kézi ellenőrzés |
| 12 | [Konténer pakolás](<12. Konténer pakolás/>) | LIS, szegmensfa | Prefix- és suffix-LIS-értékek szegmensfában, a K-adik elem szerinti söpréssel | 5 | Mélyebb megértés | ✅ kész |
| 13 | [Párhuzamos kiszámítás](<13. Párhuzamos kiszámítás/>) | Fakifejezés: ütemezés | Kritikus út adja az időt; a processzorszámot Hu-féle ütemezéssel, bináris kereséssel | 4 | Mélyebb megértés | ✅ kész |
| 14 | [Táblás játék](<14. Táblás játék/>) | Dinamikus programozás: konvolúció | Oszlopmagasság-intervallumok rekurziója, a gyerekek polinomjainak konvolúciója | 5 | Mélyebb megértés | ✅ kész |
| 15 | [Átfedő intervallumok](<15. Átfedő intervallumok/>) | Szegmensfa: lazy frissítés | Lazított szegmensfa, csúcsonként 10 maradék-darabszámmal és körforgató lazy értékkel | 4 | Mélyebb megértés | ✅ kész |
| 16 | [Facsemete](<16. Facsemete/>) | Geometria, szögrendezés | Félegyenes A-ból P-n át; szögszomszédos fák, és üres láncok két mutatóval | 4 | Mélyebb megértés | ✅ kész |
| 17 | [Szótár](<17. Szótár/>) | Stringek: trie | Prefixfa, prefixenkénti számlálás, a szótárat sorrendben építve | 3 | Magyarázat | ✅ kész |
| 18 | [Pálya ellenőrzés](<18. Pálya ellenőrzés/>) | Gráf: folyam | Alsó korlátos minimális folyam: csúcsonként 1, Dinic-algoritmussal | 5 | Mélyebb megértés | ✅ kész |
