/*
Megoldás lényege:
Egy útvonal olyan kezdőtáborból indul, ahová nem vezet szakasz, és olyan csúcsnál ér véget, ahonnan nem indul szakasz.
Elszigetelt tábor (se be-, se kimenő szakasz) nem alkot útvonalat. A gráf körmentes, ezért a táborokat topologikus
sorrendben (Kahn-algoritmussal) dolgozzuk fel. Minden tábor értéke azt adja meg, hány olyan útvonal vezet oda, amely
valamelyik kezdőtáborból indul: a kezdőtáborok értéke 1, a többié a bemenő szakaszok kezdőpontjainak értékeinek összege.
A csúcsok értékeinek összege adja a keresett számot, amelyet 20200721-gyel vett maradékban írunk ki. Az időigény O(N + M).
*/
/*
Hint 1: || Egy útvonal mindig egy kezdőtáborból indul és egy csúcsnál ér véget. Ha a táborokat olyan sorrendben dolgozod fel,
hogy minden szakasz kezdőpontja előbb kerüljön sorra, akkor egy táborba vezető útvonalak száma az előző táborokba vezető
útvonalak számából összegezhető. ||
Hint 2: || A kezdőtáborok értéke 1, a többi táboré a bemenő szakaszok kezdőpontjainak értékeinek összege, mindig 20200721
szerinti maradékban. A végső válasz a csúcsok értékeinek összege; az elszigetelt táborokat ne számold bele. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const long long MOD = 20200721;

    int n, m;
    cin >> n >> m;

    vector<vector<int>> out(n + 1);
    vector<int> indeg(n + 1, 0), outdeg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        out[u].push_back(v);
        ++indeg[v];
        ++outdeg[u];
    }

    // Topologikus sorrend (Kahn-algoritmus).
    vector<int> order;
    order.reserve(n);
    vector<int> remaining(indeg);
    for (int v = 1; v <= n; ++v) {
        if (remaining[v] == 0) {
            order.push_back(v);
        }
    }
    for (size_t i = 0; i < order.size(); ++i) {
        for (int w : out[order[i]]) {
            if (--remaining[w] == 0) {
                order.push_back(w);
            }
        }
    }

    // ways[v]: a kezdőtáborokból v-be vezető útvonalak száma (modulo MOD).
    vector<long long> ways(n + 1, 0);
    for (int v = 1; v <= n; ++v) {
        if (indeg[v] == 0 && outdeg[v] > 0) {
            ways[v] = 1;
        }
    }
    for (int v : order) {
        for (int w : out[v]) {
            ways[w] = (ways[w] + ways[v]) % MOD;
        }
    }

    // Az útvonalak a csúcsoknál (kimenő szakasz nélküli, de bemenő szakasszal rendelkező táborok) érnek véget.
    long long answer = 0;
    for (int v = 1; v <= n; ++v) {
        if (outdeg[v] == 0 && indeg[v] > 0) {
            answer = (answer + ways[v]) % MOD;
        }
    }

    cout << answer << '\n';
    return 0;
}
