/*
Megoldás lényege:
A kész hálózatban bármely két csomópont között pontosan egy egyszerű irányított út van, ezért minden él legfeljebb egy irányított körben lehet. Így az erősen összefüggő komponensek (SCC) belsejében a kört adó élek nem vihetnek új utat, a komponensek közötti élek pedig egyetlen láncot alkotnak: a forráskomponensből a nyelőkomponensbe vezető utat. A hiányzó P→Q élnek ezt az utat kell lezárnia, ezért Q a forráskomponensből kivezető él kezdőpontja, P pedig a nyelőkomponensbe bevezető él végpontja. Az SCC-ket Tarjan-algoritmussal, mélységi bejárással számoljuk ki (iteratív verzióval, hogy a mélység ne okozzon vermelést), majd a komponensek közötti éleket végignézzük. Az idő O(N+M).
*/
/*
Hint 1: || Az erősen összefüggő komponensek keresése mélységi bejárással, a Tarjan-algoritmussal történik. Mindegyik komponens belsejében minden él kör része, ezért a körön kívüli éleket kell vizsgálnod. ||
Hint 2: || Ezek az élek egyetlen irányított láncot alkotnak a komponensek között. A lánc kezdő komponensének kivezető élének kezdőpontja, illetve a végső komponens bevezető élének végpontja adja a két keresett csúcsot. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    vector<pair<int, int>> edges(m);
    for (auto &[u, v] : edges) {
        cin >> u >> v;
        g[u].push_back(v);
    }

    // Tarjan-algoritmus, iteratív verzióval.
    vector<int> idx(n + 1, -1), low(n + 1, 0), comp(n + 1, -1);
    vector<char> onStack(n + 1, 0);
    vector<int> st;
    int timer = 0, numComp = 0;
    for (int s = 1; s <= n; ++s) {
        if (idx[s] != -1) continue;
        vector<pair<int, int>> call;  // (csúcs, következő él indexe)
        idx[s] = low[s] = timer++;
        st.push_back(s);
        onStack[s] = 1;
        call.push_back({s, 0});
        while (!call.empty()) {
            int v = call.back().first;
            if (call.back().second < (int)g[v].size()) {
                int w = g[v][call.back().second++];
                if (idx[w] == -1) {
                    idx[w] = low[w] = timer++;
                    st.push_back(w);
                    onStack[w] = 1;
                    call.push_back({w, 0});
                } else if (onStack[w]) {
                    low[v] = min(low[v], idx[w]);
                }
            } else {
                if (low[v] == idx[v]) {
                    while (true) {
                        int x = st.back();
                        st.pop_back();
                        onStack[x] = 0;
                        comp[x] = numComp;
                        if (x == v) break;
                    }
                    ++numComp;
                }
                call.pop_back();
                if (!call.empty()) {
                    int p = call.back().first;
                    low[p] = min(low[p], low[v]);
                }
            }
        }
    }

    // A komponensek közötti élek: hány él megy be és ki az egyes komponensekbe.
    vector<int> inCnt(numComp, 0), outCnt(numComp, 0);
    for (auto &[u, v] : edges) {
        if (comp[u] != comp[v]) {
            outCnt[comp[u]]++;
            inCnt[comp[v]]++;
        }
    }

    // Q: a forráskomponensből kivezető él kezdőpontja; P: a nyelőkomponensbe bevezető él végpontja.
    int P = 0, Q = 0;
    for (auto &[u, v] : edges) {
        if (comp[u] == comp[v]) continue;
        if (inCnt[comp[u]] == 0) Q = u;
        if (outCnt[comp[v]] == 0) P = v;
    }

    cout << P << " " << Q << "\n";
    return 0;
}
