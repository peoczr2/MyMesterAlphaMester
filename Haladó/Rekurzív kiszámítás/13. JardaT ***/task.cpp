/*
Megoldás lényege:
Az előző profil-DP-t kiegészítjük a T-alakú tetrominókkal is. A 2 soros táblán csak azok
az elforgatások maradnak meg, amelyek beleférnek a 2×3-as sávba.

*/

// Hint 1: || A T-lapnak a 2 soros táblán csak két érvényes orientációja van. ||
// Hint 2: || A megoldás szerkezete ugyanaz, mint az L-es változatnál. ||
// Hint 3: || Az eredményt 20200111-gyel kell modulo venni. ||

#include <bits/stdc++.h>
using namespace std;

using Mask = int;

struct Shape { vector<pair<int, int>> cells; };

static vector<vector<pair<Mask, long long>>> buildTransitions(const vector<Shape>& shapes) {
    vector<vector<pair<Mask, long long>>> trans(4, vector<pair<Mask, long long>>());
    for (int rem = 1; rem <= 3; ++rem) {
        vector<vector<Mask>> cover(2);
        for (const auto& sh : shapes) {
            for (int top = 0; top < 2; ++top) {
                Mask m = 0;
                bool ok = true;
                for (auto [dr, dc] : sh.cells) {
                    int r = top + dr;
                    int c = dc;
                    if (r < 0 || r >= 2 || c < 0 || c >= rem) {
                        ok = false;
                        break;
                    }
                    m |= 1 << (2 * c + r);
                }
                if (!ok) continue;
                for (int r = 0; r < 2; ++r) if (m & (1 << r)) cover[r].push_back(m);
            }
        }
        for (int s = 0; s < 64; ++s) {
            map<Mask, long long> cnt;
            function<void(Mask)> dfs = [&](Mask cur) {
                if ((cur & 3) == 3) {
                    ++cnt[cur >> 2];
                    return;
                }
                int row = ((cur & 1) == 0 ? 0 : 1);
                for (Mask p : cover[row]) if ((p & cur) == 0) dfs(cur | p);
            };
            if ((s & 3) == 3) ++cnt[s >> 2];
            else {
                int row = ((s & 1) == 0 ? 0 : 1);
                for (Mask p : cover[row]) if ((p & s) == 0) dfs(s | p);
            }
            for (auto& kv : cnt) trans[rem].push_back({kv.first, kv.second});
        }
    }
    return trans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<Shape> shapes = {
        {{{0, 0}, {0, 1}}},
        {{{0, 0}, {1, 0}}},
        {{{0, 0}, {1, 0}, {0, 1}}},
        {{{0, 0}, {1, 0}, {1, 1}}},
        {{{0, 0}, {0, 1}, {1, 1}}},
        {{{1, 0}, {0, 1}, {1, 1}}},
        {{{0, 0}, {0, 1}, {0, 2}, {1, 1}}},
        {{{1, 0}, {1, 1}, {1, 2}, {0, 1}}}
    };

    auto trans = buildTransitions(shapes);
    const long long MOD = 20200111LL;
    vector<long long> dp(64), ndp(64);
    dp[0] = 1;

    for (int col = 0; col < N; ++col) {
        fill(ndp.begin(), ndp.end(), 0);
        int rem = min(3, N - col);
        vector<vector<Mask>> cover(2);
        for (const auto& sh : shapes) {
            for (int top = 0; top < 2; ++top) {
                Mask m = 0;
                bool ok = true;
                for (auto [dr, dc] : sh.cells) {
                    int r = top + dr;
                    int c = dc;
                    if (r < 0 || r >= 2 || c < 0 || c >= rem) {
                        ok = false;
                        break;
                    }
                    m |= 1 << (2 * c + r);
                }
                if (!ok) continue;
                for (int r = 0; r < 2; ++r) if (m & (1 << r)) cover[r].push_back(m);
            }
        }

        for (int s = 0; s < 64; ++s) {
            if (dp[s] == 0) continue;
            map<Mask, long long> cnt;
            function<void(Mask)> dfs = [&](Mask cur) {
                if ((cur & 3) == 3) {
                    ++cnt[cur >> 2];
                    return;
                }
                int row = ((cur & 1) == 0 ? 0 : 1);
                for (Mask p : cover[row]) if ((p & cur) == 0) dfs(cur | p);
            };
            if ((s & 3) == 3) ++cnt[s >> 2];
            else {
                int row = ((s & 1) == 0 ? 0 : 1);
                for (Mask p : cover[row]) if ((p & s) == 0) dfs(s | p);
            }
            for (auto& kv : cnt) ndp[kv.first] = (ndp[kv.first] + dp[s] * kv.second) % MOD;
        }
        dp.swap(ndp);
    }

    cout << dp[0] % MOD << '\n';
    return 0;
}
