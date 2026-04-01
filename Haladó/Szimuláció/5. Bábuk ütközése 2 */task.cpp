/*
Megoldas: a bábuk két dimenzióban mozognak, a széleknél megállnak.
Minden időlépésben egyet próbálnak lépni, majd ellenőrizzük az új helyeket és
az egymáson átlépést is.
*/
/*
Hint 1: || A sorrend fontos: a bábuk helyzetét mindig az előző időpillanatból kell frissíteni, különben az ütközések összekeverednek. ||
Hint 2: || Ha két bábu ugyanabba a mezőbe érne, az új állapotot az ütközési szabály dönti el. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, l, k;
    cin >> n >> m >> l >> k;
    vector<int> x(l), y(l), dx(l), dy(l);
    for (int i = 0; i < l; ++i) {
        char c;
        cin >> x[i] >> y[i] >> c;
        if (c == 'F') dx[i] = -1;
        if (c == 'L') dx[i] = 1;
        if (c == 'J') dy[i] = 1;
        if (c == 'B') dy[i] = -1;
    }

    for (int t = 1; t <= k; ++t) {
        vector<int> ox = x, oy = y;
        for (int i = 0; i < l; ++i) {
            int nx = x[i] + dx[i], ny = y[i] + dy[i];
            if (nx < 1 || nx > n) nx = x[i];
            if (ny < 1 || ny > m) ny = y[i];
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