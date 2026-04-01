#include <bits/stdc++.h>
using namespace std;

/*
    A családfa egy gyökeres fa, ahol minden taghoz ismert az apja. A legnagyobb
    távolságú leszármazottak azok, akiknek a mélysége maximális.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> depth(n + 1, 0);
    int bestDepth = 0;
    vector<int> ans;
    for (int i = 2; i <= n; ++i) {
        int p;
        cin >> p;
        depth[i] = depth[p] + 1;
        if (depth[i] > bestDepth) {
            bestDepth = depth[i];
            ans.clear();
            ans.push_back(i);
        } else if (depth[i] == bestDepth) {
            ans.push_back(i);
        }
    }

    if (n == 1) {
        cout << 1 << ' ' << 0 << '\n' << 1 << '\n';
        return 0;
    }

    cout << ans.size() << ' ' << bestDepth << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}