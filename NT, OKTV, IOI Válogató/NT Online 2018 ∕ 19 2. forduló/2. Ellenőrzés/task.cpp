/*
Megoldás lényege:
Az értékek legfeljebb 100-félék (M legfeljebb 100), ezért minden b értékhez prefixösszeg
tömböt építünk: pref[b][i] az első i elemben lévő b-k számát adja. Egy a érték két
egymást követő előfordulása közötti szakasz b-darabszáma így egyetlen kivonással
megkapható. Minden (a, b) párra előre kiszámoljuk a szomszédos előfordulási
szakaszokon mért legnagyobb b-darabszámot, így a kérdésekre azonnal válaszolhatunk.
Ha egy a értéknek kevesebb mint két előfordulása van, a válasz -1.
*/
/*
Hint 1: || Egy a érték két szomszédos előfordulása között a b-k száma csak a köztük lévő elemektől függ. Ezért minden a értékre elég a szomszédos előfordulási párokat végignézni. ||
Hint 2: || Mivel M legfeljebb 100, minden b értékre készíthetsz prefixösszeg tömböt: pref[b][i] az első i elemben lévő b-k száma. Így az l és r pozíciók közötti szakasz b-darabszáma pref[b][r-1] - pref[b][l] alakban adódik. ||
Hint 3: || Az összes (a, b) párra előre számold ki a legnagyobb darabszámot: minden a értékhez végigmész az egymást követő előfordulási párokon, és minden b-re frissíted a maximumot. Ha egy a értéknek nincs két előfordulása, a hozzá tartozó válasz -1 marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> v(n + 1);
    for (int i = 1; i <= n; ++i) cin >> v[i];

    vector<vector<int>> pref(m + 1, vector<int>(n + 1, 0));
    for (int x = 1; x <= m; ++x) {
        for (int i = 1; i <= n; ++i) {
            pref[x][i] = pref[x][i - 1] + (v[i] == x);
        }
    }

    vector<vector<int>> pos(m + 1);
    for (int i = 1; i <= n; ++i) pos[v[i]].push_back(i);

    vector<vector<int>> ans(m + 1, vector<int>(m + 1, -1));
    for (int a = 1; a <= m; ++a) {
        if ((int)pos[a].size() < 2) continue;
        for (int idx = 0; idx + 1 < (int)pos[a].size(); ++idx) {
            int l = pos[a][idx];
            int r = pos[a][idx + 1];
            for (int b = 1; b <= m; ++b) {
                int cnt = pref[b][r - 1] - pref[b][l];
                ans[a][b] = max(ans[a][b], cnt);
            }
        }
    }

    while (k--) {
        int a, b;
        cin >> a >> b;
        cout << ans[a][b] << '\n';
    }
    return 0;
}
