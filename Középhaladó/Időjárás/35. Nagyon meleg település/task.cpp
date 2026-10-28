/*
Megoldás lényege:
Minden településre a sor beolvasása közben kiszámoljuk a legkisebb és a legnagyobb előrejelzett hőmérsékletet. Az i. település akkor felel meg, ha van olyan másik k település (k ≠ i), amelynek legnagyobb értéke kisebb az i. település legkisebb értékénél. A településeket sorszám szerint vizsgáljuk, és az első megfelelőt írjuk ki; ha nincs ilyen, a válasz -1. Az idő O(N·M + N²), a memória O(N).
*/
/*
Hint 1: || Egy településhez két érték elég: a napi előrejelzések legkisebbike és legnagyobbika. A keresett i településre a feltétel: a legkisebb értéke nagyobb valamely másik k település legnagyobb értékénél. ||
Hint 2: || Mindkét értéket a sor beolvasása közben számold ki egy-egy változóban. Utána minden i-re keress olyan k ≠ i települést, amelyre legkisebb[i] > legnagyobb[k]; az első ilyen i a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> legkisebb(n + 1, INT_MAX), legnagyobb(n + 1, INT_MIN);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int h;
            cin >> h;
            legkisebb[i] = min(legkisebb[i], h);
            legnagyobb[i] = max(legnagyobb[i], h);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int k = 1; k <= n; k++) {
            if (k != i && legkisebb[i] > legnagyobb[k]) {
                cout << i << '\n';
                return 0;
            }
        }
    }

    cout << -1 << '\n';
    return 0;
}
