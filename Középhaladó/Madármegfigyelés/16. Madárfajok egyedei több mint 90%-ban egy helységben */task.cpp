/*
Megoldás lényege:
Egy faj egyedei akkor vannak több mint 90%-ban egy helységben, ha a faj összes megfigyelt darabszámának több mint 90%-a egyetlen helységben van. Fajonként gyűjtjük az összeget és az egyes helységekben látott legnagyobb darabszámot, majd egész számokkal hasonlítjuk össze: 100·maximum > 90·összeg. Így nincs tizedes törtes kerekítési hiba, és a sehol nem látott faj automatikusan kiesik. Végül a találatok számát írjuk ki, majd sorszámaikat növekvő sorrendben. Az idő O(M·N), legfeljebb 10 000 beolvasott szám.
*/
/*
Hint 1: || Fajonként elég két értéket ismerned: a faj összes megfigyelt darabszámát, és azt a legnagyobb darabszámot, amelyet egyetlen helységben láttunk. ||
Hint 2: || A "több mint 90%" feltételt tört nélkül írd fel: 100 · legnagyobb > 90 · összeg. Ez egész számokkal pontos, és a sehol nem látott faj (összeg 0) automatikusan kiesik. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;

    vector<long long> osszeg(N + 1, 0), maximum(N + 1, 0);
    for (int i = 0; i < M; ++i) {
        for (int j = 1; j <= N; ++j) {
            long long e;
            cin >> e;
            osszeg[j] += e;
            maximum[j] = max(maximum[j], e);
        }
    }

    vector<int> talalat;
    for (int j = 1; j <= N; ++j) {
        if (100 * maximum[j] > 90 * osszeg[j]) talalat.push_back(j);
    }

    cout << talalat.size() << '\n';
    for (size_t k = 0; k < talalat.size(); ++k) {
        if (k) cout << ' ';
        cout << talalat[k];
    }
    if (!talalat.empty()) cout << '\n';
    return 0;
}
