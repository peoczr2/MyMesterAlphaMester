/*
Megoldás lényege:
Ha p_i az i-edik látványos feladat helye az elvégzési sorrendben, a várakozási idők p_1, p_2-p_1, ..., p_K-p_{K-1},
összegük N, és a legnagyobb és a legkisebb közöttük legfeljebb 1. Így az értékek m = N/K (egész osztás) és m+1 közül
kerülnek ki, pontosan r = N mod K darab m+1 lesz. Az i-edik blokk az i-edik látványos feladat előtti nem látványos feladatokból és
magából a látványos feladatból áll, így a nem látványos feladatok blokkonként m-1, illetve m darabot kapnak.
Minden nem látványos feladatnak legkorábbi és legkésőbbi blokka van, amelyet az előírások és a látványos feladatok
határoznak meg; ezeket topologikus sorrendben, a gráf éleit bejárva javítjuk. A blokkok bővítéseinek helyét
(melyik r blokk kap plusz helyet) mohó módon választjuk: az intervallumokra vonatkozó feltételeket jobb végpont
szerint haladva elégítjük ki, a szakaszfával a legkisebb sérült kezdőindexet keressük, és a lehető legjobb helyre
teszünk bővítést. Ha így r-nél több kell, nincs megoldás. Végül a blokkokat határidő szerint (EDF, döntetlennél
topologikus sorrend) töltjük ki. Az időigény egy tesztesetre O((N + M) + K log K).
*/
/*
Hint 1: || Legyen p_i az i-edik látványos feladat helye. A várakozási idők p_1, p_2-p_1, ..., p_K-p_{K-1}, összegük N, és csak két érték lehet: m és m+1. Hány m+1 érték kell ilyenkor? ||
Hint 2: || Az i-edik blokk az i-edik látványos feladat előtti nem látványos feladatok és maga a látványos feladat. Minden nem látványos feladat csak egy blokkintervallumba kerülhet: legkorábban a rá vezető látványos feladatok után, legkésőbb az általa megelőzött látványos feladat előtt. Ezeket topologikus sorrendben, az éleken végigfutva számold ki. ||
Hint 3: || Ha egy blokk kapacitása már adott, az intervallumokra felírt feltétel: az intervallumba eső nem látványos feladatok száma legfeljebb az intervallum kapacitása. A bővítő blokkok helyét jobb végpont szerint haladva, a lehető legjobbra tegyük, és egy szakaszfával nyomon követhetjük, melyik intervallum sérül. ||
Hint 4: || Ha minden blokk kapacitása tudott, a nem látványos feladatokat blokkonként, határidő szerint (az EDF elv szerint) osszuk ki: a határidő a legkésőbbi megengedett blokk, egyenlőségnél a topologikus sorrend döntsön. Ha valamelyik határidő lejár, a sorrend nem létezik. ||
*/

#include <bits/stdc++.h>
using namespace std;

// Szakaszfa: intervallum-összeadás, és a legkisebb olyan index keresése, ahol az érték negatív.
struct SegTree {
    int n;
    vector<int> mn, lz;

    void init(int size) {
        n = size;
        mn.assign(4 * n + 4, 0);
        lz.assign(4 * n + 4, 0);
    }

    void add(int node, int l, int r, int ql, int qr, int v) {
        if (qr < l || r < ql) {
            return;
        }
        if (ql <= l && r <= qr) {
            mn[node] += v;
            lz[node] += v;
            return;
        }
        int mid = (l + r) / 2;
        add(2 * node, l, mid, ql, qr, v);
        add(2 * node + 1, mid + 1, r, ql, qr, v);
        mn[node] = min(mn[2 * node], mn[2 * node + 1]) + lz[node];
    }

    // acc: a felette lévő csomópontok lazy értékeinek összege
    int firstNegative(int node, int l, int r, int acc) const {
        if (mn[node] + acc >= 0) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int mid = (l + r) / 2;
        int inner = acc + lz[node];
        int res = firstNegative(2 * node, l, mid, inner);
        if (res != -1) {
            return res;
        }
        return firstNegative(2 * node + 1, mid + 1, r, inner);
    }
};

