/*
Megoldás lényege:
Az összes születési dátumot beolvassuk egy vektorba, amelyben (év, hónap, nap) hármasokat tárolunk. A rendezés a tuple lexikografikus összehasonlítása miatt automatikusan évszerint, azon belül hónap, majd nap szerint történik, így az 1. részfeladat egyszerűen a rendezett lista kiírása. A 2. részfeladatban a születésnapot csak a hónap és a nap határozza meg, ezért egy map<pair<hónap, nap>, darabszám> szerkezetben számoljuk az előfordulásokat. A map bejárása már hónap, majd nap szerint rendezett, és a darabszám legalább 2 esetén kiírjuk a dátumot hh.nn. formában. Ha nincs ilyen, egyetlen -1 kerül a kimenetbe. Az időigény O(N log N), ahol N legfeljebb 200.
*/
/*
Hint 1: || A rendezéshez elég a három számot egy hármasba (tuple) tenni: a tuple összehasonlítása pontosan az év, majd a hónap, majd a nap szerinti sorrendet adja. ||
Hint 2: || A születésnap az év nélkül is azonosítható: a hónap és a nap párját egy map-ben számold meg. A map bejárása már rendezett sorrendet ad, és csak a legalább kétszer előforduló párokat kell kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<tuple<int, int, int>> datumok(n);
    for (int i = 0; i < n; i++) {
        int ev, honap, nap;
        cin >> ev >> honap >> nap;
        datumok[i] = make_tuple(ev, honap, nap);
    }
    sort(datumok.begin(), datumok.end());

    cout << "#\n";
    for (const auto &d : datumok) {
        cout << get<0>(d) << " " << get<1>(d) << " " << get<2>(d) << "\n";
    }

    map<pair<int, int>, int> elofordulas;
    for (const auto &d : datumok) {
        elofordulas[make_pair(get<1>(d), get<2>(d))]++;
    }

    cout << "#\n";
    bool van = false;
    for (const auto &p : elofordulas) {
        if (p.second >= 2) {
            printf("%02d.%02d. %d\n", p.first.first, p.first.second, p.second);
            van = true;
        }
    }
    if (!van) {
        cout << "-1\n";
    }

    return 0;
}
