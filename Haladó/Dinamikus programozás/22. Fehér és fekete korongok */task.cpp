/*
Az intervallum két végétől lehet elvenni korongot, ezért az állapotot a megmaradt [l,r] rész írja le. Az első
játékos lépésekor a cél a megszerzett fehér korongok számának maximalizálása, a második játékos lépésekor pedig
ennek minimalizálása, mert a második játékost csak az érdekli, hogy az első minél kevesebb fehéret vigyen el.
Így két DP-t írunk fel ugyanarra az intervallumra: az egyik az első, a másik a második játékos következése esetén.
*/
/*
Hint 1: || A második játékos saját pontja nem számít, csak az, hogy az első játékosnak mennyi fehér marad. ||
Hint 2: || Külön állapot kell arra, amikor az első lép, és arra is, amikor a második. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 2, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<vector<int>> first(n + 2, vector<int>(n + 2, 0));
    vector<vector<int>> second(n + 2, vector<int>(n + 2, 0));

    for (int len = 1; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;
            first[l][r] = max(second[l + 1][r] + a[l], second[l][r - 1] + a[r]);
            second[l][r] = min(first[l + 1][r], first[l][r - 1]);
        }
    }

    cout << first[1][n] << '\n';
    return 0;
}