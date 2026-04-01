/*
Megoldási ötlet:
A játékos mindig jobbra, lefelé vagy átlósan jobbra-lefelé lép, ezért a rács aciklikus. Egy mezőre a legjobb állapotot
úgy írhatjuk le, hogy mennyi pénze marad odaérve. Ha egy elődmezőn legalább L forintja volt, akkor onnan átléphetünk,
fizetünk L-et, majd felvesszük az új mező pénzét.

A dp[i][j] az (i,j) mezőre érkezve elérhető maximális pénzmennyiség. Ha egy mező nem elérhető, -1 marad. A jobb alsó
sarokban kapott dp-érték a válasz.
*/
/*
Hint 1: || Egy mezőnek csak három lehetséges elődje van. ||
Hint 2: || Nem az összegyűjtött pénzt, hanem az aktuálisan megmaradó pénzt érdemes DP-zni. ||
Hint 3: || Csak olyan elődből jöhetsz, ahol még kifizethető a következő lépés ára. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, stepCost;
    cin >> n >> m >> stepCost;
    vector<vector<long long>> money(n + 1, vector<long long>(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cin >> money[i][j];
    }

    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, -1));
    dp[1][1] = money[1][1];

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i == 1 && j == 1) continue;
            auto relax = [&](int pi, int pj) {
                if (pi < 1 || pj < 1 || dp[pi][pj] < stepCost) return;
                dp[i][j] = max(dp[i][j], dp[pi][pj] - stepCost + money[i][j]);
            };
            relax(i - 1, j);
            relax(i, j - 1);
            relax(i - 1, j - 1);
        }
    }

    cout << dp[n][m] << '\n';
    return 0;
}