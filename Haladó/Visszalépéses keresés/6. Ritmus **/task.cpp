/*
Hungarian megoldás: minden verssort dinamikus programozással bontunk fel a megadott
ritmusminták egymás utáni illesztésével.

Hint 1: || A sorokat kis darabokra kell bontani, ahol minden darab valamelyik ismert minta. ||
Hint 2: || Mivel a minták rövidek, a lehetséges illesztéseket egyszerűen végig lehet próbálni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> minta(n + 1);
    for (int i = 1; i <= n; ++i) cin >> minta[i];
    int m;
    cin >> m;
    while (m--) {
        string sor;
        cin >> sor;
        int L = sor.size();
        vector<int> dp(L + 1, -1), prv(L + 1, -1);
        vector<int> pat(L + 1, -1);
        dp[0] = 0;
        for (int i = 0; i < L; ++i) if (dp[i] != -1) {
            for (int j = 1; j <= n; ++j) {
                int len = minta[j].size();
                if (i + len <= L && sor.compare(i, len, minta[j]) == 0) {
                    if (dp[i + len] == -1) {
                        dp[i + len] = dp[i] + 1;
                        prv[i + len] = i;
                        pat[i + len] = j;
                    }
                }
            }
        }
        if (dp[L] == -1) {
            cout << -1 << '\n';
            continue;
        }
        vector<int> sorozat;
        for (int i = L; i > 0; i = prv[i]) sorozat.push_back(pat[i]);
        reverse(sorozat.begin(), sorozat.end());
        cout << sorozat.size();
        for (int x : sorozat) cout << ' ' << x;
        cout << '\n';
    }
    return 0;
}