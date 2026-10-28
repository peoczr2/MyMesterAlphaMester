/*
Megoldás lényege:
A járatokat irányított gráfnak tekintjük: az i-ből j-be induló járat a j városba viszi az utast.
Mindkét utas ugyanarra a találkahelyre (R) tart, ezért elég egyetlen szélességi bejárást végezni az R városból,
a járatok irányát megfordítva. Az R-ből elért minden városhoz eltároljuk, melyik városba kell továbblépni az R felé,
így Éva és Ádám útvonala a kiindulási városától kezdve ezt a "következő város" tömböt követve kiolvasható.
Ha valamelyik utas nem jut el R-be, a kimenet csak "0 0". A bejárás O(N + M), ez a 0,1 mp-es korláton belül van.
*/
/*
Hint 1: || Az átszállások száma a legrövidebb út éleinek száma, tehát szélességi bejárással számolható. ||
Hint 2: || A bejárást ne Éva és Ádám kiindulópontjából, hanem a közös R találkahelyből indítsd, a járatok irányát megfordítva. ||
Hint 3: || Az R-ből elért minden városhoz jegyezd fel, melyik város felé kell továbblépni; az útvonal a kiindulási városból ezt a sorozatot követve kiolvasható. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, e, a, r, m;
    cin >> n >> e >> a >> r >> m;

    // back[j]: azok az i városok, ahonnan van járat j-be
    vector<vector<int>> back(n + 1);
    for (int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to;
        back[to].push_back(from);
    }

    // Szélességi bejárás R-ből, a járatok irányát megfordítva
    vector<int> dist(n + 1, -1), nxt(n + 1, 0);
    queue<int> q;
    dist[r] = 0;
    q.push(r);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : back[v]) {
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                nxt[u] = v;
                q.push(u);
            }
        }
    }

    if (dist[e] == -1 || dist[a] == -1) {
        cout << "0 0\n";
        return 0;
    }

    auto route = [&](int start) {
        vector<int> path;
        for (int v = start;; v = nxt[v]) {
            path.push_back(v);
            if (v == r) break;
        }
        return path;
    };

    vector<int> pe = route(e), pa = route(a);
    cout << pe.size() << ' ' << pa.size() << '\n';
    for (int v : pe) cout << v << ' ';
    cout << '\n';
    for (int v : pa) cout << v << ' ';
    cout << '\n';
    return 0;
}
