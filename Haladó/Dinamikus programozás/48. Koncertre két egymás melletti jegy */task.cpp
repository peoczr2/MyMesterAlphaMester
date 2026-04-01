/*
Minden igény pontosan két egymás melletti székre vonatkozik, ezért az elfogadott igények egy súlyozott intervallum-
halmazt alkotnak az 1..M üléssoron. Legyen dp[p] a p-edik székig elérhető legnagyobb bevétel; ekkor egy p-ben végződő
igény vagy bekerül és dp[p-2]-höz adódik, vagy kimarad és marad dp[p-1]. A döntések eltárolásával a kiválasztott igények
visszafejthetők.
*/
/*
Hint 1: || Egy igény valójában a [s,s+1] kétszékes intervallumot foglalja el. ||
Hint 2: || A p-ben végződő igény csak a p-2-ig számolt optimumhoz csatlakozhat. ||
*/

#include <bits/stdc++.h>

using namespace std;

struct Request {
    int start;
    int fee;
    int idx;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    vector<vector<Request>> by_end(m + 1);
    vector<int> fee(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int s, f;
        cin >> s >> f;
        by_end[s + 1].push_back({s, f, i});
        fee[i] = f;
    }

    vector<long long> dp(m + 1, 0);
    vector<int> take(m + 1, -1);
    for (int seat = 2; seat <= m; ++seat) {
        dp[seat] = dp[seat - 1];
        for (const Request& req : by_end[seat]) {
            long long cand = dp[seat - 2] + req.fee;
            if (cand > dp[seat]) {
                dp[seat] = cand;
                take[seat] = req.idx;
            }
        }
    }

    vector<int> chosen;
    for (int seat = m; seat >= 2;) {
        int idx = take[seat];
        if (idx != -1 && dp[seat] == dp[seat - 2] + fee[idx]) {
            chosen.push_back(idx);
            seat -= 2;
        } else {
            --seat;
        }
    }
    reverse(chosen.begin(), chosen.end());

    cout << dp[m] << '\n';
    for (int i = 0; i < (int)chosen.size(); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << chosen[i];
    }
    cout << '\n';
    return 0;
}
