/*
Megoldas lenyege:
Mindkét ember szabad időszakai intervallumokból állnak. Az együtt nyaralható
időpontok pontosan a két intervallumhalmaz metszetének összefüggő darabjai.
Mivel az intervallumok száma kicsi, egyszerűen minden párt megvizsgálunk, a
metszeteket összegyűjtjük, majd az eredményt időrendben kiírjuk.
*/
/*
Hint 1: || Két szabad intervallum együtt csak akkor jó, ha a metszetük nem üres. ||
Hint 2: || Minden A-intervallumot érdemes minden B-intervallummal összevetni. ||
Hint 3: || A kapott közös részeket rendezd az első nap szerint, és írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> a(n), b(m);
    for (auto &x : a) cin >> x.first >> x.second;
    for (auto &x : b) cin >> x.first >> x.second;

    vector<pair<int, int>> ans;
    for (auto [l1, r1] : a) {
        for (auto [l2, r2] : b) {
            int l = max(l1, l2);
            int r = min(r1, r2);
            if (l <= r) ans.push_back({l, r});
        }
    }

    sort(ans.begin(), ans.end());
    vector<pair<int, int>> merged;
    for (auto [l, r] : ans) {
        if (merged.empty() || l > merged.back().second + 1) {
            merged.push_back({l, r});
        } else {
            merged.back().second = max(merged.back().second, r);
        }
    }

    cout << merged.size() << '\n';
    for (auto [l, r] : merged) cout << l << ' ' << r << '\n';
    return 0;
}
