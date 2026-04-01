/*
Feladat: A lehető legtöbb néző igényét kell kielégíteni úgy, hogy mindenki egyetlen ülőhelyet kapjon a saját tartományán belül.
Ötlet: A kéréseket a felső határ szerint rendezzük, és minden igénynek a legkorábban szabad ülőhelyet adjuk. Ez a klasszikus interval scheduling / greedy assignment.
Hint 1: || A szűkebb igényeket érdemes előbb elhelyezni. ||
Hint 2: || Mindig a legkisebb még szabad helyet add oda, ami belefér a kért intervallumba. ||
Hint 3: || A szabad helyek kezeléséhez következő szabad hely DSU kell. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n = 0) { init(n); }
    void init(int n) { p.resize(n + 2); iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void use(int x) { p[x] = find(x + 1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n, k;
    cin >> m >> n >> k;
    vector<int> s(n + 1);
    for (int i = 1; i <= n; ++i) cin >> s[i];

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 1);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        if (s[a] + k != s[b] + k) return s[a] + k < s[b] + k;
        if (s[a] != s[b]) return s[a] < s[b];
        return a < b;
    });

    DSU dsu(m);
    vector<pair<int,int>> ans;
    for (int id : ord) {
        int seat = dsu.find(s[id]);
        if (seat <= min(m, s[id] + k)) {
            ans.push_back({id, seat});
            dsu.use(seat);
        }
    }

    cout << ans.size() << '\n';
    for (auto [id, seat] : ans) cout << id << ' ' << seat << '\n';
    return 0;
}