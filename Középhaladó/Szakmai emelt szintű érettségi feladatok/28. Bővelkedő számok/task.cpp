/*
Megoldás lényege:
A kombináció értéke (n k) = n! / (k! * (n-k)!). Mivel n legfeljebb 12, az összes lehetséges (n, k) érték előre kiszámolható egy 13 x 13-as táblázatba Pascal-háromszög szerint: minden elem a fölötte lévő két elem összege. Így nincs szükség faktoriálisokra és osztásra. A bemenő párokat ezután egyetlen táblázat-olvasással válaszoljuk meg, tehát az időigény O(M), a táblázat építése pedig állandó.
*/
/*
Hint 1: || Mivel n legfeljebb 12, csak kevés különböző (n, k) pár lehetséges. Érdemes ezeket egyszer kiszámolni, és a bemenet minden sorára csak kiolvasni az értéket. ||
Hint 2: || A kombinációkra igaz, hogy (n k) = (n-1 k-1) + (n-1 k), továbbá (n 0) = (n n) = 1. Ezzel a rekurzióval építhető fel a Pascal-háromszög. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAXN = 12;
    long long C[MAXN + 1][MAXN + 1] = {};
    for (int n = 0; n <= MAXN; ++n) {
        C[n][0] = 1;
        for (int k = 1; k <= n; ++k) {
            C[n][k] = C[n - 1][k - 1] + C[n - 1][k];
        }
    }

    int m;
    cin >> m;
    while (m--) {
        int n, k;
        cin >> n >> k;
        cout << C[n][k] << '\n';
    }
    return 0;
}
