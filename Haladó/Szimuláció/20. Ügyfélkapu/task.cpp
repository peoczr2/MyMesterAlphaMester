/*
Az ügyfeleket típus szerint külön sorokba kell rendezni, miközben az érkezési sorrend megmarad. A szimuláció során mindig a következő érkezést vagy a következő felszabaduló kaput kell kiválasztani.
*/
/*
Hint 1: || A kliens típusát mindig külön sorhoz kell rendelned, és az érkezési sorrend megmarad. ||
Hint 2: || Az események között a következő érkezést és a következő felszabadulást kell keresned. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Client {
    int arrival, duration, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Client> clients(n);
    for (int i = 0; i < n; ++i) {
        cin >> clients[i].arrival >> clients[i].duration;
        clients[i].id = i + 1;
    }

    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> waiting;
    int idx = 0;
    long long time = 0;
    bool busy = false;
    long long finish = (long long)4e18;
    int best_id = 0;
    int best_wait = 0;
    int max_waiting = 0;

    while (idx < n || busy || !waiting.empty()) {
        long long next_arrival = idx < n ? clients[idx].arrival : (long long)4e18;
        long long next_event = min(next_arrival, finish);
        if (!busy && waiting.empty() && idx < n && time < next_arrival) time = next_arrival;
        else time = next_event;

        while (idx < n && clients[idx].arrival <= time) {
            waiting.push({clients[idx].duration, clients[idx].arrival, clients[idx].id});
            ++idx;
        }

        if (busy && finish <= time) busy = false;

        if (!busy && !waiting.empty()) {
            auto [dur, arr, id] = waiting.top();
            waiting.pop();
            busy = true;
            finish = time + dur;
            int waited = (int)(time - arr);
            if (waited > best_wait || (waited == best_wait && (best_id == 0 || id < best_id))) {
                best_wait = waited;
                best_id = id;
            }
        }

        max_waiting = max<int>(max_waiting, waiting.size());
        if (!busy && waiting.empty()) finish = (long long)4e18;
    }

    if (best_wait == 0) best_id = 0;
    cout << best_id << '\n' << max_waiting << '\n';
    return 0;
}