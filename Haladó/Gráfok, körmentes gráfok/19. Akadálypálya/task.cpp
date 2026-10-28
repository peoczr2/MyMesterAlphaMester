/*
Megoldás lényege:
A start az egyetlen forrás, a cél az egyetlen nyelő, mindkettő a fokszámokból adódik. Két ellenőrző pont akkor jó, ha minden
start-cél útvonalon szerepel legalább az egyik, vagyis a start és a cél közötti legkisebb csúcsvágás mérete legfeljebb kettő.
Ezt maximális folyammal határozzuk meg: minden csúcsot két részre bontunk (be és ki), a köztük lévő él kapacitása 1, az
útszakaszoké nagy. Ha a folyam eléri a 3-at, nincs megfelelő pár, és a válasz 0 0. Különben az utolsó sikertelen keresés
után az elérhető csúcsok határán lévő telített belső élek adják a vágópontokat, topologikus sorrendben kiírva. Mivel
legfeljebb három kiegészítő utat keresünk, az időigény O(N + M).
*/
/*
Hint 1: || Két pont akkor jó, ha minden start-cél útvonalon szerepel legalább az egyik, azaz a start és a cél között el kell vágniuk az összes utat. Keresd a legkisebb ilyen vágást. ||
Hint 2: || Bontsd minden csúcsot két részre (be és ki) egy 1-es kapacitású éllel, az útszakaszokat pedig nagy kapacitású élekkel köss össze; így a legkisebb vágás mérete megegyezik a maximális folyammal. ||
Hint 3: || Legfeljebb három kiegészítő utat keress: ha a folyam eléri a 3-at, nincs megoldás (0 0). Különben az utolsó sikertelen keresésből elérhető csúcsok határán lévő belső élek adják a két pontot. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    vector<vector<int>> out(n + 1);
    vector<int> indeg(n + 1, 0), outdeg(n + 1, 0);
    for (auto &[u, v] : edges) {
        cin >> u >> v;
        out[u].push_back(v);
        ++outdeg[u];
        ++indeg[v];
    }

    // a start egyetlen forrás, a cél egyetlen nyelő
    int s = 1, t = 1;
    for (int v = 1; v <= n; ++v) {
        if (indeg[v] == 0) s = v;
        if (outdeg[v] == 0) t = v;
    }
    // közvetlen start-cél él esetén nincs olyan vágás, amely elvágná
    for (int w : out[s])
        if (w == t) {
            cout << "0 0\n";
            return 0;
        }

    // topologikus sorrend (Kahn): a vágópontokat ebben a sorrendben írjuk ki
    vector<int> order, deg = indeg;
    queue<int> q;
    for (int v = 1; v <= n; ++v)
        if (deg[v] == 0)
            q.push(v);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        order.push_back(v);
        for (int w : out[v])
            if (--deg[w] == 0)
                q.push(w);
    }
    vector<int> pos(n + 1, 0);
    for (int i = 0; i < (int)order.size(); ++i)
        pos[order[i]] = i;

    // hálózat: a v csúcs bemenete 2v, kimenete 2v+1
    const int INF = 1000000;
    const int V = 2 * (n + 1);
    vector<int> head(V, -1), nxt, to, cap;
    auto addArc = [&](int a, int b, int c) {
        to.push_back(b);
        cap.push_back(c);
        nxt.push_back(head[a]);
        head[a] = (int)to.size() - 1;
        to.push_back(a);
        cap.push_back(0);
        nxt.push_back(head[b]);
        head[b] = (int)to.size() - 1;
    };
    for (int v = 1; v <= n; ++v)
        addArc(2 * v, 2 * v + 1, 1);
    for (auto [u, v] : edges)
        addArc(2 * u + 1, 2 * v, INF);

    const int S = 2 * s + 1, T = 2 * t;
    int flow = 0;
    vector<char> vis;
    while (true) {
        vector<int> pe(V, -1);
        vis.assign(V, 0);
        queue<int> bq;
        bq.push(S);
        vis[S] = 1;
        while (!bq.empty() && !vis[T]) {
            int x = bq.front();
            bq.pop();
            for (int e = head[x]; e != -1; e = nxt[e])
                if (cap[e] > 0 && !vis[to[e]]) {
                    vis[to[e]] = 1;
                    pe[to[e]] = e;
                    bq.push(to[e]);
                }
        }
        if (!vis[T])
            break;
        int b = INF;
        for (int x = T; x != S; x = to[pe[x] ^ 1])
            b = min(b, cap[pe[x]]);
        for (int x = T; x != S; x = to[pe[x] ^ 1]) {
            cap[pe[x]] -= b;
            cap[pe[x] ^ 1] += b;
        }
        flow += b;
        if (flow >= 3) {
            cout << "0 0\n";
            return 0;
        }
    }

    // a vágás: a telített belső élek, amelyek elérhető bemenetből nem elérhető kimenetbe mutatnak
    vector<int> cut;
    for (int v = 1; v <= n; ++v)
        if (vis[2 * v] && !vis[2 * v + 1])
            cut.push_back(v);
    sort(cut.begin(), cut.end(), [&](int a, int b) { return pos[a] < pos[b]; });

    if (cut.size() == 1)
        cout << cut[0] << " " << cut[0] << "\n";
    else if (cut.size() == 2)
        cout << cut[0] << " " << cut[1] << "\n";
    else
        cout << "0 0\n";
    return 0;
}
