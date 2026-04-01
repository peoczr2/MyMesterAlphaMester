/*
   Számzár: A válasz a kombinációk száma, a hibás tárcsa miatti maximum,
   illetve azoknak a kódoknak a száma, amelyekben van legalább két azonos
   számjegy. Az utóbbit bitmaskos DP-vel számoljuk.
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