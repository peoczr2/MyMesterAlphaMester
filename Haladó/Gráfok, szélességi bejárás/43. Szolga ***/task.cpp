/*
Megoldás lényege:
Több forrású szélességi bejárást végzünk: minden kiszolgálót egyszerre tesszük a sorba, így minden csomópont
legkisebb távolsága (az élek száma) a legközelebbi kiszolgálótól egyetlen bejárással kiderül. Egy csomópont
kérését a bejárásban őt először elérő szomszédjának (a szülőjének) továbbítjuk; ennek távolsága eggyel kisebb.
Az M a kiszolgálót elérő csomópontok közül a legnagyobb távolság. Az időigény O(N + E), ahol E a vonalak száma.
*/
/*
Hint 1: || Ne egyesével indíts bejárást a kiszolgálókból, hanem mindet egyszerre tedd a sorba: így egy bejárással megkapod minden csomópont legkisebb távolságát. ||
Hint 2: || Ha egy csomópont távolsága d, akkor a kérését olyan szomszédjának kell küldenie, amelynek távolsága d-1. Az M a legnagyobb d a kiszolgálót elérő csomópontok között. ||
Hint 3: || A bejárás közben jegyezd fel, melyik csomópontból értél el egy csúcsot először: az a szülő a d-1 távolságú szomszéd, ahová a kérést továbbítani kell. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> servers(k);
    for (int &s : servers) cin >> s;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        while (cin >> x && x != 0) adj[i].push_back(x);
    }

    // Többforrású szélességi bejárás: a kiszolgálók távolsága 0, a szülő a bejárásban továbbító csomópont
    vector<int> dist(n + 1, -1), par(n + 1, 0);
    queue<int> q;
    for (int s : servers) {
        if (dist[s] == -1) {
            dist[s] = 0;
            q.push(s);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                par[v] = u;
                q.push(v);
            }
        }
    }

    int M = 0;
    for (int i = 1; i <= n; i++) M = max(M, dist[i]);
    cout << M << '\n';

    for (int i = 1; i <= n; i++) {
        if (dist[i] == -1) {
            cout << "0 0\n";
        } else if (dist[i] == 0) {
            cout << "0 " << i << '\n';
        } else {
            cout << dist[i] << ' ' << par[i] << '\n';
        }
    }
    return 0;
}
