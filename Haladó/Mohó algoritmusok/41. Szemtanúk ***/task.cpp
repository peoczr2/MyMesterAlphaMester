/*
Megoldás lényege:
A vendégeket érkezési idő szerint rendezzük, az eseményeket időrendben dolgozzuk fel. A legkorábbi, még le nem fedett eseményhez azt a vendéget választjuk, aki lefedi (E <= x <= T), és a legkésőbb távozik, így ő fedi le a legtöbb későbbi eseményt. A választott vendég intervallumába eső eseményeket kihagyjuk; ha egy eseményt senki nem fed le, a válasz 0. Ez az intervallum-stabbing klasszikus mohó megoldása, az időigény O(M log M + N).
*/
/*
Hint 1: || Először a legkisebb eseményidőpontot kell lefedni. ||
Hint 2: || Az ezt lefedő vendégek közül a legkésőbb távozót érdemes választani. ||
Hint 3: || Utána minden olyan esemény kihagyható, amely ebbe a vendég-intervallumba esik. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Guest { int s, e, id; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    vector<Guest> g(m);
    for (int i = 0; i < m; ++i) {
        cin >> g[i].s >> g[i].e;
        g[i].id = i + 1;
    }
    vector<int> events(n);
    for (int i = 0; i < n; ++i) cin >> events[i];

    vector<int> chosen;
    int ptr = 0;
    sort(g.begin(), g.end(), [](const Guest &a, const Guest &b) {
        if (a.s != b.s) return a.s < b.s;
        if (a.e != b.e) return a.e > b.e;
        return a.id < b.id;
    });

    for (int i = 0; i < n; ) {
        int x = events[i];
        int bestEnd = -1, bestId = -1;
        while (ptr < m && g[ptr].s <= x) {
            if (g[ptr].e >= x && g[ptr].e > bestEnd) {
                bestEnd = g[ptr].e;
                bestId = g[ptr].id;
            }
            ++ptr;
        }
        if (bestId == -1) {
            cout << 0 << '\n';
            return 0;
        }
        chosen.push_back(bestId);
        while (i < n && events[i] <= bestEnd) ++i;
    }

    cout << chosen.size() << '\n';
    for (int i = 0; i < (int)chosen.size(); ++i) {
        if (i) cout << ' ';
        cout << chosen[i];
    }
    cout << '\n';
    return 0;
}