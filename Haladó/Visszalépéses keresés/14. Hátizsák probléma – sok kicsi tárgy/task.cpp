/*
Hungarian megoldás: klasszikus 0/1 hátizsák dinamikus programozással, amely
megmondja a maximális hasznot és a kiválasztott tárgyakat is.

Hint 1: || A kapacitás legfeljebb 1000, ezért a DP állapota lehet a súly. ||
Hint 2: || Visszaállítással megkapjuk, melyik tárgyak kerültek a megoldásba. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> s(n + 1), e(n + 1);
    for (int i = 1; i <= n; ++i) cin >> s[i];
    for (int i = 1; i <= n; ++i) cin >> e[i];
    vector<int> dp(k + 1, -1e9), prvW(k + 1, -1), prvI(k + 1, -1);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int w = k; w >= s[i]; --w) {
            if (dp[w - s[i]] + e[i] > dp[w]) {
                dp[w] = dp[w - s[i]] + e[i];
                prvW[w] = w - s[i];
                prvI[w] = i;
            }
        }
    }
    int bestW = max_element(dp.begin(), dp.end()) - dp.begin();
    cout << dp[bestW] << '\n';
    vector<int> valasztott;
    int w = bestW;
    vector<char> used(n + 1, 0);
    while (w > 0 && prvI[w] != -1) {
        int i = prvI[w];
        if (used[i]) break;
        used[i] = 1;
        valasztott.push_back(i);
        w = prvW[w];
    }
    cout << valasztott.size() << '\n';
    for (int i = 0; i < (int)valasztott.size(); ++i) {
        if (i) cout << ' ';
        cout << valasztott[i];
    }
    cout << '\n';
    return 0;
}