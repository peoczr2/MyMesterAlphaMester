/*
Megoldás lényege:
A feladat azt kéri, hogy minden mért értékhez írjuk ki a darabszámát, növekvő sorrendben. Ha a N mérést rendezzük, az azonos értékek egymás után kerülnek, így egy lineáris bejárással a futamok hossza megszámolható. Minden futamhoz kiírjuk az értéket és a futam hosszát. A rendezés O(N log N) időt igényel, ami N = 100 000 esetén bőven belefér az időlimitbe, a kiírás pedig automatikusan növekvő sorrendben történik.
*/
/*
Hint 1: || A kiírás mért érték szerint növekvő sorrendben történik. Ha a méréseket rendezed, az azonos értékek egymás mellé kerülnek. ||
Hint 2: || Egy menetben haladj végig a rendezett sorozaton, és számold, hány egymást követő elem egyezik az aktuálissal. Amikor az érték megváltozik, írd ki az előzőt és a darabszámát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> e(n);
    for (int i = 0; i < n; ++i) {
        cin >> e[i];
    }
    sort(e.begin(), e.end());

    for (int i = 0; i < n;) {
        int j = i;
        while (j < n && e[j] == e[i]) ++j;
        cout << e[i] << ' ' << (j - i) << '\n';
        i = j;
    }
    return 0;
}
