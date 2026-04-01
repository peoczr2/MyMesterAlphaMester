/*
Feladat: A legtöbb munkát kell kiválasztani úgy, hogy mindegyik beleférjen a határidejébe.
Ötlet: Határidő szerint haladva mindig megtartjuk a már látott munkák közül a legrövidebb összidőt adó halmazt; ha a teljes idő túllépi az aktuális határidőt, a leghosszabb munkát ejtjük ki.
Hint 1: || A minél több munka megtartása miatt a hosszabbakat érdemes áldozatul dobni, ha túlcsordulunk. ||
Hint 2: || A kiválasztott halmazt a végén elég határidő szerint rendezni. ||
Hint 3: || A legnagyobb időtartamú munkát egy max-heapből tudod kivenni. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Job { int t, d, id; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Job> a(n);
    vector<Job> orig(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].t >> a[i].d;
        a[i].id = i + 1;
        orig[i + 1] = a[i];
    }
    sort(a.begin(), a.end(), [](const Job &x, const Job &y) {
        if (x.d != y.d) return x.d < y.d;
        if (x.t != y.t) return x.t < y.t;
        return x.id < y.id;
    });

    priority_queue<pair<int,int>> pq;
    long long sum = 0;
    vector<int> keep(n + 1, 0);
    for (auto &j : a) {
        pq.push({j.t, j.id});
        keep[j.id] = 1;
        sum += j.t;
        if (sum > j.d) {
            auto [t, id] = pq.top(); pq.pop();
            sum -= t;
            keep[id] = 0;
        }
    }

    vector<int> ans;
    for (auto &j : a) if (keep[j.id]) ans.push_back(j.id);
    sort(ans.begin(), ans.end(), [&](int x, int y) {
        if (orig[x].d != orig[y].d) return orig[x].d < orig[y].d;
        return x < y;
    });

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}