/*
Hungarian megoldás: a Lights Out feladatot az első sor összes lehetséges
kapcsolási mintájának kipróbálásával oldjuk meg.

Hint 1: || Ha az első sor kapcsolásai adottak, a többi sor már kényszerített. ||
Hint 2: || A legkevesebb kapcsolású megoldást kell kiválasztani. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n;

pair<bool, vector<pair<int,int>>> solveOne(vector<vector<int>> a, int mask) {
    vector<pair<int,int>> presses;
    auto toggle = [&](int r, int c) {
        if (r < 0 || r >= n || c < 0 || c >= n) return;
        a[r][c] ^= 1;
    };
    for (int c = 0; c < n; ++c) if (mask & (1 << c)) {
        presses.push_back({1, c + 1});
        toggle(0, c);
        toggle(1, c);
        toggle(0, c - 1);
        toggle(0, c + 1);
    }
    for (int r = 1; r < n; ++r) {
        for (int c = 0; c < n; ++c) if (a[r - 1][c]) {
            presses.push_back({r + 1, c + 1});
            toggle(r - 1, c);
            toggle(r, c);
            toggle(r + 1, c);
            toggle(r, c - 1);
            toggle(r, c + 1);
        }
    }
    for (int c = 0; c < n; ++c) if (a[n - 1][c]) return {false, {}};
    return {true, presses};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<vector<int>> a(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            for (int j = 0; j < n; ++j) a[i][j] = s[j] - '0';
        }
        int best = INT_MAX;
        vector<pair<int,int>> bestPress;
        for (int mask = 0; mask < (1 << n); ++mask) {
            auto [ok, cur] = solveOne(a, mask);
            if (ok && (int)cur.size() < best) {
                best = cur.size();
                bestPress = move(cur);
            }
        }
        if (best == INT_MAX) {
            cout << -1 << '\n';
            continue;
        }
        cout << best;
        for (auto [r, c] : bestPress) cout << ' ' << r << ' ' << c;
        cout << '\n';
    }
    return 0;
}