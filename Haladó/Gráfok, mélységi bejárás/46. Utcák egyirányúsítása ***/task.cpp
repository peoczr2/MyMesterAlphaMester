/*
Megoldás lényege:
Egy utca akkor és csak akkor kell kétirányúnak maradnia, ha a törlésével a hálózat szétesne, vagyis ha a gráfnak híd. Minden hidat mindkét irányba kell járhatóvá tenni, és ennél kevesebb kétirányú utca nem elég, így a minimum a hidak száma. A többi utcát egy mélységi bejárás fája alapján irányítjuk: a fa-éleket a bejárás irányába (szülőtől a gyerek felé), a visszaéleket a leszármazottól az ős felé. Ez az irányítás minden híd nélküli részt erősen összefüggővé tesz, a hidak pedig mindkét irányba járhatók, így az egész hálózat erősen összefüggő lesz. A hidakat a tin (belépési sorszám) és a low (elérhető legkisebb tin) értékekkel találjuk meg. A bejárást veremmel valósítjuk meg, hogy a mélység ne okozzon veremtúlcsordulást. Az időigény O(N + M).
*/
/*
Hint 1: || Egy utca akkor kell mindkét irányba, ha a törlésével a hálózat szétesne, vagyis híd. A hidak száma adja a minimumot. ||
Hint 2: || A mélységi bejárás fájában minden él fa-él vagy visszaél. Irányítsd a fa-éleket a bejárás irányába, a visszaéleket a leszármazottól az ős felé. ||
Hint 3: || Számold a tin és low értékeket: az (u, gyerek) él híd, ha low[gyerek] > tin[u]. A bejárást ne rekurzióval, hanem veremmel írd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> eu(m), ev(m);
    vector<vector<pair<int, int>>> adj(n + 1);  // (szomszéd, élazonosító)
    for (int i = 0; i < m; i++) {
        cin >> eu[i] >> ev[i];
        adj[eu[i]].push_back({ev[i], i});
        adj[ev[i]].push_back({eu[i], i});
    }

    vector<int> tin(n + 1, -1), low(n + 1, 0), pedge(n + 1, -1), pvert(n + 1, 0), nxt(n + 1, 0);
    vector<int> from(m, 0), to(m, 0);
    vector<char> oriented(m, 0), bridge(m, 0);
    int timer = 0;

    // Iteratív mélységi bejárás az 1. pontból (a gráf összefüggő).
    vector<int> st;
    st.push_back(1);
    tin[1] = low[1] = timer++;
    while (!st.empty()) {
        int u = st.back();
        if (nxt[u] < (int)adj[u].size()) {
            auto [v, id] = adj[u][nxt[u]++];
            if (id == pedge[u]) continue;
            if (tin[v] == -1) {
                // fa-él: a bejárás irányába
                tin[v] = low[v] = timer++;
                pedge[v] = id;
                pvert[v] = u;
                from[id] = u;
                to[id] = v;
                oriented[id] = 1;
                st.push_back(v);
            } else if (!oriented[id]) {
                // visszaél: u egy leszármazott, v az őse, így u -> v
                from[id] = u;
                to[id] = v;
                oriented[id] = 1;
                low[u] = min(low[u], tin[v]);
            }
        } else {
            st.pop_back();
            if (pedge[u] != -1) {
                int p = pvert[u];
                low[p] = min(low[p], low[u]);
                if (low[u] > tin[p]) bridge[pedge[u]] = 1;
            }
        }
    }

    int K = 0;
    for (int i = 0; i < m; i++) K += bridge[i];

    cout << K << '\n';
    for (int i = 0; i < m; i++) {
        if (bridge[i]) {
            cout << eu[i] << ' ' << ev[i] << '\n';
            cout << ev[i] << ' ' << eu[i] << '\n';
        } else {
            cout << from[i] << ' ' << to[i] << '\n';
        }
    }
    return 0;
}
