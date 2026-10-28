/*
Megoldás lényege:
A távolság az erősek legkisebb és a gyengék legnagyobb pontszámának különbsége.
Mivel a távolságnak T-nél nagyobbnak kell lennie, és T legalább 1, minden gyenge
versenyző pontszáma kisebb minden erős versenyző pontszámánál. Rendezett sorozatban
ez egyetlen vágást jelent: előtte állnak a gyengék, utána az erősek. A vágás két
szomszédos elem közé kerül, így a távolság a szomszédos különbség. A T-nél nagyobb
szomszédos különbségek közül a legnagyobbat keressük; ha nincs ilyen, a válasz -1.
A rendezés miatt az időigény O(N log N).
*/
/*
Hint 1: || Rendezés után gondold végig, hogy a két csoport hol választható szét: a gyengék egy közös határ alatt, az erősek felette állnak. Melyik két szomszédos rendezett elem között érdemes ezt a határt húzni? ||
Hint 2: || Ha a rendezett sorozat i-edik és (i+1)-edik eleme közé húzod a határt, a távolság e[i+1] - e[i] lesz. Keresd a T-nél nagyobb legnagyobb ilyen különbséget, és ha nincs ilyen, a válasz -1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, t;
    cin >> n >> m >> t;
    vector<int> e(n);
    for (int i = 0; i < n; ++i) cin >> e[i];
    sort(e.begin(), e.end());

    int ans = -1;
    for (int i = 0; i + 1 < n; ++i) {
        int gap = e[i + 1] - e[i];
        if (gap > t) ans = max(ans, gap);
    }
    cout << ans << '\n';
    return 0;
}
