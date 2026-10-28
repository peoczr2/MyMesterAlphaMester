/*
Megoldás lényege:
Az s. évben kikelt növény az s+M−1. évtől K évig hoz magot, így a magokból az s+M. … s+M+K−1. évben kelnek új növények. A t. évi kikelések száma ezért a t−M−K+1 … t−M években kikelt növények összege, amit egy prefixösszeg-tömbből O(1) időben kapunk meg. Az élő növények száma az utolsó N év kikeléseinek összege, amit futó összeggel tartunk karban: az N évnél régebbi kikeléseket kivonjuk. Minden értéket a 20180113 szerinti maradékkal számolunk, a negatív különbségeket korrigálva. Az időigény O(X).
*/
/*
Hint 1: || Az évi kikelések egy fix hosszúságú ablakban lévő korábbi kikelések összegei: egy év kikelését nem az összes múltbeli év, hanem csak a néhány évvel korábbi kikelések határozzák meg. ||
Hint 2: || Építs prefixösszeg-tömböt a kikelésekből, így egy ablak összege két tömbelemmel kiszámítható. Ügyelj, hogy az ablak eleje ne menjen az 1. év elé. ||
Hint 3: || Az élő növények száma az utolsó N év kikeléseinek összege; amikor egy kikelés N évnél régebbi lesz, a futó összegből vond ki. Minden lépésben vedd a 20180113 szerinti maradékot, és a negatív eredményhez add hozzá a modulust. ||
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
