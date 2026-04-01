/*
Feladat: N asztalt lehet két vásár között szétosztani (x és y, x+y<=N). Adott az 1..N asztalhoz tartozó összbevétel mindkét vásárra, asztalonként fix K költséggel. Maximum hasznot kell adni, holtversenyben minimális összasztalszám, azon belül maximális első vásári asztalszám.
Ötlet: Profit(x,y)=A[x]+B[y]-K*(x+y), ahol A[0]=B[0]=0. Egy fix x-hez csak a y<=N-x tartomány legjobb B[y]-K*y értéke kell. Ezt prefix-maximumként előre kiszámítjuk (holtversenyben kisebb y). Utána minden x-re O(1)-ben kapunk jelöltet, és a feladat szerinti tie-breakkel kiválasztjuk az optimumot.
Hint 1: || Vezesd be az A'[x]=A[x]-Kx és B'[y]=B[y]-Ky értékeket. ||
Hint 2: || x-hez csak a y<=N-x legjobb B' prefix kell. ||
Hint 3: || Tie-break: előbb kevesebb asztal, azon belül nagyobb x. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long K;
    cin >> N >> K;

    vector<long long> A(N + 1, 0), B(N + 1, 0);
    for (int i = 1; i <= N; ++i) cin >> A[i];
    for (int i = 1; i <= N; ++i) cin >> B[i];

    vector<long long> Bp(N + 1, 0);
    for (int y = 0; y <= N; ++y) Bp[y] = B[y] - K * y;

    vector<int> bestY(N + 1, 0);
    bestY[0] = 0;
    for (int y = 1; y <= N; ++y) {
        int prev = bestY[y - 1];
        if (Bp[y] > Bp[prev]) bestY[y] = y;
        else if (Bp[y] < Bp[prev]) bestY[y] = prev;
        else bestY[y] = min(y, prev);
    }

    long long bestProfit = LLONG_MIN;
    int ansX = 0, ansY = 0;

    for (int x = 0; x <= N; ++x) {
        long long Ap = A[x] - K * x;
        int y = bestY[N - x];
        long long profit = Ap + Bp[y];

        int total = x + y;
        int bestTotal = ansX + ansY;

        bool better = false;
        if (profit > bestProfit) better = true;
        else if (profit == bestProfit) {
            if (total < bestTotal) better = true;
            else if (total == bestTotal && x > ansX) better = true;
        }

        if (better) {
            bestProfit = profit;
            ansX = x;
            ansY = y;
        }
    }

    cout << bestProfit << '\n';
    cout << ansX << ' ' << ansY << '\n';
    return 0;
}
