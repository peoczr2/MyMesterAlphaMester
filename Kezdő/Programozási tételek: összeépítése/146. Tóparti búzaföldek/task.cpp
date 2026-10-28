/*
Megoldás lényege:
Mindkét testvér listája növekvően rendezett, és mindketten egy-egy részvényt adnak el, így egy lehetséges pár összege a + b. Azt a párt keressük, amelynek összege még nem haladja meg a nyaraló árát (X), mert ennél a hiányzó X - (a + b) összeg a legkisebb. Az első listát növekvő sorrendben végigjárva a második listában a legnagyobb, X-nél nem nagyobb elem indexe csak csökkenhet, ezért kéttámutatós módszerrel O(N + M) időben megkapjuk az optimumot. Ha nincs olyan pár, amelynek összege X-en belül marad, a kimenet X.
*/
/*
Hint 1: || Az eladott részvények összegét úgy kapod, hogy az első testvér egy és a második testvér egy részvényének értékét összeadod. Mivel mindkét lista növekvő, nem kell minden párt végignézned: elég azt figyelni, melyik a legnagyobb olyan elem a másik listában, amely még belefér X-be. ||
Hint 2: || Az első listában haladj előre sorban, a másodikban tarts egy mutatót a legnagyobb, még megfelelő elemre. Ahogy az első listában nő az érték, ez a mutató csak hátrafelé mozdulhat, így mindkét lista legfeljebb egyszer kell végigjárni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m, x;
    cin >> n >> m >> x;
    vector<long long> a(n), b(m);
    for (auto &v : a) cin >> v;
    for (auto &v : b) cin >> v;

    long long best = -1;   // a legnagyobb, X-en belüli pár összege
    long long j = m - 1;   // b-ben az aktuális legnagyobb, megfelelő elem indexe
    for (long long i = 0; i < n; i++) {
        while (j >= 0 && a[i] + b[j] > x) j--;
        if (j < 0) break;  // ennél nagyobb a-val sincs megfelelő pár
        best = max(best, a[i] + b[j]);
    }

    if (best < 0) cout << x << '\n';
    else cout << x - best << '\n';
    return 0;
}
