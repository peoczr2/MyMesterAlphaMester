/*
Megoldás lényege:
Minden vízállást készültségi szintre osztunk: 3, ha meghaladja a 1000 cm-t, 2, ha meghaladja a 900 cm-t, 1, ha meghaladja a 800 cm-t, egyébként 0.
Folyószakasz a maximális, egymás melletti, azonos szintű mérésekből álló sorozat. Egy bejárással megkeressük az összes ilyen sorozatot,
és a harmadfokú szintűeket kiírjuk: a darabszámot, a kezdő- és végsorszámukat, a hosszukat, majd az összhosszukat.
A szintek összehasonlítása O(1), így az egész megoldás O(N) időben fut.
*/
/*
Hint 1: || Először minden vízállásról állapítsd meg a készültségi szintjét: harmadfokú az, ha a vízállás nagyobb mint 1000 cm. ||
Hint 2: || Folyószakasz egy maximális, egymás melletti, azonos szintű mérésekből álló sorozat. Balról jobbra haladva, amíg a szint nem változik, ugyanahhoz a szakaszhoz tartozol. ||
Hint 3: || Minden harmadfokú szakasznál tárold a kezdő- és a végsorszámát, a hosszát (vég - kezdet + 1), és az összhosszba add hozzá. ||
*/
#include <bits/stdc++.h>
using namespace std;

int szint(int h) {
    if (h > 1000) return 3;
    if (h > 900) return 2;
    if (h > 800) return 1;
    return 0;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<pair<int, int>> harmadfokuak;
    int i = 1;
    while (i <= n) {
        int s = szint(a[i]);
        int j = i;
        while (j + 1 <= n && szint(a[j + 1]) == s) j++;
        if (s == 3) harmadfokuak.push_back({i, j});
        i = j + 1;
    }

    cout << harmadfokuak.size() << '\n';
    if (harmadfokuak.empty()) return 0;

    for (size_t k = 0; k < harmadfokuak.size(); k++) {
        if (k > 0) cout << ' ';
        cout << harmadfokuak[k].first << ' ' << harmadfokuak[k].second;
    }
    cout << '\n';

    long long osszhossz = 0;
    for (size_t k = 0; k < harmadfokuak.size(); k++) {
        int hossz = harmadfokuak[k].second - harmadfokuak[k].first + 1;
        if (k > 0) cout << ' ';
        cout << hossz;
        osszhossz += hossz;
    }
    cout << '\n';
    cout << osszhossz << '\n';

    return 0;
}
