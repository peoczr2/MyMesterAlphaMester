#include <bits/stdc++.h>
using namespace std;

/*
    A hideg napot +1-gyel, a meleg napot -1-gyel, a többit 0-val jelöljük.
    Egy intervallum akkor jó, ha a két végén hideg vagy meleg nap áll, és a
    belsejében a +1 és -1 értékek összege 0.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> t(n + 1);
    for (int i = 1; i <= n; ++i) cin >> t[i];

    vector<int> jel(n + 1);
    for (int i = 2; i <= n - 1; ++i) {
        if (t[i] < t[i - 1] && t[i] < t[i + 1]) jel[i] = 1;
        else if (t[i] > t[i - 1] && t[i] > t[i + 1]) jel[i] = -1;
    }

    vector<int> pref(n + 1);
    for (int i = 1; i <= n; ++i) pref[i] = pref[i - 1] + jel[i];

    long long db = 0;
    for (int l = 1; l <= n; ++l) {
        if (jel[l] == 0) continue;
        for (int r = l; r <= n; ++r) {
            if (jel[r] == 0) continue;
            if (pref[r] - pref[l - 1] == 0) ++db;
        }
    }

    cout << db << '\n';
    return 0;
}
