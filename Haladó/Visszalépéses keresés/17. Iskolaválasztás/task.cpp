/*
Megoldás lényege: minden tanulót pontosan egy, általa megjelölt iskolába kell felvenni, az iskolák
pedig legfeljebb a férőhelyeikig tölthetők. Ezt kapacitásos hozzárendelésnek tekintjük: a forrásból
minden tanulóhoz 1 kapacitású él megy, a tanulóktól a megjelölt iskoláikba szintén 1 kapacitású élek
vezetnek, az iskoláktól pedig a nyelőbe az iskola férőhelyeinek számával megegyező kapacitású él.
Akkor és csak akkor van jó beiskolázás, ha a maximális folyam értéke N. A Dinic-algoritmus ezt gyorsan
kiszámolja, a kis N és M miatt az időigény nem probléma.
*/
/*
Hint 1: || Egy tanuló csak a jelentkezési lapján megjelölt (legfeljebb két) iskola valamelyikébe kerülhet. ||
Hint 2: || Hálózatot építs: forrás, tanulók, iskolák, nyelő. A forrásból a tanulókba és a tanulóktól az iskolákba vezető élek kapacitása 1, az iskolából a nyelőbe vezető élé pedig az iskola férőhelyeinek száma. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> valasz(n);
    for (int i = 0; i < n; ++i) {
        cin >> valasz[i].first >> valasz[i].second;
    }
    vector<int> kap(m + 1);
    for (int i = 1; i <= m; ++i) cin >> kap[i];

    int S = 0, stu0 = 1, sch0 = 1 + n, T = 1 + n + m;
    Dinic din(T + 1);
    for (int i = 0; i < n; ++i) din.addEdge(S, stu0 + i, 1);
    for (int i = 1; i <= m; ++i) din.addEdge(sch0 + i - 1, T, kap[i]);
    for (int i = 0; i < n; ++i) {
        auto [a, b] = valasz[i];
        if (a) din.addEdge(stu0 + i, sch0 + a - 1, 1);
        if (b) din.addEdge(stu0 + i, sch0 + b - 1, 1);
    }
    if (din.maxflow(S, T) != n) {
        cout << -1 << '\n';
        return 0;
    }
    vector<int> ans(n, -1);
    for (int i = 0; i < n; ++i) {
        for (auto &e : din.g[stu0 + i]) {
            if (e.to >= sch0 && e.to < sch0 + m && e.cap == 0) ans[i] = e.to - sch0 + 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}