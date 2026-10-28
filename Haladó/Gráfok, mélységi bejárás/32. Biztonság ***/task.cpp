/*
Megoldás lényege:
A kereszteződések és utcák hálózata egyirányba nem kötött, így az A-ból B-be vezető egyszerű utak a gráf kétszeresen összefüggő részein (blokkjain) haladnak keresztül. A blokkokat és a vágópontokat Hopcroft–Tarjan-féle mélységi bejárással, egy vertexveremmel határozzuk meg: amikor egy gyerek alacsony pontja (low) nem ér el a szülőjénél magasabbra, a veremből kivesszük a blokk pontjait. Ezekből blokk-vágópont fát építünk. Az A és B közötti fa-úton lévő blokkok minden pontja szerepelhet egyszerű A–B úton, a többi pont viszont nem, mert ahhoz egy vágópontot kétszer kellene érinteni. A megoldás a fa-úton lévő blokkok pontjainak uniója, az A és B pontok nélkül. Az időigény O(N + M), a mélységi bejárás iteratív.
*/
/*
Hint 1: || Ha egy kereszteződés elválaszt két részt a hálózatban, az A-ból B-be vezető egyszerű út csak egyszer haladhat át rajta. Ezért a hálózat az ilyen vágópontok mentén darabokra bomlik, és az út ezeknek a darabsorozatán megy keresztül. ||
Hint 2: || A blokkokat mélységi bejárás közben lehet megtalálni: a pontokat egy veremben tartod, és amikor egy gyerek alacsony pontja (low) nem ér el a szülőjénél magasabbra, a verem tetejéről kiveszed a gyerek alatti pontokat a blokkig. ||
Hint 3: || Építs blokk-vágópont fát: a blokkokat és a pontokat csúcsnak veszed, egy blokk csúcsát pedig összeköti minden pontja. Az A-ból B-be vezető fa-úton lévő blokkok pontjai adják a megoldást; az A-t és a B-t kihagyod. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, A, B;
    cin >> n >> m >> A >> B;
    vector<vector<pair<int, int>>> g(n + 1);  // (szomszéd, élazonosító)
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        if (u == v) continue;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }

    // Blokkok: Hopcroft–Tarjan, iteratív mélységi bejárás
    vector<int> disc(n + 1, 0), low(n + 1, 0), parEdge(n + 1, -1), it(n + 1, 0);
    vector<int> vst;                 // vertexverem
    vector<vector<int>> bct(n + 1);  // blokk-vágópont fa; a blokk-csúcsok n+1-től indulnak
    int timer = 0;
    vector<int> call{A};
    disc[A] = low[A] = ++timer;
    vst.push_back(A);
    while (!call.empty()) {
        int u = call.back();
        if (it[u] < (int)g[u].size()) {
            auto [w, id] = g[u][it[u]++];
            if (id == parEdge[u]) continue;
            if (!disc[w]) {
                disc[w] = low[w] = ++timer;
                parEdge[w] = id;
                vst.push_back(w);
                call.push_back(w);
            } else {
                low[u] = min(low[u], disc[w]);
            }
        } else {
            call.pop_back();
            if (call.empty()) break;
            int p = call.back();
            low[p] = min(low[p], low[u]);
            if (low[u] >= disc[p]) {
                int b = (int)bct.size();
                bct.push_back({});
                int x;
                do {
                    x = vst.back();
                    vst.pop_back();
                    bct[b].push_back(x);
                    bct[x].push_back(b);
                } while (x != u);
                bct[b].push_back(p);
                bct[p].push_back(b);
            }
        }
    }

    vector<char> onPath(n + 1, 0);
    if (A != B && disc[B]) {
        // BFS a blokk-vágópont fán A-ból, majd B-ből felfelé a blokkok pontjai
        int N = (int)bct.size();
        vector<int> par(N, -1);
        vector<char> seen(N, 0);
        queue<int> q;
        q.push(A);
        seen[A] = 1;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int y : bct[x])
                if (!seen[y]) {
                    seen[y] = 1;
                    par[y] = x;
                    q.push(y);
                }
        }
        for (int x = B; x != A; x = par[x])
            if (x > n)
                for (int y : bct[x]) onPath[y] = 1;
    }

    vector<int> ans;
    for (int v = 1; v <= n; ++v)
        if (onPath[v] && v != A && v != B) ans.push_back(v);

    cout << ans.size() << "\n";
    for (size_t i = 0; i < ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << "\n";
    return 0;
}
