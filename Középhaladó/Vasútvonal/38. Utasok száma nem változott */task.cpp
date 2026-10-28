/*
Megoldás lényege:
Egy állomáson nem változik az utasok száma, ha ugyanannyian szálltak le, mint fel, vagyis le = fel. Egy bejárásban megkeressük az első ilyen állomást.
Ha nincs ilyen állomás, a válasz N+1. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Az utasok száma akkor nem változik, ha a leszállók és a felszállók száma megegyezik. ||
Hint 2: || Olvasd be az állomásokat sorban, és az első olyan állomásnál, ahol le = fel, jegyezd meg a sorszámát. Ha végig nincs ilyen, a válasz N+1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int ans = n + 1;
    for (int i = 1; i <= n; i++) {
        long long le, fel;
        cin >> le >> fel;
        if (ans == n + 1 && le == fel) ans = i;
    }

    cout << ans << "\n";
    return 0;
}
