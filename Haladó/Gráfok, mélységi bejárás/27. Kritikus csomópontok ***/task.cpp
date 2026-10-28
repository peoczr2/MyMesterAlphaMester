/*
Megoldás lényege:
A-ból mélységi bejárást végzünk, és minden csúcsra kiszámítjuk a disc (bejárási sorszám) és a low (a részfából visszaéllel elérhető legkisebb sorszám) értékét. Ha B nem érhető el A-ból, a válasz -1. Különben a fában az A-tól B-ig vezető úton állnak a jelöltek. Egy P csúcs (P != A, P != B) akkor kritikus, ha az úton a P utáni c csúcs részfájából nincs visszaél P fölé, vagyis low[c] >= disc[P]. Ezeket a B-ből az A felé haladva gyűjtjük össze. Az időigény O(N+M).
*/
/*
Hint 1: || Először azt döntsd el, hogy A és B egyáltalán összeköthető-e, mert ha nem, a válasz -1, és nincs több teendő. ||
Hint 2: || Mélységi bejárással A-ból minden csúcsnak határozd meg a bejárási sorszámát és azt, hogy a részfájából visszaéllel hová lehet feljutni. ||
Hint 3: || Az A-ból B-be vezető fa-úton B-től A felé haladva minden P csúcsra nézd meg, hogy a rá következő gyerek low értéke nem kisebb-e P sorszámánál; ha igen, P kritikus. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, A, B;
    cin >> n >> m >> A >> B;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Mélységi bejárás A-ból (iteratívan): disc, low, szülő.
    vector<int> disc(n + 1, -1), low(n + 1, 0), par(n + 1, 0), it(n + 1, 0);
    int timer = 0;
    vector<int> st;
    disc[A] = low[A] = timer++;
    st.push_back(A);
    while (!st.empty()) {
        int v = st.back();
        if (it[v] < (int)adj[v].size()) {
            int w = adj[v][it[v]++];
            if (w == par[v]) continue;
            if (disc[w] == -1) {
                par[w] = v;
                disc[w] = low[w] = timer++;
                st.push_back(w);
            } else {
                low[v] = min(low[v], disc[w]);
            }
        } else {
            st.pop_back();
            if (par[v] != 0) low[par[v]] = min(low[par[v]], low[v]);
        }
    }

    if (disc[B] == -1) {
        cout << -1 << '\n';
        return 0;
    }

    // Az A-B fa-úton B-től A felé: P kritikus, ha a rá következő c részfájából nincs visszaél P fölé.
    vector<int> res;
    int c = B, p = par[B];
    while (p != 0 && p != A) {
        if (low[c] >= disc[p]) res.push_back(p);
        c = p;
        p = par[p];
    }
    sort(res.begin(), res.end());

    cout << res.size() << '\n';
    for (size_t i = 0; i < res.size(); ++i) {
        if (i) cout << ' ';
        cout << res[i];
    }
    cout << '\n';
    return 0;
}
