/*
Megoldas: ket monqueue segitsegevel vegigszamoljuk az osszes K hosszu ablakot.
Minden ablakra taroljuk a minimumot es maximumot, es azt az ablakot valasztjuk,
amelynél a max-min kulonbseg a legnagyobb. Egyenloseg eseten a kisebb kezdoindex
marad meg.
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

    deque<int> mn, mx;
    int bestStart = 1;
    int bestMin = h[1], bestMax = h[1];
    int bestDiff = -1;

    for (int i = 1; i <= n; ++i) {
        while (!mn.empty() && h[mn.back()] >= h[i]) mn.pop_back();
        mn.push_back(i);
        while (!mx.empty() && h[mx.back()] <= h[i]) mx.pop_back();
        mx.push_back(i);

        while (!mn.empty() && mn.front() <= i - k) mn.pop_front();
        while (!mx.empty() && mx.front() <= i - k) mx.pop_front();

        if (i >= k) {
            int start = i - k + 1;
            int curMin = h[mn.front()];
            int curMax = h[mx.front()];
            int diff = curMax - curMin;
            if (diff > bestDiff || (diff == bestDiff && start < bestStart)) {
                bestDiff = diff;
                bestStart = start;
                bestMin = curMin;
                bestMax = curMax;
            }
        }
    }

    cout << bestStart << '\n' << bestMin << ' ' << bestMax << '\n';
    return 0;
}
