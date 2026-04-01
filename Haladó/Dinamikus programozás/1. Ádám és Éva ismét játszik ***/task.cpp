/*
Az f[k][h] értékkel azt jelöljük, hogy legfeljebb k kérdéssel és legfeljebb h darab "nem"
válasszal hány különböző szám különíthető el biztosan. Egy kérdés két részre bontja a lehetőségeket:
az "igen" ágban h változatlan marad, a "nem" ágban eggyel csökken, ezért f[k][h]=f[k-1][h]+f[k-1][h-1].
Az alaphelyzet az, hogy nulla engedett "nem" válasszal csak egyetlen szám kezelhető biztosan, és minden
számolást N-nél levágunk. A minimális H az első olyan érték, amelyre f[K][H]>=N; ha ilyen nincs, -1 a válasz.
*/
/*
Hint 1: || Először ne a keresett minimális H-t számold, hanem azt, hogy adott K és H mellett mekkora tartomány kezelhető biztosan. ||
Hint 2: || Egy kérdés után az "igen" és a "nem" ág külön altartományt kezel; ezek mérete összeadódik. ||
Hint 3: || A táblázat Pascal-háromszögszerűen épül fel, csak az értékeket elég N-nél levágni. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    int k;
    cin >> n >> k;

    vector<long long> dp(k + 1, 1);
    if (n <= 1) {
        cout << 0 << '\n';
        return 0;
    }

    for (int h = 1; h <= k; ++h) {
        vector<long long> next = dp;
        for (int q = 1; q <= k; ++q) {
            next[q] = min(n, next[q - 1] + dp[q - 1]);
        }
        dp.swap(next);
        if (dp[k] >= n) {
            cout << h << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';
    return 0;
}