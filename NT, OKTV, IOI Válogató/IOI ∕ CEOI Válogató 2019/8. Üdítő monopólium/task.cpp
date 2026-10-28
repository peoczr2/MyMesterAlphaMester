/*
Megoldás lényege:
Az azonos italt szeretők összefüggő csoportja egyszerre vált: ha valaki átáll, vele együtt a régi italát szerető összes összefüggő társa is átáll. Ezeket a csoportokat egy csúcsba húzva egy két színű gráfot kapunk, ahol egy lépés az egyik csúcs (csoport) átszínezése, amivel az minden szomszédjával összeolvad. Két szín esetén egy lépés legfeljebb 1-gyel csökkenti a legtávolabbi csoport távolságát egy adott középponttól, így a válasz a gráf sugara: a legkisebb excentricitású csúcs távolsága a legtávolabbi csúccsal. Ugyanazt a középpontot ismételten választva a márkák automatikusan váltakoznak, tehát a „nem küldhetünk kétszer egymás után azonos márkát” feltétel nem ront a válaszon. Számítás: minden csúcsból 0-1 BFS, ahol a színváltó él súlya 1, az azonos színű él súlya 0; a legnagyobb távolság az excentricitás, a minimumuk a válasz. N ≤ 100 miatt O(N·(N+M)) bőven belefér.
*/
/*
Hint 1: || Vonj össze minden olyan csoportot egy csúcsba, amely egyszerre vált: az azonos italt szeretők összefüggő részei egy lépésben együtt átállnak. ||
Hint 2: || Két ital esetén egy lépés egy csoportot az összes szomszédjával olvaszt össze, így az összevont gráfban a távolság a színváltások száma az úton. Ezt 0-1 BFS-sel, az azonos színű élek súlyát 0-nak véve, közvetlenül az eredeti gráfon is megkapod. ||
Hint 3: || Minden csúcsból futtass 0-1 BFS-t, és jegyezd fel a legtávolabbi csúcs távolságát (excentricitás). Ezek minimuma a válasz, mert ugyanazt a középpontot ismételve a márkák automatikusan váltakoznak. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;

        vector<int> col(n);
        for (int i = 0; i < n; i++) {
            cin >> col[i];
        }

        vector<vector<int>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int best = INT_MAX;
        for (int s = 0; s < n; s++) {
            vector<int> dist(n, INT_MAX);
            deque<int> dq;
            dist[s] = 0;
            dq.push_back(s);
            while (!dq.empty()) {
                int x = dq.front();
                dq.pop_front();
                for (int y : adj[x]) {
                    int w = (col[x] != col[y]) ? 1 : 0;
                    if (dist[x] + w < dist[y]) {
                        dist[y] = dist[x] + w;
                        if (w == 0) {
                            dq.push_front(y);
                        } else {
                            dq.push_back(y);
                        }
                    }
                }
            }
            int ecc = *max_element(dist.begin(), dist.end());
            best = min(best, ecc);
        }

        cout << best << '\n';
    }
    return 0;
}
