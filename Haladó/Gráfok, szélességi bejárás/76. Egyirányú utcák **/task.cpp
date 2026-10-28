/*
Megoldás lényege:
A kereszteződések irányított gráfot alkotnak: egy cellából csak a betűkkel jelölt irányokba lehet továbbmenni.
A sorszámból a sor- és oszlopindex kiszámítható (sorfolytonos számozás), így a szomszédok nem igényelnek külön táblázatot.
Szélességi bejárást (BFS) indítunk A-ból, minden kereszteződésnél eltároljuk, honnan érkeztünk oda: az első felfedezés adja a legrövidebb utat.
Ha B-t elértük, a szülők mentén visszafelé haladva összerakjuk az utat, majd megfordítjuk. Ha B nem érhető el, -1 a válasz.
Minden kereszteződés legfeljebb egyszer kerül a sorba, így az időigény O(N*M), ami 10^4 cellánál bőven belül van.
*/
/*
Hint 1: || Az utcák egyirányúak, ezért sima bejárás helyett irányított gráfban kell keresned: egy kereszteződésből csak a betűkkel jelölt irányokba léphetsz. Egy sorszámból a sor- és oszlopindex az osztási maradékkal és egész osztással kapható meg. ||
Hint 2: || Szélességi bejárást indíts A-ból, és minden újonnan elért kereszteződésnél jegyezd fel az előző kereszteződést. Az első felfedezés már a legrövidebb utat adja, így nem kell minden lehetséges utat végignézni. ||
Hint 3: || Ha B-t elérted, a feljegyzett előzőkön visszafelé haladva gyűjtsd össze az útvonalat, majd fordítsd meg a sorrendet. A lépések száma az út hossza, a kiírt sorszámok száma eggyel nagyobb. Ha B nem érhető el, egyetlen -1-et írj. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a, b;
    cin >> n >> m >> a >> b;
    a--;
    b--;

    string restOfLine;
    getline(cin, restOfLine);  // az első sor maradékának eldobása

    int cells = n * m;
    vector<string> out(cells);
    for (int i = 0; i < cells; ++i) {
        string line;
        if (!getline(cin, line)) line.clear();  // üres sor = zsákutca
        out[i] = line;
    }

    // Irányok: K = kelet (jobbra), D = dél (lefelé), E = észak (felfelé), N = nyugat (balra)
    const char letters[4] = {'K', 'D', 'E', 'N'};
    const int dr[4] = {0, 1, -1, 0};
    const int dc[4] = {1, 0, 0, -1};

    vector<int> dist(cells, -1), parent(cells, -1);
    queue<int> q;
    dist[a] = 0;
    q.push(a);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        int r = v / m, c = v % m;
        for (int d = 0; d < 4; ++d) {
            if (out[v].find(letters[d]) == string::npos) continue;
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            int u = nr * m + nc;
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                parent[u] = v;
                q.push(u);
            }
        }
    }

    if (dist[b] == -1) {
        cout << -1 << '\n';
        return 0;
    }

    vector<int> path;
    for (int v = b; v != a; v = parent[v]) path.push_back(v);
    path.push_back(a);
    reverse(path.begin(), path.end());

    cout << dist[b] << '\n';
    for (size_t i = 0; i < path.size(); ++i)
        cout << path[i] + 1 << (i + 1 < path.size() ? ' ' : '\n');
    return 0;
}
