/*
Megoldás lényege:
A négyzetrács celláit csomópontoknak tekintjük. Egy celláról egy irányba akkor léphet a villamos, ha a cella
(az eredeti, vagy a forgatással elért) állása ebbe az irányba köti, és a szomszédos cella belépő oldala
az eredeti állásában csatlakozik. Forgatás nélkül egyszerű szélességi bejárás adja a lépésszámot. Forgatással
minden kilépési irányhoz a szükséges forgatások számát (0..3) vesszük, így az átlépés költsége 1 plusz a
forgatások száma; ezt Dijkstra algoritmussal minimalizáljuk. Az időigény O(N * M * log(N * M)).
*/
/*
Hint 1: || Az elemek a forgatással csak négy állást vehetnek fel: egy kilépési irány akkor érhető el, ha az elem állása után az a irány is nyitva van, és a forgatások száma legfeljebb 3. ||
Hint 2: || Elég a cellákat csúcsnak venni: a belépés ellenőrzése a szomszéd eredeti állásától függ, a kilépéshez pedig a cella forgatásainak minimális száma kell. ||
Hint 3: || Forgatás nélküli változatban egyszerű szélességi bejárás elegendő; a forgatásosban prioritási sorral végzett Dijkstra algoritmust használj, ahol az élsúly 1 + a forgatások száma. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Irányok órajárás szerint: 0 = fel, 1 = jobbra, 2 = le, 3 = balra
const int DR[4] = {-1, 0, 1, 0};
const int DC[4] = {0, 1, 0, -1};

// Az elem alapállású összeköttetései bitmaszkban (ugyanezekkel az irányindexekkel)
int baseMask(int t) {
    switch (t) {
        case 0: return 0;                                // üres
        case 1: return (1 << 0) | (1 << 3);             // fel + balra
        case 2: return (1 << 1) | (1 << 3);             // jobbra + balra (vízszintes)
        case 3: return (1 << 0) | (1 << 1) | (1 << 3);  // fel + jobbra + balra
        default: return 15;                              // mind a négy irány
    }
}

// Igaz, ha a t típusú elem r forgatási állásban köti az d irányt
bool connected(int t, int r, int d) {
    int b = ((d - r) % 4 + 4) % 4;
    return (baseMask(t) >> b) & 1;
}

// Legkisebb lépésszám a start és a cél között; allowRot esetén a forgatás is lépés
int shortestSteps(const vector<vector<int>> &T, const vector<vector<int>> &R, int n, int m,
                  int sr, int sc, int tr, int tc, bool allowRot) {
    const int INF = INT_MAX;
    vector<vector<int>> dist(n, vector<int>(m, INF));
    using State = tuple<int, int, int>;  // (távolság, sor, oszlop)
    priority_queue<State, vector<State>, greater<State>> pq;

    dist[sr][sc] = 0;
    pq.push({0, sr, sc});
    int maxRot = allowRot ? 3 : 0;

    while (!pq.empty()) {
        auto [d, r, c] = pq.top();
        pq.pop();
        if (d != dist[r][c]) continue;
        if (r == tr && c == tc) return d;

        for (int dir = 0; dir < 4; dir++) {
            // legkevesebb forgatás, amellyel az elem erre az irányra nyit
            int k = -1;
            for (int x = 0; x <= maxRot; x++) {
                if (connected(T[r][c], R[r][c] + x, dir)) {
                    k = x;
                    break;
                }
            }
            if (k < 0) continue;

            int nr = r + DR[dir], nc = c + DC[dir];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            // a szomszéd belépő oldala az eredeti állásában csatlakozik
            if (!connected(T[nr][nc], R[nr][nc], (dir + 2) % 4)) continue;

            int nd = d + k + 1;
            if (nd < dist[nr][nc]) {
                dist[nr][nc] = nd;
                pq.push({nd, nr, nc});
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> T(n, vector<int>(m)), R(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char a, b;
            cin >> a >> b;  // a: az elem azonosítója, b: a forgatás
            T[i][j] = a - '0';
            R[i][j] = b - '0';
        }
    }

    int sr, sc, tr, tc;
    cin >> sr >> sc >> tr >> tc;
    sr--; sc--; tr--; tc--;

    cout << shortestSteps(T, R, n, m, sr, sc, tr, tc, false) << '\n';
    cout << shortestSteps(T, R, n, m, sr, sc, tr, tc, true) << '\n';
    return 0;
}
