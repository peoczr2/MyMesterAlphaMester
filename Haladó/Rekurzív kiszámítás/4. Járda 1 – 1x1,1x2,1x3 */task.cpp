/*
Megoldás lényege:
Az utolsó lap hossza 1, 2 vagy 3 lehet, ezért a lefedések száma háromtagú rekurzióval adódik:
dp[n] = dp[n-1] + dp[n-2] + dp[n-3], ahol dp[0] = 1 az üres járda egyetlen lefedése.
Ez azért helyes, mert minden lefedés egyértelműen egy utolsó lapból és a maradék rövidebb
járda egy lefedéséből áll, így minden lehetőséget pontosan egyszer számolunk.
N ≤ 70 esetén az eredmény kisebb 2^63-nál, ezért 64 bites egész elegendő, nagy egészre nincs szükség.
Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Nézd meg, milyen hosszúságú lap állhat legutoljára a lefedésben. ||
Hint 2: || A rekurzió alapjai: hossz 0-ra 1, majd onnan építkezünk tovább. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<long long> dp(max(3, N + 1));
    dp[0] = 1;
    if (N >= 1) dp[1] = 1;
    if (N >= 2) dp[2] = 2;
    for (int i = 3; i <= N; ++i) dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];

    cout << dp[N] << '\n';
    return 0;
}
