/*
Megoldás lényege:
Egy faj ingadozását a darabszámainak szórása méri, és a legnagyobb szórású faj ugyanaz, mint a legnagyobb szórásnégyzetű. A szórásnégyzet helyett az M·Σx² − (Σx)² értéket hasonlítjuk, ez a szórásnégyzet M²-szerese, így a sorrend nem változik, és egész számként pontosan kiszámolható (sem osztás, sem négyzetgyök nincs). Minden faj oszlopára az összeget és a négyzetösszeget egy menetben gyűjtjük, majd kiválasztjuk a legnagyobb értékű fajt. Több azonos maximum esetén az elsőt írjuk ki, mert a feladat szerint bármelyik megfelelő. Az idő O(M·N), legfeljebb 10 000 beolvasott szám.
*/
/*
Hint 1: || Nem kell tört vagy négyzetgyök: elég egy olyan értéket összehasonlítani, amelynek a sorrendje ugyanaz, mint a szórásnégyzeté. Ehhez a faj oszlopának összegét és négyzetösszegét kell ismerned. ||
Hint 2: || Oszloponként gyűjtsd az összeget (Σx) és a négyzetösszeget (Σx²) egy menetben. A kiszámított M·Σx² − (Σx)² értékből tartsd nyilván a legnagyobbat és annak a fajnak a sorszámát. ||
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
    long long legnagyobb = LLONG_MIN;
    for (int j = 1; j <= N; ++j) {
        long long szoras = M * negyzetosszeg[j] - osszeg[j] * osszeg[j];
        if (szoras > legnagyobb) {
            legnagyobb = szoras;
            legjobb = j;
        }
    }

    cout << legjobb << '\n';
    return 0;
}
