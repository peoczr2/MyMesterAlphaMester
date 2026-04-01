/*
Megoldas: a sorozat rendezett, ezert minden tipphez binaris keresessel megkeressuk
a legkozelebbi elemet. Ha a ket szomszedos elem egyforma tavolsagra van, a kisebbet
valasztjuk.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> s(n);
    for (int i = 0; i < n; ++i) cin >> s[i];

    for (int qi = 0; qi < m; ++qi) {
        int t;
        cin >> t;
        auto it = lower_bound(s.begin(), s.end(), t);
        int ans;
        if (it == s.begin()) {
            ans = *it;
        } else if (it == s.end()) {
            ans = s.back();
        } else {
            int right = *it;
            int left = *(it - 1);
            if (t - left <= right - t) ans = left;
            else ans = right;
        }
        if (qi) cout << ' ';
        cout << ans;
    }
    cout << '\n';
    return 0;
}
