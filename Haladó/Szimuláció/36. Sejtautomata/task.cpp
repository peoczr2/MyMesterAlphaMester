/*
A sejtautomata minden lépésben az előző tábla alapján frissül, ezért a következő állapotot másolatból kell számolni. A cellák sorsa a szomszédok számától függ, nem az éppen frissített soroktól.
*/
/*
Hint 1: || A szabály minden cellára ugyanaz, ezért a következő állapotot az előző tábla másolatából számold. ||
Hint 2: || A szomszédok száma alapján dől el, hogy a cella élve marad, születik vagy eltűnik. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    string a;
    cin >> a;
    int m;
    cin >> m;
    vector<int> rule(32, 0);
    for (int i = 0; i < m; ++i) {
        string p;
        cin >> p;
        int mask = 0;
        for (char c : p) mask = (mask << 1) | (c == 'Z');
        rule[mask] = 1;
    }

    for (int step = 0; step < k; ++step) {
        string b(n, 'F');
        for (int i = 2; i < n - 2; ++i) {
            int mask = 0;
            for (int j = i - 2; j <= i + 2; ++j) mask = (mask << 1) | (a[j] == 'Z');
            if (rule[mask]) b[i] = 'Z';
        }
        a.swap(b);
    }

    cout << count(a.begin(), a.end(), 'Z') << '\n';
    return 0;
}