/*
Az érkezési sorrendet itt is tartani kell, ezért a tárgyakat egymást követő menetekre bontjuk. Egy menet akkor
engedélyezett, ha a benne szereplő tárgyak összsúlya legfeljebb K, a menet költsége pedig a benne levő égetési
idők maximuma. Mivel minden súly legalább 1 és a teljes kapacitás legfeljebb 100, egy menet legfeljebb 100 tárgyat
foghat át, ezért az utolsó menet visszafelé próbálgatása O(N*K) időben elegendő.
*/
/*
Hint 1: || A tárgyak továbbra is folytonos blokkokra vágják a sort. ||
Hint 2: || Az utolsó blokkot visszafelé bővítve egyszerre karbantartható az összsúly és a maximális égetési idő. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> e(n + 1), w(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> e[i] >> w[i];
    }

    const int INF = 1e9;
    vector<int> dp(n + 1, INF), prev_start(n + 1, -1);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        int weight = 0;
        int mx = 0;
        for (int j = i; j >= 1; --j) {
            weight += w[j];
            if (weight > k) {
                break;
            }
            mx = max(mx, e[j]);
            if (dp[j - 1] + mx < dp[i]) {
                dp[i] = dp[j - 1] + mx;
                prev_start[i] = j;
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