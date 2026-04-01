/*
Minden megrendelés egy zárt időintervallum, és ha két elfogadott megrendelés metszi egymást, akkor a járművet nem
lehet mindkettőnek kiadni. A célfüggvény az elfoglalt napok számának maximalizálása, ami pontosan súlyozott intervallum-
ütemezés: az i-edik rendelés súlya Bi-Ai+1, és az utolsó vele kompatibilis előd bináris kereséssel megkereshető. Ebből
O(NlogN) időben kiszámítható a maximális kiadott napok száma.
*/
/*
Hint 1: || Egy rendelés értéke nem 1, hanem a teljes hossza. ||
Hint 2: || Két rendelés akkor fér meg egymás mellett, ha az első vége szigorúan kisebb a második elejénél. ||
*/

#include <bits/stdc++.h>

using namespace std;

struct Order {
    int l;
    int r;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Order> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].l >> a[i].r;
    }
    sort(a.begin() + 1, a.end(), [](const Order& x, const Order& y) {
        if (x.r != y.r) {
            return x.r < y.r;
        }
        return x.l < y.l;
    });

    vector<int> ends(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        ends[i] = a[i].r;
    }

    vector<int> dp(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int p = int(lower_bound(ends.begin() + 1, ends.begin() + i, a[i].l) - ends.begin()) - 1;
        dp[i] = max(dp[i - 1], dp[p] + a[i].r - a[i].l + 1);
    }

    cout << dp[n] << '\n';
    return 0;
}
