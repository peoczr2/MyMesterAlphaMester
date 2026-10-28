/*
Megoldás lényege:
Minden pont a legközelebbi szomszédjába ugrik, így minden pontnak egyetlen ugrási célja van; a pontok fákat alkotnak, amelyek gyökerei 2 hosszú ciklusok (kölcsönösen legközelebbi párok).
Egy csúcson t időpontban lévő bolhák száma a csúcs alatti fában t mélységben lévő pontok bolhái összege, ezért minden csúcsra a szintenkénti összegtömböt kell nyilvántartani.
Ezt a leghosszabb úton örökítéssel (long path decomposition) oldjuk meg, így az összes tömbmunka O(N).
A ciklusok pontjain a mélységek paritása dönti el, mely bolhák érkeznek egyszerre, ezért ott a két fázisösszeg nagyobbikát vesszük.
A bejárás szélességi (BFS-szerű) rétegekben történik a levelektől befelé; az időigény O(N+M).
*/
/*
Hint 1: || Minden pontra keresd meg a legkisebb távolságú szomszédját (az ugrási célt), így minden pontnak pontosan egy kimenő éle lesz. ||
Hint 2: || A levelektől befelé haladó, BFS-szerű rétegbejárással ismerheted meg a ciklusokat, és minden pontról azt, melyik ciklushoz tartozik és hány lépés a távolsága tőle. ||
Hint 3: || Egy u csúcson t lépés után az u alá tartozó, t mélységű pontok bolhái gyűlnek össze, ezért minden csúcsra szintenkénti összegtömböt tárolj, a gyermekek tömbjét a szülőhöz add, és a leghosszabb gyermek tömbjét eltolással örököld. A ciklusoknál a mélység szerinti maradékok (mod 2) adják a két fázis összegét; a nagyobbik a jelölt érték. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<long long> b(n + 1);
    for (int i = 1; i <= n; i++) cin >> b[i];

    // Minden pont legközelebbi szomszédja. Szomszéd nélkül a bolha helyben marad (f[i] = i).
    vector<long long> best(n + 1, LLONG_MAX);
    vector<int> f(n + 1);
    for (int i = 1; i <= n; i++) f[i] = i;
    for (int j = 0; j < m; j++) {
        int x, y;
        long long t;
        cin >> x >> y >> t;
        if (t < best[x]) { best[x] = t; f[x] = y; }
        if (t < best[y]) { best[y] = t; f[y] = x; }
    }

    // Szélességi (Kahn-féle) rétegbejárás a levelektől befelé. A gyerekek a szülők előtt kerülnek a sorba.
    vector<int> indeg(n + 1, 0);
    for (int i = 1; i <= n; i++) indeg[f[i]]++;
    vector<int> order;
    order.reserve(n);
    for (int i = 1; i <= n; i++) if (indeg[i] == 0) order.push_back(i);
    for (size_t h = 0; h < order.size(); h++) {
        int v = order[h];
        if (--indeg[f[v]] == 0) order.push_back(f[v]);
    }
    vector<char> oncyc(n + 1, 0);
    for (int i = 1; i <= n; i++) oncyc[i] = indeg[i] > 0;

    // Magasságok és a leghosszabb gyermek (heavy child).
    vector<int> height(n + 1, 0), heavy(n + 1, 0);
    for (int v : order) {
        int p = f[v];
        if (!oncyc[p] && height[v] + 1 > height[p]) {
            height[p] = height[v] + 1;
            heavy[p] = v;
        }
    }

    // Tömbcímek: a leghosszabb út tagjai egymás mellett, a gyerek címe a szülő címe + 1.
    vector<int> ptr(n + 1, -1);
    int cur = 0;
    for (int h = (int)order.size() - 1; h >= 0; h--) {
        int v = order[h];
        int p = f[v];
        if (!oncyc[p] && heavy[p] == v) {
            ptr[v] = ptr[p] + 1;
        } else {
            ptr[v] = cur;
            cur += height[v] + 1;
        }
    }

    vector<long long> buf(cur + 1, 0);
    long long ans = 0;
    for (int v : order) {
        buf[ptr[v]] = b[v];
        ans = max(ans, b[v]);
    }
    // Könnyű gyermek tömbjének hozzáadása a szülő tömbjéhez (eltolva eggyel).
    for (int v : order) {
        int p = f[v];
        if (oncyc[p] || heavy[p] == v) continue;
        for (int d = 0; d <= height[v]; d++) {
            long long &dst = buf[ptr[p] + 1 + d];
            dst += buf[ptr[v] + d];
            ans = max(ans, dst);
        }
    }

    // Ciklusok: a ciklus pontjai c_0 -> c_1 -> ... -> c_{k-1} -> c_0.
    vector<int> cid(n + 1, -1), cidx(n + 1, -1);
    vector<vector<int>> cyc;
    for (int i = 1; i <= n; i++) {
        if (!oncyc[i] || cid[i] != -1) continue;
        vector<int> c;
        int x = i;
        while (cid[x] == -1) {
            cid[x] = (int)cyc.size();
            cidx[x] = (int)c.size();
            c.push_back(x);
            x = f[x];
        }
        cyc.push_back(c);
    }

    // Minden pont gyökere (melyik ciklushoz tartozik) és mélysége a ciklustól.
    vector<int> root(n + 1, 0), depth(n + 1, 0);
    for (int i = 1; i <= n; i++) if (oncyc[i]) root[i] = i;
    for (int h = (int)order.size() - 1; h >= 0; h--) {
        int v = order[h];
        int p = f[v];
        root[v] = root[p];
        depth[v] = depth[p] + 1;
    }

    // g[id][j*k + ρ]: a ciklus j-edik fájában a ρ mod k mélységű bolhák összege.
    vector<vector<long long>> g(cyc.size());
    for (size_t id = 0; id < cyc.size(); id++) {
        size_t k = cyc[id].size();
        g[id].assign(k * k, 0);
    }
    auto addFlea = [&](int v) {
        int r = root[v];
        int id = cid[r];
        int k = (int)cyc[id].size();
        g[id][cidx[r] * k + depth[v] % k] += b[v];
    };
    for (int i = 1; i <= n; i++) if (oncyc[i]) addFlea(i);
    for (int v : order) addFlea(v);

    // Végtelen sok lépés után a fázis (s) szerint a ciklus-pontokon egyszerre lévő bolhák összege.
    for (size_t id = 0; id < cyc.size(); id++) {
        int k = (int)cyc[id].size();
        for (int s = 0; s < k; s++) {
            long long tot = 0;
            for (int j = 0; j < k; j++) tot += g[id][j * k + (j + s) % k];
            ans = max(ans, tot);
        }
    }

    cout << ans << "\n";
    return 0;
}
