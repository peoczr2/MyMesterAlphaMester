/*
Megoldás lényege:
Minden bábu helyzetét és átlós irányvektorát (dx, dy) tároljuk, és az időt egyesével léptetjük K-ig.
Ha egy bábu a tábla széléről lépne ki, mindkét iránykomponenst az ellenkezőjére változtatjuk, így
visszafelé lép, ahonnan jött. Egy lépés után két esetben van ütközés: ha két bábu ugyanarra a mezőre
lép, vagy ha egy bábu olyan mezőre lép, ahol az adott pillanatban másik bábu áll (ebbe a
két bábu helyének felcserélése is beletartozik). Az első ilyen időpont az eredmény, különben -1.
Mivel L <= 100 és K <= 1000, az összes párvizsgálat legfeljebb kb. 10^7 művelet.
*/
/*
Hint 1: || Tartsd nyilván minden bábu helyzetét és átlós irányvektorát; a tábla szélénél mindkét komponens előjele megfordul. ||
Hint 2: || K és L is kicsi (K <= 1000, L <= 100), ezért az időt egyesével léptetve, minden lépésben minden bábupárt ellenőrizhetsz. ||
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
            if (nx < 1 || nx > n || ny < 1 || ny > m) {
                p[i].dx *= -1;
                p[i].dy *= -1;
                nx = p[i].x + p[i].dx;
                ny = p[i].y + p[i].dy;
            }
            pos[i] = {nx, ny};
        }
        for (int i = 0; i < l; ++i) {
            for (int j = 0; j < l; ++j) {
                if (i == j) continue;
                bool sameCell = (i < j) && pos[i] == pos[j];
                bool onOccupied = pos[i] == make_pair(p[j].x, p[j].y);
                if (sameCell || onOccupied) {
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
