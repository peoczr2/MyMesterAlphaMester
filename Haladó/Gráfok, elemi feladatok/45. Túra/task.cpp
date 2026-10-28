/*
Megoldás lényege: egy tetszőleges csúcsból gyökerezzük a fát, és minden csúcsra kiszámoljuk, mennyi a legkisebb összeg a csúcsból lefelé induló, legalább egy csúcsot tartalmazó úton.
Minden legalább két csúcsú út legfelső csúcsa egy v csúcs, és az úthoz v-ből legfeljebb két lefelé ág tartozik; ezért v-nél elég a két legkisebb gyerek-értéket megnézni.
Az összes csúcsra a minimumot véve megkapjuk a legkisebb összegű, legalább két csúcsú utat: ha ez negatív, a túra nem szép, és az utat kiírjuk; különben minden túra szép.
A bejárás BFS-sel történik, így a rekurzió mélysége nem okoz problémát; az időigény tesztesetenként O(N).
*/
/*
Hint 1: || Egy túra összegét a csúcsok értékeinek összege adja, és elég a legkisebb összegű, legalább két csúcsú utat megkeresni: ha az sem negatív, akkor minden túra szép. ||
Hint 2: || Gyökerezzük a fát, és számoljuk ki minden csúcsra a lefelé induló utak legkisebb összegét. Egy csúcsnál a gyerekek értékéből elég a két legkisebb értéket figyelembe venni. ||
Hint 3: || Ha a legjobb út a legfelső v csúcsból indul, akkor v értéke plusz az egyik vagy mindkét legkisebb lefelé ág összege adja az út összegét. Az utat úgy írjuk ki, hogy az egyik ág fordítva, majd v, majd a másik ág következik. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    string out;
    while (T--) {
        int n;
        cin >> n;
        vector<int> t(n + 1, 0);
        for (int i = 1; i <= n; i++) cin >> t[i];

        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        // Gyökerezés az 1. csúcsból BFS-sel (nincs mélységi rekurzió).
        vector<int> par(n + 1, 0), order;
        order.reserve(n);
        vector<char> seen(n + 1, 0);
        order.push_back(1);
        seen[1] = 1;
        for (size_t i = 0; i < order.size(); i++) {
            int v = order[i];
            for (int u : adj[v]) {
                if (!seen[u]) {
                    seen[u] = 1;
                    par[u] = v;
                    order.push_back(u);
                }
            }
        }

        const int INF = INT_MAX / 4;
        // g[v]: legkisebb összeg a v-ből lefelé induló (legalább egy csúcsú) úton
        // nxt[v]: az a gyerek, amelyik felé ez az optimális lefelé út folytatódik (0, ha megáll)
        // c1[v], c2[v]: a két legkisebb g értékű gyerek
        vector<int> g(n + 1, 0), nxt(n + 1, 0), c1(n + 1, 0), c2(n + 1, 0);
        int bestSum = INF, bestTop = 0, bestMode = 0;

        for (int idx = n - 1; idx >= 0; idx--) {
            int v = order[idx];
            int m1 = INF, m2 = INF, k1 = 0, k2 = 0;
            for (int u : adj[v]) {
                if (u == par[v]) continue;
                if (g[u] < m1) {
                    m2 = m1;
                    k2 = k1;
                    m1 = g[u];
                    k1 = u;
                } else if (g[u] < m2) {
                    m2 = g[u];
                    k2 = u;
                }
            }
            if (m1 < 0) {
                g[v] = t[v] + m1;
                nxt[v] = k1;
            } else {
                g[v] = t[v];
                nxt[v] = 0;
            }
            c1[v] = k1;
            c2[v] = k2;

            if (k1) {
                int s = t[v] + m1;
                if (s < bestSum) {
                    bestSum = s;
                    bestTop = v;
                    bestMode = 1;
                }
            }
            if (k2) {
                int s = t[v] + m1 + m2;
                if (s < bestSum) {
                    bestSum = s;
                    bestTop = v;
                    bestMode = 2;
                }
            }
        }

        if (bestSum < 0) {
            auto chain = [&](int c) {
                vector<int> ch;
                for (int x = c; x != 0; x = nxt[x]) ch.push_back(x);
                return ch;
            };
            vector<int> path = chain(c1[bestTop]);
            reverse(path.begin(), path.end());
            path.push_back(bestTop);
            if (bestMode == 2) {
                vector<int> second = chain(c2[bestTop]);
                path.insert(path.end(), second.begin(), second.end());
            }
            out += "NEM\n";
            out += to_string(path.size()) + "\n";
            for (size_t i = 0; i < path.size(); i++) {
                if (i) out += ' ';
                out += to_string(path[i]);
            }
            out += '\n';
        } else {
            out += "IGEN\n";
        }
    }
    cout << out;
    return 0;
}
