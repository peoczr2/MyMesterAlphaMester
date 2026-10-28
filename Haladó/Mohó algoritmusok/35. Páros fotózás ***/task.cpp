/*
Megoldás lényege:
Két vendég akkor szerepelhet együtt, ha a későbbi érkezés a korábbi távozás előtt van, vagyis jelenléti intervallumaik átfedik egymást. A feladat tehát intervallumok maximális párosítása. A vendégeket távozási idő szerint dolgozzuk fel, és egy halmazban tartjuk a párosítatlan, már feldolgozott vendégeket. Az aktuális vendéghez a halmazból azt a párosítatlan vendéget választjuk, aki még az érkezése után is bent van, és közülük a legkorábban távozót; így a később távozók megmaradnak a jövőbeli párosításokhoz. Ha nincs ilyen vendég, az aktuális vendég kerül a halmazba. Az időigény O(N log N).
*/
/*
Hint 1: || Két vendég akkor lehet egy képen, ha jelenlétük időintervallumai átfedik egymást. ||
Hint 2: || Távozási idő szerint haladj, és minden vendégnél keress egy korábban feldolgozott, még párosítatlan vendéget, akinek a távozása az aktuális érkezés után van. ||
Hint 3: || Ha több ilyen van, a legkorábban távozót párosítsd: a később távozók több lehetőséget hagynak a jövőre. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Guest { int l, r, id; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Guest> g(n);
    for (int i = 0; i < n; ++i) {
        cin >> g[i].l >> g[i].r;
        g[i].id = i + 1;
    }
    sort(g.begin(), g.end(), [](const Guest &x, const Guest &y) {
        if (x.r != y.r) return x.r < y.r;
        return x.id < y.id;
    });

    // párosítatlan, már feldolgozott vendégek: (távozás, sorszám)
    set<pair<int,int>> freeSet;
    vector<pair<int,int>> ans;
    for (const auto &x : g) {
        // a legkorábban távozó párosítatlan vendég, aki x érkezése után még bent van
        auto it = freeSet.upper_bound({x.l, INT_MAX});
        if (it != freeSet.end()) {
            ans.push_back({it->second, x.id});
            freeSet.erase(it);
        } else {
            freeSet.insert({x.r, x.id});
        }
    }

    cout << ans.size() << '\n';
    for (auto [a, b] : ans) cout << a << ' ' << b << '\n';
    return 0;
}
