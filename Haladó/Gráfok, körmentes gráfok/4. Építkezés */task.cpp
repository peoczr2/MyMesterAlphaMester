/*
Megoldás lényege:
A munkák közötti előírások irányított gráfot alkotnak. Ha a gráfban van kör, a terv nem teljesíthető, és a válasz 0.
Különben topologikus rendezéssel (Kahn-algoritmus) haladunk, és minden munka szintjét a hozzá vezető leghosszabb
előírás-lánc hossza adja: a kezdő munkák szintje 1, egy munkáé az előző munkák legnagyobb szintje + 1.
Ugyanazon a napon csak olyan munkák végezhetők, amelyek között nincs előírás, ezért a szükséges napok száma éppen a
legnagyobb szint. A munkákat szintek szerint napokra bontjuk, és minden nap munkái növekvő sorrendben kerülnek kiírásra.
Az időigény O(N + T).
*/
/*
Hint 1: || Az előírások gráfot alkotnak: egy munka csak akkor végezhető el, ha az előtte kötelező munkák már mind megvannak. Keresd meg, mekkora a leghosszabb ilyen lánc! ||
Hint 2: || Egy munka napját a rá vezető leghosszabb előírás-lánc hossza határozza meg; ezt topologikus sorrendben, a sorban haladva kiszámolhatod. Ha a rendezés nem ad ki minden csúcsot, van kör, és 0 a válasz. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t;
    cin >> n >> t;

    vector<vector<int>> succ(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < t; ++i) {
        int a, b;
        cin >> a >> b;
        succ[a].push_back(b);
        ++indeg[b];
    }

    vector<int> level(n + 1, 1);
    vector<int> order;
    order.reserve(n);
    queue<int> q;
    for (int v = 1; v <= n; ++v) {
        if (indeg[v] == 0) {
            q.push(v);
        }
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        order.push_back(v);
        for (int w : succ[v]) {
            level[w] = max(level[w], level[v] + 1);
            if (--indeg[w] == 0) {
                q.push(w);
            }
        }
    }

    if (static_cast<int>(order.size()) < n) {
        cout << 0 << "\n";
        return 0;
    }

    int days = 0;
    for (int v = 1; v <= n; ++v) {
        days = max(days, level[v]);
    }
    vector<vector<int>> byDay(days + 1);
    for (int v = 1; v <= n; ++v) {
        byDay[level[v]].push_back(v);
    }

    cout << days << "\n";
    for (int d = 1; d <= days; ++d) {
        for (size_t i = 0; i < byDay[d].size(); ++i) {
            if (i > 0) {
                cout << ' ';
            }
            cout << byDay[d][i];
        }
        cout << "\n";
    }
    return 0;
}
