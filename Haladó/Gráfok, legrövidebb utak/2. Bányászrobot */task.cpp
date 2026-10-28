/*
Megoldás lényege:
A labirintus minden cellája csúcs, két szomszédos cella között pedig él van. Szabad cellába lépés 1 időegységbe kerül, a falba lépés (a fal kibontásával együtt) F időegységbe, ezt a mintapélda is igazolja: a 8-as eredményhez a fal kibontása és a lépés együtt 5 egység. A költségek nemnegatívak, ezért a kezdőcellából Dijkstra-algoritmussal kapjuk a legkisebb időt minden cellához, a célcella távolsága a válasz. Legfeljebb 250 000 cellával és néhány millió éllel az időigény O(NM log(NM)), ami a rövid időlimit alatt marad. Mivel minden fal kibontható, a célcella mindig elérhető.
*/
/*
Hint 1: || Minden cella csúcs, a szomszédos cellák között pedig él van. A belépés költsége attól függ, hogy a cella szabad-e vagy fal: a szabad cella 1, a fal F. Így nemnegatív élsúlyú legrövidebb út feladatot kapunk. ||
Hint 2: || A cellákat egydimenziós indexszel (sor * M + oszlop) tárold, és Dijkstra-algoritmust futtass a kezdőcellából a prioritási sorral. Egy cella távolságát csak akkor frissítsd, ha az új érték kisebb, a célcella távolsága lesz a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, f;
    cin >> n >> m >> f;
    string line;
    getline(cin, line); // a fejlécsor maradéka (például a sorvégi '\r')

    // A pálya sorai szóközöket is tartalmaznak, ezért getline-nal olvassuk őket.
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        getline(cin, line);
        if (!line.empty() && line.back() == '\r') line.pop_back();
        line.resize(m, ' ');
        grid[i] = line;
    }

    int start = -1, target = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'K') start = i * m + j;
            else if (grid[i][j] == 'C') target = i * m + j;
        }
    }

    const long long INF = LLONG_MAX / 4;
    vector<long long> dist(n * m, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    dist[start] = 0;
    pq.push({0, start});

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    while (!pq.empty()) {
        auto [d, cell] = pq.top();
        pq.pop();
        if (d != dist[cell]) continue;
        if (cell == target) break;
        int r = cell / m, c = cell % m;
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            // A falba lépés a fal kibontásával együtt F időegységbe kerül, a szabad cellába 1.
            long long w = (grid[nr][nc] == '*') ? f : 1;
            int ncell = nr * m + nc;
            if (d + w < dist[ncell]) {
                dist[ncell] = d + w;
                pq.push({dist[ncell], ncell});
            }
        }
    }

    cout << dist[target] << '\n';
    return 0;
}
