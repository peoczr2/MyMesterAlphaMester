/*
Megoldás lényege:
Két soros járdán 1x1-es lapokkal és L-alakú triominokkal dolgozunk. Profile DP-vel
haladunk balról jobbra: az állapot megmondja, mely cellák vannak már lefedve a jelenlegi
profilban.

*/

// Hint 1: || A bal szélső még üres cellát mindig valamilyen, onnan induló lappal kell lefedni. ||
// Hint 2: || Az L-lapnak csak a 2 soros táblán belül érvényes elforgatásai számítanak. ||
// Hint 3: || A jelenlegi oszlop teljesülése után a profilt egy oszloppal balra kell csúsztatni. ||

#include <bits/stdc++.h>
#include "../bigint.hpp"
using namespace std;

using Mask = int;

struct Shape {
    vector<pair<int, int>> cells;
};

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
                for (int r = 0; r < 2; ++r) {
                    if (m & (1 << r)) cover[r].push_back(m);
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
                for (Mask p : cover[row]) {
                    if ((p & cur) == 0) dfs(cur | p);
                }
            };

            if ((s & 3) == 3) {
                ++cnt[s >> 2];
            } else {
                int row = ((s & 1) == 0 ? 0 : 1);
                for (Mask p : cover[row]) {
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
        {{{0, 0}, {0, 1}}},
        {{{0, 0}, {1, 0}}},
        {{{0, 0}, {1, 0}, {0, 1}}},
        {{{0, 0}, {1, 0}, {1, 1}}},
        {{{0, 0}, {0, 1}, {1, 1}}},
        {{{1, 0}, {0, 1}, {1, 1}}}
    };

    auto trans = buildTransitions(shapes);
    vector<BigInt> dp(64), ndp(64);
    dp[0] = 1;

    for (int col = 0; col < N; ++col) {
        fill(ndp.begin(), ndp.end(), 0);
        int rem = min(3, N - col);
        for (int s = 0; s < 64; ++s) {
            if (dp[s].isZero()) continue;
            map<Mask, long long> cnt;
            // Re-run the same local generation for the exact start state.
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
                    for (int r = 0; r < 2; ++r) {
                        if (m & (1 << r)) cover[r].push_back(m);
                    }
                }
            }

            function<void(Mask)> fillCol = [&](Mask cur) {
                if ((cur & 3) == 3) {
                    ++cnt[cur >> 2];
                    return;
                }
                int row = ((cur & 1) == 0 ? 0 : 1);
                for (Mask p : cover[row]) {
                    if ((p & cur) == 0) fillCol(cur | p);
                }
            };

            if ((s & 3) == 3) {
                ++cnt[s >> 2];
            } else {
                int row = ((s & 1) == 0 ? 0 : 1);
                for (Mask p : cover[row]) {
                    if ((p & s) == 0) fillCol(s | p);
                }
            }

            for (auto& kv : cnt) ndp[kv.first] += dp[s] * kv.second;
        }
        dp.swap(ndp);
    }

    cout << dp[0] << '\n';
    return 0;
}
