/*
Megoldás lényege:
Egy átvitelnél akkor kell protokollt váltani, ha az élvégpontok különböző részhálózatban vannak, különben nincs költség. Minden csúcshoz megjegyezzük a részhálózatát, így egy él költsége 0 vagy 1. A legkevesebb protokollváltást ezért a 0-1 szélességi bejárás adja: kétvégű sorban a 0 költségű élen elért csúcs a sor elejére, az 1 költségű élen elért a végére kerül, így a csúcsok a valódi távolságuk szerint jönnek sorra. Ugyanezzel a bejárással az útvonal is megkapható: a szülőmutatókon visszafelé lépve az A-ból B-be vezető utat kapjuk, és ez már optimális. Ha B nem érhető el A-ból, a válasz -1. Az időigény O(N+K).
*/
/*
Hint 1: || Minden átviteli csatornának költsége van: ha a két végpont ugyanahhoz a részhálózathoz tartozik, 0, különben 1. A feladat tehát a súlyozott legrövidebb út keresése, ahol a súlyok csak 0 és 1. ||
Hint 2: || Nem kell az általános Dijkstra-algoritmus: 0-1 szélességi bejárás is elég, ha kétvégű sort (deque) használsz. A 0 súlyú átmenetnél a csúcsot a sor elejére, az 1 súlyúnál a végére tedd. ||
Hint 3: || Minden csúcshoz tárold a legkevesebb protokollváltást és azt a csúcsot, ahonnan oda érkeztél. Ha B-t elérted, a szülőkön visszafelé lépve megkapod az útvonalat, amit a végén meg kell fordítani. Ha B nem érhető el, csak a -1 értéket írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Minden csomópont részhálózata (1..m).
    vector<int> net(n + 1, 0);
    for (int i = 1; i <= m; i++) {
        int x;
        while (cin >> x && x != 0) net[x] = i;
    }

    int k;
    cin >> k;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    int a, b;
    cin >> a >> b;

    const int INF = INT_MAX;
    vector<int> dist(n + 1, INF), par(n + 1, 0);
    deque<int> dq;
    dist[a] = 0;
    dq.push_back(a);
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        for (int v : g[u]) {
            int w = (net[u] == net[v]) ? 0 : 1;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                par[v] = u;
                if (w == 0) dq.push_front(v);
                else dq.push_back(v);
            }
        }
    }

    if (dist[b] == INF) {
        cout << -1 << '\n';
        return 0;
    }

    cout << dist[b] << '\n';

    vector<int> path;
    for (int v = b;; v = par[v]) {
        path.push_back(v);
        if (v == a) break;
    }
    reverse(path.begin(), path.end());
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i] << (i + 1 < path.size() ? ' ' : '\n');
    }
    return 0;
}
