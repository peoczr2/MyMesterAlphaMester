/*
Jancsi és Juliska kitalálós játéka
Feladat: Juliska gondol egy 1..N közötti számra, Jancsi "benne van-e [a,b]-ben?" kérdéseket tesz fel
(válasz: kisebb / benne van / nagyobb), a kérdés ára max(f[a..b]). Mennyi pénz kell ahhoz, hogy
bármely válaszsorozat mellett kitalálja a számot?

Megoldás: a még lehetséges számok mindig egy [l, r] intervallumot alkotnak. Az [a,b] kérdés három
ágra bont: [l, a-1], [a, b], [b+1, r], és Juliska a legdrágább ágat választja:
dp[l][r] = min (M[a][b] + max(dp[l][a-1], dp[a][b], dp[b+1][r])), l <= a <= b <= r,
ahol M[a][b] = max(f[a..b]), az egyelemű és az üres intervallum értéke 0.
Az a = l, b = r kérdés semmit nem árul el, ezt ki kell hagyni (különben dp[l][r] a saját, még ki
nem számolt értékét olvasná). Intervallumhossz szerint növekvő sorrendben töltünk.
Gyorsítás: rögzített a mellett M[a][b] + max(dp[l][a-1], dp[a][b]) b-vel nem csökken, így ha már
eléri az eddigi legjobbat, a b-ciklus megszakítható.
Idő: O(N^4/24) legrosszabb esetben (N = 300 mellett kb. 0.35 mp vágás nélkül is), memória: O(N^2).
*/
/*
Hint 1: || Mutasd meg, hogy néhány kérdés után a még lehetséges számok mindig egy összefüggő [l, r] intervallumot alkotnak. ||
Hint 2: || dp[l][r] = a legkisebb pénz, amivel az [l, r]-be eső számot biztosan kitalálja. Egy [a,b] kérdés három ágra bont, és Juliska a legdrágábbat választja: max kell, nem összeg. ||
Hint 3: || dp[l][r] = min (M[a][b] + max(dp[l][a-1], dp[a][b], dp[b+1][r])) minden l ≤ a ≤ b ≤ r-re, kivéve az a=l, b=r kérdést, ami nem ad információt. M[a][b] = max f előre kiszámolva, hossz szerint töltve O(N^4/24) belefér. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // beolvasás
    int n;
    cin >> n;
    vector<int> f(n + 1);
    for (int i = 1; i <= n; ++i) cin >> f[i];

    // M[a][b] = max(f[a..b]), a kérdés ára
    vector<vector<int>> M(n + 2, vector<int>(n + 2, 0));
    for (int a = 1; a <= n; ++a) {
        int legnagyobb = 0;
        for (int b = a; b <= n; ++b) {
            legnagyobb = max(legnagyobb, f[b]);
            M[a][b] = legnagyobb;
        }
    }

    // dp[l][r]; az üres (l > r) és az egyelemű intervallum értéke 0
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
    for (int len = 2; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;
            int best = INT_MAX;
            for (int a = l; a <= r; ++a) {
                for (int b = a; b <= r; ++b) {
                    if (a == l && b == r) continue;    // ez a kérdés nem ad információt
                    // a bal és a középső ág ára b növelésével nem csökken
                    int alap = M[a][b] + max(dp[l][a - 1], dp[a][b]);
                    if (alap >= best) break;
                    best = min(best, max(alap, M[a][b] + dp[b + 1][r]));
                }
            }
            dp[l][r] = best;
        }
    }

    cout << dp[1][n] << '\n';
    return 0;
}
