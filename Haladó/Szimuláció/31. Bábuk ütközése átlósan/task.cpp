/*
Az átlósan mozgó bábuknál a két koordináta egyszerre változik, ezért a találkozást közös pozíció és azonos időpillanat alapján kell eldönteni. Ha ütköznek, az irányváltást egyszerre kell alkalmazni.
*/
/*
Hint 1: || Az átlós mozgásnál a két koordináta együtt változik, ezért a találkozást közös pozícióként kell figyelni. ||
Hint 2: || Ha két bábu ugyanarra a mezőre érkezik, egyszerre kell frissíteni az irányukat, különben rossz lesz az ütközés. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, l, k;
    cin >> n >> m >> l >> k;
    struct P { int x, y, dx, dy; };
    vector<P> p(l);
    map<string, pair<int,int>> d = {{"EN", {-1,-1}}, {"EK", {-1,1}}, {"DN", {1,-1}}, {"DK", {1,1}}};
    for (int i = 0; i < l; ++i) {
        string s; cin >> p[i].x >> p[i].y >> s;
        auto [dx, dy] = d[s]; p[i].dx = dx; p[i].dy = dy;
    }
    for (int t = 1; t <= k; ++t) {
        vector<pair<int,int>> pos(l);
        for (int i = 0; i < l; ++i) {
            int nx = p[i].x + p[i].dx, ny = p[i].y + p[i].dy;
            if (nx < 1 || nx > n) { p[i].dx *= -1; nx = p[i].x + p[i].dx; }
            if (ny < 1 || ny > m) { p[i].dy *= -1; ny = p[i].y + p[i].dy; }
            pos[i] = {nx, ny};
        }
        for (int i = 0; i < l; ++i) {
            for (int j = i + 1; j < l; ++j) {
                if (pos[i] == pos[j] || (pos[i].first == p[j].x && pos[i].second == p[j].y && pos[j].first == p[i].x && pos[j].second == p[i].y)) {
                    cout << t << '\n';
                    return 0;
                }
            }
        }
        for (int i = 0; i < l; ++i) p[i].x = pos[i].first, p[i].y = pos[i].second;
    }
    cout << -1 << '\n';
    return 0;
}