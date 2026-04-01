/*
Az érkezési sorrendet tartani kell, ezért a tárgyakat egymást követő menetekre particionáljuk. Egy menet költsége
az abban szereplő tárgyak legnagyobb szükséges égetési ideje, és legfeljebb K tárgy kerülhet bele. Így az
egyszerű DP az utolsó menet hosszát próbálja végig 1..K között, közben karbantartva a menet maximumát.
*/
/*
Hint 1: || Egymást követő blokkokra bontásról van szó. ||
Hint 2: || Ha az utolsó menetben t tárgy van, akkor az első i-t tárgy optimális értékéből jössz át. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    const int INF = 1e9;
    vector<int> dp(n + 1, INF), prev_start(n + 1, -1);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        int mx = 0;
        for (int len = 1; len <= k && len <= i; ++len) {
            mx = max(mx, a[i - len + 1]);
            if (dp[i - len] + mx < dp[i]) {
                dp[i] = dp[i - len] + mx;
                prev_start[i] = i - len + 1;
            }
        }
    }

    vector<pair<int, int>> groups;
    for (int i = n; i > 0;) {
        int s = prev_start[i];
        groups.push_back({s, i});
        i = s - 1;
    }
    reverse(groups.begin(), groups.end());

    cout << dp[n] << '\n';
    for (auto [l, r] : groups) {
        cout << l << ' ' << r << '\n';
    }
    return 0;
}