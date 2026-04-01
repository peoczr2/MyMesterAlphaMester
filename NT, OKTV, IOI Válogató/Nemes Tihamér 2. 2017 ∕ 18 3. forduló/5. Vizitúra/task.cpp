#include <bits/stdc++.h>
using namespace std;

/*
    A folyóhálózat egy fa, ezért a leghosszabb vizitúra a fa átmérője. Két DFS-sel
    megkeressük az egyik szélsőpontot, onnan pedig a másikat és a távolságot.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<pair<int,int>>> g(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }

    auto dfs = [&](int start) {
        vector<long long> dist(n + 1, -1);
        stack<int> st;
        st.push(start);
        dist[start] = 0;
        while (!st.empty()) {
            int v = st.top();
            st.pop();
            for (auto [to, w] : g[v]) {
                if (dist[to] == -1) {
                    dist[to] = dist[v] + w;
                    st.push(to);
                }
            }
        }
        int best = start;
        for (int i = 1; i <= n; ++i) if (dist[i] > dist[best]) best = i;
        return pair<int, vector<long long>>(best, move(dist));
    };

    auto [a, d1] = dfs(1);
    auto [b, d2] = dfs(a);
    cout << d2[b] << '\n' << a << ' ' << b << '\n';
    return 0;
}