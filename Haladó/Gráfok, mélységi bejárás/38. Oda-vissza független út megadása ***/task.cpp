/*
Megoldás lényege:
Az oda-vissza független út két olyan A–B út, amelyeknek a belső csúcsai diszjunktak, vagyis csak a két végpontjuk közös. Ilyen párt maximális folyammal keresünk (Menger-tétel): minden v csúcsot egy be- és egy kimeneti csúcsra bontunk, közöttük kapacitás 1 van (A-nál és B-nél ez nem korlátoz), minden irányítatlan élt pedig két irányított éllel helyettesítünk, mindkettő kapacitása 1. A kimeneti csúcsból A-ból a bemeneti csúcsba B-be keresünk két növelő utat szélességi bejárással, O(N+M) időben. Ha a folyam értéke 2, a folyamot az A-tól követve két utat kapunk, amelyek belső csúcsai nem fedik egymást. Az első utat A-tól B-ig, a másodikat fordítva, B-től A-ig írjuk ki. A megoldás nem egyértelmű, a feladat bármelyik helyes párt elfogadja.
*/
/*
Hint 1: || Keress két A–B utat, amelynek belső csúcsai nem fedik egymást. Egy csúcs legfeljebb az egyik útban szerepelhet belsőleg, az élek irányításától pedig eltekinthetsz. ||
Hint 2: || Ezt a csúcsok szétbontásával (be- és kimeneti csúcs, közöttük kapacitás 1) és minden élnek két irányba vezetésével maximális folyamként kezelheted; A kimenetéből B bemenetéig a folyam értéke legfeljebb 2. ||
Hint 3: || Két szélességi keresés elég a folyam kiszámításához. Utána a folyam mentén A-ból haladva kapod meg az egyik utat; a második utat megfordítva kell kiírni, hogy B-ből A-ba menjen. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Élek: a 2k és 2k+1 index páros, egymás fordítottjai (a kapacitás a fordítottban a visszaküldhető folyam).
vector<int> head, nxt, to;
vector<signed char> cap;

void addArc(int u, int v, int c) {
    to.push_back(v);
    cap.push_back((signed char)c);
    nxt.push_back(head[u]);
    head[u] = (int)to.size() - 1;

    to.push_back(u);
    cap.push_back(0);
    nxt.push_back(head[v]);
    head[v] = (int)to.size() - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a, b;
    cin >> n >> m >> a >> b;

    if (a == b) {
        cout << a << "\n" << a << "\n";
        return 0;
    }

    int V = 2 * (n + 1);
    head.assign(V, -1);
    to.reserve(4 * (size_t)m + 2 * (size_t)n);
    nxt.reserve(4 * (size_t)m + 2 * (size_t)n);
    cap.reserve(4 * (size_t)m + 2 * (size_t)n);

    // be(v) = 2v, ki(v) = 2v+1
    for (int v = 1; v <= n; ++v)
        addArc(2 * v, 2 * v + 1, (v == a || v == b) ? 2 : 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        addArc(2 * u + 1, 2 * v, 1);
        addArc(2 * v + 1, 2 * u, 1);
    }

    int S = 2 * a + 1, T = 2 * b;
    int flow = 0;
    for (int it = 0; it < 2; ++it) {
        vector<char> vis(V, 0);
        vector<int> parArc(V, -1);
        queue<int> q;
        q.push(S);
        vis[S] = 1;
        while (!q.empty() && !vis[T]) {
            int x = q.front();
            q.pop();
            for (int e = head[x]; e != -1; e = nxt[e]) {
                int y = to[e];
                if (cap[e] > 0 && !vis[y]) {
                    vis[y] = 1;
                    parArc[y] = e;
                    q.push(y);
                }
            }
        }
        if (!vis[T]) break;
        for (int y = T; y != S; y = to[parArc[y] ^ 1]) {
            int e = parArc[y];
            cap[e] -= 1;
            cap[e ^ 1] += 1;
        }
        ++flow;
    }

    // A folyamon követve egy utat kapunk A-tól B-ig; minden belső csúcs legfeljebb egy úton megy át.
    auto extractPath = [&]() {
        vector<int> path = {a};
        int x = S;
        for (int steps = 0; x != T && steps <= V; ++steps) {
            int chosen = -1;
            for (int e = head[x]; e != -1; e = nxt[e])
                if ((e & 1) == 0 && cap[e ^ 1] > 0) {
                    chosen = e;
                    break;
                }
            if (chosen == -1) break;
            cap[chosen ^ 1] -= 1;
            x = to[chosen];
            if (x % 2 == 0) path.push_back(x / 2);
        }
        return path;
    };

    vector<int> p1 = extractPath();
    vector<int> p2 = (flow >= 2) ? extractPath() : p1;

    for (size_t i = 0; i < p1.size(); ++i) cout << p1[i] << (i + 1 < p1.size() ? ' ' : '\n');
    for (size_t i = p2.size(); i-- > 0;) cout << p2[i] << (i > 0 ? ' ' : '\n');
    return 0;
}
