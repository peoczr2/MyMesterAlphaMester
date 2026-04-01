/*
Megoldas lenyege:
Mindkét üzletből kiolvassuk az árukat kód szerint. Egy áru akkor jó, ha legalább
az egyik üzletben X-nél olcsóbb. Ezt kódonként megvizsgáljuk, és azokat a
kódokat gyűjtjük össze, amelyek teljesítik a feltételt.
*/
/*
Hint 1: || Most elég az is, ha valamelyik üzletben olcsóbb a termék X-nél. ||
Hint 2: || Kód szerint tárold az árakat, hogy a két üzletet össze tudd hasonlítani. ||
Hint 3: || A megfelelők kódját rendezetten kell kiírni. ||
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

    set<int> ans;
    for (auto &[code, price] : a) if (price < x) ans.insert(code);
    for (auto &[code, price] : b) if (price < x) ans.insert(code);

    cout << ans.size() << '\n';
    bool first = true;
    for (int code : ans) {
        if (!first) cout << ' ';
        first = false;
        cout << code;
    }
    cout << '\n';
    return 0;
}
