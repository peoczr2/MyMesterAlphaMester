/*
Feladat: A vendégekből a lehető legtöbb párost kell képezni úgy, hogy egy pár tagjai egy időpontban együtt jelen legyenek, és mindenki legfeljebb egy képen szerepeljen.
Ötlet: Eseményidőpontoknál aktív halmazt tartunk fenn, és amikor lehet, a leghamarabb távozó aktív vendégeket párosítjuk.
Hint 1: || Egy érvényes párhoz elég, hogy a két intervallum metssze egymást. ||
Hint 2: || A leghamarabb távozók párosítása először megakadályozza az elvesző lehetőségeket. ||
Hint 3: || Az érkezési/távozási események szerinti sweep elég a maximumhoz. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Guest { int l, r, id; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Guest> g(n);
    vector<int> times;
    times.reserve(2 * n);
    for (int i = 0; i < n; ++i) {
        cin >> g[i].l >> g[i].r;
        g[i].id = i + 1;
        times.push_back(g[i].l);
        times.push_back(g[i].r);
    }
    sort(times.begin(), times.end());
    times.erase(unique(times.begin(), times.end()), times.end());

    vector<vector<int>> starts(times.size());
    for (int i = 0; i < n; ++i) {
        int pos = lower_bound(times.begin(), times.end(), g[i].l) - times.begin();
        starts[pos].push_back(i);
    }

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<pair<int,int>> ans;
    for (int ti = 0; ti < (int)times.size(); ++ti) {
        int t = times[ti];
        for (int idx : starts[ti]) pq.push({g[idx].r, g[idx].id});
        while (!pq.empty() && pq.top().first <= t) pq.pop();

        while ((int)pq.size() >= 2) {
            auto [r1, id1] = pq.top(); pq.pop();
            if (r1 <= t) continue;
            auto [r2, id2] = pq.top(); pq.pop();
            if (r2 <= t) continue;
            ans.push_back({id1, id2});
        }
    }

    cout << ans.size() << '\n';
    for (auto [a, b] : ans) cout << a << ' ' << b << '\n';
    return 0;
}