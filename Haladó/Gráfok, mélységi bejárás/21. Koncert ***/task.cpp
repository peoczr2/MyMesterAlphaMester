/*
Megoldás lényege:
A székek a csúcsok, az igények az élek: egy igény a két végpontja közül kaphat széket, és egy széket legfeljebb egy igény foglalhat el. Egy összefüggő komponensben V szék és E igény van, és legfeljebb min(V, E) igény elégíthető ki: fában (E = V-1) minden igény kielégíthető, körös komponensben pedig minden szék kiosztható. A kiosztást komponensenként egy feszítőfából építjük BFS-sel. Ha E >= V, a fán kívüli él (x, y) az x széket kapja, majd a fát x-ből bejárva minden más csúcs a szülőélét kapja meg. Fa esetén a gyökér széke üres marad. Az időigény O(N + M).
*/
/*
Hint 1: || Tekintsd a székeket csúcsoknak, az igényeket éleknek: egy igény a két végpontja közül kaphat egy széket, és egy széket legfeljebb egy igény foglalhat el. ||
Hint 2: || Egy összefüggő részben a kielégíthető igények száma a csúcsok és az élek számának kisebbike. Fa esetén minden él kielégíthető, kör esetén minden csúcs kaphat széket. ||
Hint 3: || Építs feszítőfát minden komponensben. Ha van a fán kívüli él, a gyökér legyen annak egyik végpontja, és ezt az élt a gyökér kapja; a többi csúcs a szülőélét kapja. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;  // m: székek száma, n: igények száma
    cin >> m >> n;
    vector<int> eu(n + 1), ev(n + 1);
    vector<vector<pair<int, int>>> adj(m + 1);  // (szomszéd szék, igény sorszáma)
    for (int i = 1; i <= n; ++i) {
        cin >> eu[i] >> ev[i];
        adj[eu[i]].push_back({ev[i], i});
        adj[ev[i]].push_back({eu[i], i});
    }

    vector<char> seatSeen(m + 1, 0), edgeSeen(n + 1, 0), isTree(n + 1, 0), reached(m + 1, 0);
    vector<int> reqSeat(n + 1, 0);  // igény -> kapott szék (0: nincs)

    for (int r0 = 1; r0 <= m; ++r0) {
        if (seatSeen[r0]) continue;

        // 1. feszítőfa BFS-sel, a komponens csúcsai és élei
        vector<int> verts, compEdges;
        queue<int> qu;
        qu.push(r0);
        seatSeen[r0] = 1;
        while (!qu.empty()) {
            int x = qu.front();
            qu.pop();
            verts.push_back(x);
            for (auto [y, e] : adj[x]) {
                if (!edgeSeen[e]) {
                    edgeSeen[e] = 1;
                    compEdges.push_back(e);
                }
                if (!seatSeen[y]) {
                    seatSeen[y] = 1;
                    isTree[e] = 1;
                    qu.push(y);
                }
            }
        }

        int V = verts.size(), E = compEdges.size();
        int root = r0;
        if (E >= V) {
            // van fán kívüli él: ez a gyökér székét adja
            int extra = 0;
            for (int e : compEdges)
                if (!isTree[e]) {
                    extra = e;
                    break;
                }
            root = eu[extra];
            reqSeat[extra] = root;
        }

        // 2. a feszítőfát a gyökérből bejárva minden nem gyökér csúcs a szülőélét kapja
        vector<int> st = {root};
        reached[root] = 1;
        while (!st.empty()) {
            int x = st.back();
            st.pop_back();
            for (auto [y, e] : adj[x]) {
                if (isTree[e] && !reached[y]) {
                    reached[y] = 1;
                    reqSeat[e] = y;
                    st.push_back(y);
                }
            }
        }
    }

    int K = 0;
    for (int i = 1; i <= n; ++i)
        if (reqSeat[i]) ++K;
    cout << K << '\n';
    for (int i = 1; i <= n; ++i)
        if (reqSeat[i]) cout << i << ' ' << reqSeat[i] << '\n';
}
