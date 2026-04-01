/*
Megoldas lenyege:
A két ügynök adásai rendezett, egymást nem fedő intervallumok. Kétmutatós
bejárással megkeressük az egymást fedő részeket, és ezek hosszaiból összegezzük
a biztosan két készüléket igénylő időt.
*/
/*
Hint 1: || Csak az intervallumok metszete számít. ||
Hint 2: || A két rendezett listán elég egyszerre haladni. ||
Hint 3: || Minden átfedésből a metszethossz kerül az összegbe. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int e;
    cin >> e;
    vector<pair<int,int>> a(e);
    for (auto &x : a) cin >> x.first >> x.second;
    int m;
    cin >> m;
    vector<pair<int,int>> b(m);
    for (auto &x : b) cin >> x.first >> x.second;

    int i = 0, j = 0;
    long long ans = 0;
    while (i < e && j < m) {
        int l = max(a[i].first, b[j].first);
        int r = min(a[i].second, b[j].second);
        if (l < r) ans += r - l;
        if (a[i].second < b[j].second) ++i;
        else ++j;
    }

    cout << ans << '\n';
    return 0;
}
