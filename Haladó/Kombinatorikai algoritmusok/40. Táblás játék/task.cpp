/*
Megoldás lényege:
Két bábu akkor üti egymást, ha azonos oszlopban van, vagy azonos sorban úgy, hogy közöttük a sorban végig van cella. Ezért oszloponként legfeljebb egy bábu állhat, és egy összefüggő vízszintes szakaszban is legfeljebb egy.
A tábla a legalacsonyabb oszlop magasságánál szétvágható: az alsó sáv téglalap, amelynek minden sora egyetlen szakasz, a fölötte lévő, a legalacsonyabb oszlopok által elválasztott részek pedig egymástól függetlenek. Minden részre a bábuszám-polinom (együtthatója: hány módon van t bábu) adódik rekurzívan; ezeket konvolúcióval szorozzuk, majd a sávba s bábu C(h, s)·(w−t)·…·(w−t−s+1) módon kerülhet. A végén a K-adik együttható a válasz modulo 10^9+7.
Az időigény legrosszabb esetben O(N·K²), ami N, K ≤ 500 mellett belefér az 1 másodperces időlimitbe.
*/
/*
Hint 1: || Két bábu akkor üti egymást, ha azonos oszlopban van, vagy azonos sorban úgy, hogy a köztük lévő cellák is a táblán vannak. Ezért oszloponként legfeljebb egy bábu állhat, és egy összefüggő vízszintes szakaszban is legfeljebb egy. ||
Hint 2: || Vágd szét a táblát a legalacsonyabb oszlop magasságánál: az így keletkező alsó sáv téglalap, a fölötte lévő részek pedig egymástól függetlenek. Ha a sáv h magas és w széles, és a fölötte lévő részekben t bábu van, akkor a sávba s bábu C(h, s)·(w−t)·(w−t−1)·…·(w−t−s+1) módon kerülhet. ||
Hint 3: || Rekurzívan add meg minden részre, hogy t bábuval hányféleképp lehet elhelyezni; a gyerekrészek ilyen polinomjait konvolúcióval szorozd össze, majd a sáv-képlettel kombináld. A végén a K-adik együttható a válasz modulo 10^9+7. ||
*/
#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1'000'000'007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    if (!(cin >> N >> K)) return 0;
    vector<int> h(N);
    for (int i = 0; i < N; ++i) cin >> h[i];

    vector<int> inv(K + 1, 1);
    for (int i = 2; i <= K; ++i) inv[i] = MOD - int((MOD / i) * 1LL * inv[MOD % i] % MOD);

    auto convolve = [&](const vector<int>& a, const vector<int>& b) {
        vector<int> c(min(K, (int)a.size() - 1 + (int)b.size() - 1) + 1, 0);
        for (int i = 0; i < (int)a.size(); ++i) {
            if (!a[i]) continue;
            for (int j = 0; j < (int)b.size() && i + j <= K; ++j) {
                if (!b[j]) continue;
                c[i + j] = (c[i + j] + 1LL * a[i] * b[j]) % MOD;
            }
        }
        return c;
    };

    function<vector<int>(int, int, int)> solve = [&](int l, int r, int baseH) -> vector<int> {
        if (l > r) return vector<int>{1};

        int mn = h[l];
        for (int i = l + 1; i <= r; ++i) mn = min(mn, h[i]);

        vector<vector<int>> children;
        int i = l;
        while (i <= r) {
            if (h[i] == mn) {
                ++i;
                continue;
            }
            int j = i;
            while (j <= r && h[j] > mn) ++j;
            children.push_back(solve(i, j - 1, mn));
            i = j;
        }

        vector<int> childPoly{1};
        for (const auto& dp : children) childPoly = convolve(childPoly, dp);

        int width = r - l + 1;
        int bandH = mn - baseH;

        int childMax = min(K, (int)childPoly.size() - 1);
        vector<int> res(K + 1, 0);

        vector<int> choose(min(K, bandH) + 1, 0);
        choose[0] = 1;
        for (int s = 1; s < (int)choose.size(); ++s) {
            choose[s] = 1LL * choose[s - 1] * (bandH - s + 1) % MOD * inv[s] % MOD;
        }

        for (int t = 0; t <= childMax; ++t) {
            if (!childPoly[t]) continue;
            int remCols = width - t;
            if (remCols < 0) continue;
            long long falling = 1;
            int maxS = min({K - t, bandH, remCols});
            for (int s = 0; s <= maxS; ++s) {
                if (s > 0) falling = falling * (remCols - s + 1) % MOD;
                long long ways = 1LL * childPoly[t] * choose[s] % MOD * falling % MOD;
                res[t + s] = (res[t + s] + ways) % MOD;
            }
        }

        return res;
    };

    vector<int> ans = solve(0, N - 1, 0);
    cout << (K < (int)ans.size() ? ans[K] : 0) << '\n';
    return 0;
}
