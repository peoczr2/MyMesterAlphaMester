/*
Megoldás lényege:
Egy t város pontosan akkor kap járatot, ha van olyan egyszerű út 1-ből t-be, amely látványosságot tartalmazó élen halad át. Az úthálózatot blokkokra (2-összefüggő részekre) bontjuk. Egy egyszerű 1-ből t-be vezető út pontosan azokon a blokkokon megy át, amelyek a blokk-csúcs fa 1-től t-ig vezető szakaszán vannak. Egy 2-összefüggő blokkban bármely belépő és kilépő csúcspár között van olyan egyszerű út, amely egy adott élen halad át, ezért elég azt nézni, hogy az 1-ből t-be vezető blokkok között van-e látványosságot tartalmazó. Tarjan-féle élverem-algoritmussal, 1-ből indított iteratív mélységi bejárással találjuk meg a blokkokat, majd a DFS-fa élein felülről lefelé terjesztjük a jelzést. Az időigény O(N + M).
*/
/*
Hint 1: || Bontsd az úthálózatot kétszeresen összefüggő részekre (blokkokra). Egy egyszerű út a blokkok fáján halad végig, és minden blokkban egy belépő és egy kilépő csúcs között megy. Keresd meg ezeket a blokkokat. ||
Hint 2: || Ha egy blokk legalább 2-összefüggő, akkor bármely két csúcsa között van olyan út, amely egy adott élen megy át. Így t jó, ha az 1-ből t-be vezető blokkok között van látványosságot tartalmazó. ||
Hint 3: || Tarjan-féle élverem-algoritmussal találd meg a blokkokat egy 1-ből indított mélységi bejárásban, és a blokkok élei alapján jelöld meg a látványosságos blokkokat. Ezután a DFS-fán felülről lefelé terjeszd a jelzést. Iteratív bejárást használj, mert N akár 40000. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> ea(m), eb(m);
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        cin >> ea[i] >> eb[i];
        adj[ea[i]].push_back({eb[i], i});
        adj[eb[i]].push_back({ea[i], i});
    }

    vector<int> disc(n + 1, 0), low(n + 1, 0), par(n + 1, 0), parEdge(n + 1, -1), itPos(n + 1, 0);
    vector<int> blockOfEdge(m, -1);
    vector<char> blockSight;     // blockSight[b] = 1, ha a b. blokkban van látványosság
    vector<int> order;           // DFS-sorrend
    vector<int> estack;          // élverem
    vector<int> callStack;
    int timer = 0;

    disc[1] = low[1] = ++timer;
    order.push_back(1);
    callStack.push_back(1);
    while (!callStack.empty()) {
        int v = callStack.back();
        if (itPos[v] < (int)adj[v].size()) {
            auto [to, e] = adj[v][itPos[v]++];
            if (e == parEdge[v]) continue;          // a szülőhöz vezető faél
            if (disc[to] == 0) {                    // faél
                estack.push_back(e);
                parEdge[to] = e;
                par[to] = v;
                disc[to] = low[to] = ++timer;
                order.push_back(to);
                callStack.push_back(to);
            } else if (disc[to] < disc[v]) {        // visszaél egy felmenő csúcsra
                estack.push_back(e);
                low[v] = min(low[v], disc[to]);
            }
        } else {
            callStack.pop_back();
            if (v != 1) {
                int p = par[v];
                low[p] = min(low[p], low[v]);
                if (low[v] >= disc[p]) {            // a p-hez tartozó blokk lezárul
                    int b = (int)blockSight.size();
                    blockSight.push_back(0);
                    while (true) {
                        int e = estack.back();
                        estack.pop_back();
                        blockOfEdge[e] = b;
                        if (e < k) blockSight[b] = 1;
                        if (e == parEdge[v]) break;
                    }
                }
            }
        }
    }

    // f[v] = 1, ha az 1-ből v-be vezető DFS-fa úton van látványosságos blokk.
    vector<char> f(n + 1, 0);
    for (size_t i = 1; i < order.size(); i++) {
        int v = order[i];
        f[v] = f[par[v]] || blockSight[blockOfEdge[parEdge[v]]];
    }

    vector<int> ans;
    for (int v = 2; v <= n; v++) {
        if (f[v]) ans.push_back(v);
    }

    cout << ans.size() << '\n';
    for (size_t i = 0; i < ans.size(); i++) {
        cout << ans[i] << (i + 1 < ans.size() ? ' ' : '\n');
    }
    if (ans.empty()) cout << '\n';
    return 0;
}
