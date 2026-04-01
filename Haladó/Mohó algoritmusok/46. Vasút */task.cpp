/*
Feladat: A kiinduló és végállomás közé minél több megállót kell beiktatni úgy, hogy a megállók távolsága legalább K legyen.
Ötlet: Mindig a legközelebbi még választható állomást vesszük fel, így marad a legtöbb hely a későbbi megállóknak.
Hint 1: || Az első és az utolsó állomás kötelező. ||
Hint 2: || A lehető legkorábbi következő állomást válaszd, amely még legalább K-re van. ||
Hint 3: || A maximális megállószám a mohó bejárásból közvetlenül adódik. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> t(n + 1);
    for (int i = 1; i <= n; ++i) cin >> t[i];

    vector<int> ans{1};
    int last = 1;
    for (int i = 2; i <= n; ++i) {
        if (t[i] - t[last] >= k) {
            ans.push_back(i);
            last = i;
        }
    }

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}