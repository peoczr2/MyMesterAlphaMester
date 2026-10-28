/*
Megoldás lényege:
Két egyenlő pontszám közé nem lehet vágást tenni, mert a távolságuk 0, a T pedig legalább 1, ezért csak a különböző pontszámokat kell figyelembe venni. A pontszámok legfeljebb M-ek, így egy M+1 méretű jelölőtömbbel a rendezett sorrend egyetlen bejárással megkapható. A szomszédos különböző pontszámok különbségei közül azok a lehetséges vágások távolságai, amelyek nagyobbak T-nél. Ha ilyenből kevesebb van, mint K-1, a felosztás nem lehetséges, és -1 a válasz. Egyébként a K-1 legnagyobb távolságot csökkenő sorrendben írjuk ki. Az időigény O(N + M), a memóriaigény O(M).
*/
/*
Hint 1: || Két egyenlő pontszám közé nem lehet vágást tenni, hiszen a távolságuk 0, a T pedig legalább 1. Elég a különböző pontszámokat sorba rendezve nézni. ||
Hint 2: || Egy vágás akkor megfelelő, ha a két szomszédos különböző pontszám különbsége nagyobb T-nél. Ezekből a különbségekből kell a K-1 legnagyobbat kiválasztani, csökkenő sorrendben; ha kevesebb van, a válasz -1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, t;
    cin >> n >> m >> k >> t;

    vector<char> van(m + 1, 0);
    for (int i = 0; i < n; i++) {
        int e;
        cin >> e;
        van[e] = 1;
    }

    // a szomszédos különböző pontszámok közötti, T-nél nagyobb távolságok
    vector<int> tavolsag;
    int elozo = -1;
    for (int x = 1; x <= m; x++) {
        if (!van[x]) continue;
        if (elozo != -1 && x - elozo > t) tavolsag.push_back(x - elozo);
        elozo = x;
    }

    if ((int)tavolsag.size() < k - 1) {
        cout << -1 << "\n";
        return 0;
    }

    sort(tavolsag.begin(), tavolsag.end(), greater<int>());
    for (int i = 0; i < k - 1; i++) {
        if (i) cout << ' ';
        cout << tavolsag[i];
    }
    cout << "\n";
    return 0;
}
