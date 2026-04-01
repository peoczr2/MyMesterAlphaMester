/*
   Sorrend: a tilos helyzetek a közvetlenül egymás után álló i, i+1 párok.
   Inklúzió-exklúzióval számoljuk a megfelelő permutációk számát.
*/
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
static const ull MOD = 1000000000000ULL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<ull>> C(N + 1, vector<ull>(N + 1));
    vector<ull> fact(N + 1);
    fact[0] = 1;
    for (int i = 1; i <= N; ++i) fact[i] = (ull)((__int128)fact[i - 1] * i % MOD);
    for (int n = 0; n <= N; ++n) {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k < n; ++k) C[n][k] = C[n - 1][k - 1] + C[n - 1][k];
    }

    ull ans = 0;
    for (int j = 0; j <= N - 1; ++j) {
        __int128 term = (__int128)C[N - 1][j] * fact[N - j] % MOD;
        if (j % 2 == 0) ans = (ans + (ull)term) % MOD;
        else ans = (ans + MOD - (ull)term) % MOD;
    }

    cout << ans % MOD << '\n';
    return 0;
}