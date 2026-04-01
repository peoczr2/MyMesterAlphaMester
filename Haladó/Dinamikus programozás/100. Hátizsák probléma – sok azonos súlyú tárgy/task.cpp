/*
Megoldási ötlet:
Ez a szokásos 0/1 hátizsák: minden tárgy egyszer választható, és a teljes súly legfeljebb K lehet. A dp[w] tömbben azt tároljuk, hogy
pontosan w összsúllyal mekkora maximális haszon érhető el.

Az egydimenziós DP-t súly szerint visszafelé frissítjük, így minden tárgy csak egyszer használódhat fel. Amikor egy állapot javul,
eltároljuk, melyik tárgy tette jobbá és milyen korábbi súlyból jöttünk, így a végén a kiválasztott tárgyak listája visszafejthető.
*/
/*
Hint 1: || Minden tárgy vagy bekerül, vagy kimarad, ezért visszafelé kell frissíteni a súlyokat. ||
Hint 2: || Nem muszáj pontosan K súlyt kitölteni, a legjobb válasz bármelyik legfeljebb K súlynál állhat. ||
Hint 3: || A rekonstrukcióhoz tárold el, melyik tárggyal javult utoljára az adott súly. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, cap;
    cin >> n >> cap;
    vector<int> w(n + 1), e(n + 1);
    for (int i = 1; i <= n; ++i) cin >> w[i];
    for (int i = 1; i <= n; ++i) cin >> e[i];

    vector<int> dp(cap + 1, -1), parentItem(cap + 1, -1), parentWeight(cap + 1, -1);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int curW = cap; curW >= w[i]; --curW) {
            if (dp[curW - w[i]] == -1) continue;
            int cand = dp[curW - w[i]] + e[i];
            if (cand > dp[curW]) {
                dp[curW] = cand;
                parentItem[curW] = i;
                parentWeight[curW] = curW - w[i];
            }
        }
    }

    int bestW = 0;
    for (int curW = 1; curW <= cap; ++curW) {
        if (dp[curW] > dp[bestW]) bestW = curW;
    }

    vector<int> items;
    int curW = bestW;
    while (curW > 0 && parentItem[curW] != -1) {
        items.push_back(parentItem[curW]);
        curW = parentWeight[curW];
    }
    reverse(items.begin(), items.end());

    cout << dp[bestW] << '\n';
    cout << items.size() << '\n';
    for (int i = 0; i < (int)items.size(); ++i) {
        if (i) cout << ' ';
        cout << items[i];
    }
    cout << '\n';
    return 0;
}