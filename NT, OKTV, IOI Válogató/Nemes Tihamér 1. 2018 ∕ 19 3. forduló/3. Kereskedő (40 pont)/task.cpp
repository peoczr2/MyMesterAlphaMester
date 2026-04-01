#include <bits/stdc++.h>
using namespace std;

/*
    Két konkáv bevételi függvényünk van. Az összes lehetséges asztalszám-párra
    kiszámítjuk a profitot (bevétel - K * asztalok száma), és a maximumot keressük.
    Holtversenyben a kevesebb összasztal, azon belül a több első vásári asztal a jó.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<long long> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];

    vector<long long> profitB(n + 1, 0);
    for (int y = 0; y <= n; ++y) profitB[y] = b[y] - 1LL * y * k;

    vector<long long> bestPrefixProfit(n + 1);
    vector<int> bestPrefixY(n + 1);
    bestPrefixProfit[0] = profitB[0];
    bestPrefixY[0] = 0;
    for (int y = 1; y <= n; ++y) {
        if (profitB[y] > bestPrefixProfit[y - 1] || (profitB[y] == bestPrefixProfit[y - 1] && y < bestPrefixY[y - 1])) {
            bestPrefixProfit[y] = profitB[y];
            bestPrefixY[y] = y;
        } else {
            bestPrefixProfit[y] = bestPrefixProfit[y - 1];
            bestPrefixY[y] = bestPrefixY[y - 1];
        }
    }

    long long bestProfit = LLONG_MIN;
    int bestX = 0, bestY = 0;
    int bestTables = INT_MAX;
    for (int x = 0; x <= n; ++x) {
        long long profitA = a[x] - 1LL * x * k;
        int limitY = n - x;
        long long candProfit = profitA + bestPrefixProfit[limitY];
        int candY = bestPrefixY[limitY];
        int candTables = x + candY;
        if (candProfit > bestProfit || (candProfit == bestProfit && (candTables < bestTables || (candTables == bestTables && x > bestX)))) {
            bestProfit = candProfit;
            bestX = x;
            bestY = candY;
            bestTables = candTables;
        }
    }

    cout << bestProfit << '\n' << bestX << ' ' << bestY << '\n';
    return 0;
}