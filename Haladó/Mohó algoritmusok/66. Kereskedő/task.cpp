/*
Megoldás lényege:
A profit P(x,y) = (A[x] - K*x) + (B[y] - K*y), a két vásár tehát független, így minden x-hez csak az y <= N-x tartomány legjobb B[y] - K*y értéke kell. Ezt prefixmaximummal O(1)-ben lekérdezzük, egyenlőség esetén a kisebb y marad. Minden x-re így megkapjuk a legjobb párt, majd a feladat szerinti tie-breakkel (kevesebb asztal, azonos esetben nagyobb első szám) választunk. A bevétel konkávitása itt nem kell, a prefixmaximum általánosan is helyes. Az időigény O(N).
*/
/*
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
