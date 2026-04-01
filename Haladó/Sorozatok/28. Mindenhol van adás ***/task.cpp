/*
Megoldas lenyege:
Az összes adó közös foghatósági szakaszai az egyes adók adásintervallumainak
metszetei. Kezdünk az első adó szakaszaival, majd sorban mindegyik következő
adóval elvégezzük a két rendezett intervallumlista metszését. A végén pontosan
a mindenhol fogható időszakok maradnak meg.
*/
/*
Hint 1: || Először egyetlen adó adásait tekintsd közös jelöltnek. ||
Hint 2: || Mindegyik új adóval ugyanúgy, kétmutatósan metszd ezt az intervallumlistát. ||
Hint 3: || Ami a végén megmarad, az pont azoknak az időszakoknak a listája, amikor minden adó sugároz. ||
*/
#include <bits/stdc++.h>
using namespace std;

static vector<pair<int, int>> intersectLists(const vector<pair<int, int>>& a, const vector<pair<int, int>>& b) {
    vector<pair<int, int>> res;
    int i = 0, j = 0;
    while (i < (int)a.size() && j < (int)b.size()) {
        int l = max(a[i].first, b[j].first);
        int r = min(a[i].second, b[j].second);
        if (l < r) res.push_back({l, r});
        if (a[i].second <= b[j].first) {
            ++i;
        } else if (b[j].second <= a[i].first) {
            ++j;
        } else if (a[i].second < b[j].second) {
            ++i;
        } else {
            ++j;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<pair<int, int>>> stations(n);
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        stations[i].resize(c);
        for (int j = 0; j < c; ++j) cin >> stations[i][j].first >> stations[i][j].second;
    }

    vector<pair<int, int>> common;
    if (n > 0) common = stations[0];
    for (int i = 1; i < n && !common.empty(); ++i) {
        common = intersectLists(common, stations[i]);
    }

    cout << common.size() << '\n';
    for (auto [l, r] : common) cout << l << ' ' << r << '\n';
    return 0;
}
