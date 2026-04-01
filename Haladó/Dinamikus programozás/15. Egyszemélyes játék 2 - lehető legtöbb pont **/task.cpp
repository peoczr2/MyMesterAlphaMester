/*
Itt ugyanaz a megfigyelés érvényes, mint az előző feladatnál: a levett blokkok helye üresen marad, ezért a
későbbi lépésekben sem olvadnak össze a blokkok. Így legfeljebb L darab, egymást nem átfedő, pontosan H hosszú
blokkból kell kiválasztani a maximális összsúlyút. A DP-ben dp[t][i] az első i elemre adja a legjobb értéket
t kiválasztott blokkal; szülőinformációval a blokkok kezdőpozíciói visszafejthetők.
*/
/*
Hint 1: || Az üresen maradó helyek miatt nem alakulnak ki új H hosszú blokkok a lyukakon át. ||
Hint 2: || Előre számold ki minden H hosszú szakasz összegét. ||
Hint 3: || A döntés az i-edik pozíciónál: nem használod az i-edik elemet, vagy lezársz itt egy H hosszú blokkot. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, l, h;
    cin >> n >> l >> h;
    vector<long long> a(n + 1), pref(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
    }

    vector<vector<long long>> dp(l + 1, vector<long long>(n + 1, 0));
    vector<vector<char>> take(l + 1, vector<char>(n + 1, 0));

    for (int t = 1; t <= l; ++t) {
        for (int i = 1; i <= n; ++i) {
            dp[t][i] = dp[t][i - 1];
            if (i >= h) {
                long long block = pref[i] - pref[i - h];
                long long cand = dp[t - 1][i - h] + block;
                if (cand > dp[t][i]) {
                    dp[t][i] = cand;
                    take[t][i] = 1;
                }
            }
        }
    }

    vector<int> starts;
    int t = l, i = n;
    while (t > 0 && i > 0) {
        if (take[t][i] && i >= h && dp[t][i] == dp[t - 1][i - h] + pref[i] - pref[i - h]) {
            starts.push_back(i - h + 1);
            i -= h;
            --t;
        } else {
            --i;
        }
    }
    reverse(starts.begin(), starts.end());

    cout << dp[l][n] << '\n';
    for (int idx = 0; idx < (int)starts.size(); ++idx) {
        if (idx) {
            cout << ' ';
        }
        cout << starts[idx];
    }
    cout << '\n';
    return 0;
}