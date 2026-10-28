/*
Megoldás lényege:
Minden két kimenetű csúcs pontosan egy szerkezetet (elágazást vagy feltételes ciklust) jelöl, ezért az elágazások száma a két kimenetű csúcsok számából kivonva a ciklusok számát adja.
A ciklusok száma egy mélységi bejárással (DFS) számolható a kezdőpontból: minden feltételes ciklust pontosan egy visszaél zár, vagyis olyan él, amely a bejárás aktuális útjában szereplő csúcsba mutat.
Az erősen összefüggő komponensek alapján nem lehet elágazást és ciklust megkülönböztetni, mert egy elágazás mindkét ága lehet ugyanabban a ciklusban; a visszaélek számlálása ezt is helyesen kezeli.
A bejárást veremmel, rekurzió nélkül végezzük, az időigény O(N + M).
*/
/*
Hint 1: || Minden két kimenetű csúcs pontosan egy szerkezet döntési pontja: vagy elágazás, vagy ciklus. Ha a ciklusok számát tudod, az elágazásokat a két kimenetű csúcsok számából történő kivonással kapod. ||
Hint 2: || Egy mélységi bejárás során egy él akkor zár ciklust, ha olyan csúcsba mutat, amely még a bejárás aktuális útvonalán van. Ezeket az éleket számold meg. ||
Hint 3: || A bejárást veremmel is megírhatod: csúcsonként tárold, hogy új, az aktuális úton lévő vagy már befejezett-e, és minden csúcsnál a következő kimenő élt egy számlálóval jelöld. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    vector<int> indeg(n + 1, 0), outdeg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        ++indeg[v];
        ++outdeg[u];
    }

    // Mélységi bejárás a kezdőpontból: minden feltételes ciklust pontosan egy
    // visszaél zár, ezért a visszaélek száma a ciklusok száma.
    vector<int> state(n + 1, 0), pos(n + 1, 0);  // 0: új, 1: a veremben, 2: kész
    int loops = 0;
    vector<int> roots;
    for (int v = 1; v <= n; ++v) if (indeg[v] == 0) roots.push_back(v);
    for (int v = 1; v <= n; ++v) roots.push_back(v);
    for (int s : roots) {
        if (state[s]) continue;
        vector<int> st = {s};
        state[s] = 1;
        while (!st.empty()) {
            int u = st.back();
            if (pos[u] < (int)g[u].size()) {
                int v = g[u][pos[u]++];
                if (state[v] == 1) ++loops;
                else if (state[v] == 0) {
                    state[v] = 1;
                    st.push_back(v);
                }
            } else {
                state[u] = 2;
                st.pop_back();
            }
        }
    }

    int decisions = 0;
    for (int u = 1; u <= n; ++u) if (outdeg[u] == 2) ++decisions;

    cout << loops << '\n' << decisions - loops << '\n';
    return 0;
}
