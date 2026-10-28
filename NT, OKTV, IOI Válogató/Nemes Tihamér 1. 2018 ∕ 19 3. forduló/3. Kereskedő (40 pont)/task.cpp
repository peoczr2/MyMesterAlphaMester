/*
Megoldás lényege:
Mindkét vásárra a profit bevétel − K·asztalszám. Az első vásár minden x asztalszámához a második vásárban azt az y-t keressük, amelyre y ≤ N − x és a profit a legnagyobb. Ezt a második vásár profitjainak prefix maximumával egyszer kiszámoljuk (holtversenyben a kisebb y marad), így minden x-re O(1) alatt megvan a legjobb y. Az x-ek végigpróbálásakor a legnagyobb össz-profit adódik; holtversenynél a kevesebb összes asztal, majd a nagyobb első vásári szám a jó. Az időigény O(N).
*/
/*
Hint 1: || A két vásár csak a teljes asztalszámon (legfeljebb N) osztozik. Rögzítsd az első vásár x asztalszámát, és a maradék N − x asztal közül keresd a második vásár legjobb y értékét. ||
Hint 2: || A második vásár minden y-ra kiszámolt profitját tárold prefix maximum tömbben, és mellette azt a legkisebb y-t is, amelynél ez a maximum elérhető: így minden x-re egy tömbelem kikeresése elég. ||
Hint 3: || Az összesítésnél három szempont dönt: a nagyobb össz-profit, azonos profitnál a kevesebb összes asztal, és ezen belül a nagyobb első vásári asztalszám. ||
*/
#include <bits/stdc++.h>
using namespace std;

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