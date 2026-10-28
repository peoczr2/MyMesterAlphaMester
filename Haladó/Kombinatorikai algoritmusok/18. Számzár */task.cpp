/*
Megoldás lényege:
Az összes kombináció száma a tárcsák számjegyszámának szorzata. Ha egy tárcsa elromlott, az minden számot elfogad, ezért azon nem kell próbálgatni: a próbák száma a többi tárcsa szorzata, a legrosszabb eset pedig a legkisebb számjegyszámú tárcsa elromlása. A legalább két azonos számjegyet tartalmazó kódok száma az összes kombinációból kivont, minden számjegyben különböző kódok száma. Ez utóbbit bitmaskos DP-vel számoljuk: a maszk a már használt számjegyeket (0-tól 9-ig, 10 bit) jelöli, és tárcsánként csak a még nem használt számjegyeket vesszük figyelembe. A DP O(N*2^10*10) lépésből áll, a 64 bites egész pedig a legfeljebb 10^10 értékű szorzatokat is elbírja.
*/
/*
Hint 1: || Az első két kérdés a számjegyszámok szorzatából és egy maximumból adódik: a hibás tárcsa nem igényel próbálgatást, ezért a többi tárcsa szorzata számít. ||
Hint 2: || A harmadik kérdésre a teljes számból vond ki azoknak a kódoknak a számát, ahol minden számjegy különbözik; ezt tárcsánként bővített, a már használt számjegyeket tároló maszkos DP-vel számold. ||
*/
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> d(N);
    for (int i = 0; i < N; ++i) cin >> d[i];

    ull total = 1;
    int mn = 10;
    for (int x : d) {
        total *= x;
        mn = min(mn, x);
    }

    ull worstBroken = 0;
    for (int x : d) worstBroken = max(worstBroken, total / x);

    vector<ull> dp(1 << 10, 0), ndp(1 << 10, 0);
    dp[0] = 1;
    for (int i = 0; i < N; ++i) {
        fill(ndp.begin(), ndp.end(), 0);
        for (int mask = 0; mask < (1 << 10); ++mask) if (dp[mask]) {
            for (int dig = 0; dig < d[i]; ++dig) {
                if (!(mask & (1 << dig))) ndp[mask | (1 << dig)] += dp[mask];
            }
        }
        dp.swap(ndp);
    }
    ull distinct = 0;
    for (ull x : dp) distinct += x;
    ull repeated = total - distinct;

    cout << total << '\n' << worstBroken << '\n' << repeated << '\n';
    return 0;
}
