#include <bits/stdc++.h>
using namespace std;

/*
    Minden vágányhoz külön várakozási sor tartozik. A vonatok akkor kerülnek
    egy vágány sorába, amikor az adott szakaszra ténylegesen indulhatnának.
    A sor rendezési kulcsa az indulási idő, azon belül a Kukutyinból induló
    vonat élvez elsőbbséget, majd az eredeti input-sorrend dönt.
*/

struct Train {
    int dir;         // 1 = Kukutyin -> Piripócs, 2 = fordítva
    int nextSeg;     // a következő használni kívánt szakasz
    long long ready; // mikor kerülhet sorba a következő szakaszra
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, wait;
    cin >> n >> m >> wait;
    vector<long long> travel(n);
    for (int i = 1; i <= n - 1; ++i) cin >> travel[i];

    vector<Train> trains(m);
    for (int i = 0; i < m; ++i) {
        cin >> trains[i].dir >> trains[i].ready;
        trains[i].nextSeg = (trains[i].dir == 1 ? 1 : n - 1);
    }

    using WaitItem = tuple<long long, int, int, int>; // ready, dir, input order, train id
    vector<priority_queue<WaitItem, vector<WaitItem>, greater<WaitItem>>> waiting(n);

    using Event = tuple<long long, int, int, int>; // time, type(0=finish,1=ready), segment, train id
    priority_queue<Event, vector<Event>, greater<Event>> events;

    for (int i = 0; i < m; ++i) {
        events.push({trains[i].ready, 1, trains[i].nextSeg, i});
    }

    vector<char> running(n, 0);
    vector<pair<int, long long>> result;
    result.reserve(m);

    auto start_from_queue = [&](int seg, long long now) {
        if (running[seg] || waiting[seg].empty()) return;
        auto [rdy, dir, ord, id] = waiting[seg].top();
        if (rdy > now) return;
        waiting[seg].pop();
        running[seg] = 1;
        events.push({now + travel[seg], 0, seg, id});
    };

    while (!events.empty()) {
        long long now = get<0>(events.top());
        vector<Event> bucket;
        while (!events.empty() && get<0>(events.top()) == now) {
            bucket.push_back(events.top());
            events.pop();
        }

        for (const auto& ev : bucket) {
            int type = get<1>(ev);
            int seg = get<2>(ev);
            int id = get<3>(ev);
            if (type == 0) {
                running[seg] = 0;
                if (trains[id].dir == 1) {
                    if (seg == n - 1) {
                        result.push_back({2, now});
                    } else {
                        trains[id].nextSeg = seg + 1;
                        trains[id].ready = now + wait;
                        events.push({trains[id].ready, 1, trains[id].nextSeg, id});
                    }
                } else {
                    if (seg == 1) {
                        result.push_back({1, now});
                    } else {
                        trains[id].nextSeg = seg - 1;
                        trains[id].ready = now + wait;
                        events.push({trains[id].ready, 1, trains[id].nextSeg, id});
                    }
                }
            }
        }

        for (const auto& ev : bucket) {
            int type = get<1>(ev);
            int seg = get<2>(ev);
            int id = get<3>(ev);
            if (type == 1) {
                waiting[seg].push({get<0>(ev), trains[id].dir, id, id});
            }
        }

        for (int seg = 1; seg <= n - 1; ++seg) {
            start_from_queue(seg, now);
        }
    }

    sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first > b.first;
    });

    for (auto [dir, t] : result) {
        cout << dir << ' ' << t << '\n';
    }
    return 0;
}