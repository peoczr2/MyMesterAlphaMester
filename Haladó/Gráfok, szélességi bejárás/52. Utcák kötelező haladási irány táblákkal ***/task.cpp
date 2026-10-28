/*
Megoldás lényege:
A kereszteződésekbe érkező irány és a jelzőtábla együtt határozza meg, hová léphetünk tovább: egy csomópontban háromféle továbbhaladás lehetséges (egyenesen, balra, jobbra), a táblák ezek közül tiltanak vagy kötelezőt írnak elő.
Ezért az állapot nem csak a csomópont, hanem az is, milyen irányból érkeztünk; így egy állapot (sor, oszlop, érkezési irány) lesz a BFS csúcsa.
Minden csomópont-irány párra előre kiszámoljuk a megengedett kimenő irányok bitmaszkját: alapból az egyenes, a balra és a jobbra fordulás, majd a táblák maszkjait kiszűrjük.
A szélességi bejárás a legrövidebb utat adja, és a talált állapotok irányait visszafelé gyűjtve kapjuk meg az út betűit (E, K, D, N). Az idő az állapotok számával, azaz O(N·M), arányos.
*/
/*
Hint 1: || Egy kereszteződés nem egyformán viselkedik attól függően, honnan érkezel: ugyanaz a csomópont más irányban más lépéseket enged meg. Ezért az állapot legyen (sor, oszlop, érkezési irány). ||
Hint 2: || Minden csomópontnál három lehetőség van: egyenesen, balra vagy jobbra megy tovább, a visszafordulás tilos. A táblák ezt a három lehetőséget szűkítik: BT kizárja a balra fordulást, JT a jobbra fordulást, BK csak balra engedi, JK csak jobbra. ||
Hint 3: || Az érkezési irányt és a jelzőtábla irányát egyszerűen összehasonlíthatod, ha az irányokat 0-tól 3-ig számozod az óramutató járásával megegyezően (észak, kelet, dél, nyugat): a jobbra fordulás ilyenkor +1, a balra fordulás +3 modulo 4. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, t;
    cin >> n >> m >> t;

    // Irányok: 0 = E (észak, sor+1), 1 = K (kelet, oszlop+1), 2 = D (dél, sor-1), 3 = N (nyugat, oszlop-1).
    // Az óramutató járásának megfelelő sorrend: jobbra fordulás = h+1, balra fordulás = h+3 (mod 4).
    const int dr[4] = {1, 0, -1, 0};
    const int dc[4] = {0, 1, 0, -1};
    const char letter[4] = {'E', 'K', 'D', 'N'};

    // allowed[r][c][h]: bitmaszk a megengedett kimenő irányokról, ha (r,c)-re h irányból érkezünk.
    vector<vector<array<int, 4>>> allowed(n + 2, vector<array<int, 4>>(m + 2));
    for (int r = 0; r < n + 2; r++)
        for (int c = 0; c < m + 2; c++)
            for (int h = 0; h < 4; h++)
                allowed[r][c][h] = (1 << h) | (1 << ((h + 1) % 4)) | (1 << ((h + 3) % 4));

    for (int i = 0; i < t; i++) {
        string dirStr, code;
        int r, c;
        cin >> dirStr >> r >> c >> code;
        int h = (dirStr == "E") ? 0 : (dirStr == "K") ? 1 : (dirStr == "D") ? 2 : 3;
        int mask = 0;
        if (code == "BT") mask = (1 << h) | (1 << ((h + 1) % 4));          // balra nem fordulhat
        else if (code == "JT") mask = (1 << h) | (1 << ((h + 3) % 4));     // jobbra nem fordulhat
        else if (code == "BK") mask = 1 << ((h + 3) % 4);                  // csak balra
        else if (code == "JK") mask = 1 << ((h + 1) % 4);                  // csak jobbra
        allowed[r][c][h] &= mask;
    }

    int sr, sc, tr, tc;
    cin >> sr >> sc >> tr >> tc;

    if (sr == tr && sc == tc) {
        cout << 0 << '\n' << '\n';
        return 0;
    }

    auto id = [&](int r, int c, int h) { return (r * (m + 2) + c) * 4 + h; };
    const int total = (n + 2) * (m + 2) * 4;
    vector<int> dist(total, -1), par(total, -1);
    queue<int> q;

    // Az indulási helyről bármerre indulhatunk, ezért az első lépés nem korlátozott.
    for (int d = 0; d < 4; d++) {
        int nr = sr + dr[d], nc = sc + dc[d];
        if (nr < 1 || nr > n || nc < 1 || nc > m) continue;
        int s = id(nr, nc, d);
        if (dist[s] == -1) {
            dist[s] = 1;
            par[s] = -1;
            q.push(s);
        }
    }

    int found = -1;
    while (!q.empty()) {
        int s = q.front();
        q.pop();
        int h = s % 4;
        int cell = s / 4;
        int r = cell / (m + 2), c = cell % (m + 2);
        if (r == tr && c == tc) {
            found = s;
            break;
        }
        for (int d = 0; d < 4; d++) {
            if (!((allowed[r][c][h] >> d) & 1)) continue;
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 1 || nr > n || nc < 1 || nc > m) continue;
            int ns = id(nr, nc, d);
            if (dist[ns] == -1) {
                dist[ns] = dist[s] + 1;
                par[ns] = s;
                q.push(ns);
            } else if (dist[ns] == dist[s] + 1) {
                // Azonos hosszú legrövidebb úton az utolsó előd marad, így a minta útvonala is kijön.
                par[ns] = s;
            }
        }
    }

    if (found == -1) {
        cout << -1 << '\n';
        return 0;
    }

    string path;
    for (int s = found; s != -1; s = par[s]) path.push_back(letter[s % 4]);
    reverse(path.begin(), path.end());

    cout << dist[found] << '\n' << path << '\n';
    return 0;
}
