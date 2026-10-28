/*
Megoldás lényege:
Ádám és Éva lépéseit külön-külön szélességi bejárással számoljuk ki, mindkettőjüknél figyelembe véve a saját tiltott városaikat:
a tiltott városba nem lépnek be, de a többi városon át haladhatnak. Egy v városban akkor találkozhatnak, ha mindketten el tudnak oda jutni,
és az összes lépésszám a két távolság összege. A legkisebb összegű v városot keressük, döntetlen esetén a kisebb sorszámút,
ezt a növekvő sorszám szerinti bejárás magától megadja. Ha nincs ilyen város, a válasz 0.
Az időigény O(N + M) két bejárással, ami a 100 000 élnél is gyors.
*/
/*
Hint 1: || Két független szélességi bejárás kell: egyet Ádámtól és egyet Évától, mindkettőnél a saját tiltott városokat kihagyva. ||
Hint 2: || Egy v városra a két távolság összege adja az együttes lépésszámot; csak azokat a városokat vedd figyelembe, ahová mindketten eljutnak, és döntetlennél a kisebb sorszám kell. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> bfs(int n, const vector<vector<int>> &adj, int s, const vector<char> &forbidden) {
    vector<int> d(n + 1, -1);
    queue<int> q;
    d[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int w : adj[v]) {
            if (d[w] != -1 || forbidden[w]) continue;
            d[w] = d[v] + 1;
            q.push(w);
        }
    }
    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, a, e;
    cin >> n >> m >> a >> e;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<char> fa(n + 1, 0), fe(n + 1, 0);
    int ta;
    cin >> ta;
    for (int i = 0; i < ta; i++) {
        int x;
        cin >> x;
        fa[x] = 1;
    }
    int te;
    cin >> te;
    for (int i = 0; i < te; i++) {
        int x;
        cin >> x;
        fe[x] = 1;
    }

    vector<int> da = bfs(n, adj, a, fa);
    vector<int> de = bfs(n, adj, e, fe);

    int ans = 0;
    long long best = LLONG_MAX;
    for (int v = 1; v <= n; v++) {
        if (da[v] < 0 || de[v] < 0) continue;
        long long s = (long long)da[v] + de[v];
        if (s < best) {
            best = s;
            ans = v;
        }
    }
    cout << ans << '\n';
    return 0;
}
