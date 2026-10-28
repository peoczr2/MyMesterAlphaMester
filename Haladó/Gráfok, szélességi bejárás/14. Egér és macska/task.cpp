/*
Megoldás lényege:
Először a macska legrövidebb élszámát számoljuk ki A-ból szélességi bejárással, így tudjuk, hogy a macska legkorábban mikor ér egy pontba: IM · dc[v].
Az egér szintén szélességi bejárással halad B-ből; a k-adik lépés után az ideje k · IE.
Egy pontba csak akkor léphet be, ha az ideje szigorúan kisebb a macska legkorábbi érkezésénél, mert egyenlő időnél a macska már elkapja.
A szélességi bejárás miatt minden pontot a legkorábbi lehetséges érkezéssel ér el, ami a további lépésekhez is a legjobb, ezért ez a mohó bejárás helyes.
Az első elért egérlyukat (kimenő él nélküli pontot) a szülő-tömbből visszafejtve kapjuk meg az utat.
Az időigény O(N + M).
*/
/*
Hint 1: || Két szélességi bejárás kell: az egyik a macska, a másik az egér útját számolja; mindkettő élszámban dolgozik, az időt pedig az élszám és az élidő szorzata adja. ||
Hint 2: || Az egér egy pontba csak akkor léphet, ha a k-adik lépés után az ideje (k · IE) kisebb, mint a macska legkorábbi érkezése (IM · a macska élszáma). ||
Hint 3: || Egy szülő-tömbbel jegyezd fel, honnan értél el egy pontot, és az első elért egérlyuktól visszafelé haladva rakd össze az utat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int a, b, im, ie;
    cin >> a >> b >> im >> ie;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    const int INF = 1000000000;
    // A macska legrövidebb élszáma A-ból
    vector<int> dc(n + 1, INF);
    queue<int> q;
    dc[a] = 0;
    q.push(a);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dc[v] == INF) {
                dc[v] = dc[u] + 1;
                q.push(v);
            }
        }
    }

    // Az egér szélességi bejárása B-ből: csak olyan pontba léphet, ahová előbb ér, mint a macska
    vector<int> dm(n + 1, -1), par(n + 1, 0);
    dm[b] = 0;
    q.push(b);
    int hole = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (adj[u].empty()) {
            hole = u;
            break;
        }
        for (int v : adj[u]) {
            if (dm[v] != -1) continue;
            long long egerIdo = (long long)ie * (dm[u] + 1);
            long long macskaIdo = (long long)im * dc[v];
            if (egerIdo < macskaIdo) {
                dm[v] = dm[u] + 1;
                par[v] = u;
                q.push(v);
            }
        }
    }

    if (hole == 0) {
        cout << 0 << '\n';
        return 0;
    }

    vector<int> path;
    for (int v = hole;; v = par[v]) {
        path.push_back(v);
        if (v == b) break;
    }
    reverse(path.begin(), path.end());
    for (size_t i = 0; i < path.size(); ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << '\n';
    return 0;
}
