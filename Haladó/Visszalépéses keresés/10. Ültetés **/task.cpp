/*
Megoldás lényege: a vendégek és az ülőhelyek között bipartit párosítást keresünk: minden vendég
legfeljebb négy megadott ülőhely valamelyikét kaphatja meg, és egy ülőhelyet legfeljebb egy vendég
foglalhat el. Ezt folyamhálózattal oldjuk meg: a forrásból a vendégekbe, onnan az igényelt
ülőhelyekbe, végül a nyelőbe vezetünk éleket, mindegyik kapacitása 1. Ha a maximális folyam N,
minden vendég kapott ülőhelyet, és a telített vendég-ülőhely élek adják a kiosztást. Az időigény
N ≤ 20 és M ≤ 25 mellett elhanyagolható.
*/
/*
Hint 1: || Keress olyan kiosztást, amelyben minden vendég pontosan egy, az igényei közül való ülőhelyet kap, és egy ülőhelyet legfeljebb egy vendég foglal el. ||
Hint 2: || Építs hálózatot: forrás → vendég → igényelt ülőhely → nyelő, minden él kapacitása 1; ha a maximális folyam N, a telített vendég-ülőhely élek adják a kiosztást. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> igeny(n);
    for (int i = 0; i < n; ++i) {
        int x;
        while (cin >> x && x != 0) igeny[i].push_back(x - 1);
    }
    int S = 0, guest0 = 1, seat0 = 1 + n, T = 1 + n + m;
    Dinic din(T + 1);
    for (int i = 0; i < n; ++i) din.addEdge(S, guest0 + i, 1);
    for (int j = 0; j < m; ++j) din.addEdge(seat0 + j, T, 1);
    for (int i = 0; i < n; ++i) for (int s : igeny[i]) din.addEdge(guest0 + i, seat0 + s, 1);
    if (din.maxflow(S, T) != n) {
        cout << -1 << '\n';
        return 0;
    }
    vector<int> ans(n, -1);
    for (int i = 0; i < n; ++i) {
        for (auto &e : din.g[guest0 + i]) {
            if (e.to >= seat0 && e.to < seat0 + m && e.cap == 0) ans[i] = e.to - seat0 + 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}