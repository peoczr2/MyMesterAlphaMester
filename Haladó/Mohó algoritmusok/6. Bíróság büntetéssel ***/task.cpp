/*
Feladat: A bírságok összegét minimalizáljuk úgy, hogy minden ügyet a napok valamelyikére beosztjuk.
Ötlet: Határidő szerint haladva mindig a már kiválasztott, legkisebb bírságú ügyet dobjuk ki, ha túl sok lenne az on-time feladat. Ez a klasszikus deadline + min-heap stratégia.
Hint 1: || Ha egy napra több ügy jutna, abból az on-time részhalmaznak a legnagyobb bírságúakat érdemes megtartani. ||
Hint 2: || A végleges on-time halmazt utólag a legkésőbbi szabad napokra lehet bepakolni. ||
Hint 3: || A kiesők mennek a napok végére, tetszőleges sorrendben. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n = 0) { init(n); }
    void init(int n) { p.resize(n + 1); iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void use(int x) { p[x] = find(x - 1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int, int>> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i].first >> a[i].second;

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 1);
    sort(ord.begin(), ord.end(), [&](int x, int y) {
        if (a[x].first != a[y].first) return a[x].first < a[y].first;
        if (a[x].second != a[y].second) return a[x].second > a[y].second;
        return x < y;
    });

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<int> keep(n + 1, 0);
    long long penalty = 0;
    for (int id : ord) {
        pq.push({a[id].second, id});
        keep[id] = 1;
        if ((int)pq.size() > a[id].first) {
            auto [w, j] = pq.top();
            pq.pop();
            keep[j] = 0;
            penalty += w;
        }
    }

    vector<int> ontime, late;
    for (int i = 1; i <= n; ++i) (keep[i] ? ontime : late).push_back(i);
    sort(ontime.begin(), ontime.end(), [&](int x, int y) {
        if (a[x].first != a[y].first) return a[x].first < a[y].first;
        return x < y;
    });

    DSU dsu(n);
    vector<int> dayJob(n + 1, 0);
    for (int id : ontime) {
        int day = dsu.find(a[id].first);
        dayJob[day] = id;
        dsu.use(day);
    }
    int ptr = 0;
    for (int day = 1; day <= n; ++day) {
        if (!dayJob[day]) dayJob[day] = late[ptr++];
    }

    cout << penalty << '\n';
    for (int day = 1; day <= n; ++day) {
        if (day > 1) cout << ' ';
        cout << dayJob[day];
    }
    cout << '\n';
    return 0;
}