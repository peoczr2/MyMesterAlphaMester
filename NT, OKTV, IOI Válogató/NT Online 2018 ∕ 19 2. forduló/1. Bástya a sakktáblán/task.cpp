#include <bits/stdc++.h>
using namespace std;

/*
    A bástya egy lépésben a sorában vagy oszlopában bármelyik szabad mezőre
    eljuthat. Ezért BFS-t futtatunk, és minden sort/oszlopot egyszer dolgozunk
    fel, hogy a teljes nyílt szakaszt egyszerre terjesszük.
*/

#include <bits/stdc++.h>
using namespace std;

/*
    A bástya egy lépésben a sorában vagy oszlopában bármelyik szabad mezőre
    eljuthat. Ezért a szabad sor- és oszlopszakaszokat külön csúcsokként kezeljük,
    és BFS-ben minden szakaszt csak egyszer terjesztünk ki.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    int ks, ko, cs, co;
    cin >> ks >> ko >> cs >> co;
    --ks; --ko; --cs; --co;

    if (a[ks][ko] == '+' || a[cs][co] == '+') {
        cout << -1 << '\n';
        return 0;
    }
    if (ks == cs && ko == co) {
        cout << 0 << '\n';
        return 0;
    }

    int tot = n * n;
    vector<int> rowSegOf(tot, -1), colSegOf(tot, -1);
    vector<vector<int>> rowSegCells, colSegCells;

    for (int i = 0; i < n; ++i) {
        int j = 0;
        while (j < n) {
            while (j < n && a[i][j] == '+') ++j;
            int s = j;
            vector<int> cells;
            while (j < n && a[i][j] == '-') {
                int id = i * n + j;
                rowSegOf[id] = (int)rowSegCells.size();
                cells.push_back(id);
                ++j;
            }
            if (!cells.empty()) rowSegCells.push_back(move(cells));
        }
    }

    for (int j = 0; j < n; ++j) {
        int i = 0;
        while (i < n) {
            while (i < n && a[i][j] == '+') ++i;
            vector<int> cells;
            while (i < n && a[i][j] == '-') {
                int id = i * n + j;
                colSegOf[id] = (int)colSegCells.size();
                cells.push_back(id);
                ++i;
            }
            if (!cells.empty()) colSegCells.push_back(move(cells));
        }
    }

    int start = ks * n + ko;
    int target = cs * n + co;
    vector<int> dist(tot, -1);
    vector<char> rowDone(rowSegCells.size(), 0), colDone(colSegCells.size(), 0);
    queue<int> q;
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (v == target) break;

        int rs = rowSegOf[v];
        if (rs != -1 && !rowDone[rs]) {
            rowDone[rs] = 1;
            for (int id : rowSegCells[rs]) {
                if (dist[id] == -1) {
                    dist[id] = dist[v] + 1;
                    q.push(id);
                }
            }
        }

        int csId = colSegOf[v];
        if (csId != -1 && !colDone[csId]) {
            colDone[csId] = 1;
            for (int id : colSegCells[csId]) {
                if (dist[id] == -1) {
                    dist[id] = dist[v] + 1;
                    q.push(id);
                }
            }
        }
    }

    cout << dist[target] << '\n';
    return 0;
}
