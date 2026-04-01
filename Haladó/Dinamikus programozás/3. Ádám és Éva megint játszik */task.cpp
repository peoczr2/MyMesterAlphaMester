/*
Ez egy véges hosszúságú, kétszereplős, zéróösszegű játék egy irányítatlan vagy irányított gráfon.
Legyen A[t][u] az a legjobb összpontszám-változás, amelyet Ádám biztosan elér az u csúcsról indulva,
amikor még t saját lépése és t Éva-lépése van hátra, és most Ádám következik. Legyen E[t][u] ugyanez
akkor, amikor Éva következik: ekkor ő a lehető legrosszabb utódot választja, tehát minimumot veszünk.
Az átmenetek így közvetlenül a minimax elvet követik, és O(K*E) időben kiszámolhatók.
*/
/*
Hint 1: || Külön állapot kell arra, amikor Ádám lép, és arra is, amikor Éva lép. ||
Hint 2: || Ádám maximumot, Éva minimumot választ az elérhető szomszédok között. ||
Hint 3: || Ha már nincs több Ádám-lépés hátra, onnantól a további hozzájárulás 0. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<long long> value(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> value[i];
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; ++i) {
        int v;
        while (cin >> v && v != 0) {
            adj[i].push_back(v);
        }
    }

    vector<long long> adam(n + 1, 0), eva(n + 1, 0), next_adam(n + 1), next_eva(n + 1);

    for (int step = 1; step <= k; ++step) {
        for (int u = 1; u <= n; ++u) {
            long long worst = LLONG_MAX;
            for (int v : adj[u]) {
                worst = min(worst, adam[v] - value[v]);
            }
            next_eva[u] = worst;
        }
        for (int u = 1; u <= n; ++u) {
            long long best = LLONG_MIN;
            for (int v : adj[u]) {
                best = max(best, value[v] + next_eva[v]);
            }
            next_adam[u] = best;
        }
        adam.swap(next_adam);
        eva.swap(next_eva);
    }

    cout << adam[1] << '\n';
    return 0;
}