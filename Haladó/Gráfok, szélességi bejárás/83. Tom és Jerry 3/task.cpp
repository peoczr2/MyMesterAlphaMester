/*
Megoldás lényege:
Ha a fa átmérője D legfeljebb 2K, van olyan (középső) szoba, ahonnan minden szoba K lépésen belül elérhető.
Tom ide tart K lépésenként, és ott állva Jerry bármely teleportálása után K lépésen belül elkapja.
Ha D > 2K, Tom csak az első K lépésben nyerhet: Jerry az első K lépésben normálisan menekül, és csak azokba a szobákba
ér el biztonságosan, ahol dJ(v) + 2 <= dS(v) (dS, dJ: a távolság Tom, illetve Jerry kezdőszobájától).
Ha ezek közül a Tom-tól legtávolabbi szoba távolsága legfeljebb K, Tom elkapja Jerry-t, különben Jerry megmenekül.
Ha Tom és Jerry már szomszédos, Tom az első lépésben nyer. A távolságokat BFS-sel számoljuk, így egy tesztesetre O(N) az idő.
*/
/*
Hint 1: || Először vizsgáld meg a ház átmérőjét: ha a két legtávolabbi szoba távolsága legfeljebb 2K, Tom mindig nyer. ||
Hint 2: || Két BFS-sel számold ki Tom és Jerry kezdő szobájától a távolságokat. Egy v szobába Jerry csak akkor ér „előbb”, ha az ő távolsága legalább 2-vel kisebb, mint Tomé. ||
Hint 3: || Ha Tom és Jerry szomszédos, az első lépésben elkapja. Egyébként keresd meg azokat a szobákat, ahova Jerry eljuthat, és nézd meg a Tom-tól legtávolabbit: ha ennek a távolsága legfeljebb K, Tom nyer. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> bfs(const vector<vector<int>> &adj, int src) {
    int n = (int)adj.size() - 1;
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[src] = 0;
    q.push(src);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] < 0) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, s, j, k;
        cin >> n >> s >> j >> k;

        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < n - 1; ++i) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        // Atmero: egy tetszoleges csucsbol a legtavolabbi csucs, majd onnan a legtavolabbi tavolsag.
        vector<int> d1 = bfs(adj, 1);
        int far = 1;
        for (int v = 1; v <= n; ++v) {
            if (d1[v] > d1[far]) far = v;
        }
        vector<int> d2 = bfs(adj, far);
        int diameter = 0;
        for (int v = 1; v <= n; ++v) {
            diameter = max(diameter, d2[v]);
        }

        bool tomWins;
        if (diameter <= 2 * k) {
            tomWins = true;
        } else {
            vector<int> dS = bfs(adj, s);
            vector<int> dJ = bfs(adj, j);
            if (dS[j] == 1) {
                tomWins = true;
            } else {
                int cap = 0;
                for (int v = 1; v <= n; ++v) {
                    if (dJ[v] + 2 <= dS[v]) {
                        cap = max(cap, dS[v]);
                    }
                }
                tomWins = (cap <= k);
            }
        }
        cout << (tomWins ? "IGEN" : "NEM") << '\n';
    }
    return 0;
}
