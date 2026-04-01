/*
 * Minden mókus a saját ugráshosszának többszörösére lép. Megszámoljuk a
 * látogatásokat, majd kiírjuk a sosem látogatott és a legtöbbször látogatott
 * kövek sorszámát.
 
Hint 1: || Egy d ugrású mókus pontosan a d többszöröseire lép, tehát a feladat valójában többszörösök számlálása. ||
Hint 2: || Minden ugráshosszra menj végig a `d, 2d, 3d, ...` köveken, növeld a számlálót, majd a végén keresd a 0 darabos és a maximális darabos köveket. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> jumps(m);
    for (int i = 0; i < m; ++i) cin >> jumps[i];
    vector<int> cnt(n + 1);
    for (int d : jumps) {
        for (int x = d; x <= n; x += d) ++cnt[x];
    }
    int best = 0;
    for (int x = 1; x <= n; ++x) best = max(best, cnt[x]);
    bool first = true;
    for (int x = 1; x <= n; ++x) if (cnt[x] == 0) {
        if (!first) cout << ' ';
        first = false;
        cout << x;
    }
    if (first) cout << 0;
    cout << '\n';
    first = true;
    for (int x = 1; x <= n; ++x) if (cnt[x] == best) {
        if (!first) cout << ' ';
        first = false;
        cout << x;
    }
    cout << '\n';
    return 0;
}
