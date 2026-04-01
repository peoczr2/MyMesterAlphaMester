/*
Megoldás lényege:
A találkozási mező kiválasztása után két lehetséges mintát kell figyelembe venni:
az egyikben Ádám a mezőn függőlegesen, Éva vízszintesen halad át, a másikban
fordítva. Mindkét esetben a maximális összszamócát a négy sarokból számolt DP-k
adja.

Négy dinamikus táblát számolunk:
- bal felső sarokból minden mezőbe,
- bal alsó sarokból minden mezőbe,
- jobb felső sarokból minden mezőbe,
- jobb alsó sarokból minden mezőbe.
Az első két tábla prefixet, a második kettő suffixet ad a kiválasztott találkozó-
mezőhöz. A legjobb mező és konfiguráció kiválasztása után a két útvonalat a parent
mutatókból visszaépítjük.
*/

#include <bits/stdc++.h>
using namespace std;

struct Prev {
    int r = -1, c = -1;
};

static vector<pair<int,int>> buildPrefix(const vector<vector<Prev>>& par, pair<int,int> cur, pair<int,int> src) {
    vector<pair<int,int>> rev;
    while (true) {
        rev.push_back(cur);
        if (cur == src) break;
        cur = {par[cur.first][cur.second].r, par[cur.first][cur.second].c};
    }
    reverse(rev.begin(), rev.end());
    return rev;
}

static vector<pair<int,int>> buildSuffix(const vector<vector<Prev>>& par, pair<int,int> cur, pair<int,int> dst) {
    vector<pair<int,int>> out;
    while (true) {
        out.push_back(cur);
        if (cur == dst) break;
        cur = {par[cur.first][cur.second].r, par[cur.first][cur.second].c};
    }
    return out;
}

