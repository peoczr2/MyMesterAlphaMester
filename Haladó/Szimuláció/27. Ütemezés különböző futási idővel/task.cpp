/*
Különböző futási idők esetén a következő befejeződő feladat kiválasztása a kulcs, ezért egy prioritási soros szimuláció a természetes megoldás. Minden pillanatban a legrövidebb hátralévő idejű munka kap elsőbbséget.
*/
/*
Hint 1: || Különböző futási idők esetén mindig a legrövidebb hátralévő idejű feladatot érdemes előre venni. ||
Hint 2: || A következő befejeződő folyamatot egy prioritási sorból lehet a legegyszerűbben kiolvasni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> start(n), rem(n), finish(n, 0);
    for (int i = 0; i < n; ++i) cin >> start[i] >> rem[i];

    deque<int> q;
    int idx = 0;
    long long time = 0;

    while (idx < n || !q.empty()) {
        if (q.empty() && idx < n && time < start[idx]) time = start[idx];
        while (idx < n && start[idx] <= time) q.push_back(idx++);
        if (q.empty()) continue;

        int id = q.front();
        q.pop_front();
        --rem[id];
        if (rem[id] == 0) finish[id] = time;
        else q.push_back(id);
        ++time;
    }

    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << finish[i];
    }
    cout << '\n';
    return 0;
}