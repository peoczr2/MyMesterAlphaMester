/*
Megoldás lényege:
Az s. évben ültetett virág a s+M-1 és s+M+K-2 évek között minden évben egy magot
hoz, a magból pedig a következő évben kel ki új virág. Így a t. évben kikelő
virágok száma a t-M-K+1 és t-M évek között kikelt virágok összege, amit
prefixösszegekkel csúszó ablakként számolunk.
Az X. évben élő virágok azok, amelyek az X-N+1 és X közötti években keltek ki,
ezért az élő darabszámot úgy frissítjük, hogy minden év kikelőit hozzáadjuk, és
az N évvel korábban kikeltek számát kivonjuk. Minden lépésben 20180113-mal
maradékoljuk a számokat, a negatív maradékot pedig javítjuk.
Az algoritmus O(X) időben fut, a kiírt szám az X. évben élő virágok
darabszámának 20180113-mal vett maradéka.
*/
/*
Hint 1: || Az X. évben élő virágok azok, amelyek az X-N+1 és X közötti években
keltek ki, így elég minden év kikelőit kiszámolni, és az utolsó N év összegét
követni. Egy év kikelőinek száma egy csúszó ablakos összeg: a t-M-K+1 és t-M
közötti évek kikelőinek összege. ||
Hint 2: || A kikelőkhöz prefixösszeget tárolunk, így az ablak összege két
prefixösszeg különbsége. Az élő darabszámot minden évben frissítjük: hozzáadjuk
az új kikelőket, és kivonjuk az N évvel korábban kikelteket. Minden műveletet
maradékban végzünk, és a negatív maradékot javítjuk. ||
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

    cout << all[x] % MOD << '\n';
    return 0;
}