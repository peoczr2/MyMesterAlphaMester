/*
Megoldás lényege:
A séta minden kötelező várost érint, a két végpont szabadon választható. Jelölje W a kötelező városokat összekötő legkisebb részfa (Steiner-fa) összsúlyát, D pedig két kötelező város közötti legnagyobb távolságot. Ekkor a legrövidebb séta hossza 2·W − D: a Steiner-fa minden élén kétszer kell átmenni, kivéve a végpontok közötti úton, amelyen elég egyszer. Egy él akkor tartozik a Steiner-fához, ha a két oldalán is van kötelező város; ezt egy gyökérből induló bejárásban a részfákban lévő kötelező városok számlálásával döntjük el. A D értékét két bejárással kapjuk: egy kötelező városból a legtávolabbi kötelező város lesz az egyik végpont, onnan a legtávolabbi a másik. Az útvonal a második végpontból indul, a Steiner-fát bejárja úgy, hogy a végpont felé vezető úton nem tér vissza. Az időigény O(N + K).
*/
/*
Hint 1: || Ha a séta végpontja s és t, akkor az s–t úton elég egyszer átmenni, a kötelező városokat összekötő részfa többi élén pontosan kétszer kell átmenni. Gondold végig, miért. ||
Hint 2: || Egy él pontosan akkor kell a részfához, ha a két oldalán is van kötelező város. Egy tetszőleges gyökérből indított bejárásban ezt a részfákban lévő kötelező városok számával ellenőrizheted. ||
Hint 3: || A végpontokhoz kettős bejárás kell: egy tetszőleges kötelező városból keresd meg a legtávolabbi kötelező várost, majd onnan újra a legtávolabbit. Az útvonalat az egyik végpontból indulva a részfa bejárásával készítsd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<vector<pair<int, long long>>> adj;

// Gyökérből indított bejárás: szülők, szülőél súlya, bejárási sorrend, távolság a gyökértől.
struct Rooted {
    vector<int> par, order;
    vector<long long> pw, dist;
};

Rooted rootAt(int root) {
    Rooted r;
    r.par.assign(n + 1, 0);
    r.pw.assign(n + 1, 0);
    r.dist.assign(n + 1, 0);
    vector<char> vis(n + 1, 0);
    r.order.push_back(root);
    vis[root] = 1;
    for (size_t i = 0; i < r.order.size(); ++i) {
        int v = r.order[i];
        for (auto [to, w] : adj[v]) {
            if (vis[to]) continue;
            vis[to] = 1;
            r.par[to] = v;
            r.pw[to] = w;
            r.dist[to] = r.dist[v] + w;
            r.order.push_back(to);
        }
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    adj.assign(n + 1, {});
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        long long h;
        cin >> a >> b >> h;
        adj[a].push_back({b, h});
        adj[b].push_back({a, h});
    }
    vector<int> term(k), tcount(n + 1, 0);
    for (int i = 0; i < k; ++i) {
        cin >> term[i];
        ++tcount[term[i]];
    }

    // 1. A kötelező városokat összekötő részfa (Steiner-fa) összsúlya.
    Rooted r0 = rootAt(term[0]);
    vector<int> cnt(tcount);
    for (int i = n - 1; i >= 1; --i) {
        int v = r0.order[i];
        cnt[r0.par[v]] += cnt[v];
    }
    long long W = 0;
    for (int v = 1; v <= n; ++v)
        if (cnt[v] > 0 && cnt[v] < k) W += r0.pw[v];

    // 2. Két legtávolabbi kötelező város (kettős bejárás).
    auto farthestTerm = [&](const Rooted &r) {
        int best = term[0];
        for (int t : term)
            if (r.dist[t] > r.dist[best]) best = t;
        return best;
    };
    int a = term[0];
    int b = farthestTerm(rootAt(a));
    Rooted rb = rootAt(b);
    int c = farthestTerm(rb);
    long long D = rb.dist[c];
    long long T = 2 * W - D;

    // 3. Útvonal b-ből c-be: a b gyökerű fában a c felé vezető utat jelöljük.
    vector<char> onPath(n + 1, 0);
    for (int v = c;; v = rb.par[v]) {
        onPath[v] = 1;
        if (v == b) break;
    }
    vector<int> cntB(tcount);
    for (int i = n - 1; i >= 1; --i) {
        int v = rb.order[i];
        cntB[rb.par[v]] += cntB[v];
    }
    // Gyerekek: a nem útvonal-gyerekek előre, az útvonal-gyerek utoljára kerül.
    vector<vector<int>> kids(n + 1);
    vector<int> pathKid(n + 1, 0);
    for (int i = 1; i < n; ++i) {
        int v = rb.order[i];
        if (!(cntB[v] > 0 && cntB[v] < k)) continue;
        if (onPath[v]) pathKid[rb.par[v]] = v;
        else kids[rb.par[v]].push_back(v);
    }
    for (int v = 1; v <= n; ++v)
        if (pathKid[v]) kids[v].push_back(pathKid[v]);

    vector<int> route;
    route.push_back(b);
    vector<pair<int, size_t>> st;  // (csúcs, következő gyerek indexe)
    st.push_back({b, 0});
    while (!st.empty()) {
        int v = st.back().first;
        if (st.back().second < kids[v].size()) {
            int ch = kids[v][st.back().second++];
            route.push_back(ch);
            st.push_back({ch, 0});
        } else {
            st.pop_back();
            if (!st.empty() && !onPath[v]) route.push_back(st.back().first);
        }
    }

    cout << T << "\n";
    for (size_t i = 0; i < route.size(); ++i) {
        if (i) cout << ' ';
        cout << route[i];
    }
    cout << "\n";
    return 0;
}
