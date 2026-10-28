/*
Megoldás lényege:
Szélességi bejárást végzünk a bejárati 0-s pontból, ami minden csúcsnál megadja a legrövidebb
távolságot. Minden csúcshoz eltároljuk, hány legrövidebb út vezet oda a bejárattól. Amikor egy
u csúcsot kiveszünk a sorból, minden olyan v szomszédjára, amelyre a távolság eggyel nő, a u-ig
vezető legrövidebb utak mind folytathatók v felé, ezért cnt[v] növekszik cnt[u]-val. A
számokat MOD 100 000 000 szerint tartjuk, és párhuzamos utakat külön útnak számolunk. A
szélességi bejárás miatt egy csúcs útszáma akkor már végleges, mire sorra kerül, így az
időigény O(N + M).
*/
/*
Hint 1: || A legrövidebb utakat szélességi bejárással kapjuk meg, és minden csúcsnál azt kell nyilvántartani, hány legrövidebb út vezet oda. ||
Hint 2: || Ha egy u csúcsból v-be vezet él, és v távolsága eggyel nagyobb u-énál, akkor u összes legrövidebb útja folytatható v felé, ezért az útszámokat össze kell adni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const long long MOD = 100000000LL;

    int N, M;
    cin >> N >> M;
    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> dist(N + 1, -1);
    vector<long long> cnt(N + 1, 0);
    queue<int> q;

    dist[0] = 0;
    cnt[0] = 1;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                cnt[v] = cnt[u];
                q.push(v);
            } else if (dist[v] == dist[u] + 1) {
                cnt[v] = (cnt[v] + cnt[u]) % MOD;
            }
        }
    }

    for (int i = 1; i <= N; ++i) cout << cnt[i] << '\n';
    return 0;
}
