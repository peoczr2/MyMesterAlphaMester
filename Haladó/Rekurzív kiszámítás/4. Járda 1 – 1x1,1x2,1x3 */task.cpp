/*
Megoldás lényege:
Most az utolsó lap lehet 1, 2 vagy 3 hosszú, ezért a Fibonacci helyett egy
háromtagú rekurziót kapunk. Az üres járda továbbra is egyetlen megoldás.

*/

// Hint 1: || Nézd meg, milyen hosszúságú lap állhat legutoljára a lefedésben. ||
// Hint 2: || A rekurzió alapjai: hossz 0-ra 1, majd onnan építkezünk tovább. ||
// Hint 3: || A kis N miatt akár sima dinamikus programozás is tökéletes. ||

#include <bits/stdc++.h>
#include "../bigint.hpp"
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<BigInt> dp(max(3, N + 1));
    dp[0] = 1;
    if (N >= 1) dp[1] = 1;
    if (N >= 2) dp[2] = 2;
    for (int i = 3; i <= N; ++i) dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];

    cout << dp[N] << '\n';
    return 0;
}
