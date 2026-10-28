/*
Megoldás lényege:
A Q csúcs pontosan akkor válasz, ha K-ból elérhető, de Q-ból K nem érhető el. Ezért két bejárást végzünk K-ból: az elsőt az élek irányában (ez a K-ból elérhető csúcsok halmaza), a másodikat az élek fordított irányában (ez azon csúcsok halmaza, amelyekből K elérhető). A válasz az első halmaz azon csúcsai, amelyek nincsenek a másodikban. Mindkét bejárás O(N+M), a kimenet sorrendje a feladat szerint tetszőleges, itt növekvő sorrendet írunk.
*/
/*
Hint 1: || Két bejárás kell: egyszer az élek irányában, egyszer azok fordított irányában, mindkettőt K-ból indítva. Mindkettő egy-egy halmazt ad a csúcsokról. ||
Hint 2: || Q-ra akkor teljesül a feltétel, ha az első bejárásban megvan, de a fordított bejárásban nincs benne. Ez két halmaz különbsége. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> fwd(n + 1), bwd(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        fwd[u].push_back(v);
        bwd[v].push_back(u);
    }

    auto reach = [&](const vector<vector<int>> &g) {
        vector<char> seen(n + 1, 0);
        vector<int> st = {k};
        seen[k] = 1;
        while (!st.empty()) {
            int x = st.back();
            st.pop_back();
            for (int y : g[x])
                if (!seen[y]) {
                    seen[y] = 1;
                    st.push_back(y);
                }
        }
        return seen;
    };

    vector<char> fromK = reach(fwd);
    vector<char> toK = reach(bwd);

    vector<int> ans;
    for (int q = 1; q <= n; ++q)
        if (fromK[q] && !toK[q]) ans.push_back(q);

    cout << ans.size() << "\n";
    for (size_t i = 0; i < ans.size(); ++i) cout << ans[i] << (i + 1 < ans.size() ? ' ' : '\n');
    if (ans.empty()) cout << "\n";
    return 0;
}
