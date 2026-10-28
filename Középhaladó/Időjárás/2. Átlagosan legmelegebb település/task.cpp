/*
Megoldás lényege:
Az átlag az összeg és a napok számának hányadosa. Mivel minden településnek ugyanannyi napja van, elég a településenkénti összegeket összehasonlítani. Soronként beolvassuk és összegezzük az értékeket, közben nyilvántartjuk a legnagyobb összeget és annak sorszámát. Csak szigorúan nagyobb összegnél frissítünk, így egyenlőség esetén a kisebb sorszám marad. Az idő O(N·M), a memória O(1).
*/
/*
Hint 1: || Az átlag kiszámítása helyett elég a településenkénti összegeket összehasonlítani, hiszen minden településnek ugyanannyi napja van. ||
Hint 2: || Soronként olvasd be az értékeket és közben összegezd őket. Tartsd nyilván a legnagyobb összeget és az ahhoz tartozó sorszámot, és csak szigorúan nagyobb összegnél írd felül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    long long legjobb_osszeg = LLONG_MIN;
    int legjobb = 0;
    for (int i = 1; i <= n; i++) {
        long long osszeg = 0;
        for (int j = 0; j < m; j++) {
            int h;
            cin >> h;
            osszeg += h;
        }
        // szigorú összehasonlítás: egyenlőségnél a kisebb sorszám marad
        if (osszeg > legjobb_osszeg) {
            legjobb_osszeg = osszeg;
            legjobb = i;
        }
    }

    cout << legjobb << '\n';
    return 0;
}
