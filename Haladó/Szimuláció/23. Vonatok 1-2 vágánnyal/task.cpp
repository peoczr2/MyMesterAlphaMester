/*
A két vágány közül mindig a legkorábban felszabadulót kell választani, különben könnyen rossz várakozási időt kapunk. Az érkezéseket és a felszabadulásokat ugyanabban az eseménylistában kell kezelni.
*/
/*
Hint 1: || A két vágány közül mindig azt használd, amelyiken a következő szabad időpont a legkorábbi. ||
Hint 2: || Az érkezést és a felszabadulást ugyanabban az eseménysorban érdemes kezelni, különben a sorrend elcsúszik. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Train { int dir, start; };
struct Event {
    long long time; int type, seg, train;
    bool operator>(const Event &o) const { return time != o.time ? time > o.time : type > o.type; }
};
struct Cand {
    long long time; int dir, train;
    bool operator>(const Cand &o) const {
        if (time != o.time) return time > o.time;
        if (dir != o.dir) return dir < o.dir;
        return train > o.train;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m1, m2, wait;
    cin >> n >> m1 >> m2 >> wait;
    vector<int> travel(n - 1), cap(n - 1);
    for (int i = 0; i < n - 1; ++i) cin >> travel[i];
    for (int i = 0; i < n - 1; ++i) cin >> cap[i];

    vector<Train> trains(m1 + m2);
    for (int i = 0; i < m1; ++i) { cin >> trains[i].start; trains[i].dir = 0; }
    for (int i = 0; i < m2; ++i) { cin >> trains[m1 + i].start; trains[m1 + i].dir = 1; }

    vector<priority_queue<Cand, vector<Cand>, greater<Cand>>> q(max(0, n - 1));
    vector<int> busy(max(0, n - 1), 0);
    priority_queue<Event, vector<Event>, greater<Event>> events;
    vector<int> train_dir(m1 + m2);
    for (int i = 0; i < m1 + m2; ++i) train_dir[i] = trains[i].dir;
    vector<long long> finish_time(m1 + m2, -1);

    for (int i = 0; i < m1 + m2; ++i) {
        int seg = trains[i].dir == 0 ? 0 : n - 2;
        events.push({trains[i].start, 0, seg, i});
    }

    auto start_ready = [&](long long now, int seg) {
        while (busy[seg] < cap[seg] && !q[seg].empty() && q[seg].top().time <= now) {
            Cand c = q[seg].top(); q[seg].pop();
            ++busy[seg];
            events.push({now + travel[seg], 1, seg, c.train});
        }
    };

    while (!events.empty()) {
        long long time = events.top().time;
        vector<Event> batch;
        while (!events.empty() && events.top().time == time) {
            batch.push_back(events.top());
            events.pop();
        }

        for (auto &e : batch) if (e.type == 0) q[e.seg].push({e.time, train_dir[e.train], e.train});

        for (auto &e : batch) if (e.type == 1) {
            --busy[e.seg];
            int dir = train_dir[e.train];
            if (e.seg == 0 && dir == 1) finish_time[e.train] = time;
            else if (e.seg == n - 2 && dir == 0) finish_time[e.train] = time;
            else {
                int next_seg = dir == 0 ? e.seg + 1 : e.seg - 1;
                events.push({time + wait, 0, next_seg, e.train});
            }
        }

        for (int seg = 0; seg < n - 1; ++seg) start_ready(time, seg);
    }

    vector<pair<long long,int>> ans;
    for (int i = 0; i < m1 + m2; ++i) ans.push_back({finish_time[i], train_dir[i]});
    sort(ans.begin(), ans.end(), [](auto a, auto b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second;
    });
    for (auto [t, d] : ans) cout << (d == 0 ? 2 : 1) << ' ' << t << '\n';
    return 0;
}