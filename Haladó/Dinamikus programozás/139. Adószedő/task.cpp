/*
Megoldási ötlet:
A királyság úthálózata fa, és a beszedett adót vissza is kell vinni a fővárosba, ezért ha egy részfát meglátogatunk,
annak minden bejárt élét oda-vissza használjuk. A kérdés tehát az, hogy adott időből mely részfákba érdemes „befektetni”.

Legyen dp[u][t] az a maximális adó, amit az u csúcs részfájában be lehet szedni úgy, hogy u-ból indulunk és oda is térünk
vissza pontosan t idő alatt. A részfák DP-it fán lefelé kiszámoljuk, majd zsákszerűen összefésüljük a gyerekekkel.
*/
/*
Hint 1: || Ha egy él mentén elmész egy részfába, vissza is kell jönnöd, tehát az él költsége kétszer számít. ||
Hint 2: || A DP állapot legyen: melyik csúcs részfájában vagyunk, és mennyi időt használhatunk fel. ||
Hint 3: || A gyerekek részfáinak eredményeit klasszikus fa-zsák DP-vel lehet összekombinálni. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int to;
    int cost;
};

int n, limitTime;
vector<long long> tax;
vector<vector<Edge>> graph;
vector<vector<long long>> dp;

void dfs(int u, int parent) {
    dp[u][0] = tax[u];
    for (const Edge& edge : graph[u]) {
        int v = edge.to;
        if (v == parent) continue;
        dfs(v, u);
        vector<long long> next = dp[u];
        for (int used = 0; used <= limitTime; ++used) {
            if (dp[u][used] < 0) continue;
            for (int add = 0; used + add + 2 * edge.cost <= limitTime; ++add) {
                if (dp[v][add] < 0) continue;
                next[used + add + 2 * edge.cost] = max(next[used + add + 2 * edge.cost], dp[u][used] + dp[v][add]);
            }
        }
        dp[u].swap(next);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> limitTime;
    tax.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) cin >> tax[i];
    graph.assign(n + 1, {});
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    dp.assign(n + 1, vector<long long>(limitTime + 1, -1));
    dfs(1, 0);
    cout << *max_element(dp[1].begin(), dp[1].end()) << '\n';
    return 0;
}