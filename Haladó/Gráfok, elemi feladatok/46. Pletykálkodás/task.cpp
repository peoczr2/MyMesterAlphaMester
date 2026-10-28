/*
Megoldás lényege:
Ha a gráfban van 4 hosszú kör (C4), akkor 2N-4 hívás elég, egyébként a minimum 2N-3 (ez fa-alapú
megoldással is elérhető). A kör négy csúcsa (a-b-c-d-a) négy hívással mindannyiuknál megkapja az összes pletykát:
először a két szemközti élpár (a,b) és (c,d), utána (a,d) és (b,c). A többi csúcsot a körből kiinduló BFS-fa
mentén kezeljük: a fordított BFS-sorrendben mindenki felhívja a szülőjét (a pletykái felfelé jutnak), a négy
kör-csúcs után pedig BFS-sorrendben a szülő hívja meg (így a teljes tudás lefelé jut). Összesen (N-4)+4+(N-4)=2N-4
hívás. C4 nélkül a feszítőfa gyökere (1) és annak első gyereke az utolsó összegyűjtő hívásnál egyszerre tesz
teljessé két csúcsot, így (N-1)+(N-2)=2N-3 hívás jön ki.
A C4 keresése: minden u csúcsra megnézzük, hogy egy x csúcs két különböző szomszédon át is elérhető-e u-ból.
Ha nincs C4, minden csúcspárnak legfeljebb egy közös szomszédja van, így a keresés N^2 körüli munka.
*/
/*
Hint 1: || Ha két csúcsnak két különböző közös szomszédja van, a gráfban van 4 hosszú kör, és a minimum eggyel kisebb lehet, mint a fa esetén. ||
Hint 2: || A 4 hosszú kör négy csúcsa négy hívással egymás pletykáit mind megkapja: előbb a kör két szemközti élpárját hívd meg, utána a másik két szemközti élt. ||
Hint 3: || A kör többi csúcsát egy BFS-fa mentén kezeld: a levelektől felfelé egy-egy hívás, a kör után a gyökértől lefelé egy-egy hívás jut el mindenkihez. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<vector<int>> tadj(n + 1);  // feszítőfa: a bemeneti sorrendben, körmentesen
    vector<int> dsu(n + 1);
    iota(dsu.begin(), dsu.end(), 0);
    function<int(int)> findRoot = [&](int x) { return dsu[x] == x ? x : dsu[x] = findRoot(dsu[x]); };
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        int ra = findRoot(a), rb = findRoot(b);
        if (ra != rb) {
            dsu[ra] = rb;
            tadj[a].push_back(b);
            tadj[b].push_back(a);
        }
    }
    for (auto& list : adj) {
        sort(list.begin(), list.end());
        list.erase(unique(list.begin(), list.end()), list.end());
    }

    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }

    // 4 hosszú kör keresése: u-p-x-w-u alakban
    int cu = -1, cp = -1, cx = -1, cw = -1;
    {
        vector<int> stamp(n + 1, 0), via(n + 1, 0);
        for (int u = 1; u <= n && cu == -1; ++u) {
            for (int w : adj[u]) {
                for (int x : adj[w]) {
                    if (x == u) continue;
                    if (stamp[x] == u) {
                        cu = u;
                        cp = via[x];
                        cx = x;
                        cw = w;
                        break;
                    }
                    stamp[x] = u;
                    via[x] = w;
                }
                if (cu != -1) break;
            }
        }
    }

    vector<pair<int, int>> calls;

    if (cu != -1) {
        // a-b-c-d-a kör: a=u, b=p, c=x, d=w
        int a = cu, b = cp, c = cx, d = cw;
        vector<int> par(n + 1, 0), order;
        vector<char> inCore(n + 1, 0);
        for (int v : {a, b, c, d}) {
            inCore[v] = 1;
            order.push_back(v);
        }
        for (size_t i = 0; i < order.size(); ++i) {
            int v = order[i];
            for (int w : adj[v]) {
                if (!inCore[w] && par[w] == 0) {
                    par[w] = v;
                    order.push_back(w);
                }
            }
        }
        // összegyűjtés: mélyebbről felfelé
        for (int i = static_cast<int>(order.size()) - 1; i >= 4; --i) {
            calls.push_back({order[i], par[order[i]]});
        }
        // a négy kör-csúcs teljessé tétele
        calls.push_back({a, b});
        calls.push_back({c, d});
        calls.push_back({a, d});
        calls.push_back({b, c});
        // szétosztás: szülő hívja a gyereket, BFS-sorrendben
        for (int i = 4; i < static_cast<int>(order.size()); ++i) {
            calls.push_back({order[i], par[order[i]]});
        }
    } else {
        // C4 nélkül: a feszítőfa mentén, gyökér = 1
        vector<int> par(n + 1, 0), order = {1};
        vector<char> seen(n + 1, 0);
        seen[1] = 1;
        for (size_t i = 0; i < order.size(); ++i) {
            int v = order[i];
            for (int w : tadj[v]) {
                if (!seen[w]) {
                    seen[w] = 1;
                    par[w] = v;
                    order.push_back(w);
                }
            }
        }
        // összegyűjtés: a gyökér első gyerekéig (order[1]) bezárólag
        for (int i = n - 1; i >= 1; --i) {
            calls.push_back({order[i], par[order[i]]});
        }
        // szétosztás: a gyökér és order[1] már teljes
        for (int i = 2; i < n; ++i) {
            calls.push_back({order[i], par[order[i]]});
        }
    }

    cout << calls.size() << '\n';
    for (auto& [a, b] : calls) {
        cout << a << ' ' << b << '\n';
    }
    return 0;
}
