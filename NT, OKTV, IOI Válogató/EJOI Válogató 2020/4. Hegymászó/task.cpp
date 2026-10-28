/*
Megoldas: a graf aciklikus, mert minden él kisebb csucsbol nagyobba megy. Ezert
topologikus DP-vel megszamoljuk, hany ut vezet minden csucsba a forrasoktol. A
vonalak szama a sarkok kozotti osszes ut, vagyis a kilepo csucsokba eso darabok
osszege modulo 20200721.
*/
/*
Hint 1: || A táborok és szakaszok irányított körmentes gráfot alkotnak (Kezdi < Végi). A keresett szám a forrásokból (bejövő szakasz nélküli tábor) a nyelőkbe (kimenő szakasz nélküli tábor) vezető utak száma. ||
Hint 2: || A táborokat sorszámuk szerint haladva számold, hány különböző út vezet mindegyikbe: a forrás értéke 1, más táboré a megelőző táborok értékeinek összege. A kiírt érték a nyelők értékeinek összege, a feladatban megadott számmal vett maradéka. ||
*/
#include <bits/stdc++.h>
using namespace std;

static const int MOD = 20200721;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> pred(n + 1);
    vector<int> indeg(n + 1, 0), outdeg(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        pred[v].push_back(u);
        ++indeg[v];
        ++outdeg[u];
    }

    vector<int> ways(n + 1, 0);
    for (int v = 1; v <= n; ++v) {
        if (indeg[v] == 0) ways[v] = 1;
        for (int u : pred[v]) {
            ways[v] += ways[u];
            if (ways[v] >= MOD) ways[v] %= MOD;
        }
    }

    int ans = 0;
    for (int v = 1; v <= n; ++v) {
        if (outdeg[v] == 0) {
            ans += ways[v];
            if (ans >= MOD) ans %= MOD;
        }
    }

    cout << ans % MOD << '\n';
    return 0;
}
