/*
Megoldás lényege:
Két soros járdán profile DP-t használunk. Egy állapot azt mutatja meg, melyik cellák
vannak már lefedve a jelenlegi és a következő oszlopban. A következő oszlopba lépve
az összes éppen teljes oszlopot balra csúsztatjuk.

*/

// Hint 1: || A 2×N tábla miatt elég néhány cellás „profil” állapotot fenntartani. ||
// Hint 2: || Mindig a bal szélső még üres cellát töltsd ki valamelyik lap elhelyezésével. ||
// Hint 3: || A végén csak a teljesen üres profil elfogadható. ||

#include <bits/stdc++.h>
#include "../bigint.hpp"
using namespace std;

using Mask = int;

struct Shape {
    vector<pair<int, int>> cells;
};

static vector<vector<pair<Mask, long long>>> buildTransitions(const vector<Shape>& shapes) {
    const int MAXC = 3;
    vector<vector<pair<Mask, long long>>> trans(4, vector<pair<Mask, long long>>{});

    for (int rem = 1; rem <= 3; ++rem) {
        vector<vector<Mask>> byCell(2);
        for (const auto& sh : shapes) {
            for (int r = 0; r < 2; ++r) {
                Mask m = 0;
                bool ok = true;
                for (auto [dr, dc] : sh.cells) {
                    int rr = r + dr;
                    int cc = dc;
                    if (rr < 0 || rr >= 2 || cc < 0 || cc >= rem) {
                        ok = false;
                        break;
                    }
                    m |= 1 << (2 * cc + rr);
                }
                if (!ok) continue;
                for (auto [dr, dc] : sh.cells) {
                    (void)dc;
                    int rr = r + dr;
                    if (rr == 0 || rr == 1) byCell[rr].push_back(m);
                }
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
                for (Mask p : byCell[row]) {
                    if ((p & cur) == 0) dfs(cur | p);
                }
            };
            if ((s & 3) == 3) {
                ++cnt[s >> 2];
            } else {
                int row = ((s & 1) == 0 ? 0 : 1);
                for (Mask p : byCell[row]) {
                    if ((p & s) == 0) dfs(s | p);
                }
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
        {{{0, 0}}},
        {{{0, 0}, {0, 1}}},
        {{{0, 0}, {1, 0}}}
    };

    auto trans = buildTransitions(shapes);
    vector<BigInt> dp(64), ndp(64);
    dp[0] = 1;

    for (int col = 0; col < N; ++col) {
        fill(ndp.begin(), ndp.end(), 0);
        int rem = min(3, N - col);
        for (int s = 0; s < 64; ++s) {
            if (dp[s].isZero()) continue;
            for (auto [nxt, mul] : trans[rem]) {
                // trans[rem] was filled for all states; we filter by exact state later.
                (void)nxt; (void)mul;
            }
        }
        for (int s = 0; s < 64; ++s) {
            if (dp[s].isZero()) continue;
            map<int, long long> cnt;
            function<void(int)> dfs = [&](int cur) {
                if ((cur & 3) == 3) {
                    ++cnt[cur >> 2];
                    return;
                }
                int row = ((cur & 1) == 0 ? 0 : 1);
                for (const auto& sh : shapes) {
                    for (int r = 0; r < 2; ++r) {
                        if (r != row) continue;
                        int m = 0;
                        bool ok = true;
                        for (auto [dr, dc] : sh.cells) {
                            int rr = r + dr;
                            int cc = dc;
                            if (rr < 0 || rr >= 2 || cc < 0 || cc >= rem) {
                                ok = false;
                                break;
                            }
                            m |= 1 << (2 * cc + rr);
                        }
                        if (!ok || (m & cur)) continue;
                        dfs(cur | m);
                    }
                }
            };
            if ((s & 3) == 3) {
                ++cnt[s >> 2];
            } else {
                int row = ((s & 1) == 0 ? 0 : 1);
                for (const auto& sh : shapes) {
                    for (int r = 0; r < 2; ++r) {
                        if (r != row) continue;
                        int m = 0;
                        bool ok = true;
                        for (auto [dr, dc] : sh.cells) {
                            int rr = r + dr;
                            int cc = dc;
                            if (rr < 0 || rr >= 2 || cc < 0 || cc >= rem) {
                                ok = false;
                                break;
                            }
                            m |= 1 << (2 * cc + rr);
                        }
                        if (!ok || (m & s)) continue;
                        dfs(s | m);
                    }
                }
            }
            for (auto& kv : cnt) ndp[kv.first] += dp[s] * kv.second;
        }
        dp.swap(ndp);
    }

    cout << dp[0] << '\n';
    return 0;
}
