/*
Megoldás lényege:
A programgráfban minden ciklusnak pontosan egy visszamutató éle van, így a ciklusok száma mélységi bejárásból, a verem (aktív úton lévő csúcsok) állapotát figyelve, a visszamutató élek számolásával adódik. Minden ciklusnak pontosan egy kétkimenetű csúcsa van, ahonnan a ciklusból ki lehet lépni (a ciklus feltétele), a többi kétkimenetű csúcs elágazás. Így az elágazások száma a kétkimenetű csúcsok számából levonva a ciklusok számát adódik. Az időigény O(N+M).
*/
/*
Hint 1: || Egy ciklusnak pontosan egy visszamutató éle van, amely egy még az aktív úton lévő csúcsba mutat. Mélységi bejárással ezeket megszámolhatod. ||
Hint 2: || Ha egy csúcsnak két kimenő éle van, az vagy elágazás, vagy egy ciklus kilépési pontja. Minden ciklusnak pontosan egy ilyen kilépési pontja van, így az elágazások száma a kétkimenetű csúcsok száma mínusz a ciklusok száma. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> eu(m), ev(m), start(n + 2, 0);
    for (int i = 0; i < m; ++i) {
        cin >> eu[i] >> ev[i];
        start[eu[i] + 1]++;
    }
    for (int v = 1; v <= n + 1; ++v) start[v] += start[v - 1];
    vector<int> adj(m);
    {
        vector<int> pos(start);
        for (int i = 0; i < m; ++i) adj[pos[eu[i]]++] = ev[i];
    }

    // Iteratív mélységi bejárás. state: 0 = még nem volt, 1 = az aktív úton van, 2 = kész.
    // Az aktív útra mutató él visszamutató él, minden ilyen él egy ciklust jelent.
    vector<int> state(n + 1, 0), it(n + 1, 0);
    long long loops = 0;
    for (int s = 1; s <= n; ++s) {
        if (state[s]) continue;
        vector<int> st{s};
        state[s] = 1;
        it[s] = start[s];
        while (!st.empty()) {
            int v = st.back();
            if (it[v] < start[v + 1]) {
                int w = adj[it[v]++];
                if (state[w] == 0) {
                    state[w] = 1;
                    it[w] = start[w];
                    st.push_back(w);
                } else if (state[w] == 1) {
                    ++loops;
                }
            } else {
                state[v] = 2;
                st.pop_back();
            }
        }
    }

    long long twoOut = 0;
    for (int v = 1; v <= n; ++v)
        if (start[v + 1] - start[v] == 2) ++twoOut;

    cout << loops << '\n' << twoOut - loops << '\n';
    return 0;
}
