/*
Megoldás lényege:
Az azonos italt kedvelő, egymással összefüggő bergengócok egy-egy komponenst alkotnak, és egy csomag hatására egy egész komponens vált, így az összeolvad az összes szomszédos komponensével. A komponenseket csúcsnak tekintve összefüggő gráfot kapunk, amelyben a szomszédos komponensek italai különbözők. Két italnál az optimális stratégia, hogy mindig ugyanazt a (egyre növekvő) komponenst váltjuk át: ha a v komponenst választjuk, minden héten az eddig összeolvadt rész a v-től egy lépéssel messzebbi komponensekkel bővül, ezért pontosan v excentricitásának (a tőle legtávolabbi komponens távolságának) megfelelő hét kell. Közben a váltott komponens színe minden héten megfordul, így a két egymást követő csomag márkája automatikusan különbözik. A válasz a legkisebb excentricitás, vagyis a komponensgráf sugara. Komponensek: összefüggő, azonos színű részek (DFS vagy DSU), távolságok: BFS minden komponensből, O(N·(N+M)) tesztesetenként.
*/
/*
Hint 1: || Egy átváltás nem csak egy embert érint: a vele azonos italt kedvelő, vele összefüggő emberek mindegyike vált. Fogd össze az azonos italú, összefüggő bergengócokat egy-egy csúccsá, és gondolkodj az így kapott gráfon. ||
Hint 2: || Két ital esetén mindig ugyanazt a komponenst érdemes váltogatni: minden váltással összeolvad az összes szomszédjával, a váltott komponens színe pedig minden héten megfordul, így a márkák váltakozása magától teljesül. ||
Hint 3: || Ha az v komponenssel kezdesz, a hetek száma a tőle legtávolabbi komponens távolsága. Számold ki BFS-sel minden komponensre ezt az excentricitást (N ≤ 100), és a válasz a minimum. ||
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
        vector<int> b(n);
        for (int &x : b) cin >> x;
        vector<vector<int>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // azonos színű, összefüggő komponensek (DFS)
        vector<int> comp(n, -1);
        int k = 0;
        for (int s = 0; s < n; s++) {
            if (comp[s] != -1) continue;
            vector<int> st = {s};
            comp[s] = k;
            while (!st.empty()) {
                int u = st.back();
                st.pop_back();
                for (int w : adj[u]) {
                    if (comp[w] == -1 && b[w] == b[u]) {
                        comp[w] = k;
                        st.push_back(w);
                    }
                }
            }
            k++;
        }

        // a komponensek gráfja
        vector<vector<char>> has(k, vector<char>(k, 0));
        vector<vector<int>> cadj(k);
        for (int u = 0; u < n; u++) {
            for (int w : adj[u]) {
                int a = comp[u], c = comp[w];
                if (a != c && !has[a][c]) {
                    has[a][c] = has[c][a] = 1;
                    cadj[a].push_back(c);
                    cadj[c].push_back(a);
                }
            }
        }

        // legkisebb excentricitás (a komponensgráf sugara)
        int best = INT_MAX;
        for (int s = 0; s < k; s++) {
            vector<int> dist(k, -1);
            queue<int> q;
            dist[s] = 0;
            q.push(s);
            int ecc = 0;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                ecc = max(ecc, dist[u]);
                for (int w : cadj[u]) {
                    if (dist[w] == -1) {
                        dist[w] = dist[u] + 1;
                        q.push(w);
                    }
                }
            }
            best = min(best, ecc);
        }
        cout << best << '\n';
    }
    return 0;
}
