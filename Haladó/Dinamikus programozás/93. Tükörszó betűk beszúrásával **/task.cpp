/*
Megoldási ötlet:
A minimális beszúrásszám a klasszikus palindrommá kiegészítési DP-ből adódik. Legyen dp[l][r] a minimális beszúrásszám, amellyel az
S[l..r] részszó tükörszóvá tehető. Ha a két szélső betű egyezik, beljebb lépünk, különben az egyik szélsőt kell „átmásolni” a másik
oldalra.

A DP-ből visszaépítünk egy legrövidebb palindromszuperstringet. Ezután már csak azt kell leírni, hogyan lesz ebből a megadott szóból
beszúrásokkal: végigmegyünk a célpalindromon, és amikor a következő karakter nem egyezik a jelenlegi szó megfelelő karakterével, oda
beszúrjuk.
*/
/*
Hint 1: || A részszó két széle vagy egyezik, vagy az egyik oldalt tükrözéssel kell kipótolni. ||
Hint 2: || Előbb érdemes a teljes végső palindromot visszaépíteni, és csak utána levezetni a konkrét beszúrásokat. ||
Hint 3: || A célpalindrom végigkövetése közben minden nem egyező karakter egyszerűen beszúrás lesz. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = static_cast<int>(s.size());

    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int len = 2; len <= n; ++len) {
        for (int l = 0; l + len - 1 < n; ++l) {
            int r = l + len - 1;
            if (s[l] == s[r]) {
                dp[l][r] = (l + 1 <= r - 1 ? dp[l + 1][r - 1] : 0);
            } else {
                dp[l][r] = min(dp[l + 1][r], dp[l][r - 1]) + 1;
            }
        }
    }

    string leftPart, rightPart;
    int l = 0, r = n - 1;
    while (l <= r) {
        if (l == r) {
            leftPart.push_back(s[l]);
            break;
        }
        if (s[l] == s[r]) {
            leftPart.push_back(s[l]);
            rightPart.push_back(s[r]);
            ++l;
            --r;
        } else if (dp[l + 1][r] <= dp[l][r - 1]) {
            leftPart.push_back(s[l]);
            rightPart.push_back(s[l]);
            ++l;
        } else {
            leftPart.push_back(s[r]);
            rightPart.push_back(s[r]);
            --r;
        }
    }
    reverse(rightPart.begin(), rightPart.end());
    string target = leftPart + rightPart;

    string cur = s;
    vector<pair<int, char>> ops;
    int pos = 0;
    for (char ch : target) {
        if (pos < (int)cur.size() && cur[pos] == ch) {
            ++pos;
        } else {
            ops.push_back({pos, ch});
            cur.insert(cur.begin() + pos, ch);
            ++pos;
        }
    }

    cout << ops.size() << '\n';
    for (auto [where, ch] : ops) {
        cout << where << ' ' << ch << '\n';
    }
    return 0;
}