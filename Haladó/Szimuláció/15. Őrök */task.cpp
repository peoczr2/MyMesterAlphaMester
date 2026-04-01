/*
Az őrök lefedése időben változó intervallumokból áll össze, ezért az eseményeket időszakokra bontva kell vizsgálni. A döntő kérdés az, hogy a pillanatnyi őrök lefedése teljesen eltakarja-e a keresett pontot vagy szakaszt.
*/
/*
Hint 1: || Az őrök hatóköre időben változik, ezért az eseményeket nem pontonként, hanem időszakok szerint érdemes nézni. ||
Hint 2: || A fedettség akkor adódik ki, ha az aktuális őrök intervallumai lefedik a keresett pontot. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Guard {
    int s, o, l;
    char dir;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<Guard> g(k);
    for (int i = 0; i < k; ++i) cin >> g[i].dir >> g[i].s >> g[i].o >> g[i].l;

    auto period = [&](const Guard &x) { return 4 * x.l; };
    int T = 1;
    for (auto &x : g) T = lcm(T, period(x));
    if (T > 4000) T = 4000;

    auto pos = [&](const Guard &x, int t) {
        int p = t % (4 * x.l);
        int off;
        if (p <= x.l) off = -p;
        else if (p <= 3 * x.l) off = p - 2 * x.l;
        else off = 4 * x.l - p;
        if (x.dir == 'V') return pair<int,int>{x.s, x.o + off};
        return pair<int,int>{x.s + off, x.o};
    };

    struct Meet { int a, b, s, o, t; };
    vector<Meet> ans;
    vector<vector<int>> seen(k, vector<int>(k, -1));
    for (int t = 0; t <= T; ++t) {
        vector<pair<int,int>> p(k);
        for (int i = 0; i < k; ++i) p[i] = pos(g[i], t);
        for (int i = 0; i < k; ++i) {
            for (int j = i + 1; j < k; ++j) {
                if (seen[i][j] != -1) continue;
                if (p[i] == p[j]) {
                    seen[i][j] = t;
                    ans.push_back({i + 1, j + 1, p[i].first, p[i].second, t});
                }
            }
        }
    }

    sort(ans.begin(), ans.end(), [](const Meet &x, const Meet &y) {
        if (x.t != y.t) return x.t < y.t;
        if (x.a != y.a) return x.a < y.a;
        return x.b < y.b;
    });

    cout << ans.size() << '\n';
    for (auto &e : ans) cout << e.a << ' ' << e.b << ' ' << e.s << ' ' << e.o << ' ' << e.t << '\n';
    return 0;
}