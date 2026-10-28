/*
Megoldás lényege:
A fizetős szakaszokat 1 súlyú, az ingyenes szakaszokat 0 súlyú éleknek tekintjük, így a feladat a V-ből W-be vezető legkisebb összsúlyú út megkeresése. Mivel a súlyok csak 0 és 1 lehetnek, nem kell Dijkstra: a deque-os szélességi bejárás elég, az ingyenes élet a sor elejére, a fizetőst a végére tesszük, így minden csúcs a helyes (legkisebb) költséggel kerül a sorba. Minden csúcsnál feljegyezzük, melyik csúcsból értük el a legkisebb költséggel, és W-ből ezeken az előzőkön visszafelé haladva kapjuk meg az utat V-től W-ig. Az időigény O(N + K), ami az N ≤ 95000, K ≤ 100000 bemenetre a 0,1 mp-es időlimitbe bőven belefér.
*/
/*
Hint 1: || Ha a fizetős szakaszokat 1-nek, az ingyenes szakaszokat 0-nak tekinted, akkor a kérdés egy legkisebb összsúlyú út keresése V-ből W-be. ||
Hint 2: || Mivel csak 0 és 1 súlyok vannak, nem kell Dijkstra: egy deque-os szélességi bejárás elég. A 0 súlyú élt a sor elejére, az 1 súlyút a végére tedd, és csak akkor frissíts távolságot, ha az jobb a korábbinál. ||
Hint 3: || Minden csúcsnál jegyezd fel, melyik csúcsból érted el a legkisebb költséggel. A W csúcstól ezeken az előzőkön visszafelé haladva kapod meg az utat, amit fordított sorrendben kell kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    // (szomszéd, súly): F = fizetős = 1, I = ingyenes = 0
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < k; i++) {
        int a, b;
        char t;
        cin >> a >> b >> t;
        int w = (t == 'F') ? 1 : 0;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }
    int v, w;
    cin >> v >> w;

    const int INF = INT_MAX;
    vector<int> dist(n + 1, INF), prev(n + 1, 0);
    deque<int> dq;
    dist[v] = 0;
    dq.push_back(v);
    while (!dq.empty()) {
        int x = dq.front();
        dq.pop_front();
        for (auto [y, c] : adj[x]) {
            if (dist[x] + c < dist[y]) {
                dist[y] = dist[x] + c;
                prev[y] = x;
                if (c == 0) dq.push_front(y);
                else dq.push_back(y);
            }
        }
    }

    vector<int> path;
    for (int x = w; x != v; x = prev[x]) path.push_back(x);
    path.push_back(v);
    reverse(path.begin(), path.end());

    cout << dist[w] << '\n';
    for (size_t i = 0; i < path.size(); i++) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << '\n';
    return 0;
}
