/*
Az ügyfélszolgálat modellje típusonként külön sorokat és a következő szabad kapu időpontját követi. A feladat lényege az események helyes sorrendjének fenntartása, hogy mindig a következő érkezést vagy felszabadulást kezeljük.
*/
/*
Hint 1: || Az ügyfeleket típusonként külön sorban tartsd nyilván, és mindig az érkezési sorrend maradjon meg. ||
Hint 2: || A következő esemény a legközelebbi érkezés vagy felszabadulás lesz; ezek közül kell ugrani a következő időpontra. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Client { long long arrival, service; int id; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    vector<long long> desk_time(m + 1);
    for (int i = 1; i <= m; ++i) cin >> desk_time[i];

    vector<Client> c(n);
    for (int i = 0; i < n; ++i) { cin >> c[i].arrival >> c[i].service; c[i].id = i + 1; }

    queue<Client> q;
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> busy;
    priority_queue<int, vector<int>, greater<int>> free_desks;
    for (int i = 1; i <= m; ++i) free_desks.push(i);

    vector<int> desk_of(n + 1, 0);
    long long best_wait = 0, max_queue = 0;
    long long workday_end = 0;
    int idx = 0;
    long long time = 0;

    while (idx < n || !q.empty() || !busy.empty()) {
        long long next_arrival = idx < n ? c[idx].arrival : LLONG_MAX;
        long long next_finish = busy.empty() ? LLONG_MAX : busy.top().first;
        time = min(next_arrival, next_finish);

        while (!busy.empty() && busy.top().first <= time) {
            free_desks.push(busy.top().second);
            busy.pop();
        }
        while (idx < n && c[idx].arrival <= time) q.push(c[idx++]);

        while (!q.empty() && !free_desks.empty()) {
            Client cur = q.front(); q.pop();
            int desk = free_desks.top(); free_desks.pop();
            desk_of[cur.id] = desk;
            best_wait = max(best_wait, time - cur.arrival);
            long long finish = time + desk_time[desk];
            workday_end = max(workday_end, finish);
            busy.push({finish, desk});
        }

        max_queue = max<long long>(max_queue, q.size());
        if (q.empty() && busy.empty() && idx < n && time < c[idx].arrival) time = c[idx].arrival;
    }

    cout << workday_end << ' ' << best_wait << ' ' << max_queue << '\n';
    for (int i = 1; i <= n; ++i) cout << desk_of[i] << '\n';
    return 0;
}