static string toMoves(const vector<pair<int,int>>& path, bool adam) {
    string s;
    for (int i = 0; i + 1 < (int)path.size(); ++i) {
        int dr = path[i + 1].first - path[i].first;
        int dc = path[i + 1].second - path[i].second;
        if (dr == 1) s.push_back('L');
        else if (dr == -1) s.push_back('F');
        else if (dc == 1) s.push_back('J');
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<long long>> a(n + 1, vector<long long>(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cin >> a[i][j];
    }

    const long long NEG = -(1LL << 60);

    vector<vector<long long>> tl(n + 1, vector<long long>(m + 1, NEG));
    vector<vector<long long>> tr(n + 1, vector<long long>(m + 2, NEG));
    vector<vector<long long>> bl(n + 2, vector<long long>(m + 1, NEG));
    vector<vector<long long>> br(n + 2, vector<long long>(m + 2, NEG));

    vector<vector<Prev>> pTL(n + 1, vector<Prev>(m + 1));
    vector<vector<Prev>> pTR(n + 1, vector<Prev>(m + 2));
    vector<vector<Prev>> pBL(n + 2, vector<Prev>(m + 1));
    vector<vector<Prev>> pBR(n + 2, vector<Prev>(m + 2));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i == 1 && j == 1) {
                tl[i][j] = a[i][j];
            } else {
                long long best = NEG;
                if (i > 1 && tl[i - 1][j] > best) {
                    best = tl[i - 1][j];
                    pTL[i][j] = {i - 1, j};
                }
                if (j > 1 && tl[i][j - 1] > best) {
                    best = tl[i][j - 1];
                    pTL[i][j] = {i, j - 1};
                }
                tl[i][j] = best + a[i][j];
            }
        }
    }

    for (int i = n; i >= 1; --i) {
        for (int j = m; j >= 1; --j) {
            if (i == n && j == m) {
                br[i][j] = a[i][j];
            } else {
                long long best = NEG;
                if (i < n && br[i + 1][j] > best) {
                    best = br[i + 1][j];
                    pBR[i][j] = {i + 1, j};
                }
                if (j < m && br[i][j + 1] > best) {
                    best = br[i][j + 1];
                    pBR[i][j] = {i, j + 1};
                }
                br[i][j] = best + a[i][j];
            }
        }
    }

    for (int i = n; i >= 1; --i) {
        for (int j = 1; j <= m; ++j) {
            if (i == n && j == 1) {
                bl[i][j] = a[i][j];
            } else {
                long long best = NEG;
                if (i < n && bl[i + 1][j] > best) {
                    best = bl[i + 1][j];
                    pBL[i][j] = {i + 1, j};
                }
                if (j > 1 && bl[i][j - 1] > best) {
                    best = bl[i][j - 1];
                    pBL[i][j] = {i, j - 1};
                }
                bl[i][j] = best + a[i][j];
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = m; j >= 1; --j) {
            if (i == 1 && j == m) {
                tr[i][j] = a[i][j];
            } else {
                long long best = NEG;
                if (i > 1 && tr[i - 1][j] > best) {
                    best = tr[i - 1][j];
                    pTR[i][j] = {i - 1, j};
                }
                if (j < m && tr[i][j + 1] > best) {
                    best = tr[i][j + 1];
                    pTR[i][j] = {i, j + 1};
                }
                tr[i][j] = best + a[i][j];
            }
        }
    }

    long long bestSum = NEG;
    int bestI = -1, bestJ = -1, bestCase = -1;

    for (int i = 2; i <= n - 1; ++i) {
        for (int j = 2; j <= m - 1; ++j) {
            long long case1 = tl[i - 1][j] + br[i + 1][j] + bl[i][j - 1] + tr[i][j + 1];
            if (case1 > bestSum) {
                bestSum = case1;
                bestI = i;
                bestJ = j;
                bestCase = 1;
            }
            long long case2 = tl[i][j - 1] + br[i][j + 1] + bl[i + 1][j] + tr[i - 1][j];
            if (case2 > bestSum) {
                bestSum = case2;
                bestI = i;
                bestJ = j;
                bestCase = 2;
            }
        }
    }

    vector<pair<int,int>> adam, eva;
    if (bestCase == 1) {
        auto prefA = buildPrefix(pTL, {bestI - 1, bestJ}, {1, 1});
        auto sufA = buildSuffix(pBR, {bestI + 1, bestJ}, {n, m});
        auto prefE = buildPrefix(pBL, {bestI, bestJ - 1}, {n, 1});
        auto sufE = buildSuffix(pTR, {bestI, bestJ + 1}, {1, m});

        adam = prefA;
        adam.push_back({bestI, bestJ});
        adam.insert(adam.end(), sufA.begin(), sufA.end());

        eva = prefE;
        eva.push_back({bestI, bestJ});
        eva.insert(eva.end(), sufE.begin(), sufE.end());
    } else {
        auto prefA = buildPrefix(pTL, {bestI, bestJ - 1}, {1, 1});
        auto sufA = buildSuffix(pBR, {bestI, bestJ + 1}, {n, m});
        auto prefE = buildPrefix(pBL, {bestI + 1, bestJ}, {n, 1});
        auto sufE = buildSuffix(pTR, {bestI - 1, bestJ}, {1, m});

        adam = prefA;
        adam.push_back({bestI, bestJ});
        adam.insert(adam.end(), sufA.begin(), sufA.end());

        eva = prefE;
        eva.push_back({bestI, bestJ});
        eva.insert(eva.end(), sufE.begin(), sufE.end());
    }

    cout << bestSum << '\n';
    cout << bestI << ' ' << bestJ << '\n';
    for (int i = 0; i + 1 < (int)adam.size(); ++i) {
        int dr = adam[i + 1].first - adam[i].first;
        int dc = adam[i + 1].second - adam[i].second;
        cout << (dr == 1 ? 'L' : 'J');
    }
    cout << '\n';
    for (int i = 0; i + 1 < (int)eva.size(); ++i) {
        int dr = eva[i + 1].first - eva[i].first;
        int dc = eva[i + 1].second - eva[i].second;
        cout << (dr == -1 ? 'F' : 'J');
    }
    cout << '\n';
    return 0;
}