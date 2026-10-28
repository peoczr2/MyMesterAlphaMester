/*
Megoldás lényege:
A településeket csúcsoknak, az utakat súlyozott éleknek tekintjük. Minden riasztáshoz a legközelebbi tűzoltóállomást kell megtalálni, ezt egyszerre, többforrású Dijkstra-algoritmussal érjük el: az összes állomás távolsága 0-val kezdődik a prioritási sorban, és minden csúcsnál eltároljuk az elődjét a legrövidebb úton. Így minden településhez megkapjuk a legközelebbi állomást és a hozzá vezető legrövidebb utat egy fa mentén. Egy riasztás útvonalát a riasztási helyből kiindulva az elődök követésével kapjuk, majd fordítva írjuk ki, az állomásnál megállva. Az időigény O((N + U) log N + K·N).
*/
/*
Hint 1: || Egy riasztáshoz a legközelebbi állomás kell, és ezt az összes állomásra egyszerre kaphatod meg: minden állomást kezdőpontként tekints, a távolságuk 0 legyen a prioritási sorban. ||
Hint 2: || A Dijkstra-algoritmus minden településnél tárolja az elődjét, vagyis azt a települést, ahonnan a legrövidebb úton érkezett. A riasztás helyéből az elődökön végigmenve az állomásig jutsz, az így kapott sorozatot fordítva írd ki. ||
Hint 3: || Az állomáson lévő riasztásnál az útvonal csak maga az állomás, ezért az elődök követését az állomás elérésekor állítsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, u, m, k;
    cin >> n >> u >> m >> k;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < u; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }

    vector<int> station(m);
    vector<char> isStation(n + 1, 0);
    for (int &s : station) {
        cin >> s;
        isStation[s] = 1;
    }

    vector<int> alarm(k);
    for (int &r : alarm) cin >> r;

    const long long INF = LLONG_MAX / 4;
    vector<long long> dist(n + 1, INF);
    vector<int> parent(n + 1, 0);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    for (int s : station) {
        dist[s] = 0;
        pq.push({0, s});
    }

    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (d != dist[v]) continue;
        for (auto [to, w] : adj[v]) {
            if (d + w < dist[to]) {
                dist[to] = d + w;
                parent[to] = v;
                pq.push({dist[to], to});
            }
        }
    }

    string out;
    for (int r : alarm) {
        vector<int> path;
        for (int v = r;; v = parent[v]) {
            path.push_back(v);
            if (isStation[v]) break;
        }
        reverse(path.begin(), path.end());
        for (size_t i = 0; i < path.size(); i++) {
            if (i) out += ' ';
            out += to_string(path[i]);
        }
        out += '\n';
    }
    cout << out;
    return 0;
}
