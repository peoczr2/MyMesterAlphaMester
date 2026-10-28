/*
Megoldás lényege: visszalépéses keresés. Mindig a legszűkebb lehetőségű, még ki nem osztott
üzletet választjuk (amelynek a kapacitással még kiszolgálható pékségei száma a legkisebb), és
kipróbáljuk az összes ilyen pékséget; ha egy üzletnek nem jut pékség, az ág kudarc, és
visszalépünk. Az ágat akkor is levágjuk, ha valamely X pékség-halmazra az X-ből kizárólag
kiszolgálható üzletek összigénye nagyobb X maradék kapacitásánál: ekkor ebben az ágban nincs
megoldás. Mivel a pékségek száma legfeljebb 7, a halmazok száma (legfeljebb 128) kicsi, a vágás
olcsó, és a megoldás nélküli, nehéz esetekben is jelentősen csökkenti a keresési fát.
*/
/*
Hint 1: || Mivel a pékségek száma legfeljebb 7, a keresési fa erősen korlátozott: üzletenként végig lehet próbálni a lehetséges pékségeket. ||
Hint 2: || A legszűkebb üzlettel érdemes kezdeni, vagyis amelynek kevés lehetősége van; ha egy üzletnek nincs elég kapacitású pékség, vágd le az ágat. ||
Hint 3: || Vágd le az ágat, ha egy pékség-halmazra az ott kizárólag kiszolgálható üzletek összigénye nagyobb a halmaz maradék kapacitásánál; a halmazokat bitmaszkkal érdemes kezelni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> igeny, kap;
vector<vector<int>> kapcsolatok;
vector<int> ans;
vector<char> hasznalt;

bool dfs(int placed, long long leftDemand) {
    if (placed == n) return true;
    if (leftDemand > accumulate(kap.begin(), kap.end(), 0LL)) return false;

    // Vágás: X pékség-halmazra az X-ből kizárólag kiszolgálható üzletek igénye nem haladhatja
    // meg X maradék kapacitását. need[X]: az X-be eső üzletek összigénye (részhalmaz-összeg),
    // capX[X]: X maradék kapacitása.
    const int K = 1 << m;
    long long need[1 << 7] = {0}, capX[1 << 7] = {0};
    for (int i = 0; i < n; ++i) if (!hasznalt[i]) {
        int mask = 0;
        for (int x : kapcsolatok[i]) if (kap[x] >= igeny[i]) mask |= 1 << x;
        if (mask == 0) return false;
        need[mask] += igeny[i];
    }
    for (int b = 0; b < m; ++b)
        for (int X = 0; X < K; ++X) if (X >> b & 1) need[X] += need[X ^ (1 << b)];
    for (int X = 1; X < K; ++X) {
        capX[X] = capX[X & (X - 1)] + kap[__builtin_ctz(X)];
        if (need[X] > capX[X]) return false;
    }

    int best = -1;
    vector<int> cand;
    for (int i = 0; i < n; ++i) if (!hasznalt[i]) {
        vector<int> v;
        for (int x : kapcsolatok[i]) if (kap[x] >= igeny[i]) v.push_back(x);
        if (v.empty()) return false;
        if (best == -1 || v.size() < cand.size() || (v.size() == cand.size() && igeny[i] > igeny[best])) {
            best = i;
            cand = move(v);
        }
    }
    hasznalt[best] = 1;
    for (int b : cand) {
        kap[b] -= igeny[best];
        ans[best] = b + 1;
        if (dfs(placed + 1, leftDemand - igeny[best])) return true;
        kap[b] += igeny[best];
    }
    hasznalt[best] = 0;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    igeny.resize(n);
    for (int i = 0; i < n; ++i) cin >> igeny[i];
    kap.resize(m);
    for (int i = 0; i < m; ++i) cin >> kap[i];
    kapcsolatok.assign(n, {});
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        kapcsolatok[i].resize(p);
        for (int j = 0; j < p; ++j) {
            cin >> kapcsolatok[i][j];
            --kapcsolatok[i][j];
        }
    }
    ans.assign(n, -1);
    hasznalt.assign(n, 0);
    long long total = accumulate(igeny.begin(), igeny.end(), 0LL);
    if (!dfs(0, total)) {
        cout << -1 << '\n';
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}