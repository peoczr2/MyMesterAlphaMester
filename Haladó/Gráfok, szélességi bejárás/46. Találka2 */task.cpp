/*
Megoldás lényege:
Két szélességi bejárást végzünk: egyet Ádámtól (A városból), egyet Évától (E városból). Mindkettőnél megjegyezzük
minden város szülőjét, így az útvonal a célból visszafelé kiolvasható. Ha Ádám el tud jutni Éva városába, csak Ádám
utazik, és az útját "0 M" formában írjuk ki. Ha ez nem teljesül, de Éva el tud jutni Ádám városába, akkor fordítva
járunk el, "K 0" formában. Egyébként keresünk egy olyan várost, amelyet mindketten elérnek, és azt választjuk, ahol
a két távolság összege a legkisebb. Ha ilyen város nincs, a "00" választ írjuk ki. Az időigény O(N + M), mert
bejárásonként minden élt egyszer nézünk meg.
*/
/*
Hint 1: || Az élek iránya számít, ezért nem elég a két város összekötöttségét nézni: mindkettőjüknek külön meg kell határoznod, mely városokba jut el. Ehhez két szélességi bejárás kell, az egyik Ádámtól, a másik Évától indul. ||
Hint 2: || Először azt nézd meg, eljut-e Ádám Éva városába, majd fordítva. Ha egyik sem, keress olyan várost, amelyet mindketten elérnek. Az útvonalat a bejárás szülő-tömbjéből a célból kiindulva olvasd vissza, majd fordítsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Szélességi bejárás a forrásból: távolságok és szülők (az útvonal visszafejtéséhez)
void bfs(int s, const vector<vector<int>> &g, vector<int> &dist, vector<int> &par) {
    int n = (int)g.size() - 1;
    dist.assign(n + 1, -1);
    par.assign(n + 1, -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                par[v] = u;
                q.push(v);
            }
        }
    }
}

// Útvonal a bejárás forrásától a t városig (a forrás lesz az első elem)
vector<int> pathTo(int t, const vector<int> &par) {
    vector<int> p;
    for (int v = t; v != -1; v = par[v]) p.push_back(v);
    reverse(p.begin(), p.end());
    return p;
}

void printPath(const vector<int> &p) {
    for (size_t i = 0; i < p.size(); i++) {
        if (i) cout << ' ';
        cout << p[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, e, a, m;
    cin >> n >> e >> a >> m;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    vector<int> da, pa, de, pe;
    bfs(a, g, da, pa);  // Ádám bejárása
    bfs(e, g, de, pe);  // Éva bejárása

    if (da[e] != -1) {  // Ádám eljut Éva városába: csak Ádám utazik
        vector<int> p = pathTo(e, pa);
        cout << 0 << ' ' << p.size() << '\n';
        printPath(p);
        return 0;
    }
    if (de[a] != -1) {  // Éva eljut Ádám városába: csak Éva utazik
        vector<int> p = pathTo(a, pe);
        cout << p.size() << ' ' << 0 << '\n';
        printPath(p);
        return 0;
    }

    // Közös elérhető város: a két távolság összegét minimalizáljuk
    int best = -1;
    long long bestSum = LLONG_MAX;
    for (int x = 1; x <= n; x++) {
        if (da[x] == -1 || de[x] == -1) continue;
        long long s = (long long)da[x] + de[x];
        if (s < bestSum) {
            bestSum = s;
            best = x;
        }
    }
    if (best == -1) {
        cout << "00\n";
        return 0;
    }
    vector<int> evaPath = pathTo(best, pe);
    vector<int> adamPath = pathTo(best, pa);
    cout << evaPath.size() << ' ' << adamPath.size() << '\n';
    printPath(evaPath);
    printPath(adamPath);
    return 0;
}
