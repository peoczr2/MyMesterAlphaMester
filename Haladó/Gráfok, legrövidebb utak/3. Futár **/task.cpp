/*
Megoldás lényege:
A futárok a kezdő városból indulnak, és párhuzamosan mozoghatnak, így egy város akkor érhető el, amikor az odavezető legrövidebb úton a futár odaér. Az összes elérhető városba akkor jutnak el, amikor a legtávolabbi elérhető város is elérhető, tehát a válasz a kezdő városból mért legnagyobb legrövidebb út hossza az elérhető csúcsok között. A legrövidebb utakat Dijkstra-algoritmussal kapjuk, mert minden élsúly pozitív. Az időigény O((N + M) log M), a memóriaigény O(N + M).
*/
/*
Hint 1: || Gondold meg, hogy a futárok párhuzamosan mozoghatnak. Egy város akkor van elérve, amikor az első futár odaér, és az összes város akkor, amikor a legtávolabbi elérhető városba is odaér az a futár, aki a legrövidebb úton megy. ||
Hint 2: || A kezdő városból minden csúcs legrövidebb távolságát Dijkstra-algoritmussal határozd meg (prioritási sor), majd a válasz a legnagyobb véges távolság. Az élek irányítottak, és a számok nem negatívak. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, h;
    cin >> n >> m >> h;

    vector<int> head(n + 1, -1), nxt(m), to(m), w(m);
    for (int i = 0; i < m; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        to[i] = b;
        w[i] = t;
        nxt[i] = head[a];
        head[a] = i;
    }

    const int INF = INT_MAX;
    vector<int> dist(n + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    dist[h] = 0;
    pq.push({0, h});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (int i = head[u]; i != -1; i = nxt[i]) {
            int v = to[i];
            if (d + w[i] < dist[v]) {
                dist[v] = d + w[i];
                pq.push({dist[v], v});
            }
        }
    }

    int ans = 0;
    for (int v = 1; v <= n; v++)
        if (dist[v] != INF) ans = max(ans, dist[v]);

    cout << ans << '\n';
    return 0;
}
