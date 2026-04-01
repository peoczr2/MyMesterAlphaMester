/*
Megoldás lényege:
A félzárt intervallumok végpontjain eseménysöprést végzünk. Két szomszédos eseménypont között
Ádám és Éva elérhetősége állandó, ezért ott egyszerűen ellenőrizhető, hogy pontosan egyikük ér-e rá.

Az így kapott részeket összevonjuk, ha érintkeznek.
*/
/*
Hint 1: || A keresett állapot itt az XOR: csak Ádám vagy csak Éva aktív. ||
Hint 2: || A végpontok közötti nyílt szakaszokon nem változik az állapot. ||
Hint 3: || Az egymást érintő jó darabokat össze kell vonni. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Event {
    int x;
    int da;
    int de;
    bool operator<(const Event& other) const { return x < other.x; }
};

static vector<pair<int,int>> buildSegments(const vector<Event>& events, int mode) {
    vector<pair<int,int>> answer;
    int adam = 0, eva = 0;
    int i = 0;
    while (i < (int)events.size()) {
        int x = events[i].x;
        while (i < (int)events.size() && events[i].x == x) {
            adam += events[i].da;
            eva += events[i].de;
            ++i;
        }
        if (i == (int)events.size()) break;
        int nextX = events[i].x;
        bool good = false;
        if (mode == 1) good = ((adam > 0) ^ (eva > 0));
        if (good && x < nextX) {
            if (!answer.empty() && answer.back().second == x) answer.back().second = nextX;
            else answer.push_back({x, nextX});
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int p, aCount, eCount;
    cin >> p >> aCount;
    vector<Event> events;
    events.reserve(400000);
    for (int i = 0; i < aCount; ++i) {
        int l, r;
        cin >> l >> r;
        events.push_back({l, +1, 0});
        events.push_back({r, -1, 0});
    }
    cin >> eCount;
    for (int i = 0; i < eCount; ++i) {
        int l, r;
        cin >> l >> r;
        events.push_back({l, 0, +1});
        events.push_back({r, 0, -1});
    }

    sort(events.begin(), events.end());
    auto answer = buildSegments(events, 1);
    cout << answer.size() << '\n';
    for (const auto &segment : answer) cout << segment.first << ' ' << segment.second << '\n';
    return 0;
}