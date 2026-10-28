/*
Megoldás lényege:
A javítás akkor jó, ha a megfordított vonal után a gráfban nincs kör. Ezért a fordítandó vonalnak minden körben benne kell lennie, így csak az egyetlen nemtriviális erős komponensben (S) lehet. Ha több ilyen van, a válasz 0. S-en belül egy vonal akkor jó, ha S-ből elhagyva a gráf körmentes. Egy mélységi bejárás (DFS) S-ből, ha pontosan egy visszaélt talál, akkor az a visszaél jó vonal. Ha több visszaél van, a jó vonalak csak olyan faélek lehetnek, amelyek minden visszaél körében benne vannak; ezek egy függőleges szakaszt alkotnak, és egyenként ellenőrizzük őket topologikus rendezéssel. Ha találtunk egy jó e0 vonalat, akkor az S−e0 gráf topologikus sorrendjének valamelyik határán egy másik vonal akkor és csak akkor jó, ha ott egyedül ő megy át. A vágások számlálása különbségi tömbbel (és XOR-ral) O(N+M) időben megy.
*/
/*
Hint 1: || Egy vonal csak akkor jó, ha minden körben benne van. Ezért ha a gráfban két különálló, körös erős komponens van, a válasz 0; a körök egyetlen erős komponensben vannak. ||
Hint 2: || Egy mélységi bejárás során a visszaélek száma adja a döntő információt: ha pontosan egy visszaél van, az éppen a keresett vonal. Ha több van, a jó vonalak a fák azon éleiben vannak, amelyek minden visszaél körében szerepelnek. ||
Hint 3: || Egy e0 jó vonal eltávolítása után a maradék gráf topologikus rendezését megkapod (Kahn-algoritmus). A rendezés egy vágásában akkor jó a vonal, ha az a vágás egyetlen átmenő éle, ezt különbségi tömbbel, minden vágásra gyorsan megszámolhatod. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> eu, ev;
vector<vector<int>> g, rg;
vector<int> order_, comp;
vector<char> vis;

void dfs1(int u) {
    vis[u] = 1;
    for (int id : g[u]) {
        int w = ev[id];
        if (!vis[w]) {
            dfs1(w);
        }
    }
    order_.push_back(u);
}

void dfs2(int u, int c) {
    comp[u] = c;
    for (int id : rg[u]) {
        int w = eu[id];
        if (comp[w] == -1) {
            dfs2(w, c);
        }
    }
}

vector<int> Sverts, indS;
vector<vector<int>> sout;
int sCount;

// Kahn-algoritmus S-en az "ex" él nélkül; ha körmentes, a topologikus sorrendet adja vissza.
bool kahn(int ex, vector<int> &q) {
    vector<int> d = indS;
    d[ev[ex]]--;
    q.clear();
    for (int v : Sverts) {
        if (d[v] == 0) {
            q.push_back(v);
        }
    }
    for (size_t h = 0; h < q.size(); h++) {
        int u = q[h];
        for (int id : sout[u]) {
            if (id == ex) {
                continue;
            }
            int w = ev[id];
            if (--d[w] == 0) {
                q.push_back(w);
            }
        }
    }
    return (int)q.size() == sCount;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    eu.assign(m, 0);
    ev.assign(m, 0);
    g.assign(n + 1, {});
    rg.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        cin >> eu[i] >> ev[i];
        g[eu[i]].push_back(i);
        rg[ev[i]].push_back(i);
    }

    // 1. erős komponensek (Kosaraju)
    vis.assign(n + 1, 0);
    for (int u = 1; u <= n; u++) {
        if (!vis[u]) {
            dfs1(u);
        }
    }
    comp.assign(n + 1, -1);
    vector<int> csize;
    for (int i = (int)order_.size() - 1; i >= 0; i--) {
        int u = order_[i];
        if (comp[u] == -1) {
            int c = csize.size();
            csize.push_back(0);
            dfs2(u, c);
        }
    }
    for (int v = 1; v <= n; v++) {
        csize[comp[v]]++;
    }
    int nontrivial = 0, sc = -1;
    for (int c = 0; c < (int)csize.size(); c++) {
        if (csize[c] >= 2) {
            nontrivial++;
            sc = c;
        }
    }
    if (nontrivial != 1) {
        cout << 0 << "\n";
        return 0;
    }

    // 2. az S erős komponens élei
    vector<char> inS(n + 1, 0);
    for (int v = 1; v <= n; v++) {
        if (comp[v] == sc) {
            inS[v] = 1;
            Sverts.push_back(v);
        }
    }
    sCount = Sverts.size();
    sout.assign(n + 1, {});
    indS.assign(n + 1, 0);
    vector<int> ES;
    for (int i = 0; i < m; i++) {
        if (inS[eu[i]] && inS[ev[i]]) {
            ES.push_back(i);
            sout[eu[i]].push_back(i);
            indS[ev[i]]++;
        }
    }

    // 3. DFS S-ben: a visszaélek és a fabeli szülők
    int root = Sverts[0];
    vector<int> color(n + 1, 0), par(n + 1, 0), pedge(n + 1, -1), dep(n + 1, 0), it(n + 1, 0);
    vector<int> backs;
    vector<int> st;
    st.push_back(root);
    color[root] = 1;
    par[root] = root;
    while (!st.empty()) {
        int u = st.back();
        if (it[u] < (int)sout[u].size()) {
            int id = sout[u][it[u]++];
            int w = ev[id];
            if (color[w] == 0) {
                color[w] = 1;
                par[w] = u;
                pedge[w] = id;
                dep[w] = dep[u] + 1;
                st.push_back(w);
            } else if (color[w] == 1) {
                backs.push_back(id);
            }
        } else {
            color[u] = 2;
            st.pop_back();
        }
    }

    if (backs.empty()) {
        cout << 0 << "\n";
        return 0;
    }

    // 4. egy jó e0 vonal megkeresése
    vector<int> q;
    int e0 = -1;
    if (backs.size() == 1) {
        e0 = backs[0];
        kahn(e0, q);  // biztosan körmentes, a sorrend kell a vágásokhoz
    } else {
        // a jó vonalak fabeli élek, amelyek minden visszaél körében benne vannak
        int LOG = 1;
        while ((1 << LOG) <= n) {
            LOG++;
        }
        vector<vector<int>> up(LOG, vector<int>(n + 1));
        for (int v = 1; v <= n; v++) {
            up[0][v] = par[v];
        }
        for (int k = 1; k < LOG; k++) {
            for (int v = 1; v <= n; v++) {
                up[k][v] = up[k - 1][up[k - 1][v]];
            }
        }
        auto lca = [&](int a, int b) {
            if (dep[a] < dep[b]) {
                swap(a, b);
            }
            int diff = dep[a] - dep[b];
            for (int k = 0; k < LOG; k++) {
                if (diff >> k & 1) {
                    a = up[k][a];
                }
            }
            if (a == b) {
                return a;
            }
            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][a] != up[k][b]) {
                    a = up[k][a];
                    b = up[k][b];
                }
            }
            return up[0][a];
        };
        int L = eu[backs[0]];
        int D = 0;
        for (int id : backs) {
            L = lca(L, eu[id]);
            D = max(D, dep[ev[id]]);
        }
        vector<int> cand;
        for (int z = L; dep[z] > D; z = par[z]) {
            cand.push_back(pedge[z]);
        }
        for (int id : cand) {
            int p = eu[id], z = ev[id];
            if (sout[p].size() != 1 || indS[z] != 1) {
                continue;
            }
            if (kahn(id, q)) {
                e0 = id;
                break;
            }
        }
    }

    if (e0 == -1) {
        cout << 0 << "\n";
        return 0;
    }

    // 5. a többi jó vonal: a topologikus sorrend vágásaiban az egyetlen átmenő élek
    vector<int> pos(n + 1, -1);
    for (int i = 0; i < (int)q.size(); i++) {
        pos[q[i]] = i;
    }
    int s = q.size();
    vector<int> dCnt(s + 1, 0);
    vector<int> dX(s + 1, 0);
    for (int id : ES) {
        if (id == e0) {
            continue;
        }
        int pa = pos[eu[id]], pb = pos[ev[id]];
        dCnt[pa]++;
        dCnt[pb]--;
        dX[pa] ^= id;
        dX[pb] ^= id;
    }
    vector<char> good(m, 0);
    good[e0] = 1;
    int cnt = 0, x = 0;
    for (int i = 0; i + 1 < s; i++) {
        cnt += dCnt[i];
        x ^= dX[i];
        if (cnt == 1) {
            good[x] = 1;
        }
    }

    vector<int> res;
    for (int id : ES) {
        if (good[id]) {
            res.push_back(id);
        }
    }
    cout << res.size() << "\n";
    for (int id : res) {
        cout << eu[id] << " " << ev[id] << "\n";
    }
    return 0;
}
