/*
Megoldás lényege:
Két helyiség akkor járható át egymásból, ha közös falszakaszuk pozitív hosszú. Minden x és y koordinátájú egyenesen
a falakat rendezés után kétmutatós összefésüléssel párosítjuk, és az átfedő szakaszok hosszát helyiségenként összegezzük.
Egy helyiség akkor kijáratos, ha a kerületének nem minden hossza van szomszédos helyiséggel lefedve. Ezután szélességi
bejárással (BFS) a H helyiségből a legközelebbi kijáratos helyiség távolságát adjuk meg. Idő: O(N log N).
*/
/*
Hint 1: || Két helyiség között pontosan akkor van átjárás, ha közös falszakaszuk pozitív hosszú. Keresd meg az azonos x-, illetve y-koordinátájú falak átfedő szakaszpárjait. ||
Hint 2: || Minden átfedő szakaszpárnál növeld mindkét helyiség „lefedett hossz” értékét az átfedés hosszával. Ha ez kisebb a helyiség kerületénél, a helyiség kijáratos. ||
Hint 3: || A szomszédsági gráfban szélességi bejárás adja a legkisebb távolságot a H helyiségtől a legközelebbi kijáratos helyiségig. ||
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
                         vector<vector<int>>& adj, vector<long long>& covered) {
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
            ++i;
        } else if (second[j].r <= first[i].l) {
            ++j;
        } else {
            long long len = (long long)min(first[i].r, second[j].r) - max(first[i].l, second[j].l);
            covered[first[i].id] += len;
            covered[second[j].id] += len;
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
    vector<long long> covered(n + 1, 0);
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
            processGroup(leftSides, rightSides, adj, covered);
        }
    };

    build(verticalEvents);
    build(horizontalEvents);

    for (int i = 1; i <= n; ++i) {
        long long perimeter = 2LL * ((long long)(rects[i].x2 - rects[i].x1) + (rects[i].y2 - rects[i].y1));
        boundary[i] = covered[i] < perimeter;
    }

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