/*
Megoldas lenyege:
Minden áruhoz megjegyezzük az első és a második üzletben látott árat. Azok a
kódok kellenek, amelyek mindkét üzletben szerepelnek, és mindkét ár kisebb X-nél.
A kódok száma legfeljebb 1000 körüli, ezért egy rendezett tárolóval egyszerűen
összegyűjthetők és növekvő sorrendben kiírhatók.
*/
/*
Hint 1: || Egy áru csak akkor jó, ha mindkét üzletben megvan és mindkét ára kisebb X-nél. ||
Hint 2: || Tárold külön a két üzlet árait kód szerint. ||
Hint 3: || A megfelelők kódját rendezd növekvő sorrendbe a kiírás előtt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, x;
    cin >> n >> m >> x;
    map<int, int> a, b;
    for (int i = 0; i < n; ++i) {
        int code, price;
        cin >> code >> price;
        a[code] = price;
    }
    for (int i = 0; i < m; ++i) {
        int code, price;
        cin >> code >> price;
        b[code] = price;
    }

    vector<int> ans;
    for (auto &[code, price] : a) {
        auto it = b.find(code);
        if (it != b.end() && price < x && it->second < x) ans.push_back(code);
    }

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
