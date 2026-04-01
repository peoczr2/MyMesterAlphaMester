/*
Feladat: Minden percre legalább két ügyeletes kell, és a lehető legkevesebb jelentkezőt kell kiválasztani.
Ötlet: Időben előrehaladva mindig azt az intervallumot vesszük fel, amelyik a jelenlegi pontot lefedi, és a legtovább tart. Ha a lefedettség 2 alá csökken, új intervallumot kell választani.
Hint 1: || Minden perc előtt az addig már kezdődött jelentkezőket tedd egy heapbe. ||
Hint 2: || Ha a kiválasztott ügyeletesek száma 2 alá esik, válaszd a leghosszabban tartó jelölteket. ||
Hint 3: || Ha nem tudsz két élőt biztosítani, nincs megoldás. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct App { int s, e, id; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    vector<App> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].s >> a[i].e;
        a[i].id = i + 1;
    }
    sort(a.begin(), a.end(), [](const App &x, const App &y) {
        if (x.s != y.s) return x.s < y.s;
        if (x.e != y.e) return x.e > y.e;
        return x.id < y.id;
    });

    priority_queue<pair<int,int>> cand;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> active;
    vector<int> chosen;
    int ptr = 0;
    for (int t = 1; t <= m; ++t) {
        while (ptr < n && a[ptr].s <= t) {
            cand.push({a[ptr].e, a[ptr].id});
            ++ptr;
        }
        while (!active.empty() && active.top().first < t) active.pop();
        while ((int)active.size() < 2) {
            while (!cand.empty() && cand.top().first < t) cand.pop();
            if (cand.empty()) {
                cout << 0 << '\n';
                return 0;
            }
            auto [e, id] = cand.top(); cand.pop();
            active.push({e, id});
            chosen.push_back(id);
        }
    }

    cout << chosen.size() << '\n';
    for (int i = 0; i < (int)chosen.size(); ++i) {
        if (i) cout << ' ';
        cout << chosen[i];
    }
    cout << '\n';
    return 0;
}