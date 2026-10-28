/*
Megoldás lényege:
Minden utcát két irányított élnek tekintünk, az u->v és a v->u irányt. Ebben az irányított gráfban minden pont be- és kifoka megegyezik az eredeti fokszámával, és a gráf összefüggő, ezért létezik Euler-kör, amely minden irányított élt pontosan egyszer használ. Ezt a Hierholzer-algoritmussal keressük: veremmel haladunk egy még nem használt kimenő élen, és amikor egy pontból nincs több kimenő él, a pontot az eredménylistába tesszük. Az eredménylista fordított sorrendje az 1. pontból induló és oda visszatérő útvonal. Mivel 2M irányított élünk van, a kimenet 2M + 1 szám. Az időigény O(N + M).
*/
/*
Hint 1: || Minden utcát tekints két irányított élnek (oda és vissza). Így az utcaseprő útja egy irányított gráf Euler-köre lesz. ||
Hint 2: || Hierholzer-algoritmus: a veremből mindig egy még nem bejárt kimenő élen lépj tovább, és ha egy pontból már nincs kimenő él, tedd a pontot egy listába. A lista fordítva adja az útvonalat. ||
Hint 3: || Minden ponthoz tarts egy mutatót a kimenő éllistájában: így minden irányított él pontosan egyszer kerül felhasználásra, és a bejárás O(N + M) lesz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> out(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        out[u].push_back(v);  // u -> v
        out[v].push_back(u);  // v -> u
    }

    vector<size_t> ptr(n + 1, 0);
    vector<int> stk = {1};
    vector<int> circuit;
    circuit.reserve(2 * (size_t)m + 1);
    while (!stk.empty()) {
        int u = stk.back();
        if (ptr[u] < out[u].size()) {
            stk.push_back(out[u][ptr[u]++]);
        } else {
            circuit.push_back(u);
            stk.pop_back();
        }
    }
    reverse(circuit.begin(), circuit.end());

    for (size_t i = 0; i < circuit.size(); i++) {
        if (i) cout << ' ';
        cout << circuit[i];
    }
    cout << '\n';
    return 0;
}
