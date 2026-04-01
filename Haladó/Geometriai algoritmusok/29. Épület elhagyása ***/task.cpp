/*
Megoldás lényege:
Akadályok között kell érvényes, lehetőleg minimális útvonalat keresni. A geometriai korlátokat a szakaszok és téglalapok metszésvizsgálata adja.
*/
#include <bits/stdc++.h>
using namespace std;

struct Rect {
    int x1, y1, x2, y2;
};

struct IntervalSide {
    int l, r, id;
};

struct SideEvent {
    int coord;
    int l, r;
    int id;
    bool first;
};

static void processGroup(vector<IntervalSide>& first, vector<IntervalSide>& second,
                         vector<vector<int>>& adj, vector<char>& boundary) {
    sort(first.begin(), first.end(), [](const IntervalSide& a, const IntervalSide& b) {
        if (a.l != b.l) return a.l < b.l;
        if (a.r != b.r) return a.r < b.r;
        return a.id < b.id;
    });
    sort(second.begin(), second.end(), [](const IntervalSide& a, const IntervalSide& b) {
        if (a.l != b.l) return a.l < b.l;
        if (a.r != b.r) return a.r < b.r;
        return a.id < b.id;
    });

    int i = 0, j = 0;
    while (i < (int)first.size() && j < (int)second.size()) {
        if (first[i].r <= second[j].l) {
            boundary[first[i].id] = 1;
            ++i;
        } else if (second[j].r <= first[i].l) {
            boundary[second[j].id] = 1;
            ++j;
        } else {
            adj[first[i].id].push_back(second[j].id);
            adj[second[j].id].push_back(first[i].id);
            if (first[i].r < second[j].r) {
                ++i;
            } else if (second[j].r < first[i].r) {
                ++j;
            } else {
                ++i;
                ++j;
            }
        }
    }

    while (i < (int)first.size()) {
        boundary[first[i].id] = 1;
        ++i;
    }
    while (j < (int)second.size()) {
        boundary[second[j].id] = 1;
        ++j;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, start;
    if (!(cin >> n >> start)) return 0;

    vector<Rect> rects(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;
        if (rects[i].x1 > rects[i].x2) swap(rects[i].x1, rects[i].x2);
        if (rects[i].y1 > rects[i].y2) swap(rects[i].y1, rects[i].y2);
    }

    vector<SideEvent> verticalEvents;
    vector<SideEvent> horizontalEvents;
    verticalEvents.reserve(2 * n);
    horizontalEvents.reserve(2 * n);

    for (int i = 1; i <= n; ++i) {
        verticalEvents.push_back({rects[i].x1, rects[i].y1, rects[i].y2, i, true});
        verticalEvents.push_back({rects[i].x2, rects[i].y1, rects[i].y2, i, false});
        horizontalEvents.push_back({rects[i].y1, rects[i].x1, rects[i].x2, i, true});
        horizontalEvents.push_back({rects[i].y2, rects[i].x1, rects[i].x2, i, false});
    }

    vector<vector<int>> adj(n + 1);
    vector<char> boundary(n + 1, 0);

    auto build = [&](vector<SideEvent> events) {
        sort(events.begin(), events.end(), [](const SideEvent& a, const SideEvent& b) {
            if (a.coord != b.coord) return a.coord < b.coord;
            if (a.l != b.l) return a.l < b.l;
            if (a.r != b.r) return a.r < b.r;
            if (a.first != b.first) return a.first > b.first;
            return a.id < b.id;
        });

        int pos = 0;
        while (pos < (int)events.size()) {
            int coord = events[pos].coord;
            vector<IntervalSide> leftSides, rightSides;
            while (pos < (int)events.size() && events[pos].coord == coord) {
                if (events[pos].first) leftSides.push_back({events[pos].l, events[pos].r, events[pos].id});
                else rightSides.push_back({events[pos].l, events[pos].r, events[pos].id});
                ++pos;
            }
            processGroup(leftSides, rightSides, adj, boundary);
        }
    };

    build(verticalEvents);
    build(horizontalEvents);

    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (boundary[v]) {
            cout << dist[v] << '\n';
            return 0;
        }
        for (int to : adj[v]) {
            if (dist[to] == -1) {
                dist[to] = dist[v] + 1;
                q.push(to);
            }
        }
    }

    cout << 0 << '\n';
    return 0;
}