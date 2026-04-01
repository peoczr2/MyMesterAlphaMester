#include <bits/stdc++.h>
using namespace std;

/*
    A banda egy gyökeres fa. Olyan legnagyobb részhalmazt kell választani, ahol
    nincs egymásban szülő és gyerek. Ez az egyszerű fa-független halmaz DP.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> gyerek(n + 1);
    for (int i = 2; i <= n; ++i) {
        int p;
        cin >> p;
        gyerek[p].push_back(i);
    }

    vector<int> dp0(n + 1), dp1(n + 1);
    vector<int> order;
    order.reserve(n);
    for (int i = n; i >= 1; --i) order.push_back(i);
    for (int v : order) {
        dp1[v] = 1;
        for (int to : gyerek[v]) {
            dp1[v] += dp0[to];
            dp0[v] += max(dp0[to], dp1[to]);
        }
    }

    vector<int> valasz;
    function<void(int, bool)> rek = [&](int v, bool chosenParent) {
        bool take = false;
        if (!chosenParent && dp1[v] > dp0[v]) take = true;
        if (!chosenParent && dp1[v] == dp0[v]) take = true;
        if (take) valasz.push_back(v);
        for (int to : gyerek[v]) rek(to, take);
    };
    rek(1, false);

    cout << valasz.size() << '\n';
    sort(valasz.begin(), valasz.end());
    for (int i = 0; i < (int)valasz.size(); ++i) {
        if (i) cout << ' ';
        cout << valasz[i];
    }
    cout << '\n';
    return 0;
}