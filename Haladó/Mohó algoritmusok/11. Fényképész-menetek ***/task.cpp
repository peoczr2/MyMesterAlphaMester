/*
Feladat: A lehető legkevesebb menetben kell minden vendéget lefényképezni, ahol egy menet hossza K.
Ötlet: A menet kezdőpontját mindig az első lefedetlen vendég távozási idejére tesszük. Így az adott menet a lehető legtöbb további vendéget is lefedi.
Hint 1: || Az első lefedetlen vendég távozási ideje a legkésőbbi jó kezdés. ||
Hint 2: || Ha ennél korábban kezdesz, nem fogsz kevesebb menetet elhasználni. ||
Hint 3: || Egy menet mindenkit lefed, akinek van közös jelenléti szakasza a [F, F+K) intervallummal. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;
    sort(a.begin(), a.end(), [&](auto &x, auto &y) {
        if (x.second != y.second) return x.second < y.second;
        return x.first < y.first;
    });

    vector<int> starts;
    int cur = INT_MIN / 4;
    for (auto [e, t] : a) {
        if (e < cur + k && cur <= t) continue;
        cur = t;
        starts.push_back(cur);
    }

    cout << starts.size() << '\n';
    for (int i = 0; i < (int)starts.size(); ++i) {
        if (i) cout << ' ';
        cout << starts[i];
    }
    cout << '\n';
    return 0;
}