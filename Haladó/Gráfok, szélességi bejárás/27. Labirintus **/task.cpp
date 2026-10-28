/*
Megoldás lényege:
A kapcsolók miatt az állapot nem csak a pozíciótól függ: az ajtók pillanatnyi állapotát az határozza meg, hogy eddig páros vagy páratlan számú kapcsolóra léptünk-e. Ezért egy állapot egy (sor, oszlop, paritás) hármas, ahol a paritás 0 vagy 1. Kezdetben a paritás 0, így a nyitott ajtók (3) járhatók, a zártak (4) nem. Kapcsolóra lépve a paritás megfordul, és ezzel az ajtók átjárhatósága is megfordul. Mivel minden lépés egységnyi, szélességi bejárással kapjuk a legkevesebb lépést a jobb alsó sarokba, a két paritás közül a kisebb távolságot választjuk. Az előző állapotok és a lépés betűjének tárolásával a legrövidebb lépéssorozat visszafelé követéssel kiírható. Az állapotok száma 2·M·N ≤ 20 000, így az időigény elhanyagolható.
*/
/*
Hint 1: || A kapcsoló minden alkalommal átfordítja az összes ajtó állapotát, ezért a koordináták nem elégségesek. Gondold végig, milyen egyetlen plusz információ dönti el, hogy az ajtók éppen nyitva vannak-e. ||
Hint 2: || Elég egy plusz bit: hogy páros vagy páratlan számú kapcsolóra léptél. A 3-as ajtó akkor járható, ha a bit 0, a 4-es akkor, ha a bit 1. ||
Hint 3: || Szélességi bejárásban a kapcsolóra lépés megfordítja a bitet, minden más lépés megtartja. A célmező bármelyik bitértékével elért legkisebb távolság adja a választ, és a szülőkön visszafelé haladva kiírható az útvonal. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    vector<vector<int>> g(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j) cin >> g[i][j];

    // Állapot: (sor, oszlop, paritás); paritás = 1, ha páratlan számú kapcsolóra léptünk
    auto idx = [&](int r, int c, int p) { return (r * (n + 1) + c) * 2 + p; };
    const int total = (m + 1) * (n + 1) * 2;
    vector<int> dist(total, -1), prv(total, -1);
    vector<char> move(total, 0);

    const int dr[4] = {0, 0, -1, 1};
    const int dc[4] = {-1, 1, 0, 0};
    const char letter[4] = {'B', 'J', 'F', 'L'};

    const int startId = idx(1, 1, 0);
    queue<int> q;
    dist[startId] = 0;
    q.push(startId);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        int p = cur % 2;
        int cell = cur / 2;
        int r = cell / (n + 1), c = cell % (n + 1);

        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 1 || nr > m || nc < 1 || nc > n) continue;
            int val = g[nr][nc];
            if (val == 1) continue;                 // fal
            if (val == 3 && p == 1) continue;       // nyitott ajtó, de már bezárult
            if (val == 4 && p == 0) continue;       // zárt ajtó, de még nem nyílt ki
            int np = (val == 2) ? 1 - p : p;        // kapcsoló: a paritás megfordul
            int nid = idx(nr, nc, np);
            if (dist[nid] != -1) continue;
            dist[nid] = dist[cur] + 1;
            prv[nid] = cur;
            move[nid] = letter[d];
            q.push(nid);
        }
    }

    int bestId = -1;
    for (int p = 0; p < 2; ++p) {
        int id = idx(m, n, p);
        if (dist[id] != -1 && (bestId == -1 || dist[id] < dist[bestId])) bestId = id;
    }

    if (bestId == -1) {
        cout << 0 << '\n';
        return 0;
    }

    string path;
    for (int cur = bestId; cur != startId; cur = prv[cur]) path.push_back(move[cur]);
    reverse(path.begin(), path.end());

    cout << path.size() << '\n' << path << '\n';
    return 0;
}
