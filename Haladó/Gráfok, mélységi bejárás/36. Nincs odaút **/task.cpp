/*
Megoldás lényege:
Két csúcshalmazt számolunk ki P-ből indulva. Az első az élek irányában bejárt csúcsok halmaza: ezekbe van út P-ből. A második az élek megfordításával bejárt csúcsok halmaza: ezekből van út P-be. A keresett q pontok pontosan azok, amelyek a második halmazban benne vannak, de az elsőben nincsenek, vagyis q-ból van út P-be, P-ből viszont nincs út q-ba. Mindkét bejárás mélységi keresés O(N+M) időben. A kimenet második sorában a pontok sorrendje tetszőleges; itt növekvő sorrendben írjuk ki őket.
*/
/*
Hint 1: || Két bejárást kell végezni, mindkettőt P-ből indítva: egyszer az élek irányában, egyszer az élek megfordításával. ||
Hint 2: || Egy q pont akkor válasz, ha a megfordított élekkel bejárt csúcsok között benne van, az eredeti irányú bejárásban viszont nincs benne. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, p;
    cin >> n >> m >> p;
    vector<vector<int>> fwd(n + 1), bwd(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        fwd[u].push_back(v);
        bwd[v].push_back(u);
    }

    auto reach = [&](const vector<vector<int>> &g) {
        vector<char> seen(n + 1, 0);
        vector<int> st = {p};
        seen[p] = 1;
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

    vector<char> fromP = reach(fwd); // P-ből elérhető csúcsok
    vector<char> toP = reach(bwd);   // innen P is elérhető

    vector<int> ans;
    for (int q = 1; q <= n; ++q)
        if (toP[q] && !fromP[q]) ans.push_back(q);

    cout << ans.size() << "\n";
    for (size_t i = 0; i < ans.size(); ++i) cout << ans[i] << (i + 1 < ans.size() ? ' ' : '\n');
    if (ans.empty()) cout << "\n";
    return 0;
}
