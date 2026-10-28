/*
Megoldás lényege:
Minden pontnak egyetlen legközelebbi szomszédja van, ezért a bolhák mozgása egy f(v) mutatókkal leírt funkcionális gráfon történik.
A gráfban körök vannak (különböző távolságok miatt ezek kölcsönösen legközelebbi párok), a többi pont fákba csatlakozik a körökhöz.
A fákban a bolhák mindig a gyökér felé haladnak, így egy pontban egy időpillanatban azok vannak, akik pontosan annyi lépésre vannak tőle,
amennyi az idő; ezeket a részfák mélységi összegeivel számoljuk. A hosszú-út felbontással (a legmélyebb gyereken örökített tömb) ez
lineáris időben megy, és minden változásnál frissítjük a maximumot.
A körön a bolhák a kör hossza szerinti maradékosztályokba rendeződnek és egyenként oszcillálnak, így a legnagyobb osztályösszeg adja a kör legjobb értékét.
Az összidő O(N + M), a kimenet a legnagyobb egyszerre lehetséges bolhaszám.
*/
/*
Hint 1: || Minden pontnak egy legközelebbi szomszédja van, így minden bolha egyértelműen ugrik. Vizsgáld meg, mi történik a körökben és a körök fölötti fákban. ||
Hint 2: || A fában a bolhák mindig a gyökér felé haladnak egy szinttel minden lépésben, így egy pontban egy időpillanatban azok vannak, akik pontosan annyi lépésre vannak tőle, amennyi az idő. ||
Hint 3: || A fa mélységi összegeit a legmélyebb gyermeken örökített tömbbel tartsd nyilván (hosszú-út felbontás), a körön pedig a bolhákat (pozíció mínusz idő) mod kör-hossz szerint csoportosítsd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<long long> B(n);
    for (auto &x : B) cin >> x;

    // legkozelebbi szomszed (nb[v] = -1, ha a pontnak nincs szomszedja)
    vector<int> nb(n, -1);
    vector<long long> bestD(n, LLONG_MAX);
    for (int j = 0; j < m; j++) {
        int x, y;
        long long t;
        cin >> x >> y >> t;
        x--; y--;
        if (t < bestD[x]) { bestD[x] = t; nb[x] = y; }
        if (t < bestD[y]) { bestD[y] = t; nb[y] = x; }
    }

    // korok keresese a funkcionalis grafban
    vector<int> state(n, 0), onCycle(n, -1);
    vector<vector<int>> cycles;
    for (int s = 0; s < n; s++) {
        if (nb[s] == -1 || state[s] != 0) continue;
        vector<int> path;
        int v = s;
        while (state[v] == 0) {
            state[v] = 1;
            path.push_back(v);
            v = nb[v];
        }
        if (state[v] == 1) {
            vector<int> cyc;
            int w = v;
            do {
                cyc.push_back(w);
                w = nb[w];
            } while (w != v);
            for (int c : cyc) onCycle[c] = cycles.size();
            cycles.push_back(cyc);
        }
        for (int x : path) state[x] = 2;
    }

    // gyermekek listaja: a nem kor pontok, amelyek a szomszedjuk fele mutatnak
    vector<vector<int>> ch(n);
    for (int u = 0; u < n; u++)
        if (nb[u] != -1 && onCycle[u] == -1) ch[nb[u]].push_back(u);

    long long best = 0;

    // korok: a kor j-edik pontjatol d melysegre levo bolha t idoben a (j + t - d) mod L pontban van
    for (const auto &cyc : cycles) {
        int L = cyc.size();
        vector<long long> sumKey(L, 0);
        for (int j = 0; j < L; j++) {
            vector<pair<int, int>> st;
            st.push_back({cyc[j], 0});
            while (!st.empty()) {
                auto [x, d] = st.back();
                st.pop_back();
                int key = (((j - d) % L) + L) % L;
                sumKey[key] += B[x];
                for (int y : ch[x]) st.push_back({y, d + 1});
            }
        }
        for (long long s : sumKey) best = max(best, s);
    }

    // fak: a nem kor pontok, amelyek gyokere egy kor pont vagy nincs szomszed
    vector<int> roots;
    vector<char> isRoot(n, 0);
    for (int u = 0; u < n; u++)
        if (onCycle[u] == -1 && (nb[u] == -1 || onCycle[nb[u]] != -1)) {
            roots.push_back(u);
            isRoot[u] = 1;
        }
    vector<int> order(roots.begin(), roots.end());
    for (size_t i = 0; i < order.size(); i++)
        for (int c : ch[order[i]]) order.push_back(c);

    // magassag es legmelyebb gyermek (hosszu-ut felbontas)
    vector<int> h(n, 0), heavy(n, -1);
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int v = order[i];
        for (int c : ch[v])
            if (heavy[v] == -1 || h[c] > h[heavy[v]]) heavy[v] = c;
        h[v] = (heavy[v] == -1) ? 0 : h[heavy[v]] + 1;
    }

    // tomb-cimek: a legmelyebb gyermek kozvetlenul a szulo utan kovetkezik
    vector<int> idx(n, -1);
    int ptr = 0;
    for (int v : order) {
        if (isRoot[v]) {
            idx[v] = ptr;
            ptr += h[v] + 1;
        }
        for (int c : ch[v]) {
            if (c == heavy[v]) {
                idx[c] = idx[v] + 1;
            } else {
                idx[c] = ptr;
                ptr += h[c] + 1;
            }
        }
    }

    // alulrol felfele: arr[idx[v] + k] = a v reszfajanak k melysegu bolhaszama
    vector<long long> arr(ptr + 1, 0);
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int v = order[i];
        arr[idx[v]] += B[v];
        best = max(best, arr[idx[v]]);
        for (int c : ch[v]) {
            if (c == heavy[v]) continue;
            for (int k = 0; k <= h[c]; k++) {
                arr[idx[v] + 1 + k] += arr[idx[c] + k];
                best = max(best, arr[idx[v] + 1 + k]);
            }
        }
    }

    cout << best << '\n';
    return 0;
}
