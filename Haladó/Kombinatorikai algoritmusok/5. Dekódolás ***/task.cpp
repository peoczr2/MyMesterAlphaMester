/*
Megoldás lényege:
A b_i érték azt adja meg, hány nála nagyobb elem áll tőle balra. Az a_i szám rangja az a_1 … a_i részsorozatban így i − b_i, mert a balra lévő i − 1 elem közül b_i nagyobb, i − 1 − b_i pedig kisebb nála. Jobbról balra haladva a még szabad számok halmazából kell kiválasztani a rangnak megfelelő, (i − b_i)-edik legkisebb számot, majd ezt a számot a halmazból törölni. A szabad számok halmazát Fenwick-fa tartja nyilván, amelyben a k-adik elem O(log N) időben megtalálható, így az összidő O(N log N).
*/
/*
Hint 1: || Haladj jobbról balra: az i-edik helyen álló szám rangja csak i-től és b_i-től függ, a jobb oldali számokat pedig már kiosztottuk. ||
Hint 2: || Az i-edik helyen álló szám a még szabad számok halmazában pontosan a (i − b_i)-edik legkisebb lesz, ezért ezt kell kivenni a halmazból, és folytatni a bal oldali következő pozícióval. ||
Hint 3: || A szabad számok kezelésére használj Fenwick-fát: kezdetben minden szám szabad (1-es), a k-adik 1-es pozíciót bináris ugrásokkal, log N lépésben megtalálod, a kiválasztott számot pedig 0-ra állítod. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;
    Fenwick(int n = 0) { init(n); }
    void init(int n_) { n = n_; bit.assign(n + 1, 0); }
    void add(int idx, int val) { for (; idx <= n; idx += idx & -idx) bit[idx] += val; }
    int kth(int k) const {
        int idx = 0;
        int pw = 1;
        while ((pw << 1) <= n) pw <<= 1;
        for (int d = pw; d; d >>= 1) {
            int ni = idx + d;
            if (ni <= n && bit[ni] < k) {
                idx = ni;
                k -= bit[ni];
            }
        }
        return idx + 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> b(N + 1);
    for (int i = 1; i <= N; ++i) cin >> b[i];

    Fenwick ft(N);
    for (int i = 1; i <= N; ++i) ft.add(i, 1);

    vector<int> a(N + 1);
    for (int i = N; i >= 1; --i) {
        int pos = ft.kth(i - b[i]);
        a[i] = pos;
        ft.add(pos, -1);
    }

    for (int i = 1; i <= N; ++i) {
        if (i > 1) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
    return 0;
}