/*
Megoldás lényege:
Minden levélnek pontosan egyszer kell az útvonalak végpontjának lennie, mert a levélhez tartozó él csak így tisztítható meg,
ezért páratlan levélszám esetén a válasz -1. Egy élre az számít, hogy az egyik oldalán páratlan vagy páros sok levél van:
páratlan esetben az él pontosan egy útvonalon halad át, páros esetben legalább kettőn, és ez az alsó korlát mindig elérhető.
Így a válasz a fa éleinek száma kétszerese, mínusz azon élek száma, amelyek alatt páratlan a levelek száma.
A fát egy legalább kétfokú csúcsból gyökerezzük, ami sosem lesz levél, így a részfák levélparitása egyértelmű.
Egy variációban csak az új leveleket kapó csúcsok és felmenő útvonalaik változnak: ezeket virtuális fával (LCA-val) összegezzük,
így egy variáció O(D log N) időben megoldható.
*/
/*
Hint 1: || Egy levél éle csak akkor tisztítható meg, ha a levél útvonal végpontja, ezért minden levelet pontosan egyszer kell felhasználni. ||
Hint 2: || Gyökerezd a fát egy nem-levél csúcsban, és számold ki minden élre, hogy a gyerek-részfájában páros vagy páratlan sok levél van. ||
Hint 3: || Egy variációban csak az új leveleket kapó csúcsok felmenő útvonalainak paritása változik, ezeket virtuális fán érdemes összegezni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1, 0);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    // Gyökér: legalább kétfokú csúcs (ilyen van, mert N >= 3), így sosem lesz levél.
    int root = 1;
    for (int v = 1; v <= n; v++) {
        if (deg[v] >= 2) {
            root = v;
            break;
        }
    }

    // Preorder bejárás: szülők, mélység, belépési sorszám, részfa-méret.
    vector<int> par(n + 1, 0), dep(n + 1, 0), tin(n + 1, 0), sz(n + 1, 1), order;
    order.reserve(n);
    {
        vector<char> vis(n + 1, 0);
        vector<int> st;
        st.push_back(root);
        vis[root] = 1;
        par[root] = root;
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            tin[u] = (int)order.size();
            order.push_back(u);
            for (int w : adj[u]) {
                if (!vis[w]) {
                    vis[w] = 1;
                    par[w] = u;
                    dep[w] = dep[u] + 1;
                    st.push_back(w);
                }
            }
        }
    }
    for (int i = n - 1; i >= 1; i--) {
        int u = order[i];
        sz[par[u]] += sz[u];
    }

    const int LOG = 17;
    vector<vector<int>> up(LOG, vector<int>(n + 1));
    for (int v = 1; v <= n; v++) up[0][v] = par[v];
    for (int k = 1; k < LOG; k++)
        for (int v = 1; v <= n; v++) up[k][v] = up[k - 1][up[k - 1][v]];

    auto isAnc = [&](int a, int b) { return tin[a] <= tin[b] && tin[b] < tin[a] + sz[a]; };
    auto lca = [&](int a, int b) {
        if (isAnc(a, b)) return a;
        if (isAnc(b, a)) return b;
        for (int k = LOG - 1; k >= 0; k--)
            if (!isAnc(up[k][a], b)) a = up[k][a];
        return par[a];
    };

    // Levelek: fokszám 1 (a gyökér nem levél). P[v]: a v részfájában lévő levelek száma mod 2.
    vector<int> leaf(n + 1, 0);
    int L0 = 0;
    for (int v = 1; v <= n; v++)
        if (deg[v] == 1) {
            leaf[v] = 1;
            L0++;
        }
    vector<int> P(n + 1, 0);
    for (int v = 1; v <= n; v++) P[v] = leaf[v];
    for (int i = n - 1; i >= 1; i--) {
        int u = order[i];
        P[par[u]] ^= P[u];
    }

    // G[v]: a gyökértől v-ig tartó úton a g(x) = 1 - 2*P[x] értékek összege (g(gyökér) = 0).
    vector<long long> G(n + 1, 0);
    long long odd0 = 0;
    for (int i = 0; i < n; i++) {
        int u = order[i];
        if (u == root) {
            G[u] = 0;
            continue;
        }
        G[u] = G[par[u]] + (1 - 2 * P[u]);
        if (P[u]) odd0++;
    }

    vector<int> cntA(n + 1, 0), inW(n + 1, 0), vpar(n + 1, 0), cc(n + 1, 0);
    string out;
    while (q--) {
        int d;
        cin >> d;
        vector<int> a(d);
        for (auto &x : a) cin >> x;

        vector<int> distinctA;
        for (int x : a) {
            if (cntA[x] == 0) distinctA.push_back(x);
            cntA[x]++;
        }

        // Az érintett eredeti levelek már nem levelek; az új levelek száma D.
        long long F = 0;
        for (int x : distinctA)
            if (leaf[x]) F++;
        long long total = (long long)L0 - F + d;

        if (total % 2 == 1) {
            out += "-1\n";
        } else {
            // W: azok a csúcsok, ahonnan a páritás változása felfelé terjed.
            vector<int> W;
            for (int x : distinctA)
                if (x != root && ((cntA[x] + leaf[x]) & 1)) W.push_back(x);

            // sumG: az érintett csúcsokon a g értékek összege (a páritás-változás miatt).
            long long sumG = 0;
            if (!W.empty()) {
                for (int x : W) inW[x] = 1;
                vector<int> S = W;
                S.push_back(root);
                auto byTin = [&](int x, int y) { return tin[x] < tin[y]; };
                sort(S.begin(), S.end(), byTin);
                int m0 = (int)S.size();
                for (int i = 0; i + 1 < m0; i++) S.push_back(lca(S[i], S[i + 1]));
                sort(S.begin(), S.end(), byTin);
                S.erase(unique(S.begin(), S.end()), S.end());

                vector<int> st;
                for (int v : S) {
                    while (!st.empty() && !isAnc(st.back(), v)) st.pop_back();
                    vpar[v] = st.empty() ? 0 : st.back();
                    st.push_back(v);
                    cc[v] = inW[v];
                }
                for (int i = (int)S.size() - 1; i >= 0; i--) {
                    int v = S[i];
                    if (vpar[v]) cc[vpar[v]] += cc[v];
                }
                for (int v : S) {
                    if (v != root && (cc[v] & 1)) sumG += G[v] - G[vpar[v]];
                }
                for (int v : S) {
                    inW[v] = 0;
                    cc[v] = 0;
                    vpar[v] = 0;
                }
            }

            long long oddNow = odd0 + sumG;
            long long ans = 2LL * (n - 1) + d - oddNow;
            out += to_string(ans) + "\n";
        }

        for (int x : distinctA) cntA[x] = 0;
    }
    cout << out;
    return 0;
}
