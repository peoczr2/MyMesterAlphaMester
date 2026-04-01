/*
Egy menet teljes ideje a benne szereplő tárgyak legnagyobb egyedi égetési ideje, mert a két kemence párhuzamosan
dolgozik, és a menet csak akkor ér véget, ha mindkettő végzett. Így csak azt kell eldönteni, meddig tartson egy-egy
menet: egy menetben 2 és 2K közötti darab egymást követő tárgy szerepelhet, mert mindkét kemencébe legalább egy és
legfeljebb K tárgy kerülhet. A DP az utolsó menet hosszát próbálja végig, majd a visszafejtett menetekben tetszőleges,
de érvényes 1-es/2-es kemencekiosztást adunk.
*/
/*
Hint 1: || Egy menet költsége független attól, hogy a meneten belül melyik tárgy melyik kemencébe kerül. ||
Hint 2: || Csak az számít, hogy egy menetben hány egymást követő tárgy van: legalább 2 és legfeljebb 2K. ||
Hint 3: || A konkrét kemencekiosztást a végén bármelyik érvényes módon felírhatod, például az elejét az elsőbe, a maradékot a másodikba rakva. ||
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

    const long long INF = (1LL << 60);
    vector<long long> dp(n + 1, INF);
    vector<int> prev_start(n + 1, -1);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        int mx = 0;
        for (int len = 1; len <= 2 * k && len <= i; ++len) {
            mx = max(mx, a[i - len + 1]);
            if (len >= 2 && dp[i - len] + mx < dp[i]) {
                dp[i] = dp[i - len] + mx;
                prev_start[i] = i - len + 1;
            }
        }
    }

    vector<pair<int, int>> rounds;
    for (int i = n; i > 0;) {
        int s = prev_start[i];
        rounds.push_back({s, i});
        i = s - 1;
    }
    reverse(rounds.begin(), rounds.end());

    vector<pair<int, int>> answer(n + 1);
    for (int r = 0; r < (int)rounds.size(); ++r) {
        int l = rounds[r].first, rr = rounds[r].second;
        int len = rr - l + 1;
        int first_oven = max(1, len - k);
        for (int i = l; i < l + first_oven; ++i) {
            answer[i] = {r + 1, 1};
        }
        for (int i = l + first_oven; i <= rr; ++i) {
            answer[i] = {r + 1, 2};
        }
    }

    cout << dp[n] << '\n';
    for (int i = 1; i <= n; ++i) {
        cout << answer[i].first << ' ' << answer[i].second << '\n';
    }
    return 0;
}