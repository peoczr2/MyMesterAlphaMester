#include <bits/stdc++.h>
using namespace std;

/*
    Először megjelöljük a csúcsokat, majd egy hossz K-hoz tartozó prefixösszeg-
    tömbbel minden lehetséges [A, A+K-1] szakasz csúcsszámát O(1)-ben kiolvassuk.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> m(n + 1);
    for (int i = 1; i <= n; ++i) cin >> m[i];

    vector<int> csucs(n + 1);
    for (int i = 2; i <= n - 1; ++i) {
        if (m[i] > m[i - 1] && m[i] > m[i + 1]) csucs[i] = 1;
    }

    vector<int> pref(n + 1);
    for (int i = 1; i <= n; ++i) pref[i] = pref[i - 1] + csucs[i];

    int legjobb = 0;
    int kezd = -1;
    for (int a = 1; a + k - 1 <= n; ++a) {
        int veg = a + k - 1;
        int darab = 0;
        if (k >= 3) darab = pref[veg - 1] - pref[a];
        if (darab > legjobb) {
            legjobb = darab;
            kezd = a;
        }
    }

    if (legjobb == 0) cout << -1 << ' ' << -1 << '\n';
    else cout << kezd << ' ' << kezd + k - 1 << '\n';
    return 0;
}