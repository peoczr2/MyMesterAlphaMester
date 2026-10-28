/*
Megoldás lényege:
Minden csúcshoz kiszámoljuk, hogy az S központból legkevesebb hány kritikus élen keresztül érhető el. A bemenet első K éle kritikus, a többi nem: így a kritikus él súlya 1, a többié 0, és a feladat egy 0-1 súlyú legrövidebb út feladat. Ezt 0-1 BFS-sel oldjuk meg egy kétvégű sorral: a 0 súlyú élt a sor elejére, az 1 súlyút a végére tesszük. A jó csúcsok azok, amelyek távolsága legfeljebb 1, így S (távolsága 0) is benne van. Az időigény O(N+M), a fő költség az élek beolvasása.
*/
/*
Hint 1: || Nem kell az összes utat végignézni: minden csúcsra elég tudni a legkevesebb kritikus élen átvezető út kritikus éleinek számát. ||
Hint 2: || Az élek súlya 0 vagy 1, ezért a távolságokat egy kétvégű sorral lehet gyorsan számolni: a 0 súlyú élnél a csúcs a sor elejére, az 1 súlyú élnél a végére kerül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, s;
    cin >> n >> m >> k >> s;
    vector<int> eu(m), ev(m);
    vector<int> start(n + 2, 0);
    for (int i = 0; i < m; ++i) {
        cin >> eu[i] >> ev[i];
        start[eu[i] + 1]++;
    }
    for (int v = 1; v <= n + 1; ++v) start[v] += start[v - 1];

    // Az élek CSR tárolásban: a kódolt érték = célcsúcs * 2 + (1, ha az él kritikus).
    vector<int> adj(m);
    vector<int> pos(start);
    for (int i = 0; i < m; ++i) adj[pos[eu[i]]++] = ev[i] * 2 + (i < k ? 1 : 0);

    const int INF = INT_MAX;
    vector<int> dist(n + 1, INF);
    deque<int> dq;
    dist[s] = 0;
    dq.push_back(s);
    while (!dq.empty()) {
        int v = dq.front();
        dq.pop_front();
        for (int i = start[v]; i < start[v + 1]; ++i) {
            int to = adj[i] / 2, w = adj[i] % 2;
            if (dist[v] + w < dist[to]) {
                dist[to] = dist[v] + w;
                if (w == 0)
                    dq.push_front(to);
                else
                    dq.push_back(to);
            }
        }
    }

    vector<int> ans;
    for (int v = 1; v <= n; ++v)
        if (dist[v] <= 1) ans.push_back(v);

    cout << ans.size() << "\n";
    for (size_t i = 0; i < ans.size(); ++i) cout << ans[i] << (i + 1 < ans.size() ? ' ' : '\n');
    if (ans.empty()) cout << "\n";
    return 0;
}
