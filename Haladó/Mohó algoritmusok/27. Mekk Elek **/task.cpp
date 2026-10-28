/*
Megoldás lényege: A munkákat határidő szerint növekvő sorrendben dolgozzuk fel, és mindegyiket a határidejéig még szabad legkésőbbi napra tesszük, ha van ilyen; ha nincs, a munka kimarad. Így a korábbi napok a szorosabb határidejű munkáknak maradnak. Ez a mohó választás maximális darabszámot ad, mert egy munka felvételének egyetlen feltétele, hogy legyen szabad nap a határidejéig. A szabad napokat DSU tartja nyilván, az időigény O(N log N), ahol N a munkák száma.
*/
/*
Hint 1: || Ha egy munka nem fér be a határidejéig, akkor a későbbi napokon sem javítható meg. ||
Hint 2: || Feldolgozd a munkákat határidő szerint növekvően, és mindegyiknél keresd meg a legkésőbbi szabad napot a határidőig. ||
Hint 3: || A kiválasztott munkák napra helyezéséhez DSU-t érdemes használni. ||
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

    int m, n;
    cin >> m >> n;
    vector<int> d(n + 1);
    for (int i = 1; i <= n; ++i) cin >> d[i];

    vector<pair<int, int>> jobs;
    jobs.reserve(n);
    for (int i = 1; i <= n; ++i) jobs.push_back({d[i], i});
    sort(jobs.begin(), jobs.end());

    DSU dsu(m);
    vector<int> dayOfJob(n + 1, 0);
    int done = 0;
    for (auto [deadline, id] : jobs) {
        int day = dsu.find(deadline);
        if (day == 0) continue;
        dayOfJob[id] = day;
        ++done;
        dsu.use(day);
    }

    cout << done << '\n';
    for (int i = 1; i <= n; ++i) {
        if (dayOfJob[i]) {
            cout << i << ' ' << dayOfJob[i] << '\n';
        }
    }
    return 0;
}