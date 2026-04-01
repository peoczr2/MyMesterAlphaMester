/*
Feladat: A vendégekből a lehető legtöbb K fős csoportképet kell készíteni úgy, hogy minden vendég legfeljebb egy képen szerepeljen.
Ötlet: Időpont-söprés közben aktív vendégeket tartunk, és mindig a leghamarabb távozó K vendéget fényképezzük le.
Hint 1: || Egy csoport akkor készíthető, ha van K vendég, akik ugyanabban a pillanatban bent vannak. ||
Hint 2: || A korán távozókat érdemes előbb felhasználni. ||
Hint 3: || Eseményidőpontokban ismételd a „K darab legkisebb végidő kiválasztását”. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Guest { int l, r, id; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
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
    vector<vector<int>> photos;
    vector<int> photoTime;

    for (int ti = 0; ti < (int)times.size(); ++ti) {
        int t = times[ti];
        for (int idx : starts[ti]) pq.push({g[idx].r, g[idx].id});
        while (!pq.empty() && pq.top().first < t) pq.pop();

        while ((int)pq.size() >= k) {
            vector<int> group;
            group.reserve(k);
            bool ok = true;
            for (int i = 0; i < k; ++i) {
                if (pq.empty() || pq.top().first < t) {
                    ok = false;
                    break;
                }
                group.push_back(pq.top().second);
                pq.pop();
            }
            if (!ok) break;
            photos.push_back(group);
            photoTime.push_back(t);
        }
    }

    cout << photos.size() << '\n';
    for (int i = 0; i < (int)photos.size(); ++i) {
        cout << photoTime[i];
        for (int id : photos[i]) cout << ' ' << id;
        cout << '\n';
    }
    return 0;
}