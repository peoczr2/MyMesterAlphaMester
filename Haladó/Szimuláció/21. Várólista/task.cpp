/*
A várólista akkor egyszerű, ha csak az érkezési sorrendet és az aktuális feldolgozható elemet tartod nyilván. Ha a sor üres, a következő érkezésig kell ugrani, különben az élő elemet azonnal feldolgozhatod.
*/
/*
Hint 1: || A várólista elejét mindig az érkezési sorrend határozza meg, ezért a sorból csak előlről vehetsz ki elemet. ||
Hint 2: || Ha a sor üres, ugorj a következő érkezési időpontra, különben egyetlen lépésben dolgozd fel az aktuális elemet. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arrival(n), duration(n);
    for (int i = 0; i < n; ++i) cin >> arrival[i] >> duration[i];

    queue<int> q;
    int idx = 0;
    int time = 0;
    int current = -1;
    int finish = INT_MAX;
    int best_id = 0, best_wait = 0, max_waiting = 0;

    while (idx < n || current != -1 || !q.empty()) {
        int next_arrival = idx < n ? arrival[idx] : INT_MAX;
        int next_event = min(next_arrival, finish);
        if (current == -1 && q.empty() && idx < n && time < next_arrival) time = next_arrival;
        else time = next_event;

        while (idx < n && arrival[idx] == time) q.push(idx++);
        if (current != -1 && finish == time) current = -1;

        if (current == -1 && !q.empty()) {
            current = q.front(); q.pop();
            finish = time + duration[current];
            int w = time - arrival[current];
            if (w > best_wait || (w == best_wait && (best_id == 0 || current + 1 < best_id))) {
                best_wait = w;
                best_id = current + 1;
            }
        }

        max_waiting = max<int>(max_waiting, q.size());
        if (current == -1 && q.empty()) finish = INT_MAX;
    }

    if (best_wait == 0) best_id = 0;
    cout << best_id << '\n' << max_waiting << '\n';
    return 0;
}