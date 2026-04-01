/*
Megoldas lenyege:
A tilalmi idoszakok intervallumai adottak. Ezeket rendezve osszevonjuk, majd az egesz ev
[1..365] szakaszabol kivonjuk a lefedett reszeket. A fennmarado maximalis szakaszok pontosan
a szabad horgaszati idoszakok.
*/
/*
Hint 1: || Először a tilalmakat kell összemetszeni, mert az egymást fedő intervallumokat össze lehet vonni. ||
Hint 2: || A szabad időszakok a lefedett intervallumok közötti rések. ||
Hint 3: || Az év elejét és végét is külön kezeld, mert ott is lehet szabad nap. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int, int>> intervals(n);
    for (int i = 0; i < n; ++i) cin >> intervals[i].first >> intervals[i].second;
    sort(intervals.begin(), intervals.end());

    vector<pair<int, int>> merged;
    for (auto [l, r] : intervals) {
        if (merged.empty() || l > merged.back().second + 1) {
            merged.push_back({l, r});
        } else {
            merged.back().second = max(merged.back().second, r);
        }
    }

    vector<pair<int, int>> freeIntervals;
    int current = 1;
    for (auto [l, r] : merged) {
        if (current < l) freeIntervals.push_back({current, l - 1});
        current = max(current, r + 1);
    }
    if (current <= 365) freeIntervals.push_back({current, 365});

    cout << freeIntervals.size() << '\n';
    for (auto [l, r] : freeIntervals) {
        cout << l << ' ' << r << '\n';
    }

    return 0;
}
