#include <bits/stdc++.h>
using namespace std;

/*
    Aki a legtöbb emberrel találkozott, az a legtöbb más intervallummal metsző
    intervallummal rendelkezik. Két végpont sort és egy sweepet használunk,
    hogy megszámoljuk az átfedéseket.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int,int>> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i].first >> a[i].second;

    vector<int> starts, ends;
    for (int i = 1; i <= n; ++i) {
        starts.push_back(a[i].first);
        ends.push_back(a[i].second);
    }
    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());

    int bestId = 1, bestCnt = -1;
    for (int i = 1; i <= n; ++i) {
        int x = a[i].first, y = a[i].second;
        int left = upper_bound(starts.begin(), starts.end(), y) - starts.begin();
        int right = lower_bound(ends.begin(), ends.end(), x) - ends.begin();
        int cnt = left - right - 1;
        if (cnt > bestCnt) {
            bestCnt = cnt;
            bestId = i;
        }
    }

    cout << bestId << '\n' << bestCnt << '\n';
    return 0;
}