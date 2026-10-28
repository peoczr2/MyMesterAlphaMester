/*
Megoldás lényege:
A városi rácson minden kereszteződés egy csúcs, és a behajtani tilos tábla egy irányított él tiltását jelenti: a táblával jelölt (a -> b) lépés nem használható, a fordított irány viszont igen.
Ezért egy egyszerű szélességi bejárást (BFS) futtatunk a rácson, a tiltott éleket kihagyva; a BFS minden csúcsnál eltárolja, melyik lépéssel érkeztünk oda.
A BFS távolsága adja a legrövidebb út hosszát, a célból a tárolt lépéseken visszafelé haladva pedig a legrövidebb út betűit (E, K, D, N) kapjuk meg.
A futási idő O(N·M + T), ami bőven belül van a 0.1 mp-es időlimiten.
*/
/*
Hint 1: || Modellezd a rácsot gráfként: minden kereszteződés egy csúcs, és a négy szomszédos mező között irányított él van. A behajtani tilos tábla azt jelenti, hogy az adott irányított élt nem szabad használni. ||
Hint 2: || A legrövidebb útra szélességi bejárás (BFS) a legegyszerűbb: a táblákat úgy vedd figyelembe, hogy egy él csak akkor kerül be a sorba, ha nincs rajta tilos tábla. Tárold minden csúcsról, melyik lépéssel érted el. ||
Hint 3: || A lépések betűit a visszafelé követett szülőpointerekből kapod: a célból indulva visszafelé lépkedj, majd fordítsd meg a sorrendet. Az E irány észak (sor+1), a K kelet (oszlop+1), a D dél (sor-1), az N nyugat (oszlop-1). ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, t;
    cin >> n >> m >> t;

    // ban[r][c][d]: a (r,c) csomópontból d irányba indulni tilos.
    // d: 0 = E (észak, sor+1), 1 = K (kelet, oszlop+1), 2 = D (dél, sor-1), 3 = N (nyugat, oszlop-1)
    vector<vector<array<bool, 4>>> ban(n + 2, vector<array<bool, 4>>(m + 2, array<bool, 4>{}));
    for (int i = 0; i < t; i++) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        int d = -1;
        if (r2 == r1 + 1 && c2 == c1) d = 0;
        else if (r2 == r1 && c2 == c1 + 1) d = 1;
        else if (r2 == r1 - 1 && c2 == c1) d = 2;
        else if (r2 == r1 && c2 == c1 - 1) d = 3;
        if (d >= 0) ban[r1][c1][d] = true;
    }

    int sr, sc, tr, tc;
    cin >> sr >> sc >> tr >> tc;

    const int dr[4] = {1, 0, -1, 0};
    const int dc[4] = {0, 1, 0, -1};
    const char letter[4] = {'E', 'K', 'D', 'N'};

    vector<vector<int>> dist(n + 2, vector<int>(m + 2, -1));
    vector<vector<int>> par(n + 2, vector<int>(m + 2, -1));
    queue<pair<int, int>> q;
    dist[sr][sc] = 0;
    q.push({sr, sc});
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            if (ban[r][c][d]) continue;
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 1 || nr > n || nc < 1 || nc > m) continue;
            if (dist[nr][nc] != -1) continue;
            dist[nr][nc] = dist[r][c] + 1;
            par[nr][nc] = d;
            q.push({nr, nc});
        }
    }

    if (dist[tr][tc] == -1) {
        cout << -1 << '\n';
        return 0;
    }

    string path;
    int r = tr, c = tc;
    while (!(r == sr && c == sc)) {
        int d = par[r][c];
        path.push_back(letter[d]);
        r -= dr[d];
        c -= dc[d];
    }
    reverse(path.begin(), path.end());

    cout << dist[tr][tc] << '\n' << path << '\n';
    return 0;
}
