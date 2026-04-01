/*
Hungarian megoldás: a megyeszínezést visszalépéssel, mindig a legkisebb
használható szín kipróbálásával keressük.

Hint 1: || Legfeljebb 4 szín van, ezért a színek végigpróbálhatók. ||
Hint 2: || A legszűkebb megyét érdemes előre választani. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<vector<int>> g;
vector<int> col;

bool dfs(int cnt) {
    if (cnt == n) return true;
    int v = -1, best = 100;
    for (int i = 0; i < n; ++i) if (!col[i]) {
        bool used[5] = {};
        int cntc = 0;
        for (int to : g[i]) if (col[to]) used[col[to]] = true;
        for (int c = 1; c <= k; ++c) if (!used[c]) ++cntc;
        if (cntc < best) best = cntc, v = i;
    }
    bool used[5] = {};
    for (int to : g[v]) if (col[to]) used[col[to]] = true;
    for (int c = 1; c <= k; ++c) if (!used[c]) {
        col[v] = c;
        if (dfs(cnt + 1)) return true;
        col[v] = 0;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    g.assign(n, {});
    for (int i = 0; i < n; ++i) {
        int x;
        while (cin >> x && x != 0) {
            --x;
            g[i].push_back(x);
        }
    }
    col.assign(n, 0);
    if (!dfs(0)) {
        cout << -1 << '\n';
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << col[i];
    }
    cout << '\n';
    return 0;
}