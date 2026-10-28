/*
Megoldás lényege:
Egy útvonalrészlet pontjai közül az utolsó kivételével mindegyikből legfeljebb egy él indul, ezért egy elágazás nélküli szakasz
kezdőpontjából egyértelmű a folytatás. Minden olyan csomópontból, amelyből pontosan egy él indul, az egyetlen kimenő éleken
haladva a szakasz addig folytatható, amíg el nem érünk egy olyan csomópontot, amelyből nem pontosan egy él indul: ez a szakasz
végpontja. A szakasz rövidebb részei nem lehetnek hosszabbak, így minden kezdőponthoz a teljes lánc a leghosszabb.
A gráf körmentes, ezért Kahn-algoritmussal topologikus sorrendet kapunk, és ebben fordított sorrendben kiszámoljuk minden
csomópontra a belőle induló lánc hosszát és végpontját. A maximumot úgy keressük, hogy holtverseny esetén a kisebb kezdőpont nyerjen.
Az időigény O(N + M).
*/
/*
Hint 1: || Az elágazás nélküli szakasz minden pontjából (az utolsó kivételével) pontosan egy él vezet ki, így a kezdőpontból
is csak egy irányba lehet továbbmenni. Gondold végig, meddig tart a szakasz egy ilyen kezdőponttól. ||
Hint 2: || Dolgozd fel a csomópontokat a topologikus sorrend fordítottjában: egy egyetlen kimenő élű v csomópont szakaszának hossza
az él hossza plusz a következő csomópont szakaszának hossza, a végpontja pedig a következő csomópont végpontja. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, long long>>> out(n + 1);
    vector<int> indeg(n + 1, 0), outdeg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int k, v;
        long long h;
        cin >> k >> v >> h;
        out[k].push_back({v, h});
        ++indeg[v];
        ++outdeg[k];
    }

    // Topologikus sorrend (Kahn-algoritmus).
    vector<int> order;
    order.reserve(n);
    vector<int> remaining = indeg;
    for (int v = 1; v <= n; ++v) {
        if (remaining[v] == 0) {
            order.push_back(v);
        }
    }
    for (size_t i = 0; i < order.size(); ++i) {
        for (const auto& [w, h] : out[order[i]]) {
            if (--remaining[w] == 0) {
                order.push_back(w);
            }
        }
    }

    // len[v]: az elágazás nélküli szakasz hossza v-től, term[v]: a szakasz végpontja.
    // Ha v-ből nem pontosan egy él indul, a szakasz üres: len = 0, term = v.
    vector<long long> len(n + 1, 0);
    vector<int> term(n + 1);
    for (int v = 1; v <= n; ++v) {
        term[v] = v;
    }
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int v = order[i];
        if (outdeg[v] == 1) {
            auto [w, h] = out[v][0];
            len[v] = h + len[w];
            term[v] = term[w];
        }
    }

    long long bestLen = -1;
    int bestStart = 0, bestEnd = 0;
    for (int v = 1; v <= n; ++v) {
        if (outdeg[v] == 1 && len[v] > bestLen) {
            bestLen = len[v];
            bestStart = v;
            bestEnd = term[v];
        }
    }

    cout << bestStart << ' ' << bestEnd << '\n';
    return 0;
}
