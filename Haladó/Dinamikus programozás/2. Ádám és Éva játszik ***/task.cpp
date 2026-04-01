/*
Itt közvetlenül az f[k][h] dinamikus programozást kell kiszámolni, ahol f[k][h] azt adja meg,
legfeljebb k kérdéssel és legfeljebb h darab "nem" válasszal mekkora N tartomány fedhető le biztosan.
Az első kérdés után az "igen" ágban h nem-válasz marad, a "nem" ágban h-1, ezért a visszavezetés
f[k][h]=f[k-1][h]+f[k-1][h-1]. Az alapérték minden oszlopban 1, mert kérdés nélkül csak egyetlen szám
azonosítható biztosan. A kért legnagyobb N éppen f[K][H].
*/
/*
Hint 1: || Ugyanazt a táblázatot érdemes felírni, mint az előző feladatban, csak most nem keresni kell benne, hanem kiírni az adott cellát. ||
Hint 2: || A két ág kezelhető mérete összeadódik, mert a kérdés a tartományt két részre bontja. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, h;
    cin >> k >> h;

    vector<long long> dp(k + 1, 1);
    for (int no = 1; no <= h; ++no) {
        vector<long long> next = dp;
        for (int q = 1; q <= k; ++q) {
            next[q] = next[q - 1] + dp[q - 1];
        }
        dp.swap(next);
    }

    cout << dp[k] << '\n';
    return 0;
}