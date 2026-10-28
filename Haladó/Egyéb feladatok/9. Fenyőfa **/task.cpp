/*
Megoldás lényege:
Kétdimenziós prefixösszeg-táblával (a bal felső sarkától a (i, j) pontig terjedő fák száma) egy téglalap
fáinak száma négy táblázati értékből O(1) idő alatt megkapható. A rácson minden sor-párra (felső, alsó) és
minden oszlop-párra (bal, jobb) ellenőrizzük, hogy a téglalapban pontosan K fa van-e. Ezek közül a legkisebb
területűt tartjuk meg (azonos területnél az elsőként talált marad). Ha nincs ilyen, négy -1 a válasz.
Az időigény O(N^2 M^2 / 4), ami N, M <= 100 esetén kb. 2,6 * 10^7 egyszerű művelet.
*/
/*
Hint 1: || Nem kell minden téglalapot külön megszámolni: készíts egy táblázatot, amely minden (i, j) pontig a fák számát tartalmazza, így egy téglalap fáit négy érték kivonásával és összeadásával kapod meg. ||
Hint 2: || Válassz ki egy felső és egy alsó sort, majd az oszlopok minden bal-jobb párját végigpróbáld. Ekkor minden oszlopra a két sor közötti fák számát egyetlen szám adja, és a téglalap fáinak száma egy egyszerű összeg. ||
Hint 3: || A téglalap területe (alsó - felső + 1) * (jobb - bal + 1). Azt a téglalapot kell megtartani, amelyre a fák száma K és a terület a legkisebb. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    if (scanf("%d %d %d", &n, &m, &k) != 3) return 0;
    // ps[i][j]: a (1,1)-tól (i,j)-ig terjedő téglalapban lévő fák száma
    vector<vector<int>> ps(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            int x;
            if (scanf("%d", &x) != 1) return 0;
            ps[i][j] = ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1] + x;
        }
    long long best = LLONG_MAX;
    int br1 = -1, bc1 = -1, br2 = -1, bc2 = -1;
    for (int r1 = 1; r1 <= n; r1++)
        for (int r2 = r1; r2 <= n; r2++)
            for (int c1 = 1; c1 <= m; c1++)
                for (int c2 = c1; c2 <= m; c2++) {
                    int cnt = ps[r2][c2] - ps[r1 - 1][c2] - ps[r2][c1 - 1] + ps[r1 - 1][c1 - 1];
                    if (cnt != k) continue;
                    long long area = (long long)(r2 - r1 + 1) * (c2 - c1 + 1);
                    if (area < best) {
                        best = area;
                        br1 = r1; bc1 = c1; br2 = r2; bc2 = c2;
                    }
                }
    if (best == LLONG_MAX) printf("-1 -1 -1 -1\n");
    else printf("%d %d %d %d\n", br1, bc1, br2, bc2);
    return 0;
}
