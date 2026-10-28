/*
    A folyóhálózat egy fa, ezért a leghosszabb vizitúra a fa átmérője. Két DFS-sel
    megkeressük az egyik szélsőpontot, onnan pedig a másikat és a távolságot.
    Az időigény O(N), mert minden csúcsot és élt állandó számú alkalommal járunk be.
*/
/*
Hint 1: || A települések és a folyószakaszok fát alkotnak, így bármely két település között pontosan egy útvonal van. A leghosszabb vizitúra tehát két település közti legnagyobb távolság, vagyis a fa átmérője. ||

Hint 2: || Válassz egy tetszőleges kezdőcsúcsot, járd be a fát, és számold ki minden csúcsra a távolságot. A kezdőcsúcstól legtávolabbi csúcs mindig az átmérő egyik végpontja. ||

Hint 3: || Az így kapott csúcsból újabb bejárást indítva megkapod a másik végpontot és az átmérő hosszát; a két csúcs lesz a kért kezdő- és végpont. ||
*/
#include <bits/stdc++.h>
using namespace std;

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