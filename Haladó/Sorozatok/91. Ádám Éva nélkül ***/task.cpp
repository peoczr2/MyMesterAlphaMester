/*
Megoldás lényege:
Az időszakokat félzárt [kezdet, vég) intervallumként kezeljük. Minden végpontnál eseményt teszünk:
Ádám és Éva elérhetősége külön-külön be- illetve kikapcsolódik. Két szomszédos eseménypont között az
állapot állandó, ezért ott egyszerűen eldönthető, hogy pontosan Ádám ér-e rá.

Az eseménysöprés közben azokat a szakaszokat írjuk ki, ahol Ádám aktív, Éva pedig nem.
*/
/*
Hint 1: || A példákból látszik, hogy a [K,V) félzárt értelmezés a jó. ||
Hint 2: || Elegendő az összes intervallum végpontját eseményként kezelni. ||
Hint 3: || Két szomszédos eseménypont között az állapot nem változik. ||
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
        if (mode == 0) good = (adam > 0 && eva == 0);
        if (mode == 1) good = ((adam > 0) ^ (eva > 0));
        if (mode == 2) good = (adam > 0 && eva > 0);
        if (mode == 3) good = (adam > 0 || eva > 0);
        if (good && x < nextX) {
            if (!answer.empty() && answer.back().second == x) {
                answer.back().second = nextX;
            } else {
                answer.push_back({x, nextX});
            }
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
    events.reserve(2 * (aCount + 100000));
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
    auto answer = buildSegments(events, 0);
    cout << answer.size() << '\n';
    for (const auto &segment : answer) cout << segment.first << ' ' << segment.second << '\n';
    return 0;
}