/*
Megoldási ötlet:
A termékek száma legfeljebb 9, ezért bitmaszkos dinamikus programozás használható. A napokat sorban dolgozzuk
fel, és dp[nap][mask] azt jelenti, hogy az első nap nap feldolgozása után a mask által jelölt termékeket már
megvettem, és ez a lehető legkisebb költség.

Egy napon vagy nem vásárolunk semmit, vagy megvesszük valamelyik még hiányzó terméket. A végén a teljes maszkhoz
tartozó minimális költséget választjuk, majd a mentett elődökből visszafejtjük, hogy melyik terméket melyik napon
vettük meg.
*/
/*
Hint 1: || A napok száma nagyobb, de a termékek száma kicsi, ezért a részhalmazos állapottér lesz a megfelelő. ||
Hint 2: || Egy napon legfeljebb egy terméket vehetsz, tehát az átmenet vagy „nem veszek semmit”, vagy egy bit bekapcsolása. ||
Hint 3: || Rekonstrukcióhoz tárold el minden javításnál az előző maszkot és hogy azon a napon melyik terméket vetted meg. ||
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    cin >> k >> n;
    vector<vector<int>> price(k, vector<int>(n + 1));
    for (int product = 0; product < k; ++product) {
        for (int day = 1; day <= n; ++day) cin >> price[product][day];
    }

    int allMask = (1 << k) - 1;
    const long long inf = numeric_limits<long long>::max() / 4;
    vector<vector<long long>> dp(n + 1, vector<long long>(1 << k, inf));
    vector<vector<int>> prevMask(n + 1, vector<int>(1 << k, -1));
    vector<vector<int>> bought(n + 1, vector<int>(1 << k, -1));
    dp[0][0] = 0;

    for (int day = 1; day <= n; ++day) {
        for (int mask = 0; mask <= allMask; ++mask) {
            if (dp[day - 1][mask] < dp[day][mask]) {
                dp[day][mask] = dp[day - 1][mask];
                prevMask[day][mask] = mask;
                bought[day][mask] = -1;
            }
            if (dp[day - 1][mask] == inf) continue;
            for (int product = 0; product < k; ++product) {
                if (mask & (1 << product)) continue;
                int nextMask = mask | (1 << product);
                long long candidate = dp[day - 1][mask] + price[product][day];
                if (candidate < dp[day][nextMask]) {
                    dp[day][nextMask] = candidate;
                    prevMask[day][nextMask] = mask;
                    bought[day][nextMask] = product;
                }
            }
        }
    }

    long long bestCost = dp[n][allMask];
    vector<int> answer(k, -1);
    int mask = allMask;
    for (int day = n; day >= 1; --day) {
        int product = bought[day][mask];
        if (product != -1) answer[product] = day;
        mask = prevMask[day][mask];
    }

    cout << bestCost << '\n';
    for (int product = 0; product < k; ++product) {
        if (product > 0) cout << ' ';
        cout << answer[product];
    }
    cout << '\n';
    return 0;
}