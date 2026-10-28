/*
Megoldás lényege: mivel minden unoka más mennyiséget kap, a kiosztás sorrendje nem számít,
így a feladat azt kérdezi, hány olyan K elemű halmaz van {1..M}-ből, amelynek összege N.
Ezt egy 0/1 hátizsák-típusú DP számolja: dp[c][s] az eddig feldolgozott értékekből c elemmel
s összeget adó halmazok száma; minden v értéket legfeljebb egyszer veszünk figyelembe, mert
a c és s ciklusokat fordítva járjuk be. A válasz dp[K][N] mod 20200202. Az idő O(M * K * N),
ami N, M <= 500 és K <= 20 mellett kb. 5 * 10^6 művelet.
*/
/*
Hint 1: || Mivel a kapott mennyiségek különbözőek, a sorrend nem számít: a kérdés az, hány K elemű, különböző, 1..M közötti számhalmaz összege N. ||
Hint 2: || Számold meg a halmazokat úgy, hogy az értékeket egyenként vesszük sorra, és dp[c][s]-ben tároljuk, hány halmazt lehet c elemmel s összegig felépíteni. ||
Hint 3: || A dp frissítésénél a c és s ciklusokat csökkenő sorrendben futtasd, így minden v érték legfeljebb egyszer kerül a halmazba. ||
*/
#include <bits/stdc++.h>
using namespace std;

static const int MOD = 20200202;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K, M;
    cin >> N >> K >> M;
    vector<vector<int>> dp(K + 1, vector<int>(N + 1, 0));
    dp[0][0] = 1;
    for (int v = 1; v <= M; ++v) {
        for (int c = K; c >= 1; --c) {
            for (int s = N; s >= v; --s) {
                dp[c][s] += dp[c - 1][s - v];
                if (dp[c][s] >= MOD) dp[c][s] -= MOD;
            }
        }
    }
    cout << dp[K][N] % MOD << '\n';
    return 0;
}