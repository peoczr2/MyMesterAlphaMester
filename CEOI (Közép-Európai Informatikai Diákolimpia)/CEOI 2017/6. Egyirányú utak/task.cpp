/*
Megoldás lényege:
Egy nem híd él egy 2-élű-összefüggő komponens része, és az ilyen komponens erősen irányítható, ezért a nem híd éleket mindkét irányba lehet állítani (B). A hidak egy fát alkotnak, és az (x, y) követelmény szerint az x és y közötti fa-úton lévő minden hidat x felől y felé kell irányítani. A gráf DFS-fájában a hidakat megkeressük a low-értékekkel, majd minden útvonal által lefelé és felfelé használt élet különbségtömbbel és részfa-összegzéssel számoljuk; az LCA-t bináris felugrással kapjuk.
Ha egy hídon csak lefelé, vagy csak felfelé halad követelményű út, az irány kötelező (R vagy L); ha egyik sem, a híd szabadon irányítható (B).
Az időigény O((N + M + P) log N), a memória O(N log N).
*/
/*
Hint 1: || Egy él akkor kényszerül egy irányba, ha az elhagyása szétszakítaná a gráfot, vagyis híd. Keresd meg a hidakat egy DFS-bejárással a low-értékek segítségével; a párhuzamos éleket és a hurok-éleket figyelembe kell venni. ||
Hint 2: || A DFS-fában tekintsd az (x, y) követelményeket: a fa x–y útján lévő hidakat abban az irányban kell állítani, amerre az út halad. Egy x-ből felfelé és egy y felé lefelé haladó útvonal a közös ősig (LCA) egy-egy élét érinti. ||
Hint 3: || Az útvonalak számlálását tedd különbségtömbbe: x-ben +1, az LCA-ban -1 (felfelé), illetve y-ban +1, az LCA-ban -1 (lefelé), majd a gyerekektől a szülők felé összegezve megkapod, hány követelmény megy át az adott éleken. Az LCA-t 2^k-ados ősökkel számold ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> ea(m), eb(m);
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        cin >> ea[i] >> eb[i];
        adj[ea[i]].push_back({eb[i], i});
        adj[eb[i]].push_back({ea[i], i});
    }

    // Iteratív DFS: tin, low, szülő és a szülőél azonosítója (párhuzamos élek kezelése miatt élazonosítóval).
    vector<int> tin(n + 1, -1), low(n + 1, 0), par(n + 1, 0), parEdge(n + 1, -1), depth(n + 1, 0), it(n + 1, 0);
    vector<int> order;
    order.reserve(n);
    int timer = 0;
    vector<int> st;
    for (int s = 1; s <= n; s++) {
        if (tin[s] != -1) continue;
        tin[s] = low[s] = timer++;
        order.push_back(s);
        st.push_back(s);
        while (!st.empty()) {
            int v = st.back();
            if (it[v] < (int)adj[v].size()) {
                auto [to, id] = adj[v][it[v]++];
                if (id == parEdge[v]) continue;
                if (tin[to] == -1) {
                    tin[to] = low[to] = timer++;
                    par[to] = v;
                    parEdge[to] = id;
                    depth[to] = depth[v] + 1;
                    order.push_back(to);
                    st.push_back(to);
                } else {
                    low[v] = min(low[v], tin[to]);
                }
            } else {
                st.pop_back();
                if (par[v] != 0) low[par[v]] = min(low[par[v]], low[v]);
            }
        }
    }

    // Binárisan ugráló ősök az LCA-hoz.
    const int LOG = 17;
    vector<vector<int>> up(LOG, vector<int>(n + 1));
    for (int v = 1; v <= n; v++) up[0][v] = par[v] ? par[v] : v;
    for (int k = 1; k < LOG; k++)
        for (int v = 1; v <= n; v++) up[k][v] = up[k - 1][up[k - 1][v]];

    auto lca = [&](int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int d = depth[u] - depth[v];
        for (int k = 0; k < LOG; k++)
            if ((d >> k) & 1) u = up[k][u];
        if (u == v) return u;
        for (int k = LOG - 1; k >= 0; k--)
            if (up[k][u] != up[k][v]) {
                u = up[k][u];
                v = up[k][v];
            }
        return up[0][u];
    };

    // dU: felfelé (gyerek -> szülő) használat, dD: lefelé (szülő -> gyerek) használat.
    int p;
    cin >> p;
    vector<int> dU(n + 1, 0), dD(n + 1, 0);
    for (int i = 0; i < p; i++) {
        int x, y;
        cin >> x >> y;
        int l = lca(x, y);
        dU[x]++;
        dU[l]--;
        dD[y]++;
        dD[l]--;
    }
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int v = order[i];
        if (par[v] != 0) {
            dU[par[v]] += dU[v];
            dD[par[v]] += dD[v];
        }
    }

    string res(m, 'B');
    for (int v = 1; v <= n; v++) {
        if (par[v] == 0) continue;
        if (!(low[v] > tin[par[v]])) continue; // nem híd
        int e = parEdge[v];
        bool down = dD[v] > 0;  // szülő -> gyerek irány kötelező
        bool upward = dU[v] > 0; // gyerek -> szülő irány kötelező
        if (down && !upward) {
            res[e] = (ea[e] == par[v]) ? 'R' : 'L';
        } else if (upward && !down) {
            res[e] = (ea[e] == v) ? 'R' : 'L';
        }
    }

    cout << res << '\n';
    return 0;
}
