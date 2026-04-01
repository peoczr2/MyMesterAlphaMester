/*
Az eseményeket időrendben kell feldolgozni, mert minden érkezés vagy indulás a pályaszakasz foglaltságát módosítja. A megfelelő sorrend megtartása dönti el, hogy egy vonat vár-e vagy továbbléphet.
*/
/*
Hint 1: || Az eseményeket időrendbe kell tenni: érkezéskor a vonat vár, induláskor pedig a szakasz felszabadul. ||
Hint 2: || Ha két esemény egy időben történik, a menetirány és a szakasz foglaltsága dönti el, melyik vonat léphet tovább. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Train {
    int dir, start;
};

struct Event {
    long long time;
    int type; // 0 arrival, 1 finish
    int seg, train;
    bool operator>(const Event &other) const {
        if (time != other.time) return time > other.time;
        return type > other.type;
    }
};

struct Cand {
    long long time;
    int dir, train;
    bool operator>(const Cand &other) const {
        if (time != other.time) return time > other.time;
        if (dir != other.dir) return dir < other.dir; // dir 1 (Piripócs) later in heap
        return train > other.train;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, wait;
    cin >> n >> m >> wait;
    vector<int> travel(n - 1);
    for (int i = 0; i < n - 1; ++i) cin >> travel[i];

    vector<Train> trains(m);
    for (int i = 0; i < m; ++i) cin >> trains[i].dir >> trains[i].start, --trains[i].dir;

    vector<priority_queue<Cand, vector<Cand>, greater<Cand>>> q(max(0, n - 1));
    vector<int> busy(max(0, n - 1), 0);
    priority_queue<Event, vector<Event>, greater<Event>> events;
    vector<pair<long long,int>> out;

    auto add_arrival = [&](long long time, int seg, int train) {
        events.push({time, 0, seg, train});
    };

    for (int i = 0; i < m; ++i) {
        int seg = trains[i].dir == 0 ? 0 : n - 2;
        add_arrival(trains[i].start, seg, i);
    }

    auto start_ready = [&](long long now, int seg) {
        while (busy[seg] == 0 && !q[seg].empty() && q[seg].top().time <= now) {
            Cand c = q[seg].top(); q[seg].pop();
            busy[seg] = 1;
            events.push({now + travel[seg], 1, seg, c.train});
            // store direction in train index sign? recover from input
        }
    };

    vector<int> train_dir(m);
    for (int i = 0; i < m; ++i) train_dir[i] = trains[i].dir;

    vector<long long> finish_time(m, -1);

    while (!events.empty()) {
        long long time = events.top().time;
        vector<Event> batch;
        while (!events.empty() && events.top().time == time) {
            batch.push_back(events.top());
            events.pop();
        }

        for (auto &e : batch) {
            if (e.type == 0) {
                q[e.seg].push({e.time, train_dir[e.train], e.train});
            }
        }

        for (auto &e : batch) {
            if (e.type == 1) {
                busy[e.seg] = 0;
                int dir = train_dir[e.train];
                if (e.seg == 0 && dir == 1) {
                    finish_time[e.train] = time;
                } else if (e.seg == n - 2 && dir == 0) {
                    finish_time[e.train] = time;
                } else {
                    int next_seg = dir == 0 ? e.seg + 1 : e.seg - 1;
                    long long arrive = time + wait;
                    events.push({arrive, 0, next_seg, e.train});
                }
            }
        }

        for (int seg = 0; seg < n - 1; ++seg) start_ready(time, seg);
    }

    vector<pair<long long,int>> ans;
    for (int i = 0; i < m; ++i) ans.push_back({finish_time[i], train_dir[i]});
    sort(ans.begin(), ans.end(), [](auto a, auto b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second;
    });
    for (auto [t, d] : ans) cout << (d == 0 ? 2 : 1) << ' ' << t << '\n';
    return 0;
}