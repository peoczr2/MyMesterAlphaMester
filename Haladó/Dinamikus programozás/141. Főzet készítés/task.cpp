/*
Megoldás lényege:
Egy főzet aránya a:b, és két főzet arányát az egyszerűsített (p,q) pár határozza meg, ahol gcd(p,q)=1. Minden különböző
arányhoz egy ilyen párt használunk, és a feladat szerint a kikevert főzetek összesen legfeljebb A liter 1-es és B liter 2-es
főzetet fogyasztanak. Így azt kell eldönteni, hogy legfeljebb hány különböző relatív prím párt lehet úgy választani, hogy
a p-k összege legfeljebb A, a q-k összege legfeljebb B legyen. Ez egy 0/1 hátizsák-feladat két kapacitással, ahol minden
tárgy értéke 1. Az állapot: hány párt választottunk, és ezek p-összege mekkora; az érték a minimális q-összeg.
Mivel a válasz legfeljebb 87 lehet, és egy (p,q) párt csak akkor érdemes használni, ha kevés nála kisebb relatív prím pár
van, a szóba jöhető párok száma kb. 400, így a DP gyorsan lefut. Minden A-ra a prefixminimumokból O(1) a válasz.
*/
/*
Hint 1: || Két főzet akkor különbözik, ha egyszerűsített aránya különbözik, ezért minden arány egy relatív prím (p,q) párral írható le. ||
Hint 2: || Ha ezeket a párokat tárgyaknak tekinted, a feladat: hány tárgyat választhatsz úgy, hogy a p-k összege legfeljebb A, a q-k összege legfeljebb B legyen. ||
Hint 3: || A DP-t úgy építsd, hogy az állapot a kiválasztott párok száma és p-összege, az érték pedig a minimális q-összeg; a nagy párokat ne vedd be, mert egy (p,q) pár csak akkor lehet a kiválasztott halmazban, ha kevés kisebb relatív prím pár van. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int LIM = 500;
    const int K = 90;
    const int INF = 1000000000;

    // C[p][q]: a [1..p]x[1..q] téglalapban hány relatív prím pár van
    vector<vector<int>> C(LIM + 1, vector<int>(LIM + 1, 0));
    for (int p = 1; p <= LIM; ++p) {
        for (int q = 1; q <= LIM; ++q) {
            C[p][q] = C[p - 1][q] + C[p][q - 1] - C[p - 1][q - 1] + (gcd(p, q) == 1 ? 1 : 0);
        }
    }

    // g[k][s]: k pár választása, p-összeg pontosan s, minimális q-összeg
    vector<vector<int>> g(K + 1, vector<int>(LIM + 1, INF));
    g[0][0] = 0;
    for (int p = 1; p <= LIM; ++p) {
        for (int q = 1; q <= LIM; ++q) {
            if (gcd(p, q) != 1 || C[p][q] > K) continue;
            for (int k = K; k >= 1; --k) {
                for (int s = LIM; s >= p; --s) {
                    if (g[k - 1][s - p] < INF) {
                        g[k][s] = min(g[k][s], g[k - 1][s - p] + q);
                    }
                }
            }
        }
    }

    // best[k][A]: k pár választása úgy, hogy a p-összeg legfeljebb A legyen; ennek minimális q-összege
    vector<vector<int>> best(K + 1, vector<int>(LIM + 1, INF));
    for (int k = 0; k <= K; ++k) {
        int cur = INF;
        for (int a = 0; a <= LIM; ++a) {
            cur = min(cur, g[k][a]);
            best[k][a] = cur;
        }
    }

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        int ans = 0;
        for (int k = 1; k <= K; ++k) {
            if (best[k][a] <= b) ans = k;
        }
        cout << ans << '\n';
    }
    return 0;
}
