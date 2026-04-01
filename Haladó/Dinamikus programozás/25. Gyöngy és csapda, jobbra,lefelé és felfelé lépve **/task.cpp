/*
Mivel balra nem lehet lépni és mezőt sem szabad ismételni, minden oszlopban az útvonal csak monoton tud haladni:
vagy egy belépési sorból lefelé, vagy onnan felfelé. Ezért oszloponként számolhatjuk a legjobb értéket két söpréssel:
egy lefelé és egy felfelé menettel. Az optimális állapothoz eltároljuk, hogy az adott oszlopba melyik sorban léptünk be
balról, ebből a teljes útvonal visszaépíthető.
*/
/*
Hint 1: || Balra nem léphetsz, ezért egy oszlopon belül nem fordulhatsz meg anélkül, hogy mezőt ismételnél. ||
Hint 2: || Egy oszlop legjobb állapotait külön lefelé és külön felfelé söpréssel lehet kiszámolni. ||
Hint 3: || Az út kiírásához azt tedd el, hogy az adott oszlopba melyik sorból érkeztél jobbról. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int r, c;
    cin >> r >> c;
    vector<vector<long long>> a(r + 1, vector<long long>(c + 1));
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            cin >> a[i][j];
        }
    }

    const long long NEG = -(1LL << 60);
    vector<long long> prev(r + 1, NEG), best(r + 1, NEG), down(r + 1, NEG), up(r + 2, NEG);
    vector<vector<int>> enter(r + 1, vector<int>(c + 1, -1));
    vector<int> enter_down(r + 1, -1), enter_up(r + 2, -1);

    long long sum = 0;
    for (int i = 1; i <= r; ++i) {
        if (a[i][1] == -1 || sum == NEG) {
            sum = NEG;
        } else {
            sum += a[i][1];
        }
        prev[i] = sum;
        if (sum != NEG) {
            enter[i][1] = 1;
        }
    }

    for (int col = 2; col <= c; ++col) {
        for (int row = 1; row <= r; ++row) {
            down[row] = NEG;
            enter_down[row] = -1;
            if (a[row][col] == -1) {
                continue;
            }
            if (prev[row] != NEG) {
                down[row] = prev[row] + a[row][col];
                enter_down[row] = row;
            }
            if (row > 1 && down[row - 1] != NEG && down[row - 1] + a[row][col] > down[row]) {
                down[row] = down[row - 1] + a[row][col];
                enter_down[row] = enter_down[row - 1];
            }
        }

        for (int row = r; row >= 1; --row) {
            up[row] = NEG;
            enter_up[row] = -1;
            if (a[row][col] == -1) {
                continue;
            }
            if (prev[row] != NEG) {
                up[row] = prev[row] + a[row][col];
                enter_up[row] = row;
            }
            if (row < r && up[row + 1] != NEG && up[row + 1] + a[row][col] > up[row]) {
                up[row] = up[row + 1] + a[row][col];
                enter_up[row] = enter_up[row + 1];
            }
        }

        for (int row = 1; row <= r; ++row) {
            if (down[row] >= up[row]) {
                best[row] = down[row];
                enter[row][col] = enter_down[row];
            } else {
                best[row] = up[row];
                enter[row][col] = enter_up[row];
            }
        }
        prev.swap(best);
    }

    cout << prev[r] << '\n';

    vector<int> rows(c + 1, 1);
    rows[c] = r;
    for (int col = c; col >= 2; --col) {
        rows[col - 1] = enter[rows[col]][col];
    }

    string path;
    path.append(rows[1] - 1, 'L');
    for (int col = 2; col <= c; ++col) {
        path.push_back('J');
        if (rows[col] > rows[col - 1]) {
            path.append(rows[col] - rows[col - 1], 'L');
        } else if (rows[col] < rows[col - 1]) {
            path.append(rows[col - 1] - rows[col], 'F');
        }
    }
    cout << path << '\n';
    return 0;
}