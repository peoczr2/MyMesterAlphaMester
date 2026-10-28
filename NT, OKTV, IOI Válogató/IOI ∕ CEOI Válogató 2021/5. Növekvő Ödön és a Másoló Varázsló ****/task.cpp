/*
Megoldás lényege:
A módosított elemek végső értékei a szigorú növekvés miatt mind különbözők, így minden módosított elemhez külön bűbáj kell; a feladat a módosított elemek minimális számát keresi, vagyis a megtartható elemek maximumát.
Két egymást követő megtartott j < i elem között az (i-j-1) módosított elemnek A[j] és A[i] közötti, különböző B-értékek kellenek; ha cB(v) a B-beli v-nél kisebb értékek száma, ez cB(A[i]) - cB(A[j]) >= i-j-1 alakban írható, vagyis a_j <= a_i + 1, ahol a_p = cB(A[p]) - p.
Így dp[i] = 1 + max dp[j], ahol j < i, A[j] < A[i] és a_j <= a_i + 1; a kezdő és a záró feltétel külön ellenőrizhető.
A lekérdezés két dimenziós: a külső Fenwick-fa az A-értékek sorszáma szerint, a belső (maximumot tároló) Fenwick-fa az a-értékek szerint halad, offline előkészített koordinátákkal; az összidő O(N log^2 N).
*/
/*
Hint 1: || Minden módosított elem végső értéke más, mert a sorozat szigorúan nő, így minden módosított elemhez külön bűbáj tartozik. A feladat tehát a megtartott elemek legnagyobb számát keresi. ||
Hint 2: || Két megtartott elem között lévő módosított elemeknek A[j] és A[i] közötti B-értékek kellenek. Ha a B-értékeket rendezed, ez egy prefixösszeg-különbség, így a feltétel egy elemre nézve egyszerű egyenlőtlenség. ||
Hint 3: || A feltétel három dimenziós (sorrend, A-érték, átalakított érték), ezért a maximum-lekérdezéshez két Fenwick-fát kell egymásba ágyazni, és a koordinátákat előre (offline) kiszámolni. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int NEG = INT_MIN / 2;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<int> A(N + 1), B(M);
    for (int i = 1; i <= N; i++) cin >> A[i];
    for (int i = 0; i < M; i++) cin >> B[i];
    sort(B.begin(), B.end());

    // c[p] = a B-értékek közül hány kisebb A[p]-nél; a[p] = c[p] - p
    vector<int> c(N + 1), a(N + 1);
    for (int p = 1; p <= N; p++) {
        c[p] = int(lower_bound(B.begin(), B.end(), A[p]) - B.begin());
        a[p] = c[p] - p;
    }

    // rk[p]: A[p] sorszáma az A-értékek növekvő sorrendjében (1..N)
    vector<int> sortedA(A.begin() + 1, A.end());
    sort(sortedA.begin(), sortedA.end());
    vector<int> rk(N + 1);
    for (int p = 1; p <= N; p++)
        rk[p] = int(lower_bound(sortedA.begin(), sortedA.end(), A[p]) - sortedA.begin()) + 1;

    // Külső Fenwick-fa (rang szerint): minden csomópontban az oda kerülő a-értékek
    vector<vector<int>> vals(N + 1);
    for (int p = 1; p <= N; p++)
        for (int k = rk[p]; k <= N; k += k & -k) vals[k].push_back(a[p]);
    vector<vector<int>> inner(N + 1);
    for (int k = 1; k <= N; k++) {
        sort(vals[k].begin(), vals[k].end());
        vals[k].erase(unique(vals[k].begin(), vals[k].end()), vals[k].end());
        inner[k].assign(vals[k].size() + 1, NEG);
    }

    auto innerQuery = [&](int k, int pos) {
        int r = NEG;
        for (; pos > 0; pos -= pos & -pos) r = max(r, inner[k][pos]);
        return r;
    };
    auto innerUpdate = [&](int k, int pos, int val) {
        for (; pos < (int)inner[k].size(); pos += pos & -pos) inner[k][pos] = max(inner[k][pos], val);
    };

    int bestKept = 0;  // 0 megtartott elem mindig lehetséges, mert N <= M
    for (int i = 1; i <= N; i++) {
        // Kezdő szakasz: az első megtartott elem előtti i-1 módosított elemnek A[i] alatti B-érték kell.
        // Ez a virtuális kezdőpont (a_0 = 0) feltétele: 0 <= a_i + 1.
        int best = (a[i] + 1 >= 0) ? 0 : NEG;

        // Lekérdezés: j < i, A[j] < A[i], a_j <= a_i + 1
        for (int k = rk[i] - 1; k > 0; k -= k & -k) {
            int pos = int(upper_bound(vals[k].begin(), vals[k].end(), a[i] + 1) - vals[k].begin());
            best = max(best, innerQuery(k, pos));
        }
        if (best == NEG) continue;  // i nem lehet megtartott elem

        int dp = best + 1;
        for (int k = rk[i]; k <= N; k += k & -k) {
            int pos = int(lower_bound(vals[k].begin(), vals[k].end(), a[i]) - vals[k].begin()) + 1;
            innerUpdate(k, pos, dp);
        }

        // Záró szakasz: az i utáni N-i elemnek A[i]-nél nagyobb B-érték kell
        if (M - c[i] >= N - i) bestKept = max(bestKept, dp);
    }

    cout << N - bestKept << '\n';
    return 0;
}
