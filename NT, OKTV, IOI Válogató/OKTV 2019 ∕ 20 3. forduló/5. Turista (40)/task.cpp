/*
Megoldás lényege:
A városok közötti utazási idő az átszállások miatt a legrövidebb utak hossza, ezért először Floyd–Warshall algoritmussal kiszámoljuk minden várospárra. Az N legfeljebb 10, így a feladat egy kis méretű körút-keresés: a lakóhelyről indulva minden más várost pontosan egyszer kell meglátogatni, majd visszaérni. Ezt bitmaszkos dinamikus programozással oldjuk meg: rem[maszk][c] azt adja meg, hogy a c városból kiindulva mennyi a minimális idő a maszkban még ki nem jelölt városok bejárásához és a lakóhelyre való visszaérkezéshez. A kiinduló állapot értéke adja a minimális teljes utazási időt. A sorrendet úgy kapjuk vissza, hogy mindig a legkisebb sorszámú olyan várost választjuk, amely az optimális értéket megtartja; így a kimenet a lehetséges optimális sorrendek közül a lexikografikusan legkisebb lesz. Az időigény O(N^3 + 2^N · N^2), a memóriaigény O(2^N · N).
*/
/*
Hint 1: || Az átszállások miatt két város közötti utazási idő a legrövidebb utak hossza. Ezt előre kiszámolhatod egy egyszerű három egymásba ágyazott ciklusos algoritmussal, így utána már csak városok közötti összegekkel kell dolgozni. ||
Hint 2: || Legfeljebb 9 várost kell bejárni, ezért az állapotot leírhatod: mely városok vannak már bejárva (bitmaszk), és melyikben tartózkodsz. Az állapot értéke a még hátralévő bejárás és a hazaút minimális ideje. ||
Hint 3: || A sorrend visszafejtésénél a lakóhelyről indulj, és mindig olyan következő várost válassz, amelyre az utazási idő és a hátralévő állapot értéke együtt pont az aktuális állapot értékét adja. Ha több ilyen van, a legkisebb sorszámút vedd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, home;
    cin >> n >> m >> home;

    const int INF = 100000000;
    vector<vector<int>> d(n + 1, vector<int>(n + 1, INF));
    for (int i = 1; i <= n; i++) d[i][i] = 0;
    for (int i = 0; i < m; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        d[a][b] = min(d[a][b], t);
        d[b][a] = min(d[b][a], t);
    }
    // Floyd–Warshall: az átszállásokkal elérhető legrövidebb utak
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    // a meglátogatandó városok (a lakóhely nélkül), növekvő sorrendben
    vector<int> others;
    for (int i = 1; i <= n; i++)
        if (i != home) others.push_back(i);
    int k = (int)others.size();
    int full = (1 << k) - 1;

    // rem[mask][c]: a c városban állva, a maskban még nem jelölt városok bejárása
    // és a lakóhelyre való visszaérkezés minimális ideje
    vector<vector<int>> rem(1 << k, vector<int>(n + 1, 0));
    for (int mask = full; mask >= 0; mask--) {
        for (int c = 1; c <= n; c++) {
            if (mask == full) {
                rem[mask][c] = d[c][home];
                continue;
            }
            int best = INF;
            for (int j = 0; j < k; j++)
                if (!((mask >> j) & 1))
                    best = min(best, d[c][others[j]] + rem[mask | (1 << j)][others[j]]);
            rem[mask][c] = best;
        }
    }

    cout << rem[0][home] << "\n";

    // visszafejtés a lakóhelyről: mindig a legkisebb sorszámú optimális következő város
    vector<int> order;
    int cur = home, mask = 0;
    for (int step = 0; step < k; step++) {
        for (int j = 0; j < k; j++) {
            if ((mask >> j) & 1) continue;
            int v = others[j];
            if (d[cur][v] + rem[mask | (1 << j)][v] == rem[mask][cur]) {
                order.push_back(v);
                mask |= 1 << j;
                cur = v;
                break;
            }
        }
    }
    for (size_t i = 0; i < order.size(); i++) {
        if (i) cout << ' ';
        cout << order[i];
    }
    cout << "\n";
    return 0;
}
