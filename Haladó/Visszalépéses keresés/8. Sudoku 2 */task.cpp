/*
Hungarian megoldás: a 4x4-es sudoku összes szabályos kitöltését előállítjuk,
és megszámoljuk, melyek illeszkednek a megadott táblára.

Hint 1: || A méret kicsi, ezért a teljes 4x4-es megoldáshalmaz végigjárható. ||
Hint 2: || A megadott számokkal ellentmondó táblák kiesnek. ||
*/

#include <bits/stdc++.h>
using namespace std;

int a[4][4];
vector<array<array<int,4>,4>> boards;

bool good(const array<array<int,4>,4> &b) {
    for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) if (a[i][j] && a[i][j] != b[i][j]) return false;
    return true;
}

void gen() {
    array<int,4> r0 = {1,2,3,4};
    do {
        array<array<int,4>,4> b{};
        for (int i = 0; i < 4; ++i) b[0][i] = r0[i];
        function<void(int)> dfs = [&](int r) {
            if (r == 4) {
                boards.push_back(b);
                return;
            }
            array<int,4> row = {1,2,3,4};
            do {
                bool ok = true;
                for (int c = 0; c < 4 && ok; ++c) {
                    for (int rr = 0; rr < r; ++rr) if (b[rr][c] == row[c]) ok = false;
                    int br = (r / 2) * 2, bc = (c / 2) * 2;
                    for (int rr = br; rr < r && ok; ++rr) for (int cc = bc; cc < bc + 2; ++cc) if (b[rr][cc] == row[c]) ok = false;
                }
                if (!ok) continue;
                for (int c = 0; c < 4; ++c) b[r][c] = row[c];
                dfs(r + 1);
            } while (next_permutation(row.begin(), row.end()));
        };
        dfs(1);
    } while (next_permutation(r0.begin(), r0.end()));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) cin >> a[i][j];
    gen();
    long long cnt = 0;
    for (auto &b : boards) if (good(b)) ++cnt;
    cout << cnt << '\n';
    return 0;
}