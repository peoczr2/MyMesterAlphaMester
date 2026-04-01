#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
Minden folyó legfeljebb egy másikba folyik bele, ezért a rendszer egy irányított
erdei fa. Az F folyóba beérkező összes víz forrásai pontosan azok a csúcsok,
amelyekből az ellentétes irányú gráfban elérhető F.

A F-ből induló szennyezés pedig a folyásirány szerinti utódokat éri el. A két
halmazt két egyszerű DFS/BFS bejárással megkapjuk, majd növekvő sorrendben kiírjuk.

Hint 1: || A folyók be- és kifolyási kapcsolatai két külön bejárással kezelhetők. ||
Hint 2: || Az egyik bejárás a fordított éleken halad, a másik az eredeti éleken. ||
Hint 3: || Mivel minden folyó legfeljebb egy másikba folyik bele, az eredeti gráf nagyon egyszerű. ||
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, F;
    cin >> N >> M >> F;
    vector<vector<int>> rev(N + 1), orig(N + 1);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        orig[a].push_back(b);
        rev[b].push_back(a);
    }

    auto collect = [&](const vector<vector<int>>& g, int start) {
        vector<int> vis(N + 1, 0), res;
        stack<int> st;
        st.push(start);
        vis[start] = 1;
        while (!st.empty()) {
            int u = st.top(); st.pop();
            res.push_back(u);
            for (int v : g[u]) {
                if (!vis[v]) {
                    vis[v] = 1;
                    st.push(v);
                }
            }
        }
        sort(res.begin(), res.end());
        return res;
    };

    vector<int> source = collect(rev, F);
    vector<int> sink = collect(orig, F);
    source.erase(remove(source.begin(), source.end(), F), source.end());
    sink.erase(remove(sink.begin(), sink.end(), F), sink.end());

    cout << source.size();
    for (int x : source) cout << ' ' << x;
    cout << '\n';

    cout << sink.size();
    for (int x : sink) cout << ' ' << x;
    cout << '\n';
    return 0;
}