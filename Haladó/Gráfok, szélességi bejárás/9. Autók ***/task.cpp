/*
Megoldás lényege:
Az állapot most nem csak a pozíció, hanem a sebesség is: (sor, oszlop, sebesség). Egy időegység alatt az autó a sebességének megfelelően pontosan annyi cellát lép egyenes vonalban, és a lépés előtt a sebesség legfeljebb 1-gyel változhat, így minden állapotból legfeljebb 3 sebességgel és 4 irányba lehet továbblépni. Mivel minden lépés egy időegység, a legrövidebb idő szélességi bejárással (BFS) adódik. Egy lépés akkor engedélyezett, ha a megtett cellák mindegyike szabad, ezt minden cellára és irányra előre kiszámoljuk (legfeljebb K hosszan). Az állapotok száma N·M·(K+1) legfeljebb 200·200·11, így az időigény O(N·M·K).
*/
/*
Hint 1: || Az állapot ne csak a pozíció legyen: a következő lépés hossza a sebességtől függ. Mivel minden lépés egy időegység, a legkevesebb lépés adja a legrövidebb időt. ||
Hint 2: || Egy lépésben az autó egyenes vonalban pontosan s cellát megy, ahol s a sebessége. A következő sebesség csak s-1, s vagy s+1 lehet, és legalább 1, legfeljebb K. ||
Hint 3: || Minden cellából és irányból előre számold ki, hány szabad cella van egymás után (legfeljebb K), így a lépés ellenőrzése O(1). Kezdéskor a sebesség 0, az első lépés csak 1 lehet, a célt pedig csak 1 sebességgel szabad elfogadni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, kmax;
    cin >> n >> m >> kmax;
    string line;
    getline(cin, line);

    vector<string> g(n);
    int sr = 0, sc = 0, cr = 0, cc = 0;
    for (int i = 0; i < n; i++) {
        getline(cin, line);
        if (!line.empty() && line.back() == '\r') line.pop_back();
        line.resize(m, ' ');
        g[i] = line;
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 'K') { sr = i; sc = j; }
            if (g[i][j] == 'C') { cr = i; cc = j; }
        }
    }

    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    auto isFree = [&](int r, int c) {
        return r >= 0 && r < n && c >= 0 && c < m && g[r][c] != '*';
    };

    // run[cella][d]: hány szabad cella van egymás után a cellától d irányban (legfeljebb kmax)
    vector<array<int, 4>> run(n * m);
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            for (int d = 0; d < 4; d++) {
                int len = 0, rr = r, cc2 = c;
                while (len < kmax && isFree(rr + dr[d], cc2 + dc[d])) {
                    rr += dr[d];
                    cc2 += dc[d];
                    len++;
                }
                run[r * m + c][d] = len;
            }

    const int S = kmax + 1;
    vector<int> dist(n * m * S, -1);
    auto id = [&](int r, int c, int s) { return (r * m + c) * S + s; };

    queue<array<int, 3>> q;
    dist[id(sr, sc, 0)] = 0;
    q.push({sr, sc, 0});
    int answer = -1;
    while (!q.empty()) {
        auto [r, c, s] = q.front();
        q.pop();
        if (r == cr && c == cc && s == 1) {
            answer = dist[id(r, c, s)];
            break;
        }
        int lo = max(1, s - 1), hi = min(kmax, s + 1);
        for (int s2 = lo; s2 <= hi; s2++)
            for (int d = 0; d < 4; d++) {
                if (run[r * m + c][d] < s2) continue;
                int nr = r + dr[d] * s2, nc = c + dc[d] * s2;
                if (dist[id(nr, nc, s2)] != -1) continue;
                dist[id(nr, nc, s2)] = dist[id(r, c, s)] + 1;
                q.push({nr, nc, s2});
            }
    }
    cout << answer << '\n';
    return 0;
}
