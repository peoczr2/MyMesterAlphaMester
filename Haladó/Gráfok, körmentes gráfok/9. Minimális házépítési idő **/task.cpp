/*
Megoldás lényege:
A munkák irányított gráfot alkotnak. Egy a b k előírás azt jelenti, hogy a b munka napja legalább az a munka napja
plusz k + 1. Ha a gráfban kör van, a terv nem teljesíthető, és a válasz -1. Egyébként topologikus sorrendben
haladva minden munka legkorábbi napját megkapjuk: ez az elődök (napjuk + k + 1) értékeinek maximuma, és legalább 1.
A ház minimális építési ideje az összes legkorábbi nap maximuma, vagyis a leghosszabb út súlya. Az időigény O(N + M).
*/
/*
Hint 1: || Egy a b k előírás azt kényszeríti ki, hogy b napja legalább a napja + k + 1 legyen. Ez leghosszabb út keresés egy irányított gráfban. ||
Hint 2: || Topologikus sorrendben haladva minden munkára számold ki a legkorábbi napját, a kimenő éleken át továbbadva. A legnagyobb napszám a válasz. Ha nem minden munka kerül a sorrendbe, kör van, és -1 a válasz. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // out[a]: (b, súly), ahol súly = k + 1.
    vector<vector<pair<int, int>>> out(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int a, b, k;
        cin >> a >> b >> k;
        out[a].push_back({b, k + 1});
        ++indeg[b];
    }

    // Topologikus sorrend (Kahn-algoritmus).
    vector<int> order;
    order.reserve(n);
    queue<int> ready;
    for (int v = 1; v <= n; ++v) {
        if (indeg[v] == 0) ready.push(v);
    }
    while (!ready.empty()) {
        int u = ready.front();
        ready.pop();
        order.push_back(u);
        for (auto [v, w] : out[u]) {
            if (--indeg[v] == 0) ready.push(v);
        }
    }

    if ((int)order.size() < n) {
        cout << -1 << "\n";
        return 0;
    }

    // start[v]: a v munka legkorábbi napja (napok 1-től számítva).
    vector<long long> start(n + 1, 1);
    for (int u : order) {
        for (auto [v, w] : out[u]) {
            start[v] = max(start[v], start[u] + w);
        }
    }

    long long answer = 0;
    for (int v = 1; v <= n; ++v) {
        answer = max(answer, start[v]);
    }
    cout << answer << "\n";
    return 0;
}
