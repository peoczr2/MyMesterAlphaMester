/*
Megoldási ötlet:
Először minden részszóról eldöntjük, hogy tükörszó-e. Ezután a szokásos prefix-DP következik: dp[i] a szó első i karakterének minimális
tükörszavas felbontási darabszáma.

Ha az [j..i] részszó palindrom, akkor dp[i] frissíthető dp[j-1] + 1 értékkel. Mivel a szó legfeljebb 1000 hosszú, az O(N^2) palindrom-
DP és az O(N^2) felbontásvizsgálat kényelmesen belefér.
*/
/*
Hint 1: || A feladat két részre bontható: mely részszavak palindromok, és hogyan vágjuk fel a teljes szót. ||
Hint 2: || A palindromitás DP-je a két szélső karakter egyezésére épül. ||
Hint 3: || A minimális felbontáshoz a végső palindromdarab elejét kell végigpróbálni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = static_cast<int>(s.size());

    vector<vector<char>> pal(n, vector<char>(n, 0));
    for (int len = 1; len <= n; ++len) {
        for (int l = 0; l + len - 1 < n; ++l) {
            int r = l + len - 1;
            if (len == 1) pal[l][r] = 1;
            else if (len == 2) pal[l][r] = (s[l] == s[r]);
            else pal[l][r] = (s[l] == s[r] && pal[l + 1][r - 1]);
        }
    }

    const int INF = 1e9;
    vector<int> dp(n + 1, INF);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            if (pal[j - 1][i - 1]) dp[i] = min(dp[i], dp[j - 1] + 1);
        }
    }

    cout << dp[n] << '\n';
    return 0;
}