#include <bits/stdc++.h>
using namespace std;

/*
    A páciensek érkezési sorrendben kerülnek ellátásra. Az egyes várakozási
    időket egyszerűen kiszámoljuk a kezdési időből, majd az [érkezés, kezdés)
    intervallumok maximum átfedését sweep line-nal kapjuk meg.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> er(n + 1), kez(n + 1);
    for (int i = 1; i <= n; ++i) cin >> er[i] >> kez[i];

    vector<int> start(n + 1), vege(n + 1), var(n + 1);
    int cur = 0;
    for (int i = 1; i <= n; ++i) {
        start[i] = max(cur, er[i]);
        var[i] = start[i] - er[i];
        cur = start[i] + kez[i];
    }

    int bestId = 0, bestWait = 0;
    for (int i = 1; i <= n; ++i) {
        if (var[i] > bestWait) {
            bestWait = var[i];
            bestId = i;
        }
    }

    vector<pair<int, int>> es;
    for (int i = 1; i <= n; ++i) {
        if (var[i] > 0) {
            es.push_back({er[i], 1});
            es.push_back({start[i], -1});
        }
    }
    sort(es.begin(), es.end(), [](auto& a, auto& b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second; // -1 előbb, mint +1
    });
    int akt = 0, maxWaiters = 0;
    for (auto [t, d] : es) {
        akt += d;
        maxWaiters = max(maxWaiters, akt);
    }

    cout << bestId << '\n' << maxWaiters << '\n';
    return 0;
}