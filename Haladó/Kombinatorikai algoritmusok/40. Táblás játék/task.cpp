#include <bits/stdc++.h>
using namespace std;

/*
  A tábla egy oszlopmagasság-sorozatból álló „hullámhegy”.
  Egy adott intervallumban a legalacsonyabb oszlopok választják szét a magasabb
  részeket. Ha a minimális magasságot levágjuk, akkor a magasabb, összefüggő
  részek független részproblémákká válnak.

  Az intervallumokra rekurzívan dolgozunk:
  - a gyerekek a minimumok közötti, m-nél magasabb szakaszok,
  - a jelenlegi „alsó sáv” egy teljes téglalap: szélesség = intervallum hossza,
    magasság = jelenlegi minimum - szülő minimum.

  Ha a gyerekek összesen t bábut használnak, akkor a sávban a maradék
  width - t oszlopba tehetünk még s bábut. Ennek száma:
      C(sávmagasság, s) * falling(width - t, s)
  ahol a sávban tetszőleges s sort és s oszlopot választunk.

  A rekurzió fája legfeljebb N csúcsú, N,K <= 500 mellett a K^2-es konvolúció
  elfér.
*/

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