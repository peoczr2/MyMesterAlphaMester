/*
Megoldás lényege:
Mélységi bejárást (DFS) végzünk a fővárosból, és minden csúcshoz feljegyezzük a bejárási sorszámát (tin)
és a low értékét, ami a részfából elérhető legkorábbi sorszám. Egy x csúcs (x nem főváros és nem kikötő)
akkor metszi el a fővárost a kikötőtől, ha a fa szerint a kikötőt tartalmazó gyerekágának low értéke nem
kisebb x sorszámánál, vagyis a részfából nincs visszaút a x fölé. Ilyen csúcsok a fővárostól a kikötőig
vezető fa-úton vannak, ezért elég végigmenni ezen az úton, a kikötőtől visszafelé. Az időigény O(N + M).
*/
/*
Hint 1: || Az a város, amelyen minden út átmegy, biztosan rajta van a fővárosból a kikötőbe vezető bármely úton. Elég egyetlen ilyen utat keresni. ||
Hint 2: || Mélységi bejárásból kapott fában a fővárostól a kikötőig vezető ágon kell végigmenni. Egy x csúcsra akkor lesz vége a kapcsolatnak, ha a kikötő felé vezető gyermeke nem tud x fölé visszalépni. ||
Hint 3: || Minden csúcsra számold ki a tin (belépési sorszám) és a low értéket: low az elérhető legkisebb tin a részfából, a visszaélekkel együtt. Ha low[gyerek] >= tin[x], akkor x elválasztja a részt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, f, k;
    cin >> n >> m >> f >> k;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // iteratív mélységi bejárás a fővárosból
    vector<int> tin(n + 1, -1), low(n + 1, 0), par(n + 1, 0), it(n + 1, 0);
    int timer = 0;
    vector<int> stk;
    stk.push_back(f);
    tin[f] = low[f] = timer++;
    while (!stk.empty()) {
        int u = stk.back();
        if (it[u] < (int)adj[u].size()) {
            int v = adj[u][it[u]++];
            if (tin[v] < 0) {
                par[v] = u;
                tin[v] = low[v] = timer++;
                stk.push_back(v);
            } else if (v != par[u]) {
                low[u] = min(low[u], tin[v]);
            }
        } else {
            stk.pop_back();
            if (par[u] != 0) low[par[u]] = min(low[par[u]], low[u]);
        }
    }

    // a fa-úton f -> k: az x csúcs, ha a gyereke (az úton lefelé) nem tud x fölé jutni
    int answer = -1;
    int child = k;
    for (int x = par[k]; x != f && x != 0; x = par[x]) {
        if (low[child] >= tin[x]) {
            answer = x;
            break;
        }
        child = x;
    }
    cout << answer << '\n';
    return 0;
}
