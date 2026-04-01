/*
Az állapotot a még asztalon lévő [l,r] intervallum írja le, mindig a játékos lépése előtt. Ha a játékos balról
vesz el, akkor utána a játékvezető az új két szélső közül a nagyobbat veszi le, és így kapunk egy kisebb
intervallumot; jobbról választva ugyanez történik szimmetrikusan. A dp[l][r] érték ezért egyszerűen a két
lehetséges első döntés maximuma, a szülőtáblából pedig a B/J lépéssor visszafejthető.
*/
/*
Hint 1: || Az állapot legyen a megmaradt folytonos intervallum a játékos lépése előtt. ||
Hint 2: || Egy játékoslépés után a játékvezető lépése determinisztikus: mindig a nagyobbik szélsőt viszi el. ||
Hint 3: || Csak páros hosszú intervallumokat kell tárolni, mert két szám tűnik el egy teljes körben. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n + 2, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<vector<long long>> dp(n + 2, vector<long long>(n + 2, 0));
    vector<vector<char>> choice(n + 2, vector<char>(n + 2, 'B'));

    for (int len = 2; len <= n; len += 2) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;

            long long take_left = a[l];
            if (l + 1 <= r) {
                if (l + 1 == r) {
                    take_left += 0;
                } else if (a[l + 1] >= a[r]) {
                    take_left += dp[l + 2][r];
                } else {
                    take_left += dp[l + 1][r - 1];
                }
            }

            long long take_right = a[r];
            if (l <= r - 1) {
                if (l == r - 1) {
                    take_right += 0;
                } else if (a[l] >= a[r - 1]) {
                    take_right += dp[l + 1][r - 1];
                } else {
                    take_right += dp[l][r - 2];
                }
            }

            if (take_right > take_left) {
                dp[l][r] = take_right;
                choice[l][r] = 'J';
            } else {
                dp[l][r] = take_left;
                choice[l][r] = 'B';
            }
        }
    }

    cout << dp[1][n] << '\n';
    string steps;
    int l = 1, r = n;
    while (l <= r) {
        char ch = choice[l][r];
        steps.push_back(ch);
        if (ch == 'B') {
            ++l;
            if (l > r) {
                break;
            }
            if (l == r) {
                break;
            }
            if (a[l] >= a[r]) {
                ++l;
            } else {
                --r;
            }
        } else {
            --r;
            if (l > r) {
                break;
            }
            if (l == r) {
                break;
            }
            if (a[l] >= a[r]) {
                ++l;
            } else {
                --r;
            }
        }
    }
    cout << steps << '\n';
    return 0;
}