/*
Megoldás lényege:
A játék állapota két adattal írható le: hány dobás történt, és melyik mezőn
állunk. A dp[lépés][mező] azt számolja, hányféle dobássorozat vezet az adott
mezőre az adott lépésszám után úgy, hogy közben még nem értünk célba. A célmező
után nem lépünk tovább, ezért a célba érkezések számát a lépésszám 1..K
értékeire összegezzük.
A túllépés visszafelé lépés: ha a mező + dobás értéke N-nél nagyobb, az új mező
2N - (mező + dobás). Így minden átmenet konstans idejű.
Időigény O(K·N·6), memória O(K·N), a számok mod 10^6-tal vannak tárolva.
*/
/*
Hint 1: || Az állapot két dologtól függ: hány dobás történt már, és melyik mezőn állunk. Számoljuk meg, hányféle dobássorozat vezet egy adott (dobásszám, mező) párhoz, és a célmezőről ne lépjünk tovább. ||
Hint 2: || Ha a dobás után a mező N fölé kerülne, a túllépést vissza kell tükrözni: az új mező 2N - (mező + dobás). Így minden dobás az 1..N mezők egyikére visz. ||
Hint 3: || Legyen dp[i][j] azon dobássorozatok száma, amelyek i dobás után a j. mezőn állnak, és még nem értek célba. Kezdetben dp[0][1] = 1. A válasz a célmező értékeinek összege i = 1..K-ra, mod 10^6. ||
*/
#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    vector<vector<int>> dp(K + 1, vector<int>(N + 1, 0));
    dp[0][1] = 1;
    for (int step = 0; step < K; ++step) {
        for (int pos = 1; pos <= N; ++pos) {
            if (!dp[step][pos] || pos == N) continue;
            for (int roll = 1; roll <= 6; ++roll) {
                int nxt = pos + roll;
                if (nxt > N) nxt = 2 * N - nxt;
                dp[step + 1][nxt] = (dp[step + 1][nxt] + dp[step][pos]) % MOD;
            }
        }
    }

    int ans = 0;
    for (int step = 1; step <= K; ++step) ans = (ans + dp[step][N]) % MOD;
    cout << ans << '\n';
    return 0;
}