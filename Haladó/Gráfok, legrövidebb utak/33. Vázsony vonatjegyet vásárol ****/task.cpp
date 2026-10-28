/*
Megoldás lényege:
Dijkstra-algoritmussal minden állomásra kiszámoljuk a B célállomástól mért legrövidebb d(v) távolságot. Egy u→v vonaton utazva a jegy feltétele szerint d(v) ≤ d(u), vagyis a távolság az úton nem nőhet. Azonos d-értékű, szomszédos állomások között oda-vissza is lehet utazni, ezért egy ilyen összefüggő csoport minden állomását be lehet járni, és a csoportban tetszőleges állomásban lehet kilépni. Az ilyen csoportokat DSU-val kezeljük, és a csoportok között a d szerint csökkenő sorrendben DP-t futtatunk: egy csoport értéke a méretének és a fölötte lévő legjobb csoport értékének összege, a kezdő csoport A-t tartalmazza, a végső érték a B csoportjának értéke. A visszakövetett csoportok állomásai adják a második sort. Az idő O(M log N), ami az 1.5 mp-es korláton belül van.
*/
/*
Hint 1: || Egy vonaton ülve nem lehet a célállomástól távolabb kerülni: számold ki minden állomásra a B-től mért legrövidebb távolságot Dijkstra-val, az út távolságai így nem nőhetnek. ||
Hint 2: || Ha két szomszédos állomás távolsága B-től azonos, oda-vissza is szabad utazni köztük, így az ilyen állomások összefüggő csoportján mind bejárható; ezeket egyesítsd DSU-val. ||
Hint 3: || A csoportokat távolságuk szerint csökkenő sorrendben dolgozd fel: egy csoport értéke a méretéből és a fölötte lévő, elérhető csoportok legjobb értékéből adódik, A csoportjából indulva a B csoportjában kapott érték a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> parentDsu;

int findRoot(int x) {
    while (parentDsu[x] != x) {
        parentDsu[x] = parentDsu[parentDsu[x]];
        x = parentDsu[x];
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a, b;
    cin >> n >> m >> a >> b;
    a--;
    b--;

    vector<int> ex(m), ey(m);
    vector<long long> et(m);
    vector<int> deg(n, 0);
    for (int i = 0; i < m; i++) {
        cin >> ex[i] >> ey[i] >> et[i];
        ex[i]--;
        ey[i]--;
        deg[ex[i]]++;
        deg[ey[i]]++;
    }
    vector<int> start(n + 1, 0);
    for (int v = 0; v < n; v++) start[v + 1] = start[v] + deg[v];
    vector<int> fillPos(start.begin(), start.end() - 1);
    vector<int> to(2 * m);
    vector<long long> wt(2 * m);
    for (int i = 0; i < m; i++) {
        to[fillPos[ex[i]]] = ey[i];
        wt[fillPos[ex[i]]++] = et[i];
        to[fillPos[ey[i]]] = ex[i];
        wt[fillPos[ey[i]]++] = et[i];
    }

    // Dijkstra: d[v] = legrövidebb távolság v-ből B-be
    const long long INF = LLONG_MAX / 4;
    vector<long long> d(n, INF);
    d[b] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, b});
    while (!pq.empty()) {
        auto [dd, u] = pq.top();
        pq.pop();
        if (dd != d[u]) continue;
        for (int e = start[u]; e < start[u + 1]; e++) {
            int v = to[e];
            if (dd + wt[e] < d[v]) {
                d[v] = dd + wt[e];
                pq.push({d[v], v});
            }
        }
    }

    // az azonos d-értékű szomszédok egy csoportba kerülnek (ezeken oda-vissza lehet utazni)
    parentDsu.resize(n);
    iota(parentDsu.begin(), parentDsu.end(), 0);
    for (int x = 0; x < n; x++) {
        if (d[x] >= INF) continue;
        for (int e = start[x]; e < start[x + 1]; e++) {
            int y = to[e];
            if (d[y] == d[x]) {
                int rx = findRoot(x), ry = findRoot(y);
                if (rx != ry) parentDsu[rx] = ry;
            }
        }
    }
    vector<long long> csize(n, 0);
    for (int v = 0; v < n; v++)
        if (d[v] < INF) csize[findRoot(v)]++;

    // a DP a csoportok között: f[C] = a C csoportba eljutó legtöbb állomás (C-t is beleértve)
    vector<long long> f(n, -1);
    vector<int> prevGroup(n, -1);
    int ca = findRoot(a);
    f[ca] = csize[ca];

    vector<int> order;
    for (int v = 0; v < n; v++)
        if (d[v] < INF) order.push_back(v);
    sort(order.begin(), order.end(), [&](int x, int y) { return d[x] > d[y]; });

    for (int x : order) {
        int cx = findRoot(x);
        if (f[cx] < 0) continue;
        for (int e = start[x]; e < start[x + 1]; e++) {
            int y = to[e];
            if (d[y] < d[x]) {
                int cy = findRoot(y);
                long long cand = f[cx] + csize[cy];
                if (cand > f[cy]) {
                    f[cy] = cand;
                    prevGroup[cy] = cx;
                }
            }
        }
    }

    int cb = findRoot(b);
    if (f[cb] < 0) {
        cout << 0 << '\n' << '\n';
        return 0;
    }

    // a legjobb lánc csoportjainak visszakövetése
    vector<char> onChain(n, 0);
    int c = cb;
    onChain[c] = 1;
    while (c != ca && prevGroup[c] >= 0) {
        c = prevGroup[c];
        onChain[c] = 1;
    }

    vector<int> chosen;
    for (int v = 0; v < n; v++)
        if (d[v] < INF && onChain[findRoot(v)]) chosen.push_back(v);

    cout << chosen.size() << '\n';
    for (size_t i = 0; i < chosen.size(); i++) {
        if (i) cout << ' ';
        cout << chosen[i] + 1;
    }
    cout << '\n';
    return 0;
}
