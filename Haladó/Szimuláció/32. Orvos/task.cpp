/*
Az orvosi rendelés tipikus eseményszimuláció: az érkezések és a rendelő felszabadulása ugyanabban az idővonalban jelenik meg. A válasz a várakozási idők és a lezárás idejének követéséből adódik.
*/
/*
Hint 1: || Az orvoshoz érkezők és a rendelő felszabadulása ugyanabban az eseménysorban kezelhető. ||
Hint 2: || A legfontosabb kimenet a leghosszabb várakozás és a rendelés vége, ami a következő szabad időpontból számolható. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arr(n), dur(n);
    for (int i = 0; i < n; ++i) cin >> arr[i] >> dur[i];

    queue<int> q;
    int idx = 0;
    int time = 0;
    int current = -1, finish = INT_MAX;
    int best_id = 0, best_wait = 0, max_waiting = 0;

    while (idx < n || current != -1 || !q.empty()) {
        int next_arrival = idx < n ? arr[idx] : INT_MAX;
        if (current == -1 && q.empty() && idx < n && time < next_arrival) time = next_arrival;
        else time = min(next_arrival, finish);

        while (idx < n && arr[idx] == time) q.push(idx++);
        if (current != -1 && finish == time) current = -1;

        if (current == -1 && !q.empty()) {
            current = q.front(); q.pop();
            finish = time + dur[current];
            int w = time - arr[current];
            if (w > best_wait || (w == best_wait && (best_id == 0 || current + 1 < best_id))) {
                best_wait = w;
                best_id = current + 1;
            }
        }

        max_waiting = max<int>(max_waiting, q.size());
        if (current == -1 && q.empty()) finish = INT_MAX;
    }

    if (best_wait == 0) best_id = 0;
    cout << best_id << ' ' << best_wait << '\n' << max_waiting << '\n';
    return 0;
}