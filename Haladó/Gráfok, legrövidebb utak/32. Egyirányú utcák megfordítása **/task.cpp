/*
Megoldás lényege:
A kereszteződések gráfjában minden egyirányú utca egy él az irányával, és minden utca másik irányú bejárása egy utca megfordítását jelenti. A feladat két mennyiséget minimalizál, és először a megfordítások számát kell minimalizálnunk, utána az út hosszát. Ezt egyetlen egész költséggel kódoljuk: egy sima lépés költsége 1, egy megfordított utcán való lépésé BIG+1, ahol BIG = 10^6 nagyobb, mint bármely legrövidebb út hossza. Így az összköltség = megfordítások száma · BIG + út hossza, és a két lexikografikusan legjobb érték egyetlen számként minimalizálódik. A Dijkstra-algoritmust a B kereszteződésből futtatjuk a fordított éleken, így minden kereszteződésre ismert a B-be vezető legkisebb költség; ezután A-ból mindig olyan szomszédba lépünk, amelyre ez a költség pontosan csökken, tehát az így kapott út optimális. Legfeljebb 10^4 csúcson és 4·10^4 élen az idő O(E log V), ami a 0.2 mp-es korlátnál jóval kisebb.
*/
/*
Hint 1: || Ha az út egy utca ellenirányába halad, ezt az utcát meg kell fordítani; a feladat először a megfordítások számát, utána az út hosszát minimalizálja. ||
Hint 2: || Készíts irányított gráfot: minden utcához egy él az utca irányában, és egy él az ellenkező irányban, de az ellenirányú éle legyen lényegesen drágább. ||
Hint 3: || Egy megfordítás súlya legyen BIG+1, egy sima lépésé 1, ahol BIG = 10^6; a Dijkstra eredményét BIG-vel osztva kapod a megfordítások számát, a maradékból pedig az út hosszát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a, b;
    cin >> n >> m >> a >> b;
    string line;
    getline(cin, line);  // az első sor maradéka

    const int total = n * m;
    const long long BIG = 1000000;  // egy utca megfordítása: BIG + 1
    vector<vector<pair<int, long long>>> adj(total);
    for (int i = 0; i < total; i++) {
        line.clear();
        getline(cin, line);  // üres sor is lehet: ez a kereszteződés zsákutca
        int r = i / m, c = i % m;
        for (char ch : line) {
            int v = -1;
            if (ch == 'E' && r > 0) v = i - m;          // északi
            else if (ch == 'D' && r + 1 < n) v = i + m;  // déli
            else if (ch == 'K' && c + 1 < m) v = i + 1;  // keleti
            else if (ch == 'N' && c > 0) v = i - 1;      // nyugati
            if (v < 0) continue;
            adj[i].push_back({v, 1});        // az utca irányában: 1 lépés
            adj[v].push_back({i, BIG + 1});  // ellenirányban: utca megfordítása
        }
    }

    // Dijkstra a B csúcsból a fordított éleken: dB[x] = az x-ből B-be vezető legkisebb költség
    const long long INF = LLONG_MAX / 4;
    vector<vector<pair<int, long long>>> radj(total);
    for (int u = 0; u < total; u++)
        for (auto [v, w] : adj[u]) radj[v].push_back({u, w});
    int s = a - 1, t = b - 1;
    vector<long long> dB(total, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    dB[t] = 0;
    pq.push({0, t});
    while (!pq.empty()) {
        auto [dd, u] = pq.top();
        pq.pop();
        if (dd != dB[u]) continue;
        for (auto [v, w] : radj[u]) {
            if (dd + w < dB[v]) {
                dB[v] = dd + w;
                pq.push({dB[v], v});
            }
        }
    }

    // a kiindulásból mindig egy olyan szomszédba lépünk, amelyre a költség pontosan csökken
    // (irányok sorrendje: le, jobbra, fel, balra)
    const int dr[4] = {1, 0, -1, 0};
    const int dc[4] = {0, 1, 0, -1};
    vector<int> path;
    int cur = s;
    path.push_back(cur);
    while (cur != t) {
        int r = cur / m, c = cur % m;
        int nxt = -1;
        for (int k = 0; k < 4 && nxt < 0; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            int v = nr * m + nc;
            for (auto [y, w] : adj[cur])
                if (y == v && dB[v] + w == dB[cur]) {
                    nxt = v;
                    break;
                }
        }
        cur = nxt;
        path.push_back(cur);
    }

    cout << dB[s] / BIG << '\n';
    cout << dB[s] % BIG << '\n';
    for (size_t i = 0; i < path.size(); i++) {
        if (i) cout << ' ';
        cout << path[i] + 1;
    }
    cout << '\n';
    return 0;
}
