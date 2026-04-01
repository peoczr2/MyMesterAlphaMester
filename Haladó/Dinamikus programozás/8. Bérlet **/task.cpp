/*
Az egyes megrendelések súlya az általuk lefedett napok száma, és nem fedhetnek át egymással, ezért ez
klasszikus súlyozott intervallumütemezés. Az intervallumokat végpont szerint rendezzük, minden i-re megkeressük
bináris kereséssel az utolsó olyan korábbi intervallumot, amely még az i-edik kezdete előtt véget ér. Ezután
dp[i]=max(dp[i-1], dp[p(i)]+hossz(i)), és visszafejtjük az elfogadott megrendelések eredeti sorszámait.
*/
/*
Hint 1: || Az optimalizálandó érték nem a megrendelések száma, hanem a lefedett napok száma. ||
Hint 2: || Sorbarendezés után minden intervallumhoz keresd meg az utolsó kompatibilis előzőt. ||
Hint 3: || Ugyanaz a DP kell, mint a súlyozott intervallumütemezésnél. ||
*/

#include <bits/stdc++.h>

using namespace std;

struct Order {
    int start;
    int finish;
    int index;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Order> orders(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> orders[i].start >> orders[i].finish;
        orders[i].index = i;
    }

    sort(orders.begin() + 1, orders.end(), [](const Order& a, const Order& b) {
        if (a.finish != b.finish) {
            return a.finish < b.finish;
        }
        return a.start < b.start;
    });

    vector<int> finishes(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        finishes[i] = orders[i].finish;
    }

    vector<long long> dp(n + 1, 0);
    vector<int> prev_ok(n + 1, 0);
    vector<char> take(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        int p = int(upper_bound(finishes.begin() + 1, finishes.begin() + i, orders[i].start - 1) - finishes.begin()) - 1;
        prev_ok[i] = p;
        long long len = orders[i].finish - orders[i].start + 1;
        long long with = dp[p] + len;
        long long without = dp[i - 1];
        if (with > without) {
            dp[i] = with;
            take[i] = 1;
        } else {
            dp[i] = without;
        }
    }

    vector<int> chosen;
    for (int i = n; i >= 1;) {
        if (take[i] && dp[i] == dp[prev_ok[i]] + (orders[i].finish - orders[i].start + 1)) {
            chosen.push_back(orders[i].index);
            i = prev_ok[i];
        } else {
            --i;
        }
    }
    reverse(chosen.begin(), chosen.end());

    cout << dp[n] << '\n';
    cout << chosen.size() << '\n';
    for (int i = 0; i < (int)chosen.size(); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << chosen[i];
    }
    cout << '\n';
    return 0;
}