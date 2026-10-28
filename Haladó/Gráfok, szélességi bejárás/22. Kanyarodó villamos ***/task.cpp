/*
Megoldás lényege:
A villamos állapota nemcsak a pályaelem, hanem az is, hogy melyik oldalán lépett be, mert egy elemen belül nem minden oldalpár van összekötve (az 5-ös elemen például a felső és az alsó oldal csak a bal oldalon át érhető el). Az elemtípusok alapállású összekötéseit a forgatás minden oldal sorszámát ugyanannyival növelve (modulo 4) adja meg. Az állapotok (sor, oszlop, belépési oldal) hármasai; egy lépés egy szomszédos elembe való átlépés, a visszafordulás pedig a belépési oldalon való kilépés, ami szintén egy lépés. Mivel minden lépés egységnyi, a legkisebb lépésszám szélességi bejárással kapható meg. Az állapotok száma 4NM, így az időigény O(NM), ami N, M ≤ 100 esetén bőven elég.
*/
/*
Hint 1: || Az ábrák alapján minden elemtípushoz külön meg kell adni, mely oldalak vannak egymással összekötve; a 0-s elem üres, azon nem lehet áthaladni. ||
Hint 2: || A villamos helyzetét ne csak az elem koordinátái írják le, hanem az is, hogy melyik oldalán lépett be: ugyanaz az elem más belépési oldalról más kilépéseket enged meg. ||
Hint 3: || Szélességi bejárást végezz a (sor, oszlop, belépési oldal) állapotokon: a villamos a belépési oldallal összekötött oldalon vagy a belépési oldalon (visszafordulva) léphet ki, és a szomszédos elem azon oldalán vágánynak kell lennie, ahol belép. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Oldalak sorszáma az óramutató járása szerint: 0 felső, 1 jobb, 2 alsó, 3 bal.
// Az elemtípusok alapállású összekötései (oldalpárok).
const vector<vector<pair<int, int>>> BASE = {
    {},                          // 0: üres
    {{3, 2}},                    // 1: bal-alsó ív
    {{3, 1}},                    // 2: vízszintes egyenes
    {{3, 1}, {3, 2}},            // 3: bal oldalról jobbra és lefelé
    {{0, 1}, {3, 1}, {3, 2}},    // 4
    {{0, 3}, {3, 2}},            // 5: felső-bal és bal-alsó
    {{0, 1}, {3, 2}},            // 6: két különálló ív
    {{0, 3}, {3, 1}, {3, 2}}     // 7
};

const int dr[4] = {-1, 0, 1, 0};
const int dc[4] = {0, 1, 0, -1};

struct Cell {
    bool link[4][4] = {};  // link[a][b]: az a és b oldal össze van kötve
    bool side[4] = {};     // side[a]: van vágány az a oldalon
};

Cell makeCell(int type, int rot) {
    Cell cell;
    for (auto [a, b] : BASE[type]) {
        int x = (a + rot) % 4;
        int y = (b + rot) % 4;
        cell.link[x][y] = cell.link[y][x] = true;
        cell.side[x] = cell.side[y] = true;
    }
    return cell;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<Cell>> grid(n, vector<Cell>(m));
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            string code;
            cin >> code;
            grid[r][c] = makeCell(code[0] - '0', code[1] - '0');
        }
    }

    int sr, sc, dirCode, tr, tc;
    cin >> sr >> sc >> dirCode >> tr >> tc;
    sr--; sc--; tr--; tc--;
    // Belépési kód: 0 bal, 1 felső, 2 jobb, 3 alsó; ezek az oldalsorszámok: 3, 0, 1, 2.
    int entry = (dirCode + 3) % 4;

    // Állapot azonosítója: (sor, oszlop, belépési oldal).
    vector<int> dist(n * m * 4, -1);
    queue<int> q;
    int startState = (sr * m + sc) * 4 + entry;
    dist[startState] = 0;
    q.push(startState);

    while (!q.empty()) {
        int s = q.front();
        q.pop();
        int cell = s / 4;
        int e = s % 4;
        int r = cell / m, c = cell % m;
        if (r == tr && c == tc) {
            cout << dist[s] << "\n";
            return 0;
        }
        for (int x = 0; x < 4; x++) {
            // Csak a belépési oldallal összekötött oldalra lehet kilépni, vagy visszafordulni.
            if (x != e && !grid[r][c].link[e][x]) continue;
            int nr = r + dr[x], nc = c + dc[x];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            int ne = (x + 2) % 4;
            if (!grid[nr][nc].side[ne]) continue;
            int ns = (nr * m + nc) * 4 + ne;
            if (dist[ns] != -1) continue;
            dist[ns] = dist[s] + 1;
            q.push(ns);
        }
    }

    cout << -1 << "\n";
    return 0;
}
