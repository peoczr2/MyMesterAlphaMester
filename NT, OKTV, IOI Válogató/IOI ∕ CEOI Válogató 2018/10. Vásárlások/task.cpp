/*
Megoldás lényege:
K legfeljebb 10, ezért a megvásárolt termékek halmazát bitmaskkal lehet leírni.
Haladunk napokon, és dp[mask] azt jelenti, hogy az eddigi napokból a maskban lévő
termékeket már megvettük, minimális költséggel. Egy napon vagy nem vásárolunk,
vagy megvesszük az egyik még hiányzó terméket.

Mivel N legfeljebb 100, az O(N * 2^K * K) dinamikus programozás kényelmesen elég.
A szülőmutatókból visszaállítjuk, melyik terméket melyik napon vettük meg.
*/
/*
Hint 1: || A napok sorrendje nem számít, csak az, hogy melyik napon melyik terméket vesszük. Mivel K kicsi, a már megvett termékek halmaza egy bitmaskkal leírható. ||
Hint 2: || Haladj a napokon sorban: dp[nap][maszk] legyen a minimális költség, ha az eddigi napokon a maszkban lévő termékeket már megvettük. Egy napon vagy nem veszel semmit, vagy egy még hiányzó terméket. ||
Hint 3: || Az állapotokhoz tárold el az előző maszkot és a megvett terméket, majd a végállapotból visszafelé haladva rekonstruáld, melyik terméket melyik napon vetted. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    if (!(cin >> k >> n)) return 0;

    vector<vector<int>> a(k, vector<int>(n + 1));
    for (int i = 0; i < k; ++i) {
        for (int d = 1; d <= n; ++d) cin >> a[i][d];
    }

    const long long INF = (1LL << 60);
    int full = (1 << k) - 1;
    vector<vector<long long>> dp(n + 1, vector<long long>(1 << k, INF));
    vector<vector<int>> prevMask(n + 1, vector<int>(1 << k, -1));
    vector<vector<int>> prevProd(n + 1, vector<int>(1 << k, -1));

    dp[0][0] = 0;
    for (int day = 1; day <= n; ++day) {
        for (int mask = 0; mask <= full; ++mask) {
            if (dp[day - 1][mask] >= INF) continue;
            if (dp[day - 1][mask] < dp[day][mask]) {
                dp[day][mask] = dp[day - 1][mask];
                prevMask[day][mask] = mask;
                prevProd[day][mask] = -1;
            }
            for (int prod = 0; prod < k; ++prod) {
                if (mask & (1 << prod)) continue;
                int nmask = mask | (1 << prod);
                long long cost = dp[day - 1][mask] + a[prod][day];
                if (cost < dp[day][nmask]) {
                    dp[day][nmask] = cost;
                    prevMask[day][nmask] = mask;
                    prevProd[day][nmask] = prod;
                }
            }
        }
    }

    cout << dp[n][full] << '\n';

    vector<int> assign(k + 1, -1);
    int mask = full;
    for (int day = n; day >= 1; --day) {
        int prod = prevProd[day][mask];
        int pmask = prevMask[day][mask];
        if (prod != -1) assign[prod + 1] = day;
        mask = pmask;
    }

    for (int i = 1; i <= k; ++i) {
        if (i > 1) cout << ' ';
        cout << assign[i];
    }
    cout << '\n';
    return 0;
}