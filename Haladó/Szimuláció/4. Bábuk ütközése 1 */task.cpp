/*
Megoldas: a bábuk egy egyenes pályán mozognak, a széleknél visszafordulnak.
Minden időlépésben kiszámoljuk az új pozíciókat, majd ellenőrizzük, hogy
valamelyik két bábu ugyanoda érkezett-e vagy egymáson átlépett-e.
*/
/*
Hint 1: || A bábuk mozgását időlépésenként szimuláld, és minden lépésben csak az aktuális pozíciójuk alapján dönts. ||
Hint 2: || A szélen a mozgás iránya változik meg, ezért a következő állapotot a szélső esetek kezelése adja. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, l, k;
    cin >> n >> l >> k;
    vector<int> pos(l), dir(l);
    for (int i = 0; i < l; ++i) {
        char c;
        cin >> pos[i] >> c;
        dir[i] = (c == 'J' ? 1 : -1);
    }

    for (int t = 1; t <= k; ++t) {
        vector<int> old = pos;
        for (int i = 0; i < l; ++i) {
            if (pos[i] == 1 && dir[i] == -1) dir[i] = 1;
            else if (pos[i] == n && dir[i] == 1) dir[i] = -1;
            pos[i] += dir[i];
        }

        for (int i = 0; i < l; ++i) {
            for (int j = i + 1; j < l; ++j) {
                if (pos[i] == pos[j] || (old[i] == pos[j] && old[j] == pos[i])) {
                    cout << t << '\n';
                    return 0;
                }
            }
        }
    }

    cout << -1 << '\n';
    return 0;
}