/*
   Színezés: 0-1 sorozatot kell előállítani úgy, hogy két szomszédos 1-es
   ne legyen. DP-vel számoljuk a folytatások számát, majd unrankeléssel
   kiválasztjuk a K-adik sorozatot.
*/
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ull K;
    cin >> N >> K;
    int L = N + 1;
    vector<array<ull, 2>> memo(L + 1);
    vector<array<char, 2>> vis(L + 1);

    function<ull(int, int)> ways = [&](int pos, int prev) -> ull {
        if (pos == L) return 1;
        if (vis[pos][prev]) return memo[pos][prev];
        vis[pos][prev] = 1;
        ull res = ways(pos + 1, 0);
        if (!prev) res += ways(pos + 1, 1);
        return memo[pos][prev] = res;
    };

    ull total = ways(0, 0);
    cout << total << '\n';

    vector<int> ans;
    int prev = 0;
    for (int pos = 0; pos < L; ++pos) {
        if (prev == 1) {
            ans.push_back(0);
            prev = 0;
            continue;
        }
        ull cnt0 = ways(pos + 1, 0);
        if (K <= cnt0) {
            ans.push_back(0);
            prev = 0;
        } else {
            K -= cnt0;
            ans.push_back(1);
            prev = 1;
        }
    }

    for (int i = 0; i < L; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}