/*
Megoldas lenyege:
A latogatok [Erkezes, Tavozas] intervallumaihoz a munkatarsaknak pontosan
az ezek uniojanak megfelelo idoszakokban kell jelen lenniuk. Mivel a
pontok zartak, a kozos vegpontot is egybe kell vonni, ezert a rendezett
intervallumokat osszefuzzuk, ha a kovetkezo kezdet nem nagyobb az aktualis
vegnel.
*/
/*
Hint 1: || Eloszor rendezd az intervallumokat kezdet szerint. ||
Hint 2: || Ha a kovetkezo intervallum atfed vagy csak erinti az aktualisat, egybe kell olvasztani. ||
Hint 3: || A kimenet a minimalis szamu, egymasbol diszjunkt fedett intervallum lesz. ||
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
        if (merged.empty() || l > merged.back().second) {
            merged.push_back({l, r});
        } else {
            merged.back().second = max(merged.back().second, r);
        }
    }

    cout << merged.size() << '\n';
    for (auto [l, r] : merged) {
        cout << l << ' ' << r << '\n';
    }
    return 0;
}
