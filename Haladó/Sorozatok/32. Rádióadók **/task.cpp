/*
Megoldas lenyege:
Mindkét adó műsorai időrendben adott, nem átfedő intervallumokból állnak. Két
műsorsorozat akkor lehet ugyanattól az adótól, ha nincs bennük egyetlen közös
időpont sem. Ezért két mutatóval végigpásztázzuk a két listát, és az első
átfedő párt adjuk meg, ha találunk ilyet.
*/
/*
Hint 1: || Ha két adás egyszerre megy, akkor biztosan nem lehet ugyanaz az adó. ||
Hint 2: || A két listát időrendben kell végigjárni, mint két rendezett intervallumsort. ||
Hint 3: || Az első átfedésnél megállhatunk, különben IGEN a válasz. ||
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

    int i = 0, j = 0;
    while (i < n && j < m) {
        if (max(a[i].first, b[j].first) <= min(a[i].second, b[j].second)) {
            cout << "NEM\n" << i + 1 << ' ' << j + 1 << '\n';
            return 0;
        }
        if (a[i].second < b[j].first) ++i;
        else ++j;
    }

    cout << "IGEN\n";
    return 0;
}
