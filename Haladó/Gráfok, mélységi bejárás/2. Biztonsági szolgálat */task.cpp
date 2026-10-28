/*
Megoldás lényege:
Egy kereszteződés pontosan akkor szerepel valamelyik A-ból B-be vezető egyszerű úton, ha benne van egy olyan kétszeresen összefüggő részben (blokkban), amely a blokk-vágópont fán az A és B közötti úton van. Ezért először Tarjan módszerével, mélységi bejárással (lowpoint-értékekkel és veremmel) megkeressük a blokkokat; a bejárás iteratív, így nagy N esetén sem okoz veremtúlcsordulást. Ezután BFS-sel megkeressük az A és B közötti utat a blokkok és csúcsok kétoldalú gráfjában, és az úton lévő blokkok csúcsait gyűjtjük. A végpontokat (A és B) kihagyjuk a kimenetből. Az idő O(N + M).
*/
/*
Hint 1: || Keresd meg a gráf kétszeresen összefüggő részeit (blokkjait) mélységi bejárással: a lowpoint-értékek megmutatják, mikor záródik egy blokk. ||
Hint 2: || Az A-ból B-be vezető utak csak azokon a blokkokon haladhatnak át, amelyek a blokkok és vágópontok fáján az A és B közötti úton vannak. Ezt BFS-sel kapod meg, A-ból kiindulva. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int A, B;
    cin >> A >> B;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Tarjan-féle blokkbontás, iteratív mélységi bejárással, vertex-veremmel.
    vector<int> disc(n + 1, 0), low(n + 1, 0), par(n + 1, 0), itIdx(n + 1, 0);
    vector<vector<int>> blocks;
    vector<int> vstack, callstack;
    int timer = 0;

    disc[A] = low[A] = ++timer;
    vstack.push_back(A);
    callstack.push_back(A);
    while (!callstack.empty()) {
        int u = callstack.back();
        if (itIdx[u] < (int)adj[u].size()) {
            int w = adj[u][itIdx[u]++];
            if (w == par[u]) continue;
            if (!disc[w]) {
                par[w] = u;
                disc[w] = low[w] = ++timer;
                vstack.push_back(w);
                callstack.push_back(w);
            } else {
                low[u] = min(low[u], disc[w]);
            }
        } else {
            callstack.pop_back();
            if (!callstack.empty()) {
                int p = callstack.back();
                low[p] = min(low[p], low[u]);
                if (low[u] >= disc[p]) {
                    vector<int> block = {p};
                    while (true) {
                        int x = vstack.back();
                        vstack.pop_back();
                        block.push_back(x);
                        if (x == u) break;
                    }
                    blocks.push_back(block);
                }
            }
        }
    }

    // Kétoldalú gráf: csúcsok (1..n) és blokkok (n+1..n+K). BFS A-ból B-be.
    int K = blocks.size();
    vector<vector<int>> inc(n + K + 1);
    for (int b = 0; b < K; ++b)
        for (int x : blocks[b]) {
            inc[x].push_back(n + 1 + b);
            inc[n + 1 + b].push_back(x);
        }

    vector<int> from(n + K + 1, -1);
    queue<int> q;
    from[A] = A;
    q.push(A);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int y : inc[x])
            if (from[y] == -1) {
                from[y] = x;
                q.push(y);
            }
    }

    vector<char> chosen(n + 1, 0);
    if (from[B] != -1) {
        // A B felől visszafelé követjük az utat, és a rajta lévő blokkok csúcsait jelöljük.
        int cur = B;
        while (cur != A) {
            if (cur > n) {
                for (int x : blocks[cur - n - 1]) chosen[x] = 1;
            }
            cur = from[cur];
        }
    }

    vector<int> ans;
    for (int x = 1; x <= n; ++x)
        if (chosen[x] && x != A && x != B) ans.push_back(x);

    cout << ans.size() << "\n";
    for (size_t i = 0; i < ans.size(); ++i) cout << ans[i] << (i + 1 < ans.size() ? ' ' : '\n');
    if (ans.empty()) cout << "\n";
    return 0;
}
