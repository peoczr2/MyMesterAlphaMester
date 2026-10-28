/*
Megoldás lényege:
Egy helységben akkor van a madarak több mint 90%-a egyféle, ha a legtöbbször látott faj darabszáma
nagyobb, mint a helység összes madarának 90%-a. Ezt tört nélkül, egész számokkal ellenőrizzük:
100 · maximum > 90 · összeg. Így nincs lebegőpontos kerekítési hiba, és az üres helység (összeg 0)
automatikusan kiesik. Végül kiírjuk a találatok számát és sorszámaikat növekvő sorrendben.
*/
/*
Hint 1: || Egy helységnél elég a sorban a legnagyobb darabszámot és a sor összegét nézni, a többi faj részletei nem számítanak. ||
Hint 2: || A "több mint 90%" feltétel tört nélkül is felírható: 100 · (sor maximuma) > 90 · (sor összege). Így egész számokkal dolgozhatsz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    vector<int> talalat;
    for (int i = 1; i <= M; ++i) {
        long long osszeg = 0, maximum = 0;
        for (int j = 0; j < N; ++j) {
            long long e;
            cin >> e;
            osszeg += e;
            maximum = max(maximum, e);
        }
        if (100 * maximum > 90 * osszeg) talalat.push_back(i);
    }

    cout << talalat.size() << '\n';
    for (size_t k = 0; k < talalat.size(); ++k) {
        if (k) cout << ' ';
        cout << talalat[k];
    }
    if (!talalat.empty()) cout << '\n';
    return 0;
}
