/*
Megoldás lényege:
A két soros járda oszlopaira profil-DP-t használunk, de az 1×3 vízszintes lap miatt a profilnak
három oszlopnyi előretekintést kell tartania. Egy állapot (6 bites maszk, 64 állapot) azt mutatja
meg, mely cellák foglaltak már az aktuális és a következő két oszlopban. Mindig a bal szélső még
üres cellát fedjük le egy 1×2 vagy 1×3 lappal (a függőleges 1×2 lap egy oszlop mindkét cellájét
fedi), és ha az oszlop megtelt, az állapot egy oszloppal előrébb lép. A válasz a végén a teljesen
üres állapotba vezető utak száma, ami N ≤ 50 esetén 64 bites egész alatt marad, így az időigény O(N).
*/
/*
Hint 1: || A vízszintes 1×3 lap miatt a jelenlegi oszlopon túl még két oszlopot is figyelni kell. ||
Hint 2: || Az állapotok száma kicsi (64), ezért minden állapotból a lehetséges lapelhelyezéseket egyszerűen végigpróbálhatjuk. ||
*/

#include <bits/stdc++.h>
using namespace std;

using Mask = int;

struct Shape { vector<pair<int, int>> cells; };

static vector<vector<pair<Mask, long long>>> buildTransitions(const vector<Shape>& shapes) {
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
        {{{0, 0}, {0, 1}}},
        {{{0, 0}, {0, 1}, {0, 2}}},
        {{{0, 0}, {1, 0}}}
    };

    auto trans = buildTransitions(shapes);
    vector<unsigned long long> dp(64), ndp(64);
    dp[0] = 1;

    for (int col = 0; col < N; ++col) {
        fill(ndp.begin(), ndp.end(), 0);
        int rem = min(3, N - col);
        for (int s = 0; s < 64; ++s) {
            if (dp[s] == 0) continue;
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
