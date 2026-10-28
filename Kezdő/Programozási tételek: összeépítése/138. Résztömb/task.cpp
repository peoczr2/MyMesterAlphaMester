/*
Megoldás lényege:
Legyen D_i = F_i - N_i, és P_i a D_1..D_i prefixösszege (P_0 = 0). Egy [l..r] időszak férfi-nő különbsége P_r - P_(l-1),
így a feladat: az összes P_i-közül a legközelebbi pár megtalálása. A P értékeket növekvő sorrendbe rendezzük (az indexszel együtt),
és a szomszédos elemek különbsége adja a minimumot, hiszen rendezett sorozatban a legkisebb különbség mindig szomszédos párban van.
A kiírt időszak a párban szereplő két index közül a kisebbtől +1 napjától a nagyobbik napjáig tart.
Az időigény O(M log M), a memóriaigény O(M).
*/
/*
Hint 1: || A férfiak és nők különbségét napokra összegezve prefixösszegekkel fejezhetjük ki: egy időszak különbsége két prefixösszeg különbsége. ||
Hint 2: || Keress két prefixösszeget, amelyek a lehető legközelebb vannak egymáshoz. Rendezés után ez egy szomszédos pár lesz; a nap-tartományt az indexekből kapod meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> m;

    vector<pair<long long, int>> pre(m + 1);
    pre[0] = {0, 0};
    long long cur = 0;
    for (int i = 1; i <= m; i++) {
        long long f, n;
        cin >> f >> n;
        cur += f - n;
        pre[i] = {cur, i};
    }

    sort(pre.begin(), pre.end());

    long long best = LLONG_MAX;
    int bl = 0, br = 0;
    for (int i = 0; i + 1 <= m; i++) {
        long long d = pre[i + 1].first - pre[i].first;
        if (d < best) {
            best = d;
            int a = pre[i].second, b = pre[i + 1].second;
            bl = min(a, b) + 1;
            br = max(a, b);
        }
    }

    cout << best << '\n' << bl << ' ' << br << '\n';
    return 0;
}
