/*
Megoldás lényege: Az i-edik fa akkor jó, ha a tőle legfeljebb K távolságra lévő fák egyike sem magasabb nála. Ehhez minden i-re kiszámoljuk a bal oldali [i-K, i-1] és a jobb oldali [i+1, i+K] intervallum maximumát egy-egy monoton (csúszóablakos) deque-val. Az első olyan i a válasz, amelynél a saját magasság mindkét maximumnál nem kisebb; ha nincs ilyen, -1. Az egyenlő magasságú fák nem számítanak magasabbnak. Az időigény O(N).
*/
/*
Hint 1: || A kérdés valójában egy mozgó ablakos maximumvizsgálat. ||
Hint 2: || Egy fa akkor megfelelő, ha a tőle legfeljebb K távolságra lévő összes fa alacsonyabb nála. ||
Hint 3: || Ezt két irányú csúszóablakos maximumokkal gyorsan meg lehet nézni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> h(n + 1);
    for (int i = 1; i <= n; ++i) cin >> h[i];

    vector<int> leftMax(n + 1, 0), rightMax(n + 1, 0);
    deque<int> dq;

    for (int i = 1; i <= n; ++i) {
        int idx = i - 1;
        if (idx >= 1) {
            while (!dq.empty() && h[dq.back()] <= h[idx]) dq.pop_back();
            dq.push_back(idx);
        }
        while (!dq.empty() && dq.front() < i - k) dq.pop_front();
        leftMax[i] = dq.empty() ? 0 : h[dq.front()];
    }

    dq.clear();
    for (int i = n; i >= 1; --i) {
        int idx = i + 1;
        if (idx <= n) {
            while (!dq.empty() && h[dq.back()] <= h[idx]) dq.pop_back();
            dq.push_back(idx);
        }
        while (!dq.empty() && dq.front() > i + k) dq.pop_front();
        rightMax[i] = dq.empty() ? 0 : h[dq.front()];
    }

    for (int i = 1; i <= n; ++i) {
        if (h[i] >= leftMax[i] && h[i] >= rightMax[i]) {
            cout << i << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';
    return 0;
}