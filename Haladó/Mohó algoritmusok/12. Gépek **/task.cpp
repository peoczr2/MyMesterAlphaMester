/*
Feladat: Az N munkát a lehető legkevesebb gépre kell ütemezni úgy, hogy minden munka a határidőig elkészüljön.
Ötlet: Először kiszámoljuk, hogy egy géphez hány munka jutna adott határidőig; ebből a maximális napi terhelés adja a szükséges gépszámot. Ezután a munkákat határidő szerint sorba rendezve, napokra és gépekre osztjuk.
Hint 1: || Az i. napig legfeljebb G*i munka fér el, ha G gépünk van. ||
Hint 2: || A szükséges gépszám a prefixekre vett ceil(eddigi munkák száma / napok száma) maximuma. ||
Hint 3: || Ha G ismert, a munkákat határidő szerint rendezve lehet a legkésőbbi szabad napra tenni. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n = 0) { init(n); }
    void init(int n) {
        p.resize(n + 1);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void use(int x) { p[x] = find(x - 1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> h(m + 1);
    for (int i = 1; i <= m; ++i) cin >> h[i];

    vector<int> cnt(n + 1, 0);
    for (int x : h) ++cnt[x];
    int pref = 0, g = 0;
    for (int d = 1; d <= n; ++d) {
        pref += cnt[d];
        g = max(g, (pref + d - 1) / d);
    }

    vector<pair<int, int>> jobs;
    jobs.reserve(m);
    for (int i = 1; i <= m; ++i) jobs.push_back({h[i], i});
    sort(jobs.begin(), jobs.end());

    DSU dsu(n);
    vector<int> usedOnDay(n + 1, 0), dayOfJob(m + 1), machineOfJob(m + 1);
    for (auto [deadline, id] : jobs) {
        int day = dsu.find(deadline);
        while (day > 0 && usedOnDay[day] == g) day = dsu.find(day - 1);
        dayOfJob[id] = day;
        machineOfJob[id] = usedOnDay[day] + 1;
        ++usedOnDay[day];
        if (usedOnDay[day] == g) dsu.use(day);
    }

    cout << g << '\n';
    for (int i = 1; i <= m; ++i) {
        cout << dayOfJob[i] << ' ' << machineOfJob[i] << '\n';
    }
    return 0;
}