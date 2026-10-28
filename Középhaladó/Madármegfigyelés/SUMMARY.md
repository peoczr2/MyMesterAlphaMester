# Madármegfigyelés – oktatási összefoglaló

> Generált fájl (`library/tools/catalog.py`). Ne szerkeszd kézzel: a adatok a `library/meta/` fájlokból és az automatikus ellenőrzésből jönnek.

Összesítés: 27 feladat · ✅ kész 1 · ❌ hibás 0 · 🟡 kézi 4 · 🟡 nincs minta/speciális 22 · ⬜ nincs megoldás 0

Skála:
- **Nehézség 1–5**: a mappanév csillagai (`*` … `****`); csillag nélkül a megoldó becslése.
- **Órai cél**: `Bevezetés` (alapok) · `Magyarázat` (egy ötlet, egy trükk) · `Mélyebb megértés` (több lépéses ötlet)

| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |
|---|---|---|---|---:|---|---|
| 1 | [Ahol a madár se jár](<1. Ahol a madár se jár */>) | Keresés mátrix sorában | Soronkénti bejárással keressük az első csupa nulla sor sorszámát. | 1 | Bevezetés | ✅ kész |
| 2 | [Egy átlagosan legkedveltebb helység](<2. Egy átlagosan legkedveltebb helység */>) | Összegzés: eltérések összege | Az átlagtól vett eltérések összege a sorösszegtől függ, ezért a legnagyobb sorösszeget keressük. | 1 | Magyarázat | 🟡 nincs minta |
| 3 | [Együtt előforduló madárfajok](<3. Együtt előforduló madárfajok */>) | Halmaz: állandó társak | Páronkénti ellenőrzés: minden helységben, ahol j előfordul, k is jelen van-e. | 1 | Magyarázat | 🟡 nincs minta |
| 4 | [Elterjedt madárfajok száma](<4. Elterjedt madárfajok száma */>) | Arány-feltétel, számlálás | Fajonként a helységek számát egész aritmetikával hasonlítjuk a 90%-hoz: 10·h > 9·M. | 1 | Bevezetés | 🟡 nincs minta |
| 5 | [Gyakori madárfaj](<5. Gyakori madárfaj */>) | Halmazmetszet: közös faj | Azt a fajt keressük, amelyik minden madarat tartalmazó helységben jelen volt; jelzőtömbbel szűrünk. | 1 | Bevezetés | 🟡 nincs minta |
| 6 | [Helységek csupa máshol is előforduló madárfajjal](<6. Helységek csupa máshol is előforduló madárfajjal */>) | Számlálás: máshol is előfordult | Fajonként a helységek számát megszámoljuk, majd helységenként ellenőrizzük a feltételt. | 1 | Magyarázat | 🟡 nincs minta |
| 7 | [Helységek egyedi madárral](<7. Helységek egyedi madárral */>) | Előfordulás-számlálás, egyediség | Fajonként számoljuk, hány helységben fordult elő; az egyedi fajhoz tartozó helységet jelöljük. | 1 | Magyarázat | 🟡 nincs minta |
| 8 | [Helységek egyféle madárral](<8. Helységek egyféle madárral */>) | Soronkénti számlálás | Helységenként megszámoljuk a pozitív darabszámú fajokat; a pontosan egy fajt tartalmazókat írjuk ki. | 1 | Bevezetés | 🟡 nincs minta |
| 9 | [Helységek mindenféle madárral](<9. Helységek mindenféle madárral */>) | Soronkénti feltételellenőrzés | Soronként ellenőrizzük, hogy nincs-e nulla; csak a nulla nélküli sorok helységeit írjuk ki. | 1 | Bevezetés | 🟡 nincs minta |
| 10 | [Helységek minimális madárszámmal](<10. Helységek minimális madárszámmal */>) | Összegzés, minimumkeresés | Helységenkénti sorösszegek kiszámítása, majd a minimummal egyező összegű sorok kiválogatása. | 1 | Bevezetés | 🟡 nincs minta |
| 11 | [Helységek több mint 90%-ban egyféle madárral](<11. Helységek több mint 90%-ban egyféle madárral */>) | Arány-feltétel, összegzés | Sorönként a legnagyobb darabszámot és az összeget egész számokkal hasonlítjuk össze: 100·max > 90·összeg. | 1 | Bevezetés | 🟡 nincs minta |
| 12 | [Legegyenletesebben előforduló madárfaj](<12. Legegyenletesebben előforduló madárfaj */>) | Szórás, minimumkeresés | Fajonként a M·Σx² − (Σx)² értéket számoljuk egészekkel, és a legkisebbet keressük. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 13 | [Legnagyobb ingadozással előforduló madárfaj](<13. Legnagyobb ingadozással előforduló madárfaj */>) | Szórás, maximumkeresés | Oszloponként M·Σx² − (Σx)² egész értékek összehasonlítása, a legnagyobb kiválasztása. | 1 | Magyarázat | 🟡 kézi ellenőrzés |
| 14 | [Madárfaj alkalmi társfaja?](<14. Madárfaj alkalmi társfaja? */>) | Mátrix: páronkénti együttelőfordulás | Helységenként a jelenlévő fajpárok bejelölése egy N×N-es logikai táblázatban. | 1 | Bevezetés | 🟡 nincs minta |
| 15 | [Madárfajok állandó társfajai](<15. Madárfajok állandó társfajai */>) | Halmaz: állandó társak | Páronként: minden olyan helységben, ahol j előfordul, k is jelen van-e; logikai táblázattal. | 1 | Magyarázat | 🟡 nincs minta |
| 16 | [Madárfajok egyedei több mint 90%-ban egy helységben](<16. Madárfajok egyedei több mint 90%-ban egy helységben */>) | Arány-feltétel, összegzés | Fajonként a legnagyobb egyedi darabszám és az összeg egész számokkal: 100·max > 90·összeg. | 1 | Bevezetés | 🟡 nincs minta |
| 17 | [Magának való madárfaj](<17. Magának való madárfaj */>) | Átlag: feltételes számlálás | Fajonként az előforduló helységekben mért társaságszámok átlaga, minimum keresése keresztszorzással. | 1 | Magyarázat | 🟡 nincs minta |
| 18 | [Maximális egyedszámú helységek](<18. Maximális egyedszámú helységek */>) | Szélsőérték: oszloponkénti maximum | Oszloponkénti maximumkeresés egy bejárással, egyenlőségnél a legkisebb sorszám marad. | 1 | Bevezetés | 🟡 nincs minta |
| 19 | [Maximális madárszámú helység](<19. Maximális madárszámú helység */>) | Összegzés: sorösszeg maximum | Soronkénti összegzés, a legnagyobb összegű helység sorszámának megjegyzése. | 1 | Bevezetés | 🟡 nincs minta |
| 20 | [Mindenhol előforduló madárfajok](<20. Mindenhol előforduló madárfajok */>) | Mátrix: minden sorban előfordul | Fajonként nullaellenőrzés: egy nulla darabszám kizárja a fajt a jelöltek közül. | 1 | Bevezetés | 🟡 nincs minta |
| 21 | [Mindenhol legalább annyi van az egyikből, mint a másikból?](<21. Mindenhol legalább annyi van az egyikből, mint a másikból? */>) | Mátrix: oszloppárok összehasonlítása | Oszloppárok páronkénti összehasonlítása minden helységben, a főátló kihagyásával. | 1 | Bevezetés | 🟡 nincs minta |
| 22 | [Minimális madárfajszámú helység](<22. Minimális madárfajszámú helység */>) | Mátrix: sorok számlálása, minimum | Helységenként a nem nulla darabszámok megszámolása, majd a legkisebb számlálójú helység kiválasztása. | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 23 | [Ritka madárfaj](<23. Ritka madárfaj */>) | Számlálás: egyedi előfordulás | Fajonként a helységek számának számlálása, majd az első pontosan 1-et kapó faj kiválasztása. | 1 | Bevezetés | 🟡 kézi ellenőrzés |
| 24 | [Volt helység mindenféle madárral?](<24. Volt helység mindenféle madárral? */>) | Keresés, sorfeltétel | Soronkénti bejárás, nulla nélküli sor keresése, egy találat elég. | 1 | Bevezetés | 🟡 nincs minta |
| 25 | [Volt maximális helység?](<25. Volt maximális helység? */>) | Maximumkeresés oszloponként | Oszloponkénti maximum, majd annak ellenőrzése, hogy egy sor minden eleme maximális-e. | 1 | Magyarázat | 🟡 nincs minta |
| 26 | [Volt maximális madárfaj?](<26. Volt maximális madárfaj? */>) | Halmazmetszet, maximum | Helységenként a leggyakoribb fajok halmaza; a halmazok metszete nem üres-e. | 1 | Magyarázat | 🟡 nincs minta |
| 27 | [Volt ritka madárfaj?](<27. Volt ritka madárfaj? */>) | Számlálás fajonként | Fajonként a nullától különböző darabszámok számlálása; van-e pontosan 1-es. | 1 | Bevezetés | 🟡 nincs minta |
