/*
A feladat a leghosszabb tukorszo-reszsorozat hosszat kerdezi, ami a klasszikus longest
palindromic subsequence problema. Legyen dp[l][r] a legjobb valasz az S[l..r] reszszora.
Ha a ket szelso betu egyezik, akkor ezek egy optimalis tukorszo ket szelere tehetok, igy
dp[l][r] = dp[l+1][r-1] + 2. Kulonben legalabb az egyik szelso betut el kell hagyni, ezert
dp[l][r] = max(dp[l+1][r], dp[l][r-1]). A tablazat rovidebb intervallumoktol hosszuak fele
toltheto fel O(n^2) idoben.
*/
/*
Hint 1: || Nem reszsztringet, hanem reszsorozatot keresunk, vagyis betuket ki lehet hagyni. ||
Hint 2: || Egy intervallum valasza csak kisebb belso intervallumok valaszaitol fugg. ||
Hint 3: || Ha a ket szelso karakter megegyezik, erdemes oket egyszerre felhasznalni. ||
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string text;
    cin >> text;
    int n = static_cast<int>(text.size());

    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int index = 0; index < n; ++index) {
        dp[index][index] = 1;
    }

    for (int length = 2; length <= n; ++length) {
        for (int left = 0; left + length - 1 < n; ++left) {
            int right = left + length - 1;
            if (text[left] == text[right]) {
                dp[left][right] = 2;
                if (left + 1 <= right - 1) {
                    dp[left][right] += dp[left + 1][right - 1];
                }
            } else {
                dp[left][right] = max(dp[left + 1][right], dp[left][right - 1]);
            }
        }
    }

    cout << dp[0][n - 1] << '\n';
    return 0;
}