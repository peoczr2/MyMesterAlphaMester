/*
Megoldás lényege: a bűnöző minden városba legfeljebb egyszer ér, ezért U-ból V-n át csak egyszerű úton juthat el a jelenlegi helyére.
Egy w város pontosan akkor lehet a bűnöző helye, ha létezik olyan egyszerű út U-ból w-be, amely átmegy V-n.
Az egyszerű utak a kétszeresen összefüggő részeken (blokkokon) belül szabadon bejárhatók, a blokkok között pedig a vágópontokon haladnak át.
Ezért a mélységi bejárás fáját U-ból gyökerezzük, és egy csúcs akkor jó, ha a gyökértől vezető úton van olyan blokk, amely tartalmazza V-t.
A blokkokat Tarjan-féle algoritmussal kapjuk, az időigény O(N + M).
*/
/*
Hint 1: || A bűnöző nem járhat kétszer ugyanabban a városban, ezért nem térhet vissza U-ba. Egy útvonal akkor jó, ha minden városon csak egyszer halad át. ||
Hint 2: || Egy kétszeresen összefüggő részben (blokkban) bármely három különböző csúcs között van egyszerű út, így a blokkon belül bármelyik csúcson át lehet menni. Ezért elég megnézni, hogy az U-ból w-be vezető úton van-e olyan blokk, amely tartalmazza V-t. ||
Hint 3: || Tarjan-algoritmussal a mélységi bejárás közben csúcsveremmel a blokkokat zárd le: ha low[v] >= tin[u], akkor u és v alatti csúcsok új blokkot alkotnak u-val együtt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, m, U, V;
vector<vector<int>> g;
vector<int> tin, low, blockOf, stk, order_;
vector<int> blockTop;  // blokk -> a blokk felső (vágó)csúcsa
int timerCnt = 0;

void dfs(int u) {
    tin[u] = low[u] = ++timerCnt;
    order_.push_back(u);
    stk.push_back(u);
    for (int v : g[u]) {
        if (tin[v] == 0) {
            dfs(v);
            low[u] = min(low[u], low[v]);
            if (low[v] >= tin[u]) {
                int id = (int)blockTop.size();
                blockTop.push_back(u);
                while (true) {
                    int x = stk.back();
                    stk.pop_back();
                    blockOf[x] = id;
                    if (x == v) break;
                }
            }
        } else {
            low[u] = min(low[u], tin[v]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> U >> V;
    g.assign(n + 1, {});
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    tin.assign(n + 1, 0);
    low.assign(n + 1, 0);
    blockOf.assign(n + 1, -1);
    dfs(U);

    // ok[x]: létezik-e U-ból x-be egyszerű út, amely átmegy V-n
    vector<char> ok(n + 1, 0);
    for (int x : order_) {
        if (x == U) continue;
        int b = blockOf[x];
        int t = blockTop[b];
        bool inBlock = (t == V) || (blockOf[V] == b);
        ok[x] = (inBlock || ok[t]) ? 1 : 0;
    }

    vector<int> ans;
    for (int x = 1; x <= n; ++x)
        if (x != U && ok[x]) ans.push_back(x);

    cout << ans.size() << "\n";
    for (size_t i = 0; i < ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << "\n";
    return 0;
}
