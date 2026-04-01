/*
Megoldas lenyege:
Mindkét utazó városlátogatásai időben rendezett, nem átfedő intervallumok.
Kétmutatós bejárással egyszerre haladunk a két listán, és minden olyan város
nevét megjegyezzük, ahol a két intervallum pozitív hosszon metszi egymást. Az
eredmény így a találkozások időrendi sorrendjében áll elő.
*/
/*
Hint 1: || A két lista rendezett, ezért elég egyszerre végigmenni rajtuk. ||
Hint 2: || Ha két városlátogatás időintervalluma metszi egymást, akkor ott találkozhattak. ||
Hint 3: || Minden átfedésnél a későbbi végű intervallum felé kell továbblépni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    map<string, pair<int, int>> a;
    for (int i = 0; i < n; ++i) {
        int l, r;
        string city;
        cin >> l >> r >> city;
        a[city] = {l, r};
    }

    int m;
    cin >> m;
    map<string, pair<int, int>> b;
    for (int i = 0; i < m; ++i) {
        int l, r;
        string city;
        cin >> l >> r >> city;
        b[city] = {l, r};
    }

    vector<pair<int, string>> ans;
    for (auto &[city, intervalA] : a) {
        auto it = b.find(city);
        if (it == b.end()) continue;
        int l = max(intervalA.first, it->second.first);
        int r = min(intervalA.second, it->second.second);
        if (l <= r) ans.push_back({l, city});
    }

    sort(ans.begin(), ans.end());

    cout << ans.size() << '\n';
    for (auto &[l, city] : ans) cout << city << '\n';
    return 0;
}
