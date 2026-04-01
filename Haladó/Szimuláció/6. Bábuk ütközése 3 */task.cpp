/*
Megoldas: a bábuk 2D-ben mozognak, a széleknél visszafordulnak.
Minden időlépésben előbb a következő pozíciókat számoljuk ki, majd azonos
mezőre érkezés vagy átlépés esetén megállunk.
*/
/*
Hint 1: || Két dimenzióban a helyzetet és az irányvektort együtt érdemes tárolni. ||
Hint 2: || Az ütközés utáni mozgás egyszerűen az irány előjelének vagy összetevőinek módosítása. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, l, k;
    cin >> n >> m >> l >> k;
    vector<int> x(l), y(l), dx(l), dy(l);
    auto parse = [&](const string& s) {
        if (s == "F") return pair<int,int>{-1,0};
        if (s == "L") return pair<int,int>{1,0};
        if (s == "B") return pair<int,int>{0,-1};
        if (s == "J") return pair<int,int>{0,1};
        return pair<int,int>{0,0};
    };
    for (int i = 0; i < l; ++i) {
        string s;
        cin >> x[i] >> y[i] >> s;
        tie(dx[i], dy[i]) = parse(s);
    }

    for (int t = 1; t <= k; ++t) {
        vector<int> ox = x, oy = y;
        for (int i = 0; i < l; ++i) {
            int nx = x[i] + dx[i], ny = y[i] + dy[i];
            if (nx < 1 || nx > n) {
                dx[i] *= -1;
                nx = x[i] + dx[i];
            }
            if (ny < 1 || ny > m) {
                dy[i] *= -1;
                ny = y[i] + dy[i];
            }
            x[i] = nx;
            y[i] = ny;
        }
        for (int i = 0; i < l; ++i) {
            for (int j = i + 1; j < l; ++j) {
                if ((x[i] == x[j] && y[i] == y[j]) || (ox[i] == x[j] && oy[i] == y[j] && ox[j] == x[i] && oy[j] == y[i])) {
                    cout << t << '\n';
                    return 0;
                }
            }
        }
    }

    cout << -1 << '\n';
    return 0;
}