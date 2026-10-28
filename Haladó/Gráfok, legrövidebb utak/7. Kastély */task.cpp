/*
Megoldás lényege:
A termek rácsot alkotnak. Az oldalszomszédos termek között normál átjáró van, ezért ott nincs extra költség. Az átlósan
szomszédos termeket a négyzet alakú rejtekajtó köti össze, és ezen átmenni R forintba kerül. Egy terembe való belépés
költsége a terem értéke, a kiindulási teremért nem kell fizetni. Így a termek csúcsok, az élek költsége pedig a belépett
terem értéke (átlós élnél plusz R), és a legkisebb költségű utat Dijkstra algoritmussal keressük. A rács legfeljebb
500·500 csúcsból áll, így a futás O(N·M·log(N·M)).
*/
/*
Hint 1: || Tekintsd a termeket csúcsoknak. Egy lépés költsége a belépett terem értéke, és ha a lépés átlós (rejtekajtón át), még R forint hozzájön. ||
Hint 2: || A kiindulási teremért nem kell fizetni, így annak távolsága 0. Pozitív élsúlyok mellett a legkisebb költség Dijkstra-algoritmussal kiszámítható. ||
*/

#include <bits/stdc++.h>

using namespace std;

// A számok közé a mintafájlokban néha nem szóköz (0xA0) kerül, ezért minden nem számjegy elválasztónak számít.
long long readNumber() {
    int c = cin.get();
    while (c != EOF && (c < '0' || c > '9')) c = cin.get();
    long long x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = cin.get();
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = (int)readNumber();
    int m = (int)readNumber();
    long long r = readNumber();

    int sr = (int)readNumber(), sc = (int)readNumber();
    int tr = (int)readNumber(), tc = (int)readNumber();

    vector<int> cost(n * m);
    for (int i = 0; i < n * m; ++i) {
        cost[i] = (int)readNumber();
    }

    const int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    const int start = (sr - 1) * m + (sc - 1);
    const int target = (tr - 1) * m + (tc - 1);

    vector<long long> dist(n * m, LLONG_MAX);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        if (u == target) break;

        int ur = u / m, uc = u % m;
        for (int k = 0; k < 8; ++k) {
            int nr = ur + dr[k], nc = uc + dc[k];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;

            bool diagonal = dr[k] != 0 && dc[k] != 0;
            int v = nr * m + nc;
            long long nd = d + cost[v] + (diagonal ? r : 0);
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push({nd, v});
            }
        }
    }

    cout << dist[target] << '\n';
    return 0;
}
