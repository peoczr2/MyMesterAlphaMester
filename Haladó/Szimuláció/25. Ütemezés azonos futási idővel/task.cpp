/*
Azonos futási időnél a feladatok egy körbeforgó sorba rendezhetők, és mindig a sor elején álló egységnyi munkát kell előrevinni. A megoldás ezért egy egyszerű körkörös feldolgozás, amelyben a még hátralévő munkát visszateszed a sor végére.
*/
/*
Hint 1: || Azonos futási idő esetén a feladatok körbeforgó sorban dolgozhatók fel. ||
Hint 2: || Amelyik feladat még nem készült el, azt egyszerűen tedd vissza a sor végére, amíg a rem értéke nullára nem csökken. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, f;
    cin >> n >> f;
    vector<int> start(n), rem(n, f), finish(n, 0);
    for (int i = 0; i < n; ++i) cin >> start[i];

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