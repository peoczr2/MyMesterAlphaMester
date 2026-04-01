/*
Az érkezési sorrend nem változhat, tehát a korsók egymást követő menetekre bontják a sort. Egy menet akkor lehet jó,
ha legfeljebb K korsót tartalmaz, létezik közös égetési ideje a benne levő intervallumok metszetében, és a menet vége
nem lépi túl egyik résztvevő határidejét sem. Mivel a minimális összidő a cél, egy rögzített menethez mindig a legkisebb
megengedett égetési időt érdemes választani, így egy egyszerű O(NK) DP adja az optimumot és a beosztást.
*/
/*
Hint 1: || Az utolsó menet mindig egy folytonos blokkból áll. ||
Hint 2: || Egy blokk közös égetési ideje akkor létezik, ha a minimumok maximuma nem nagyobb a maximumok minimumánál. ||
Hint 3: || Optimális megoldásban a blokk égetési ideje a lehető legkisebb választható érték. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K;
    cin >> n >> K;
    vector<int> lo(n + 1), hi(n + 1), deadline(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> lo[i] >> hi[i] >> deadline[i];
    }

    const int INF = 1e9;
    vector<int> dp(n + 1, INF), prev_start(n + 1, -1);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        int need = 0;
        int allow = INF;
        int last_deadline = INF;
        for (int j = i; j >= 1 && i - j + 1 <= K; --j) {
            need = max(need, lo[j]);
            allow = min(allow, hi[j]);
            last_deadline = min(last_deadline, deadline[j]);
            if (need > allow) {
                break;
            }
            if (dp[j - 1] == INF) {
                continue;
            }
            int finish = dp[j - 1] + 1 + need;
            if (finish <= last_deadline && finish < dp[i]) {
                dp[i] = finish;
                prev_start[i] = j;
            }
        }
    }

    vector<pair<int, int>> groups;
    for (int i = n; i > 0; i = prev_start[i] - 1) {
        groups.push_back({prev_start[i], i});
    }
    reverse(groups.begin(), groups.end());

    cout << dp[n] << '\n';
    cout << groups.size() << '\n';
    for (auto [l, r] : groups) {
        cout << l << ' ' << r << '\n';
    }
    return 0;
}
