/*
Megoldás lényege:
Ha a lehetséges számok halmaza az [l, r] intervallum, és Jancsi az [a, b]
intervallumra kérdez rá, akkor háromféle eset maradhat:
- a szám kisebb mint a, ekkor [l, a-1] marad,
- a szám benne van [a, b]-ben, ekkor [a, b] marad,
- a szám nagyobb mint b, ekkor [b+1, r] marad.

A kérdés ára a max(f[a], ..., f[b]) érték. Mivel Juliska a legrosszabb választ is
adhatja, az [l, r] állapot optimális költsége:

dp[l][r] = min_{l <= a <= b <= r} (maxPrice[a][b] + max(dp[l][a-1], dp[a][b], dp[b+1][r])).

Az egyelemű intervallum ára 0, mert ott Jancsi már tudja a számot. A maxPrice
tömböt előre kiszámítjuk, majd intervallumhossz szerint növekvő sorrendben töltjük
a DP-t.

Idő: O(N^4), ami N <= 300 mellett elegendő.
*/
/*
Hint 1: || Egy kérdés után nem két, hanem három ág lehet: balra, középre vagy jobbra esik a szám. ||
Hint 2: || A [0] válasz után a megmaradó lehetőségek éppen a lekérdezett [a,b] intervallum. ||
Hint 3: || Az ár nem a kérdezett blokk összege, hanem a benne lévő f[i] értékek maximuma. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> price(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> price[i];
    }

    vector<vector<int>> max_price(n + 2, vector<int>(n + 2, 0));
    for (int l = 1; l <= n; ++l) {
        int current = 0;
        for (int r = l; r <= n; ++r) {
            current = max(current, price[r]);
            max_price[l][r] = current;
        }
    }

    const int INF = 1e9;
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

    for (int len = 2; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;
            int best = INF;
            for (int a = l; a <= r; ++a) {
                for (int b = a; b <= r; ++b) {
                    int worst_child = max({dp[l][a - 1], dp[a][b], dp[b + 1][r]});
                    best = min(best, max_price[a][b] + worst_child);
                }
            }
            dp[l][r] = best;
        }
    }

    cout << dp[1][n] << '\n';
    return 0;
}