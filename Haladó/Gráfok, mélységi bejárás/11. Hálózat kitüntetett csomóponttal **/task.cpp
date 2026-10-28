/*
Megoldás lényege:
Egy X csúcs akkor felel meg, ha K-ból legfeljebb T közbülső csúcson át elérhető, és X-ből K elérhető. Az első feltétel T közbülső csúcs esetén legfeljebb T+1 élet jelent, ezért K-ból az élek irányában BFS-sel kiszámoljuk a K-tól mért élszámot (a legrövidebb út minimális közbülső csúcsszámot ad). A második feltételhez a fordított élek irányában egy másik BFS-t indítunk K-ból: az itt elért csúcsokból K elérhető. A válasz az a csúcsok halmaza, amelyek mindkét feltételt teljesítik, K-t kivéve; ezeket növekvő sorrendben írjuk ki. Mindkét bejárás O(N+M).
*/
/*
Hint 1: || Két külön feltétel van: egy távolságkorlát K-tól, és egy elérhetőség visszafelé. Mindkettőhöz egy-egy bejárás kell, és a kettő metszetét kell venned. ||
Hint 2: || T közbülső csúcs pontosan T+1 élnek felel meg. A K-ból induló BFS-ben tehát csak a legfeljebb T+1 élre lévő csúcsok jöhetnek szóba, a fordított élekkel bejárt csúcsok pedig a K-ba eljutók. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, t;
    cin >> n >> m >> k >> t;
    vector<vector<int>> fwd(n + 1), bwd(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        fwd[u].push_back(v);
        bwd[v].push_back(u);
    }

    // K-tól az élek irányában mért távolság (élek száma), -1 ha nem érhető el.
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[k] = 0;
    q.push(k);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int y : fwd[x])
            if (dist[y] < 0) {
                dist[y] = dist[x] + 1;
                q.push(y);
            }
    }

    // Azok a csúcsok, amelyekből K elérhető: K-ból a fordított élek mentén bejárva.
    vector<char> toK(n + 1, 0);
    toK[k] = 1;
    q.push(k);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int y : bwd[x])
            if (!toK[y]) {
                toK[y] = 1;
                q.push(y);
            }
    }

    vector<int> ans;
    for (int x = 1; x <= n; ++x)
        if (x != k && dist[x] >= 0 && dist[x] <= t + 1 && toK[x]) ans.push_back(x);

    cout << ans.size() << "\n";
    for (size_t i = 0; i < ans.size(); ++i) cout << ans[i] << (i + 1 < ans.size() ? ' ' : '\n');
    if (ans.empty()) cout << "\n";
    return 0;
}
