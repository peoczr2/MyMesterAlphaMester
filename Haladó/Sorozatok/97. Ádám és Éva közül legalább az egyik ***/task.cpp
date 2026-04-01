/*
Megoldás lényege:
Itt Ádám és Éva elérhetőségi intervallumainak unióját kell kiírni, félzárt [K,V) értelmezésben.
Eseménysöpréssel követjük, hogy éppen hányuk elérhető; ahol ez pozitív, ott a találkozás lehetséges.

Az egymást érintő darabokat összevonjuk.
*/
/*
Hint 1: || A keresett állapot most az, hogy legalább egyikük aktív legyen. ||
Hint 2: || A végpontok közötti szakaszokon az aktívak száma állandó. ||
Hint 3: || Ha két jó darab összeér, egyetlen nagyobb intervallummá kell olvasztani őket. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Event {
    int x;
    int da;
    int de;
    bool operator<(const Event& other) const { return x < other.x; }
};

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
        if ((adam > 0 || eva > 0) && x < nextX) {
            if (!answer.empty() && answer.back().second == x) answer.back().second = nextX;
            else answer.push_back({x, nextX});
        }
    }

    cout << answer.size() << '\n';
    for (const auto &segment : answer) cout << segment.first << ' ' << segment.second << '\n';
    return 0;
}