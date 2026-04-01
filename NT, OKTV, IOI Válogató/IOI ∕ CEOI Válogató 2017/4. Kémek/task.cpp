/*
Megoldás lényege:
Az eltávolított tag utáni csoportszám az ő komponensében keletkező szétesések száma.
Ez pontosan az artikulációs pontok klasszikus lowlink számításával adható meg.

Egy nem gyökér csúcsnál minden olyan gyermek-alfa komponens új csoportot alkot,
amelyre low[gyermek] >= tin[csúcs]. A gyökérnél a csoportszám egyszerűen a DFS-fa
gyerekszáma. A teljes gráfban a legnagyobb szétesést okozó csúcsot kell kiválasztani;
ha senki sem növeli a komponensek számát, 0-t írunk ki.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> tin(n + 1, 0), low(n + 1, 0), parent(n + 1, 0), it(n + 1, 0), score(n + 1, 0);
    int timer = 0;

    for (int start = 1; start <= n; ++start) {
        if (tin[start]) continue;

        vector<int> st;
        st.push_back(start);
        parent[start] = 0;

        int rootChildren = 0;
        while (!st.empty()) {
            int v = st.back();
            if (!tin[v]) {
                tin[v] = low[v] = ++timer;
            }

            if (it[v] == (int)g[v].size()) {
                st.pop_back();
                if (parent[v] != 0) {
                    int p = parent[v];
                    low[p] = min(low[p], low[v]);
                    if (low[v] >= tin[p]) {
                        ++score[p];
                    }
                }
                continue;
            }

            int to = g[v][it[v]++];
            if (to == parent[v]) continue;
            if (!tin[to]) {
                parent[to] = v;
                if (v == start) ++rootChildren;
                st.push_back(to);
            } else {
                low[v] = min(low[v], tin[to]);
            }
        }

        score[start] = rootChildren;
    }

    int best = 0;
    int bestScore = 0;
    for (int v = 1; v <= n; ++v) {
        int delta = (parent[v] == 0 ? score[v] - 1 : score[v]);
        if (delta > bestScore) {
            bestScore = delta;
            best = v;
        }
    }

    if (bestScore <= 0) cout << 0 << '\n';
    else cout << best << '\n';
    return 0;
}