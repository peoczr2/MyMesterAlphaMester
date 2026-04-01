/*
Feladat: A lehető legkevesebb vendéget kell kiválasztani úgy, hogy minden eseményidőpontot lefedjenek.
Ötlet: A legkorábban még lefedetlen eseményhez mindig a legtovább bent maradó, azt lefedő vendéget választjuk. Ez az intervallum-stabbing klasszikus mohó megoldása.
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