/*
Egy adott fajta összes előfordulásának ugyanabban a d szerinti maradékosztályban kell lennie, mert ha két
azonos tárgy szerepel, akkor a következő ugyanolyan pontosan d hellyel később áll. Ezért először kiszámítjuk,
hány pozíció van az egyes maradékosztályokban, majd a darabszámokat ezekre a csoportokra osztjuk szét.
d<=3 miatt ez megoldható kis dimenziós részösszeg-DP-vel, utána pedig a csoportokból közvetlenül felírható
az eredeti sorrend.
*/
/*
Hint 1: || Az azonos típusú elemek pozíciói egyetlen 1, 2 vagy 3 maradékosztályba eshetnek csak. ||
Hint 2: || Először ne a teljes sorrendet keresd, hanem azt, melyik típus melyik maradékosztályba kerüljön. ||
Hint 3: || d=3 esetén kétdimenziós részösszeg-DP elég, a harmadik csoport maradékként adódik. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, d;
    cin >> m >> d;
    vector<int> cnt(m + 1);
    int total = 0;
    for (int i = 1; i <= m; ++i) {
        cin >> cnt[i];
        total += cnt[i];
    }

    vector<int> need(d + 1, 0);
    for (int r = 1; r <= d; ++r) {
        if (r <= total) {
            need[r] = (total - r) / d + 1;
        }
    }

    vector<int> group(m + 1, 1);

    if (d == 2) {
        vector<vector<char>> take(m + 1, vector<char>(need[1] + 1, 0));
        take[0][0] = 1;
        for (int i = 1; i <= m; ++i) {
            for (int s = 0; s <= need[1]; ++s) {
                if (!take[i - 1][s]) {
                    continue;
                }
                if (!take[i][s]) {
                    take[i][s] = 2;
                }
                if (s + cnt[i] <= need[1] && !take[i][s + cnt[i]]) {
                    take[i][s + cnt[i]] = 1;
                }
            }
        }
        int s = need[1];
        for (int i = m; i >= 1; --i) {
            if (take[i][s] == 1) {
                group[i] = 1;
                s -= cnt[i];
            } else {
                group[i] = 2;
            }
        }
    } else if (d == 3) {
        int amax = need[1], bmax = need[2];
        auto idx = [amax, bmax](int i, int a, int b) {
            return (i * (amax + 1) + a) * (bmax + 1) + b;
        };
        vector<char> choice((m + 1) * (amax + 1) * (bmax + 1), 0);
        vector<vector<char>> cur(amax + 1, vector<char>(bmax + 1, 0));
        vector<vector<char>> nxt(amax + 1, vector<char>(bmax + 1, 0));
        cur[0][0] = 1;
        choice[idx(0, 0, 0)] = 4;
        for (int i = 1; i <= m; ++i) {
            for (int a = 0; a <= amax; ++a) {
                fill(nxt[a].begin(), nxt[a].end(), 0);
            }
            for (int a = 0; a <= amax; ++a) {
                for (int b = 0; b <= bmax; ++b) {
                    if (!cur[a][b]) {
                        continue;
                    }
                    if (!nxt[a][b]) {
                        nxt[a][b] = 1;
                        choice[idx(i, a, b)] = 3;
                    }
                    if (a + cnt[i] <= amax && !nxt[a + cnt[i]][b]) {
                        nxt[a + cnt[i]][b] = 1;
                        choice[idx(i, a + cnt[i], b)] = 1;
                    }
                    if (b + cnt[i] <= bmax && !nxt[a][b + cnt[i]]) {
                        nxt[a][b + cnt[i]] = 1;
                        choice[idx(i, a, b + cnt[i])] = 2;
                    }
                }
            }
            cur.swap(nxt);
        }
        int a = need[1], b = need[2];
        for (int i = m; i >= 1; --i) {
            char ch = choice[idx(i, a, b)];
            group[i] = ch;
            if (ch == 1) {
                a -= cnt[i];
            } else if (ch == 2) {
                b -= cnt[i];
            }
        }
    }

    vector<vector<int>> order(d + 1);
    for (int i = 1; i <= m; ++i) {
        order[group[i]].push_back(i);
    }

    vector<int> answer(total + 1, 0);
    for (int r = 1; r <= d; ++r) {
        int pos = r;
        for (int type : order[r]) {
            for (int c = 0; c < cnt[type]; ++c) {
                answer[pos] = type;
                pos += d;
            }
        }
    }

    for (int i = 1; i <= total; ++i) {
        if (i > 1) {
            cout << ' ';
        }
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}