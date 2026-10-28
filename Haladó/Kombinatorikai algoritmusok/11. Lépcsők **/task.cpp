/*
   Lépcsők: a feljutási módok száma az N összeg K-ig terjedő pozitív
   lépésekre bontása. Ez egy egyszerű összegző DP: dp[i] az i lépcsőfokra
   feljutási módok száma, dp[0] = 1, és dp[i] a dp[i-1], ..., dp[i-K]
   értékek összege (csak a nem negatív indexűeket véve). A sorrend számít,
   ezért az (1,2) és a (2,1) két külön módnak számít, amit az összegző
   rekurzió pontosan megszámol. Az idő O(N * K), és a legnagyobb érték
   (legfeljebb 2^31) 64 bites típusban biztosan elfér.
*/
/*
Hint 1: || Az utolsó lépésre figyelj: ha az utolsó lépés j fokos (1 <= j <= K), akkor a feljutás előtt az i-j lépcsőfokon kellett állni. ||
Hint 2: || Legyen dp[i] az i lépcsőfokra feljutási módok száma, dp[0] = 1. Ekkor dp[i] = dp[i-1] + dp[i-2] + ... + dp[i-K], ahol csak a nem negatív indexeket adjuk össze, a válasz pedig dp[N]. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;
    vector<unsigned long long> dp(N + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= N; ++i) {
        for (int jump = 1; jump <= K && i - jump >= 0; ++jump) {
            dp[i] += dp[i - jump];
        }
    }
    cout << dp[N] << '\n';
    return 0;
}