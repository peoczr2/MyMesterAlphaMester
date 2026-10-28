/*
Megoldás lényege:
A bástya egy lépésben a sorában vagy oszlopában bármelyik mezőre eljut, amely
ugyanabban a szabad szakaszban van. A szabad szakasz a bábuk között álló, összefüggő
szabad mezők sora vagy oszlopa. Ezért a szakaszokat tekintjük csúcsoknak: két mező
között akkor van él, ha ugyanabban a szakaszban vannak. A kezdőmezőből indított
szélességi keresés (BFS) adja a minimális lépésszámot. Minden szakaszt csak egyszer
terjesztünk ki, így a futás időigénye O(N^2).
*/
/*
Hint 1: || Egy lépésben a bástya a sorának vagy oszlopának teljes szabad szakaszán bármelyik mezőre eljuthat. Ezért a lépésszám nem a megtett mezők számától függ, hanem attól, hány szakaszváltásra van szükség. ||
Hint 2: || Modellezd a feladatot gráfként: a csúcsok a mezők, és két mező között akkor van él, ha ugyanabban a vízszintes vagy függőleges szabad szakaszban vannak. A legkevesebb lépés a kezdőmezőtől a célmezőig szélességi kereséssel (BFS) kapható meg. ||
Hint 3: || Nem kell minden élet kiépíteni: elég minden szakaszt egyszer kiterjeszteni. Előre számold ki minden mezőhöz a vízszintes és a függőleges szakaszának azonosítóját, a BFS-ben pedig egy szakasz első feldolgozásakor állítsd be a benne lévő, még nem látott mezők távolságát. ||
*/
#include <bits/stdc++.h>
using namespace std;

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
