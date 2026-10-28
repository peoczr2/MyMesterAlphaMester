/*
Megoldás lényege:
Az utolsó állapotban az A rész egy összefüggő részfa mérete pontosan N/2.
Ha egy összefüggő részfát nézünk, akkor a minimális vágások száma azokat az
éleket számolja, amelyek a kiválasztott részfa és a komplementer rész között
vezetnek. Ezt egy fa-DP számolja ki.

Minden csúcs u-ra azokat az összefüggő részfákat tartjuk nyilván, amelyek u-t
is tartalmazzák, és u gyökerű részfában vannak. dp[u][s] a legkisebb határélszám,
ha pontosan s csúcsot választunk u-ból lefelé. Egy gyermekre két lehetőség van:
vagy egyáltalán nem választunk onnan csúcsot (ekkor az u-v él vágás, +1 költség),
vagy a gyermekből is választunk egy összefüggő részfát, amely tartalmazza a gyereket
(ekkor a gyermek dp-je adja a költséget, és az u-v él belső él lesz).
*/
/*
Hint 1: || A kérdés: van-e olyan összefüggő, N/2 csúcsú részfa, amelynek a többi csúcshoz vezető éleinek száma a legkisebb. Gyökerezd a fát egy csúcsban; a részfa felső csúcsának szülőéle is határél lesz. ||
Hint 2: || Fa-DP: dp[v][s] legyen a legkisebb határélszám, ha a v gyökerű részfából pontosan s csúcsot választunk úgy, hogy a kiválasztott rész tartalmazza v-t. Egy gyermeket vagy kihagyunk (ekkor az élére +1 jár), vagy beveszünk a gyermek dp-jéből. ||
Hint 3: || A gyermekek összevonását a méretek szerint végezd: az összes összevonás költsége O(N²), ami N ≤ 4000 mellett elég. A válasz a dp[v][N/2] minimuma minden v-re, a v ≠ 1 csúcsoknál a szülőéllel együtt. ||
*/
#include <bits/stdc++.h>
using namespace std;

static const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> parent(n + 1, 0), order;
    order.reserve(n);
    stack<int> st;
    st.push(1);
    parent[1] = -1;
    while (!st.empty()) {
        int v = st.top();
        st.pop();
        order.push_back(v);
        for (int to : g[v]) {
            if (to == parent[v]) continue;
            parent[to] = v;
            st.push(to);
        }
    }

    vector<int> sz(n + 1, 1);
    vector<vector<int>> dp(n + 1);
    for (int idx = n - 1; idx >= 0; --idx) {
        int v = order[idx];
        vector<int> cur(2, INF);
        cur[1] = 0;
        int curSize = 1;

        for (int to : g[v]) {
            if (to == parent[v]) continue;
            vector<int> nxt(curSize + sz[to] + 1, INF);

            for (int used = 1; used <= curSize; ++used) {
                if (cur[used] >= INF) continue;
                nxt[used] = min(nxt[used], cur[used] + 1);
                for (int take = 1; take <= sz[to]; ++take) {
                    if (dp[to][take] >= INF) continue;
                    nxt[used + take] = min(nxt[used + take], cur[used] + dp[to][take]);
                }
            }

            cur.swap(nxt);
            curSize += sz[to];
        }

        sz[v] = curSize;
        dp[v] = move(cur);
    }

    int target = n / 2;
    int answer = INF;
    for (int v = 1; v <= n; ++v) {
        if (target < (int)dp[v].size()) {
            int extra = (v == 1 ? 0 : 1);
            answer = min(answer, dp[v][target] + extra);
        }
    }

    cout << answer << '\n';
    return 0;
}