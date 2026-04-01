#include <bits/stdc++.h>
using namespace std;

/*
    Minden naphoz prefixösszeget képezünk. A legrövidebb időszakot kétmutatós
    ablakkal keressük meg: amint az összeg eléri a hajó kapacitását, a bal oldalt
    tovább tolva minimalizáljuk a hosszát. Egyenlőség esetén a korábbi kezdést
    választjuk.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, h;
    cin >> n >> h;
    vector<int> d(n + 1);
    for (int i = 1; i <= n; ++i) cin >> d[i];

    int l = 1;
    long long sum = 0;
    int bestL = -1, bestR = -1, bestLen = INT_MAX;
    for (int r = 1; r <= n; ++r) {
        sum += d[r];
        while (l <= r && sum - d[l] >= h) {
            sum -= d[l++];
        }
        if (sum >= h) {
            int len = r - l + 1;
            if (len < bestLen || (len == bestLen && l < bestL)) {
                bestLen = len;
                bestL = l;
                bestR = r;
            }
        }
    }

    if (bestL == -1) cout << -1 << '\n';
    else cout << bestL << ' ' << bestR << '\n';
    return 0;
}