// Egy teszteset megoldása. Ha van érvényes sorrend, true, és out-ban a sorrend.
bool buildOrder(int n, int k, const vector<vector<int>>& pred, const vector<vector<int>>& succ,
                const vector<int>& vis, const vector<int>& visList, vector<int>& out) {
    // Topologikus sorrend; kör esetén nincs megoldás.
    vector<int> order;
    order.reserve(n);
    vector<int> deg(n + 1, 0);
    vector<int> stk;
    for (int v = 1; v <= n; ++v) {
        deg[v] = static_cast<int>(pred[v].size());
        if (deg[v] == 0) {
            stk.push_back(v);
        }
    }
    while (!stk.empty()) {
        int v = stk.back();
        stk.pop_back();
        order.push_back(v);
        for (int w : succ[v]) {
            if (--deg[w] == 0) {
                stk.push_back(w);
            }
        }
    }
    if (static_cast<int>(order.size()) != n) {
        return false;
    }
    vector<int> rnk(n + 1);
    for (int i = 0; i < n; ++i) {
        rnk[order[i]] = i;
    }

    // Legkorábbi (rel) és legkésőbbi (dl) blokk minden feladatra; látványos feladatnál rel = dl = sorszáma.
    vector<int> rel(n + 1, 1), dl(n + 1, k);
    for (int v : order) {
        if (vis[v]) {
            rel[v] = vis[v];
        }
        for (int u : pred[v]) {
            rel[v] = max(rel[v], rel[u] + (vis[u] ? 1 : 0));
        }
    }
    for (int idx = n - 1; idx >= 0; --idx) {
        int v = order[idx];
        if (vis[v]) {
            dl[v] = vis[v];
            continue;
        }
        for (int w : succ[v]) {
            dl[v] = min(dl[v], dl[w]);
        }
    }
    for (int v = 1; v <= n; ++v) {
        if (rel[v] > dl[v]) {
            return false;
        }
    }

    int m = n / k;
    int r = n % k;

    // Nem látványos feladatok csoportosítása: határidő szerint és kezdő blokk szerint.
    vector<vector<int>> relByDl(k + 1), nodesByRel(k + 2);
    for (int v = 1; v <= n; ++v) {
        if (!vis[v]) {
            relByDl[dl[v]].push_back(rel[v]);
            nodesByRel[rel[v]].push_back(v);
        }
    }

    // Mohó lefedés: e[i] = 1, ha az i-edik blokk m+1 hosszú (pontosan r ilyen lesz).
    SegTree st;
    st.init(k);
    vector<int> par(k + 1);
    for (int i = 0; i <= k; ++i) {
        par[i] = i;
    }
    auto findFree = [&](int x) {
        int root = x;
        while (root > 0 && par[root] != root) {
            root = par[root];
        }
        while (x > 0 && par[x] != x) {
            int nx = par[x];
            par[x] = root;
            x = nx;
        }
        return root;
    };

    vector<int> e(k + 1, 0);
    int cnt = 0;
    for (int b = 1; b <= k; ++b) {
        st.add(1, 1, k, 1, b, m - 1);
        for (int j : relByDl[b]) {
            st.add(1, 1, k, 1, j, -1);
        }
        while (true) {
            int a = st.firstNegative(1, 1, k, 0);
            if (a == -1) {
                break;
            }
            int p = findFree(b);
            if (p == 0 || p < a) {
                return false;
            }
            ++cnt;
            if (cnt > r) {
                return false;
            }
            e[p] = 1;
            par[p] = p - 1;
            st.add(1, 1, k, 1, p, 1);
        }
    }
    for (int p = k; p >= 1 && cnt < r; --p) {
        if (!e[p]) {
            e[p] = 1;
            ++cnt;
        }
    }

    // EDF: blokkonként m-1+e[i] nem látványos feladat, határidő, majd topologikus sorrend szerint.
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    out.clear();
    out.reserve(n);
    for (int i = 1; i <= k; ++i) {
        for (int v : nodesByRel[i]) {
            pq.emplace(dl[v], rnk[v], v);
        }
        int w = m - 1 + e[i];
        for (int t = 0; t < w; ++t) {
            if (pq.empty()) {
                return false;
            }
            auto top = pq.top();
            pq.pop();
            if (get<0>(top) < i) {
                return false;
            }
            out.push_back(get<2>(top));
        }
        if (!pq.empty() && get<0>(pq.top()) <= i) {
            return false;
        }
        out.push_back(visList[i]);
    }
    return pq.empty() && static_cast<int>(out.size()) == n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;
    while (tests--) {
        int n, k;
        cin >> n >> k;

        vector<vector<int>> pred(n + 1), succ(n + 1);
        for (int v = 1; v <= n; ++v) {
            int s;
            cin >> s;
            pred[v].resize(s);
            for (int j = 0; j < s; ++j) {
                cin >> pred[v][j];
                succ[pred[v][j]].push_back(v);
            }
        }

        vector<int> visList(k + 1, 0), vis(n + 1, 0);
        for (int i = 1; i <= k; ++i) {
            cin >> visList[i];
            vis[visList[i]] = i;
        }

        vector<int> out;
        if (buildOrder(n, k, pred, succ, vis, visList, out)) {
            for (int i = 0; i < n; ++i) {
                if (i > 0) {
                    cout << ' ';
                }
                cout << out[i];
            }
            cout << "\n";
        } else {
            cout << -1 << "\n";
        }
    }
    return 0;
}
