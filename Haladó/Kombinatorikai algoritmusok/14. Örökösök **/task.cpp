/*
   Örökösök: a vármegyék száma K nemnövekvő, pozitív részre bontásának
   száma. A feltételek miatt a fiúk vármegyeszámai idősebbtől fiatalabbig
   nemnövekvő sorozatot alkotnak, és mindegyik legalább 1, így a feladat az
   N pontosan K pozitív összegre bontásainak számolása (sorrend nélkül). Ezt
   a klasszikus partitió-rekurzióval számoljuk: dp[n][k] = dp[n-1][k-1] +
   dp[n-k][k], mert vagy van a felbontásban 1-es tag (elhagyva n-1 bontandó
   k-1 tagra), vagy minden tag legalább 2, így mindegyikből 1-et levonva
   n-k bontandó k tagra. Az idő O(N * K), ami N <= 100 és K <= 10 mellett
   bőven belefér.
*/
/*
Hint 1: || A feltétel szerint a fiúk darabszámai idősebbtől a fiatalabbak felé haladva nem nőnek, és mindegyik legalább 1. Így a kérdés az, hogy N hányféleképpen írható fel K pozitív szám összegeként, ahol a sorrend nem számít. ||
Hint 2: || Legyen dp[n][k] az n szám k pozitív összegre bontásainak száma, dp[0][0] = 1. Ha van 1-es tag, azt elhagyva dp[n-1][k-1]-et kapsz; ha nincs 1-es tag, minden tagból levonva 1-et, dp[n-k][k]-t kapsz. Az összeg a két eset összege. ||
*/
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    vector<vector<ull>> dp(N + 1, vector<ull>(K + 1, 0));
    dp[0][0] = 1;
    for (int n = 1; n <= N; ++n) {
        for (int k = 1; k <= K; ++k) {
            ull ans = 0;
            if (n - 1 >= 0 && k - 1 >= 0) ans += dp[n - 1][k - 1];
            if (n - k >= 0) ans += dp[n - k][k];
            dp[n][k] = ans;
        }
    }
    cout << dp[N][K] << '\n';
    return 0;
}