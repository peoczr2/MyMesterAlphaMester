/*
   Halmazok sorrendje: a K elemű részhalmazok rendezése a legnagyobb eltérő
   elem alapján pontosan a colex-szerű sorrend. A M-edik halmazt a legnagyobb
   elemről lefelé haladva, binomiális számolással állítjuk elő.
*/
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
static ull C[31][31];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int n = 0; n <= 30; ++n) {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k < n; ++k) C[n][k] = C[n - 1][k - 1] + C[n - 1][k];
    }

    int N, K;
    ull M;
    cin >> N >> K >> M;

    vector<int> ans;
    for (int x = N; x >= 1 && K > 0; --x) {
        ull cnt = C[x - 1][K - 1];
        if (M <= cnt) {
            ans.push_back(x);
            --K;
        } else {
            M -= cnt;
        }
    }

    reverse(ans.begin(), ans.end());
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}