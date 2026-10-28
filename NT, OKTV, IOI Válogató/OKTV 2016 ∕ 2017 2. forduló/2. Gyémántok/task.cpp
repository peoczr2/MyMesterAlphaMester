/*
Megoldás lényege: azt kell megszámolni, hányféleképpen írható fel N mint különböző pozitív egészek összege, a tagok sorrendjétől eltekintve. Mivel minden szám legfeljebb egyszer szerepelhet, ez egy 0/1 hátizsák-típusú számolás: dp[j] azt tárolja, hányféle felbontás van j-re az eddig vizsgált számokkal. Egy k szám figyelembevételénél j-t visszafelé haladva frissítjük, így ugyanaz a k nem kerülhet be kétszer. Az időigény O(N^2), N <= 200 esetén ez bőven elég, a válasz pedig 64 bites egészben elfér.
*/
/*
Hint 1: || Gondolj a 0/1 hátizsák problémára: minden k számot legfeljebb egyszer használhatsz, és a tagok sorrendje nem számít. ||
Hint 2: || Legyen dp[j] azon felbontások száma, amelyek összege j. Egy új k szám bevételekor a dp[j] += dp[j-k] frissítést j-től visszafelé, k-tól N-ig végezd, hogy ne kerülhessen be ugyanaz a szám kétszer. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> dp(n + 1, 0);
    dp[0] = 1;
    for (int k = 1; k <= n; k++) {
        for (int j = n; j >= k; j--) {
            dp[j] += dp[j - k];
        }
    }

    cout << dp[n] << '\n';
    return 0;
}
