/*
Megoldás lényege:
Az állapot a három korong helyzete. Mivel a korongok sorrendje közömbös, az állapotot a három mező rendezett hármasaként tároljuk. A 6x6-os táblán 36 mező van, így legfeljebb 36^3 állapot lehet, ami kicsi. Szélességi bejárással (BFS) a kezdőállapotból kiindulva minden állapot legkisebb lépésszámát megkapjuk, a célállapot távolsága lesz a válasz. Egy korong minden irányban két módon mozdulhat: ha a szomszéd mező üres, oda lép; ha a szomszédon korong van, és az azon túli mező üres, átugorhat oda. Minden állapotot legfeljebb egyszer dolgozunk fel, egy állapotból legfeljebb 12 lépés indul (3 korong, 4 irány), így az időigény O(36^3 * 12), ami az időlimiten belül van.
*/
/*
Hint 1: || Tekintsd az állapotot a három korong helyzetének, a lépések számát pedig a kezdőállapottól mért távolságnak. Mivel a korongok sorrendje nem számít, a három mezőt rendezve tárold, és szélességi bejárást (BFS) futtass. ||
Hint 2: || Egy korong lépése két esetben lehetséges: a szomszéd mező üres (akkor oda lépsz), vagy a szomszéd mezőn korong van és az azon túli mező üres (akkor azon átugrasz). A mezőket számozd meg egyetlen számmal (sor * 6 + oszlop), és az állapot kódját a három szám alapján képezd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int R = 6, C = 6, CELLS = R * C;
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    array<int, 3> start{}, goal{};
    for (int i = 0; i < 3; i++) {
        int r, c;
        cin >> r >> c;
        start[i] = (r - 1) * C + (c - 1);
    }
    for (int i = 0; i < 3; i++) {
        int r, c;
        cin >> r >> c;
        goal[i] = (r - 1) * C + (c - 1);
    }

    // Az állapot kódja: a rendezett hármas egyetlen szám.
    auto encode = [&](array<int, 3> s) {
        sort(s.begin(), s.end());
        return (s[0] * CELLS + s[1]) * CELLS + s[2];
    };

    vector<int> dist(CELLS * CELLS * CELLS, -1);
    queue<array<int, 3>> q;
    sort(start.begin(), start.end());
    dist[encode(start)] = 0;
    q.push(start);

    while (!q.empty()) {
        array<int, 3> cur = q.front();
        q.pop();
        int code = encode(cur);

        bool occ[CELLS];
        fill(occ, occ + CELLS, false);
        for (int x : cur) occ[x] = true;

        for (int i = 0; i < 3; i++) {
            int r = cur[i] / C, c = cur[i] % C;
            for (int d = 0; d < 4; d++) {
                int r1 = r + dr[d], c1 = c + dc[d];
                if (r1 < 0 || r1 >= R || c1 < 0 || c1 >= C) continue;

                int to;
                if (!occ[r1 * C + c1]) {
                    to = r1 * C + c1;
                } else {
                    // Átugrás a szomszédos korong fölött, a mögötte lévő üres mezőre.
                    int r2 = r + 2 * dr[d], c2 = c + 2 * dc[d];
                    if (r2 < 0 || r2 >= R || c2 < 0 || c2 >= C) continue;
                    if (occ[r2 * C + c2]) continue;
                    to = r2 * C + c2;
                }

                array<int, 3> nxt = cur;
                nxt[i] = to;
                int nc = encode(nxt);
                if (dist[nc] == -1) {
                    dist[nc] = dist[code] + 1;
                    q.push(nxt);
                }
            }
        }
    }

    cout << dist[encode(goal)] << '\n';
    return 0;
}
