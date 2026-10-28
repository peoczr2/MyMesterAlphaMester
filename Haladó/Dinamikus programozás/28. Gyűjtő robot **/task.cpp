/*
Megoldás lényege: a robot oszloponként halad. Egy oszlopban (mivel balra nem léphet, és közvetlenül nem fordulhat vissza)
egyetlen, egy irányú függőleges szakaszt jár be: a belépő sortól a kilépő sorig. A szakasz akkor gyűjti be az oszlop
összes tárgyát, ha lefedi a legfelső (lo) és a legalsó (hi) tárgy sorát, a közbülső tárgyakra nincs külön feltétel.
Ezért dp[e] = a legkevesebb függőleges lépés, amellyel az aktuális oszlop e. sorában lépünk ki. Az átmenetet két
előre kiszámolt minimummal (lefelé: p ≤ lo, e ≥ hi; felfelé: p ≥ hi, e ≤ lo) végezzük, így oszloponként O(N) munka van,
összesen O(N²). A lépésszám M = (N−1) + a függőleges lépések száma; az utat a belépő sorok visszakövetésével építjük fel.
*/
/*
Hint 1: || Egy oszlopban elég tudni, hogy a bejárt függőleges szakasz lefedi-e a legfelső és a legalsó tárgyat. ||
Hint 2: || Legyen dp[e] a legkevesebb függőleges lépés, amellyel az oszlop e. sorában lépünk ki. A belépő sor p akkor jó, ha p ≤ lo és e ≥ hi (lefelé megyünk), vagy p ≥ hi és e ≤ lo (felfelé megyünk). ||
Hint 3: || A lefelé eset költsége e − p, a felfelé eseté p − e, ezért a p-re vonatkozó minimumot egyszer, előre kiszámolhatod, és minden e-hez O(1)-ben használhatod. Az optimális utat tárold a belépő sorral. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    // lo[c]: a c. oszlop legfelső, hi[c]: legalsó tárgyának sora
    vector<int> lo(n + 1, n + 1), hi(n + 1, 0);
    for (int i = 0; i < k; ++i) {
        int r, c;
        cin >> r >> c;
        lo[c] = min(lo[c], r);
        hi[c] = max(hi[c], r);
    }

    const int INF = 1e9;
    // dp[e]: legkevesebb függőleges lépés, amellyel az aktuális oszlop e. sorában lépünk ki.
    // kezdetben a bal felső sarokban (1. sor) állunk, ez az "0. oszlop" kilépése.
    vector<int> dp(n + 1, INF), nxt(n + 1, INF);
    dp[1] = 0;
    // par[c][e]: a c. oszlopba a belépő sor, ha e-ben lépünk ki belőle
    vector<vector<int>> par(n + 1, vector<int>(n + 1, 0));

    for (int c = 1; c <= n; ++c) {
        int top = min(lo[c], n), bot = min(hi[c], n);
        // lefelé: p ≤ top belépésből e ≥ bot kilépésig, költség e − p = e + (dp[p] − p)
        int bestDown = INF, argDown = 0;
        for (int p = 1; p <= top; ++p) {
            if (dp[p] < INF && dp[p] - p < bestDown) { bestDown = dp[p] - p; argDown = p; }
        }
        // felfelé: p ≥ bot belépésből e ≤ top kilépésig, költség p − e = −e + (dp[p] + p)
        int bestUp = INF, argUp = 0;
        for (int p = bot; p <= n; ++p) {
            if (dp[p] < INF && dp[p] + p < bestUp) { bestUp = dp[p] + p; argUp = p; }
        }
        fill(nxt.begin(), nxt.end(), INF);
        for (int e = 1; e <= n; ++e) {
            if (argDown && e >= bot) { nxt[e] = bestDown + e; par[c][e] = argDown; }
            if (argUp && e <= top && bestUp - e < nxt[e]) { nxt[e] = bestUp - e; par[c][e] = argUp; }
        }
        swap(dp, nxt);
    }

    // a célba (N,N) az utolsó oszlopból a N. sorban lépünk ki; M = (N−1) J-lépés + a függőleges lépések
    int answer = dp[n] + (n - 1);

    // visszafejtés: ki[c] = a c. oszlopból kilépő sor, ki[0] = 1 (a start sora)
    vector<int> ki(n + 1, 1);
    ki[n] = n;
    for (int c = n; c >= 1; --c) ki[c - 1] = par[c][ki[c]];

    string path;
    for (int c = 1; c <= n; ++c) {
        if (c > 1) path.push_back('J');
        if (ki[c] > ki[c - 1]) path.append(ki[c] - ki[c - 1], 'L');
        else path.append(ki[c - 1] - ki[c], 'F');
    }

    cout << answer << '\n' << path << '\n';
    return 0;
}
