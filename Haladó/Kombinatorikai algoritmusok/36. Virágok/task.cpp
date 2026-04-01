/*
Megoldás lényege:
Ugyanaz a növényes rekurzió, mint a 35. feladatban, csak most az X. évben
élő növények számát kell kiírni.
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