/*
Megoldás lényege:
Keressük az olyan [L, U] korlátpárt, amelyre minden ország legalább L és legfeljebb U csomagot kaphat úgy, hogy az összes felajánlott csomag elfér; a válasz a lehető legkisebb U - L. Az első x országba csak az E_i <= x felajánlók küldhetnek, így x * U >= Σ(E_i <= x) Cs_i kell legyen, az x+1..N országokat pedig csak az E_i > x felajánlások látják el, így (N - x) * L <= Σ(E_i > x) Cs_i kell legyen. Ez a két feltételrendszer egymástól független, így U és L külön-külön számolható. Elég az x értékeket az E_i értékeknek és a nullának venni, a rendezés és a prefixösszegek után így O(M log M) időben kapjuk U = max ceil(R(E) / E) és L = min(floor(S / N), floor((S - R(E)) / (N - E))) értékét, ahol R(E) az E_i <= E felajánlások összege, S pedig az összes csomag.
*/
/*
Hint 1: || Egy elosztás akkor jó, ha minden országnak legalább L és legfeljebb U csomag jut. A kérdés tehát az, hogy az alsó és a felső korlát milyen feltételekből adódik, és ezek hogyan függenek egymástól. ||
Hint 2: || Gondold végig, melyik országokba juthat el egy felajánlás: aki E_i-ig küldhet, az csak az 1..E_i országokba küldhet. Ebből az következik, hogy az első x országra összesen legalább annyi csomag kerül, mint amennyit az E_i <= x felajánlók kötelezően oda küldenek, és az utolsó N - x országot csak az E_i > x felajánlók tudják ellátni. ||
Hint 3: || Mindkét feltétel csak az E_i értékeknél változik, így elég ezeket az x értékeket ellenőrizni. Rendezd a felajánlásokat E szerint, és prefixösszegekkel számold ki az E_i <= E összegeket. A felső korlát U = max ceil(R(E) / E), az alsó korlát L = min(floor(S / N), floor((S - R(E)) / (N - E))) minden E < N értékre. A válasz U - L. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m;
    cin >> n >> m;

    vector<pair<long long, long long>> offers(m);  // (E_i, Cs_i)
    long long total = 0;
    for (auto &o : offers) {
        long long cs, e;
        cin >> cs >> e;
        o = {e, cs};
        total += cs;
    }
    sort(offers.begin(), offers.end());

    long long upper = 0;            // U: legnagyobb kötelező terhelés
    long long lower = total / n;    // L: legkisebb megengedett alsó korlát
    long long prefix = 0;           // R(e): az e-nél nem nagyobb E_i-jű felajánlások összege

    size_t i = 0;
    while (i < offers.size()) {
        long long e = offers[i].first;
        while (i < offers.size() && offers[i].first == e) {
            prefix += offers[i].second;
            ++i;
        }
        upper = max(upper, (prefix + e - 1) / e);
        if (e < n) lower = min(lower, (total - prefix) / (n - e));
    }

    cout << upper - lower << '\n';
    return 0;
}
