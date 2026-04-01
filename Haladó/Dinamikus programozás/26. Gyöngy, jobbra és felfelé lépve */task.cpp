/*
Az útvonalon bejárt mezők közül a két legnagyobb értékűt érdemes kiválasztani, ezért minden cellához nem a teljes
útvonalat, csak a rajta szereplő két legjobb mezőt tároljuk. A jobb- és lefelé-lépéses DP-ben egy állapot a két
legjobb mező koordinátáit és értékét viszi tovább; az új cellával ezt a párost frissítjük. A végén a szülőirányokból
visszafejtjük az útvonalat, majd megkeressük rajta a kiválasztott két mező sorrendjét.
*/
/*
Hint 1: || Egy adott útvonalról csak a két legértékesebb meglátogatott mező számít. ||
Hint 2: || Ezért minden cellához elég ezt a két mezőt eltárolni, nem kell az egész út. ||
Hint 3: || A végén a visszafejtett útvonalból megállapítható, melyik kiválasztott mező szerepel korábban. ||
*/

#include <bits/stdc++.h>

using namespace std;

struct State {
    long long sum = -(1LL << 60);
    int v1 = -1, r1 = -1, c1 = -1;
    int v2 = -1, r2 = -1, c2 = -1;
    bool valid = false;
};

static State add_cell(const State& s, int value, int row, int col) {
    State res = s;
    vector<tuple<int, int, int>> cand;
    if (s.valid) {
        cand.push_back({s.v1, s.r1, s.c1});
        if (s.v2 >= 0) {
            cand.push_back({s.v2, s.r2, s.c2});
        }
    }
    cand.push_back({value, row, col});
    sort(cand.begin(), cand.end(), [](const auto& a, const auto& b) {
        return get<0>(a) > get<0>(b);
    });

    res.valid = true;
    res.v1 = get<0>(cand[0]);
    res.r1 = get<1>(cand[0]);
    res.c1 = get<2>(cand[0]);
    res.v2 = -1;
    for (const auto& item : cand) {
        int vr = get<0>(item), rr = get<1>(item), cc = get<2>(item);
        if (rr != res.r1 || cc != res.c1) {
            res.v2 = vr;
            res.r2 = rr;
            res.c2 = cc;
            break;
        }
    }
    res.sum = (res.v2 >= 0 ? 1LL * res.v1 + res.v2 : -(1LL << 60));
    return res;
}

static bool better(const State& a, const State& b) {
    if (a.sum != b.sum) {
        return a.sum > b.sum;
    }
    return a.valid && !b.valid;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int r, c;
    cin >> r >> c;
    vector<vector<int>> a(r + 1, vector<int>(c + 1));
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            cin >> a[i][j];
        }
    }

    vector<vector<State>> dp(r + 1, vector<State>(c + 1));
    vector<vector<char>> par(r + 1, vector<char>(c + 1, '?'));

    State start;
    start.valid = true;
    start.v1 = a[1][1];
    start.r1 = 1;
    start.c1 = 1;
    dp[1][1] = start;

    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            if (i == 1 && j == 1) {
                continue;
            }
            State best;
            if (i > 1 && dp[i - 1][j].valid) {
                State cand = add_cell(dp[i - 1][j], a[i][j], i, j);
                if (better(cand, best)) {
                    best = cand;
                    par[i][j] = 'L';
                }
            }
            if (j > 1 && dp[i][j - 1].valid) {
                State cand = add_cell(dp[i][j - 1], a[i][j], i, j);
                if (better(cand, best)) {
                    best = cand;
                    par[i][j] = 'J';
                }
            }
            dp[i][j] = best;
        }
    }

    cout << dp[r][c].sum << '\n';

    vector<pair<int, int>> path_cells;
    string path;
    int i = r, j = c;
    while (true) {
        path_cells.push_back({i, j});
        if (i == 1 && j == 1) {
            break;
        }
        path.push_back(par[i][j]);
        if (par[i][j] == 'L') {
            --i;
        } else {
            --j;
        }
    }
    reverse(path.begin(), path.end());
    reverse(path_cells.begin(), path_cells.end());

    pair<int, int> p1 = {dp[r][c].r1, dp[r][c].c1};
    pair<int, int> p2 = {dp[r][c].r2, dp[r][c].c2};
    int pos1 = 0, pos2 = 0;
    for (int idx = 0; idx < (int)path_cells.size(); ++idx) {
        if (path_cells[idx] == p1) {
            pos1 = idx;
        }
        if (path_cells[idx] == p2) {
            pos2 = idx;
        }
    }
    if (pos2 < pos1) {
        swap(p1, p2);
    }

    cout << p1.first << ' ' << p1.second << ' ' << p2.first << ' ' << p2.second << '\n';
    cout << path << '\n';
    return 0;
}