/*
Megoldás lényege:
Az idővonal végpontjain eseménysöprést végzünk. Két szomszédos eseménypont között az elérhetőség
nem változik, ezért ott könnyen eldönthető, hogy Ádám és Éva egyszerre aktívak-e.

Azokból a darabokból építjük fel a választ, ahol mindkettőjük állapota pozitív.
*/
/*
Hint 1: || Itt a metszet kell: mindkettőjük elérhetősége egyszerre legyen igaz. ||
Hint 2: || A félzárt intervallumok miatt a végpontokon kapcsol be és ki az állapot. ||
Hint 3: || A jó szakaszok egymás után összevonhatók, ha érintkeznek. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Event {
    int x;
    int da;
    int de;
    bool operator<(const Event& other) const { return x < other.x; }
};

static vector<pair<int,int>> buildSegments(const vector<Event>& events) {
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
        if (adam > 0 && eva > 0 && x < nextX) {
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
    auto answer = buildSegments(events);
    cout << answer.size() << '\n';
    for (const auto &segment : answer) cout << segment.first << ' ' << segment.second << '\n';
    return 0;
}