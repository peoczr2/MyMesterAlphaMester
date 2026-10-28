/*
Megoldás lényege:
A városok közötti utak kétirányú, súlyozott élek, ezért minden csúcspár legrövidebb távolságát ki kell számolni. Mivel N legfeljebb 400, a Floyd-Warshall algoritmus (három egymásba ágyazott ciklus, kb. 64 millió egyszerű művelet) belefér az időkorlátba. A távolságok ismeretében minden városra meghatározzuk a legtávolabbi várost (az excentricitást), és azt a várost választjuk, amelynek ez a legkisebb értéke; egyenlőség esetén a kisebb sorszámút. A kimenetre ennek a városnak a sorszámát és az excentricitás értékét írjuk. Az időigény O(N^3 + M), a memóriaigény O(N^2).
*/
/*
Hint 1: || Egy város akkor jó telephely, ha a tőle legtávolabbi várost a lehető legkisebb távolságra éri el. Ehhez minden városra ismerni kell a többi városig vezető legrövidebb utat. ||
Hint 2: || A távolságokat Floyd-Warshall algoritmussal kapod: minden k csúcsra d[i][j] = min(d[i][j], d[i][k] + d[k][j]). Kezdéskor d[i][i] = 0, az utakat pedig mindkét irányba írd be (párhuzamos utaknál a rövidebbet tartsd meg). ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    const int INF = 1000000000;
    vector<vector<int>> d(n + 1, vector<int>(n + 1, INF));
    for (int i = 1; i <= n; i++) d[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int x, y, h;
        cin >> x >> y >> h;
        d[x][y] = min(d[x][y], h);
        d[y][x] = min(d[y][x], h);
    }

    // Floyd-Warshall: minden csúcspár legrövidebb távolsága.
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (d[i][k] + d[k][j] < d[i][j])
                    d[i][j] = d[i][k] + d[k][j];

    int bestCity = 1, bestEcc = INF;
    for (int i = 1; i <= n; i++) {
        int ecc = 0;
        for (int j = 1; j <= n; j++) ecc = max(ecc, d[i][j]);
        if (ecc < bestEcc) {
            bestEcc = ecc;
            bestCity = i;
        }
    }

    cout << bestCity << '\n' << bestEcc << '\n';
    return 0;
}
