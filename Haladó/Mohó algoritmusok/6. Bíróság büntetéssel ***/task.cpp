/*
Megoldás lényege:
Az ügyeket határidő szerint haladva egy min-kupacba tesszük, és ha a kupac mérete meghaladja az aktuális határidőt, a legkisebb díjú ügyet kiejtjük. Így a kiesett ügyek díjösszege minimális lesz. A megmaradt ügyeket a határidejükhöz legközelebbi szabad napra ütemezzük (DSU segít megtalálni a szabad napot), a kiesőket pedig a maradék napokra tesszük. Az időigény O(N log N), ahol N az ügyek száma.
*/
/*
Hint 1: || Ha egy napra több ügy jutna, az on-time részhalmazban a nagyobb díjú ügyeket érdemes megtartani. ||
Hint 2: || A megtartott ügyeket a határidejükhöz legközelebbi szabad napra érdemes rakni, így a többi ügy is elférhet. ||
Hint 3: || A kiesett ügyeket a maradék szabad napokra tesszük; ezek díja adja a végső összeget. ||
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