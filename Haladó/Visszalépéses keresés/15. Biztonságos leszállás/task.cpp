/*
Hungarian megoldás: kis N miatt minden sorrendet kipróbálunk, és egy adott
minimális távolságra ellenőrizzük, hogy az időpontok elhelyezhetők-e az
intervallumokon belül.

Hint 1: || Ha a sorrend adott, akkor mindig a lehető legkorábbi időpontot érdemes választani. ||
Hint 2: || A legnagyobb biztonsági időt bináris kereséssel is meg lehet találni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i], a[i] *= 60, b[i] *= 60;

    auto good = [&](int d) {
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        do {
            int last = -1e9;
            bool ok = true;
            for (int id : p) {
                int t = max(a[id], last + d);
                if (t > b[id]) { ok = false; break; }
                last = t;
            }
            if (ok) return true;
        } while (next_permutation(p.begin(), p.end()));
        return false;
    };

    int lo = 0, hi = 24 * 60 * 60, best = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (good(mid)) best = mid, lo = mid + 1;
        else hi = mid - 1;
    }
    cout << best / 60 << ':' << setw(2) << setfill('0') << best % 60 << '\n';
    return 0;
}