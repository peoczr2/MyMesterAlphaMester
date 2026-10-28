/*
Megoldás lényege:
A négy irány (bal, alsó, jobb, felső) egymástól független, ezért mindegyiket külön számoljuk, mindig a kép szélétől befelé haladva.
Egy oszlop akkor vágható le, ha a két képen a teljes oszlopa megegyezik; egy sor akkor, ha a teljes sora megegyezik.
Balról és jobbról oszlopokat, alulról és felülről sorokat vizsgálunk, és az első eltérésnél megállunk: a megálló előtti darabszám adja a levágható méretet.
A kiírás sorrendje: bal, alsó, jobb, felső. Minden irányban legfeljebb egyszer haladunk végig a képen, így az időigény O(N·M).
*/
/*
Hint 1: || A négy irányt egymástól függetlenül kezeld: mindegyiknél a kép szélétől kezdve haladj befelé. ||
Hint 2: || Egy oszlopról vagy sorról elég annyit tudni, hogy a két képen minden pontja egyezik-e. Írj rá egy kis függvényt, és az első eltérésnél állj meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n, vector<int>(m)), b(n, vector<int>(m));
    for (auto& row : a)
        for (int& x : row)
            cin >> x;
    for (auto& row : b)
        for (int& x : row)
            cin >> x;

    auto colSame = [&](int j) {
        for (int i = 0; i < n; ++i)
            if (a[i][j] != b[i][j])
                return false;
        return true;
    };
    auto rowSame = [&](int i) {
        for (int j = 0; j < m; ++j)
            if (a[i][j] != b[i][j])
                return false;
        return true;
    };

    int left = 0;
    while (left < m && colSame(left))
        ++left;

    int bottom = 0;
    while (bottom < n && rowSame(n - 1 - bottom))
        ++bottom;

    int right = 0;
    while (right < m && colSame(m - 1 - right))
        ++right;

    int top = 0;
    while (top < n && rowSame(top))
        ++top;

    cout << left << ' ' << bottom << ' ' << right << ' ' << top << "\n";
    return 0;
}
