/*
Megoldás lényege:
Olyan egyszerű útvonalat keresünk Ádám városából a kirándulási városba, amely érinti Éva városát. Ez akkor és csak akkor lehetséges, ha Évából két olyan út indul, amelyek csak Évában találkoznak: az egyik Ádámhoz, a másik a kirándulási városhoz. Ezt csúcsszétbontásos maximális folyammal ellenőrizzük: minden város be- és kimenő csúcsa között 1-es kapacitású él van, így minden várost legfeljebb egy út használhat. Ha a folyam értéke 2, a két utat összefűzzük Ádámtól a kirándulási városig, különben a válasz 0. Két növelő út elég, az időigény O(N + M).
*/
/*
Hint 1: || Az útvonal Ádám városából a kirándulási városba megy, és közben érinti Évát. Bontsd két részre: Ádám → Éva és Éva → kirándulás, és a két rész ne használjon közös várost (Évát kivéve). ||
Hint 2: || Ez azt jelenti, hogy Évából két csúcsdiszjunkt út kell: az egyik Ádámhoz, a másik a kirándulási városhoz. Ezt maximális folyammal kereshetjük, ha minden várost csak egy egység átvitelére engedünk (csúcsszétbontás: be- és kimenő csúcs között 1-es kapacitású él). ||
Hint 3: || Ha a folyam értéke 2, a telített élek mentén haladva megkapod a két utat: az Ádámhoz vezetőt fordítva kell kiírni, utána a kirándulási városig tartó részt fűzöd hozzá. Ha a folyam kisebb 2-nél, a válasz 0. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Arc {
    int to, rev;
    char cap;   // maradék kapacitás (0 vagy 1)
    char orig;  // 1, ha eredeti él, 0, ha visszairányú párja
};

vector<vector<Arc>> g;

void addArc(int u, int v, int cap) {
    g[u].push_back({v, (int)g[v].size(), (char)cap, 1});
    g[v].push_back({u, (int)g[u].size() - 1, 0, 0});
}

// Egy egységnyi növelő út keresése BFS-sel s-ből t-be a maradék kapacitások mentén.
bool augment(int s, int t) {
    int sz = g.size();
    vector<int> pv(sz, -1), pe(sz, -1);
    vector<char> seen(sz, 0);
    queue<int> q;
    q.push(s);
    seen[s] = 1;
    while (!q.empty() && !seen[t]) {
        int x = q.front();
        q.pop();
        for (int i = 0; i < (int)g[x].size(); ++i) {
            const Arc &a = g[x][i];
            if (a.cap > 0 && !seen[a.to]) {
                seen[a.to] = 1;
                pv[a.to] = x;
                pe[a.to] = i;
                q.push(a.to);
            }
        }
    }
    if (!seen[t]) return false;
    for (int x = t; x != s; x = pv[x]) {
        Arc &a = g[pv[x]][pe[x]];
        a.cap -= 1;
        g[x][a.rev].cap += 1;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int a, e, k;
    cin >> a >> e >> k;

    // Csúcs v: bemenő csúcs 2v, kimenő csúcs 2v+1. Forrás: Éva kimenő csúcsa, nyelő: T.
    g.assign(2 * n + 3, {});
    const int S = 2 * e + 1, T = 2 * n + 2;

    for (int v = 1; v <= n; ++v)
        if (v != e) addArc(2 * v, 2 * v + 1, 1);  // minden város legfeljebb egy úton
    addArc(2 * a + 1, T, 1);
    addArc(2 * k + 1, T, 1);
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        addArc(2 * x + 1, 2 * y, 1);
        addArc(2 * y + 1, 2 * x, 1);
    }

    int flow = 0;
    while (flow < 2 && augment(S, T)) ++flow;
    if (flow < 2) {
        cout << 0 << '\n';
        return 0;
    }

    // A telített élek mentén kiolvassuk az egyik utat S-ből T-be (Évától a nyelőig).
    auto walk = [&]() {
        vector<int> path = {e};
        int cur = S;
        while (cur != T) {
            int nxt = -1;
            for (Arc &ar : g[cur]) {
                if (ar.orig && ar.cap == 0) {
                    ar.cap = 1;  // felhasznált él, a második bejárás nem veszi újra
                    nxt = ar.to;
                    break;
                }
            }
            if (nxt == -1) break;
            cur = nxt;
            if (cur != T && cur % 2 == 0) path.push_back(cur / 2);
        }
        return path;
    };

    vector<int> p1 = walk(), p2 = walk();
    if (p1.back() != a) swap(p1, p2);  // p1: Évától Ádámig, p2: Évától a kirándulási városig

    vector<int> ans(p1.rbegin(), p1.rend());
    for (size_t i = 1; i < p2.size(); ++i) ans.push_back(p2[i]);

    for (size_t i = 0; i < ans.size(); ++i)
        cout << ans[i] << (i + 1 < ans.size() ? ' ' : '\n');
    return 0;
}
