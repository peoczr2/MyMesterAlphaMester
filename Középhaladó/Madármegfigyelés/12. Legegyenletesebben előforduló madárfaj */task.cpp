/*
Megoldás lényege:
Egy faj egyenletességét a darabszámainak szórása méri, ezért a legkisebb szórású faj ugyanaz, mint
a legkisebb szórásnégyzetű. A szórásnégyzet M²-szerese M·Σx² − (Σx)², ez egész számként, osztás
nélkül pontosan kiszámolható. Minden fajra az összeget és a négyzetösszeget egy menetben gyűjtjük,
majd kiválasztjuk a legkisebb értékű fajt. Több azonos minimum esetén az elsőt írjuk ki, mert a
feladat szerint bármelyik megfelelő.
*/
/*
Hint 1: || A szórás minimumát ugyanaz a faj adja, mint a szórásnégyzetét, így a négyzetgyököt nem kell kiszámolni. Minden fajt külön vizsgálhatsz a saját oszlopa alapján. ||
Hint 2: || Egy fajra elég két összeget gyűjteni: a darabszámok összegét és a négyzetük összegét. A szórásnégyzet helyett a M·Σx² − (Σx)² értéket hasonlítsd, mert ez egész számként is pontos. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    vector<long long> osszeg(N + 1, 0), negyzetosszeg(N + 1, 0);
    for (int i = 0; i < M; ++i) {
        for (int j = 1; j <= N; ++j) {
            long long e;
            cin >> e;
            osszeg[j] += e;
            negyzetosszeg[j] += e * e;
        }
    }

    int legjobb = 1;
    long long legkisebb = LLONG_MAX;
    for (int j = 1; j <= N; ++j) {
        long long szoras = M * negyzetosszeg[j] - osszeg[j] * osszeg[j];
        if (szoras < legkisebb) {
            legkisebb = szoras;
            legjobb = j;
        }
    }

    cout << legjobb << '\n';
    return 0;
}
