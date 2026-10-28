/*
 * Barátságos számpárok keresése. Először szitával kiszámoljuk minden 1..N szám valódi osztóinak összegét (minden d
 * szám a többszöröseinek osztója), majd azokat a P < Q párokat írjuk ki, amelyekre sum[P] = Q és sum[Q] = P.
 * A szita O(N log N) időben fut.
*/
/*
Hint 1: || Előbb minden számhoz számold ki a valódi osztók összegét, és csak utána keresd a párokat. ||
Hint 2: || Ha sum[P]=Q, sum[Q]=P és P<Q, akkor megvan egy barátságos pár, amit pontosan egyszer kell kiírni. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> sum(n + 1);
    for (int d = 1; d * 2 <= n; ++d) {
        for (int m = d * 2; m <= n; m += d) sum[m] += d;
    }
    for (int p = 2; p <= n; ++p) {
        int q = sum[p];
        if (q > p && q <= n && sum[q] == p) {
            cout << p << ' ' << q << '\n';
        }
    }
    return 0;
}
