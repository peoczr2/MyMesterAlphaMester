/*
Megoldás lényege:
Az átlagos eljutási idő a lakosonkénti idők összege osztva a teljes lakosszámmal, ezért elég azt a települést keresni, amelynél a lakosok számával súlyozott összes eljutási idő minimális, mert az osztó minden jelöltnél ugyanannyi.
Mivel N legfeljebb 500, a települések közötti legrövidebb utakat Floyd-Warshall algoritmussal minden párra kiszámoljuk; a gráf összefüggő, így minden távolság véges.
Ezután minden v településre összegezzük a lakosok számának és a v-ből mért távolságnak a szorzatát, és a legkisebb összegű települést írjuk ki (egyenlőség esetén a kisebb sorszámút).
Az időigény O(N^3), ami N ≤ 500 esetén gyors.
*/
/*
Hint 1: || Nem kell tényleges átlagot számolni: elég a lakosokkal súlyozott távolságösszeget minimalizálni, mert az osztó minden településnél ugyanaz. ||
Hint 2: || N kicsi, ezért minden csúcspár legrövidebb útja kiszámolható Floyd-Warshall algoritmussal (háromszoros ciklus), utána egy újabb kétszeres ciklussal választható ki a legjobb település. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> lakos(n + 1);
    for (int i = 1; i <= n; ++i) cin >> lakos[i];

    const long long INF = LLONG_MAX / 4;
    vector<vector<long long>> d(n + 1, vector<long long>(n + 1, INF));
    for (int i = 1; i <= n; ++i) d[i][i] = 0;

    for (int i = 0; i < m; ++i) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        d[a][b] = min(d[a][b], c);
        d[b][a] = min(d[b][a], c);
    }

    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (d[i][k] + d[k][j] < d[i][j]) d[i][j] = d[i][k] + d[k][j];

    int legjobb = 1;
    long long legkisebb = LLONG_MAX;
    for (int v = 1; v <= n; ++v) {
        long long osszeg = 0;
        for (int i = 1; i <= n; ++i) osszeg += lakos[i] * d[v][i];
        if (osszeg < legkisebb) {
            legkisebb = osszeg;
            legjobb = v;
        }
    }

    cout << legjobb << '\n';
    return 0;
}
