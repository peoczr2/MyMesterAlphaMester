/*
 * Az erősen összetett számok azok, amelyeknek a pozitív osztóinak száma új
 * rekordot jelent. Minden szám osztószámát megszámoljuk, és a rekordokat kiírjuk.
 
Hint 1: || Erősen összetett szám akkor lesz valami, ha az osztóinak száma nagyobb minden kisebb száménál. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> divs(n + 1, 0);
    for (int d = 1; d <= n; ++d) {
        for (int m = d; m <= n; m += d) ++divs[m];
    }
    int best = 0;
    bool first = true;
    for (int x = 1; x <= n; ++x) {
        if (divs[x] > best) {
            best = divs[x];
            if (!first) cout << ' ';
            first = false;
            cout << x;
        }
    }
    cout << '\n';
    return 0;
}
