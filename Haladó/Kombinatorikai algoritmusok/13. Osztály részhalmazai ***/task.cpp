/*
   Osztály részhalmazai: az N bites számok növekvő sorrendje. A K elemű
   csoport M-edik elemét a legnagyobb bit felől haladva, binomiális
   számolással állítjuk elő.
*/
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
static ull C[41][41];

vector<int> unrankSubset(int N, int K, ull M) {
    vector<int> ans;
    for (int bit = N - 1; bit >= 0 && K > 0; --bit) {
        ull cnt = C[bit][K];
        if (M > cnt) {
            ans.push_back(bit);
            M -= cnt;
            --K;
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int n = 0; n <= 40; ++n) {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k < n; ++k) C[n][k] = C[n - 1][k - 1] + C[n - 1][k];
    }

    int N, K, Q;
    cin >> N >> K >> Q;
    while (Q--) {
        ull M;
        cin >> M;
        vector<int> ans = unrankSubset(N, K, M);
        for (int i = 0; i < (int)ans.size(); ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}