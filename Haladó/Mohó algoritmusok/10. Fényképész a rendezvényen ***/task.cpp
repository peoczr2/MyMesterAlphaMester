/*
Feladat: A lehető legkevesebb időpontban kell fényképezni úgy, hogy minden vendég rajta legyen legalább egy képen.
Ötlet: A vendégeket a távozási idő szerint rendezzük, és mindig az első lefedetlen vendég távozása előtti utolsó időpontban fotózunk. Ez lefedi a legtöbb további vendéget.
Hint 1: || Az első olyan vendég, akit még nem fedett le kép, megszabja az új fotó időpontját. ||
Hint 2: || A távozási idő előtti legutolsó egész időpont a legjobb választás. ||
Hint 3: || Ezután minden olyan vendéget hagyj ki, aki ezen az időponton még jelen van. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;
    sort(a.begin(), a.end(), [&](auto &x, auto &y) {
        if (x.second != y.second) return x.second < y.second;
        return x.first < y.first;
    });

    vector<int> ans;
    int last = INT_MIN;
    for (auto [e, u] : a) {
        if (e <= last && last < u) continue;
        last = u - 1;
        ans.push_back(last);
    }

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}