/*
Megoldás lényege:
A gyémántok odaadásának sorrendje nem számít, csak az, hogy melyik unokának mennyi jut, így a kérdés az N szám olyan felbontásainak száma, amelyek pontosan K darab, 1 és M közötti részből állnak (partíciók). Ezt zsákprobléma-szerű DP-vel számoljuk: a részek értékein (v = 1 … M) sorban végigmenve dp[k][s] az eddig vizsgált értékekből felírható, k darab tagú, s összegű felbontások számát adja. Mivel k és s növekvő sorrendben frissül, egy v érték többször is felhasználható. Az eredményt 20200202 szerinti maradékként írjuk ki. Az idő O(M · K · N), ami N ≤ 500 és K ≤ 20 mellett bőven belefér az időlimitbe.
*/
/*
Hint 1: || Mivel a sorrend nem számít, a kérdés az, hogy az N szám hányféleképpen bontható fel pontosan K darab, 1 és M közötti tagra. ||
Hint 2: || Tekintsd a tagok lehetséges értékeit egyesével (1-től M-ig), és tartsd nyilván dp[k][s]-ben, hány k tagú felbontás van s összeggel az eddig vizsgált értékekkel. ||
Hint 3: || Ha a v értéket hozzáveszed, a dp-t k és s szerint növekvő sorrendben frissítsd: dp[k][s] += dp[k−1][s−v] modulo 20200202. Így a v érték többször is szerepelhet a felbontásban. ||
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
        for (int k = 1; k <= K; ++k) {
            for (int s = v; s <= N; ++s) {
                dp[k][s] += dp[k - 1][s - v];
                if (dp[k][s] >= MOD) dp[k][s] -= MOD;
            }
        }
    }
    cout << dp[K][N] % MOD << '\n';
    return 0;
}