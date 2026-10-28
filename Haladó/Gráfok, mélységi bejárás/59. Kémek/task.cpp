/*
Megoldás lényege:
Az a tag, akinek letartóztatása a legtöbb csoportra bontja a hálózatot, a gráf artikulációs pontja: ha őt töröljük, a komponensek száma nő. Mélységi bejárással (DFS) minden csúcshoz kiszámoljuk a felfedezési idejét (disc) és a low értékét, ami a részfájából visszamutató élek közül a legkisebb felfedezési idő. Egy v csúcs gyerekei közül azok szakadnak le külön csoportra, amelyekre low[gyerek] >= disc[v]; a gyökérnél minden DFS-gyerek külön csoport, másutt a szülő felé eső rész is egy csoport. Ha a gráf nem összefüggő, a többi komponens számát is hozzáadjuk. A legtöbb csoportra bontó csúcs sorszámát írjuk ki (egyenlőség esetén a legkisebbet), ha legalább 2 csoport keletkezik, különben 0. Az időigény O(N+M).
*/
/*
Hint 1: || Keresd azt a csúcsot, amelynek törlése után a gráf legtöbb részre esik szét. Ezek a gráf artikulációs pontjai, és a csoportok számát a törölt csúcs nélküli gráfban kell megszámolni. ||
Hint 2: || Mélységi bejárással minden csúcsra számold ki a felfedezési idejét (disc) és a low értékét, ami a részfából visszamutató élek legkisebb felfedezési ideje. ||
Hint 3: || Egy v csúcsnál a gyerek c külön részre szakad le, ha low[c] >= disc[v]. A gyökérnél minden DFS-gyerek külön rész, másutt pedig a szülő felé eső rész is egy további csoport. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> disc, low_, within;
int timer_ = 0;

// p = 0 jelöli a DFS gyökerét
void dfs(int v, int p) {
    disc[v] = low_[v] = ++timer_;
    int children = 0, separated = 0;
    for (int u : adj[v]) {
        if (!disc[u]) {
            dfs(u, v);
            low_[v] = min(low_[v], low_[u]);
            children++;
            if (low_[u] >= disc[v]) separated++;
        } else {
            low_[v] = min(low_[v], disc[u]);
        }
    }
    if (p == 0) within[v] = children;
    else within[v] = separated + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    adj.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    disc.assign(n + 1, 0);
    low_.assign(n + 1, 0);
    within.assign(n + 1, 0);
    int roots = 0;
    for (int v = 1; v <= n; v++) {
        if (!disc[v]) {
            roots++;
            dfs(v, 0);
        }
    }

    // v törlése után a csoportok száma: a többi komponens + a v komponensében keletkező részek
    int best = -1, ans = 0;
    for (int v = 1; v <= n; v++) {
        int groups = roots - 1 + within[v];
        if (groups > best) {
            best = groups;
            ans = v;
        }
    }
    cout << (best >= 2 ? ans : 0) << '\n';
    return 0;
}
