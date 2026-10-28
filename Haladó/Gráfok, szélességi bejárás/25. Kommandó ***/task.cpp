/*
Megoldás lényege:
Az országokat csúcsoknak, a szomszédságot éleknek tekintjük. Az útvonalon trikócserére akkor van szükség, ha egy szomszédos országpár színe különbözik, hiszen mindig az aktuális ország színű trikót hordjuk. A kezdő ország trikója ingyen van, ezért az útvonal trikócseréinek száma a színváltások száma az útvonal mentén. Két szempont szerint kell optimalizálni: előbb a trikócserék száma, utána a legkevesebb ország legyen az útvonalban. Ezt a Dijkstra-algoritmussal oldjuk meg, ahol minden csúcsnál a (trikócsere, országok száma) párt tároljuk, és a párokat lexikografikusan hasonlítjuk össze. Az időigény O((N+M) log N), ami a korlátok mellett gyors.
*/
/*
Hint 1: || Két szomszédos országnál csak az számít, hogy a színük egyezik-e. Számold meg, hány olyan átmenet van az útvonalon, ahol a szín változik. ||
Hint 2: || Egy csúcsnál két értéket kell tudnod: az eddigi trikócserék számát és az érintett országok számát. Ezek párját kell minimalizálni, előbb az elsőt, majd a másodikat. ||
Hint 3: || Dijkstra-nál a prioritási sorba (csere, országok száma, ország) hármasokat tegyél, és minden országnál tárold az előző országot. A célból ezen láncon visszafelé haladva kapod meg az útvonalat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k;
        adj[i].resize(k);
        for (int& v : adj[i]) cin >> v;
    }

    vector<int> color(n + 1);
    for (int i = 1; i <= n; ++i) cin >> color[i];

    int s, t;
    cin >> s >> t;

    const pair<int, int> INF = {INT_MAX, INT_MAX};
    vector<pair<int, int>> best(n + 1, INF);  // (trikócsere, országok száma)
    vector<int> parent(n + 1, 0);

    using State = tuple<int, int, int>;  // (trikócsere, országok száma, ország)
    priority_queue<State, vector<State>, greater<State>> pq;
    best[s] = {0, 1};
    pq.push({0, 1, s});

    while (!pq.empty()) {
        auto [c, len, u] = pq.top();
        pq.pop();
        if (make_pair(c, len) != best[u]) continue;

        for (int v : adj[u]) {
            pair<int, int> cand = {c + (color[u] != color[v] ? 1 : 0), len + 1};
            if (cand < best[v]) {
                best[v] = cand;
                parent[v] = u;
                pq.push({cand.first, cand.second, v});
            }
        }
    }

    if (best[t] == INF) {
        cout << -1 << '\n';
        return 0;
    }

    vector<int> path;
    for (int x = t;; x = parent[x]) {
        path.push_back(x);
        if (x == s) break;
    }
    reverse(path.begin(), path.end());

    cout << best[t].first << ' ' << best[t].second << '\n';
    for (size_t i = 0; i < path.size(); ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << '\n';
    return 0;
}
