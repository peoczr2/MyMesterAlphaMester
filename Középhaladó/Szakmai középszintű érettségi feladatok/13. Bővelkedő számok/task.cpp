/*
Megoldás lényege:
Egy szám valódi osztóinak összegét úgy kapjuk meg, hogy a 2-től √n-ig terjedő d értékeket megvizsgáljuk: ha d osztója n-nek, akkor d-t és a hozzá tartozó n/d párt is hozzáadjuk az összeghez (négyzetszám esetén csak egyszer). Az 1 minden n > 1 szám valódi osztója, ezt külön adjuk hozzá. A szám bővelkedő, ha ez az összeg nagyobb magánál a számnál. Mivel K ≤ 10 000, egy szám ellenőrzése legfeljebb 100 lépés, így az N ≤ 500 darab szám feldolgozása gyorsan lefut. A bővelkedő számokat vektorba gyűjtjük, majd rendezve kiírjuk a darabszámukkal együtt.
*/
/*
Hint 1: || Egy szám osztóit nem kell mind végigpróbálni: elég az 1-től √n-ig terjedő osztókat keresni, mert az osztók párban jönnek (d és n/d). ||
Hint 2: || Írj függvényt, amely egy szám valódi osztóinak összegét adja vissza: a d = 2 kezdőértéktől addig ciklusozz, amíg d·d ≤ n, és ha d osztója n-nek, adj hozzá d-t és n/d-t is (ügyelj a négyzetszámokra). Az 1-et külön add hozzá, ha n > 1. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Az n valódi osztóinak (n-nél kisebb osztók) összege
long long properDivisorSum(long long n) {
    long long sum = 0;
    if (n > 1) sum = 1;
    for (long long d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            sum += d;
            long long e = n / d;
            if (e != d) sum += e;
        }
    }
    return sum;
}

int main() {
    int n;
    cin >> n;

    vector<long long> abundant;
    for (int i = 0; i < n; i++) {
        long long k;
        cin >> k;
        if (properDivisorSum(k) > k) abundant.push_back(k);
    }

    sort(abundant.begin(), abundant.end());

    cout << abundant.size() << "\n";
    for (long long x : abundant) {
        cout << x << "\n";
    }

    return 0;
}
