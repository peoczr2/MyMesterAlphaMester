/*
Feladat: A legkevesebb vendéget kell kiválasztani úgy, hogy minden vendég találkozzon legalább eggyel a kiválasztottak közül.
Ötlet: Ez az intervallumfedés vendég-intervallumokkal. Az első még nem fedett vendéghez a legtovább bent maradó, vele még találkozó vendéget választjuk.
Hint 1: || Az események itt az intervallumok metszetei. ||
Hint 2: || A legkorábban távozó lefedetlen vendéghez keresd a legtovább bent maradót, aki még jelen volt akkor. ||
Hint 3: || Ha nincs ilyen vendég, akkor nincs megoldás. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Guest { int s, e, id; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int guestCount, eventCount;
    cin >> guestCount >> eventCount;
    vector<Guest> g(guestCount);
    for (int i = 0; i < guestCount; ++i) {
        cin >> g[i].s >> g[i].e;
        g[i].id = i + 1;
    }
    vector<int> events(eventCount);
    for (int i = 0; i < eventCount; ++i) cin >> events[i];

    sort(g.begin(), g.end(), [](const Guest &a, const Guest &b) {
        if (a.s != b.s) return a.s < b.s;
        if (a.e != b.e) return a.e > b.e;
        return a.id < b.id;
    });

    vector<int> chosen;
    priority_queue<pair<int, int>> pq;
    int guestPtr = 0;
    int eventPtr = 0;
    while (eventPtr < eventCount) {
        int cur = events[eventPtr];
        while (guestPtr < guestCount && g[guestPtr].s <= cur) {
            pq.push({g[guestPtr].e, g[guestPtr].id});
            ++guestPtr;
        }
        while (!pq.empty() && pq.top().first < cur) pq.pop();
        if (pq.empty()) {
            cout << 0 << '\n';
            return 0;
        }

        auto [endTime, id] = pq.top();
        pq.pop();
        chosen.push_back(id);
        while (eventPtr < eventCount && events[eventPtr] <= endTime) ++eventPtr;
    }

    cout << chosen.size() << '\n';
    for (int i = 0; i < (int)chosen.size(); ++i) {
        if (i) cout << ' ';
        cout << chosen[i];
    }
    cout << '\n';
    return 0;
}