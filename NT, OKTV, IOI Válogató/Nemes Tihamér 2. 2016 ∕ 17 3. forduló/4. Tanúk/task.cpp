#include <bits/stdc++.h>
using namespace std;

/*
    A vendégek intervallumai közül a megadott időpontokat minél kevesebb vendég
    lefedésével kell ellátni. Ez klasszikus interval cover: mindig az aktuális
    eseményt lefedő, legtovább tartó vendéget választjuk.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> vendeg(n + 1);
    for (int i = 1; i <= n; ++i) cin >> vendeg[i].first >> vendeg[i].second;
    vector<int> esemeny(m);
    for (int i = 0; i < m; ++i) cin >> esemeny[i];

    int i = 1, j = 0;
    vector<int> valasztott;
    while (j < m) {
        int t = esemeny[j];
        int best = -1, bestEnd = -1;
        while (i <= n && vendeg[i].first <= t) {
            if (vendeg[i].second >= t && vendeg[i].second > bestEnd) {
                bestEnd = vendeg[i].second;
                best = i;
            }
            ++i;
        }
        if (best == -1) {
            ++j;
            continue;
        }
        valasztott.push_back(best);
        while (j < m && esemeny[j] <= bestEnd) ++j;
    }

    cout << m << '\n' << valasztott.size() << '\n';
    for (int k = 0; k < (int)valasztott.size(); ++k) {
        if (k) cout << ' ';
        cout << valasztott[k];
    }
    cout << '\n';
    return 0;
}