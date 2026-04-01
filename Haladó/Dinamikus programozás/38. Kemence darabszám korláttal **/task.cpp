/*
Az érkezési sorrendet tartani kell, ezért a tárgyakat egymást követő menetekre particionáljuk. Egy menet költsége az
abba rakott tárgyak égetési idejének maximuma, és legfeljebb K tárgy kerülhet bele. Az utolsó menet hosszát 1..K között
végigpróbálva, közben a blokk maximumát karbantartva O(NK) időben meghatározható a minimum és a konkrét bontás is.
*/
/*
Hint 1: || A megoldás folytonos blokkokra bontja a tárgysort. ||
Hint 2: || Ha az utolsó blokk hossza ismert, akkor csak annak maximumát kell hozzáadni az előző optimumhoz. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K;
    cin >> n >> K;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    const int INF = 1e9;
    vector<int> dp(n + 1, INF), prev_start(n + 1, -1);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        int mx = 0;
        for (int len = 1; len <= K && len <= i; ++len) {
            mx = max(mx, a[i - len + 1]);
            if (dp[i - len] + mx < dp[i]) {
                dp[i] = dp[i - len] + mx;
                prev_start[i] = i - len + 1;
            }
        }
    }

    vector<pair<int, int>> groups;
    for (int i = n; i > 0; i = prev_start[i] - 1) {
        groups.push_back({prev_start[i], i});
    }
    reverse(groups.begin(), groups.end());

    cout << dp[n] << '\n';
    for (auto [l, r] : groups) {
        cout << l << ' ' << r << '\n';
    }
    return 0;
}
