/*
Megoldás lényege:
Az s. évben ültetett növény a s+M-1 és s+M+K-2 évek között minden évben egy
magot hoz, a magból pedig a következő évben kel ki új növény. Így a t. évben
kikelő növények száma a t-M-K+1 és t-M évek között kikelt növények összege, amit
prefixösszegekkel csúszó ablakként számolunk.
Az élő növények számát úgy frissítjük, hogy minden év kikelőit hozzáadjuk az
összeshez, és az N évvel korábban kikeltek számát, akik ebben az évben
elpusztulnak, kivonjuk belőle. Minden lépésben 20180113-mal maradékoljuk a
számokat, a negatív maradékot pedig javítjuk.
Az algoritmus O(X) időben fut, ami X ≤ 100 000 mellett bőven az időlimiten belül
van; a kiírt két szám az X. évi kikelő, illetve az X. évben élő növények
maradéka.
*/
/*
Hint 1: || Egy év kikelőinek száma a t-M-K+1 és t-M közötti évek kikelőinek
összege: ezek a növények adnak magot a t-1. évben. Az ablak két határát M és K
adja meg. ||
Hint 2: || Tároljuk az évenkénti kikelők prefixösszegét, így egy ablak összege
két prefixösszeg különbsége, O(1) idő alatt. Az élő növények számát az előző
évhez képest frissítjük: hozzáadjuk az újonnan kikelőket, és kivonjuk az N évvel
korábban kikelteket. A műveleteket minden lépésben a 20180113 szerinti
maradékban végezzük. ||
*/

#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 20180113;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, l;
    cin >> n >> m >> k >> l;
    int x;
    cin >> x;

    vector<long long> born(x + 1, 0), pref(x + 1, 0), all(x + 1, 0);
    born[1] = l % MOD;
    pref[1] = born[1];
    all[1] = born[1];

    for (int t = 2; t <= x; ++t) {
        long long left = t - m - k;
        long long right = t - m;
        long long sum = 0;
        if (right >= 1) sum += pref[right];
        if (left >= 1) sum -= pref[left];
        sum %= MOD;
        if (sum < 0) sum += MOD;
        born[t] = sum;
        pref[t] = (pref[t - 1] + born[t]) % MOD;
        all[t] = (all[t - 1] + born[t]) % MOD;
        if (t > n) {
            all[t] -= born[t - n];
            all[t] %= MOD;
            if (all[t] < 0) all[t] += MOD;
        }
    }

    cout << born[x] % MOD << '\n' << all[x] % MOD << '\n';
    return 0;
}