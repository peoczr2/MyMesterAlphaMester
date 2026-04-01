/*
Ez egy tiszta eseményszimuláció: az érkező autókat mindig a jelenleg legrövidebb sorhoz kell rendelni, majd a kiszolgálások időpontjait külön követni. A helyes sorrendhez elég a sorhosszakat és a következő felszabadulási időket karbantartani.
*/
/*
Hint 1: || Minden autót mindig a jelenleg legrövidebb sorhoz rendelj, mert csak a sorhossz számít. ||
Hint 2: || A kiszolgálási időket soronként előrehaladva, eseményszimulációval lehet pontosan követni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, l;
    cin >> n >> l;
    vector<int> e(n), t(n);
    for (int i = 0; i < n; ++i) cin >> e[i] >> t[i];

    vector<deque<long long>> q(l);
    long long best_wait = 0;
    int best_count = 0;
    long long current_total = 0;
    for (int i = 0; i < n; ++i) {
        long long time = e[i];
        while (true) {
            bool changed = false;
            for (int s = 0; s < l; ++s) {
                while (!q[s].empty() && q[s].front() <= time) {
                    q[s].pop_front();
                    --current_total;
                    changed = true;
                }
            }
            if (!changed) break;
        }

        int best = 0;
        int best_waiting = INT_MAX;
        for (int s = 0; s < l; ++s) {
            int waiting = (int)q[s].size();
            if (waiting < best_waiting) {
                best_waiting = waiting;
                best = s;
            }
        }

        long long start = q[best].empty() ? time : q[best].back();
        long long fin = max(start, time) + t[i];
        q[best].push_back(fin);
        ++current_total;
        best_wait = max(best_wait, fin - time);
        best_count = max<long long>(best_count, current_total);
    }

    cout << best_wait << '\n' << best_count << '\n';
    return 0;
}