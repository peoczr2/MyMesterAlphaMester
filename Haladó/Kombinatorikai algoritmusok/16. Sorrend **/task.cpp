/*
Megoldás lényege:
Inklúzió-exklúzióval számolunk: a tiltott helyzetek a közvetlenül egymás után álló (i, i+1) párok. Ezek láncot alkotnak, ezért bármely részhalmazuk egyszerre teljesíthető; ha j darab tiltott párt kiválasztunk és előírjuk őket, a párok blokkokba fognak össze, így N-j blokk marad, amelyek (N-j)!-féleképpen állhatnak. A j elemű párhalmazok száma C(N-1, j), az előjel a j paritásától függ, így a válasz összege (-1)^j * C(N-1, j) * (N-j)! lesz j = 0 .. N-1 között. A binomiálisokat Pascal-háromszöggel számoljuk, a munka O(N^2). N<=30 esetén a szorzatokat 128 bites egészben képezzük, így a MOD 10^12 mellett sem csordul túl a számítás.
*/
/*
Hint 1: || Számoljuk a rossz sorrendeket inklúzió-exklúzióval: válasszunk ki j darab tiltott (i, i+1) párt, és nézzük meg, hányféle sorrend teljesíti mindet. ||
Hint 2: || A kiválasztott párokat összevonva N-j blokk marad; ezek sorrendje (N-j)!-féle, a párok kiválasztása C(N-1, j)-féleképpen történhet, az előjel pedig j paritásától függ. ||
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
