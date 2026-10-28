/*
Megoldás lényege:
Egy [l..r] időszak akkor jó, ha a benne jelentkező minden személy legalább K-szor szerepel benne. A jó időszakok nem alkotnak egyszerű kétmutatós családot, ezért l-et jobbról balra mozgatva dolgozunk. Ha egy személy első előfordulása l, akkor az [l, a K-adik előfordulása előtti nap] szakaszon az r végpont rossz, mert ott a személy 1 és K-1 közötti számszor szerepel.
Ezeket a tiltott intervallumokat szegmensfában tartjuk nyilván (range-add), és minden l-hez megkeressük a legnagyobb olyan r >= l napot, amelyet semmilyen tiltott intervallum nem fed. Az időigény O(M log M).
*/
/*
Hint 1: || Rögzítsd a kezdőnapot (l). Egy személy első előfordulásától a K-adik előfordulása előtti napig minden végpont rossz, mert addig a személy kevesebbszer szerepel K-nál. ||
Hint 2: || Ha l eggyel csökken, csak egyetlen személy tiltott intervalluma változik: a régi intervallumot ki kell venni, és az új első előfordulásból kiindulót fel kell venni. Egy nap tiltott, ha legalább egy intervallum fedi. ||
Hint 3: || Szegmensfában range-add művelettel tartsd nyilván, hogy hány tiltott intervallum fedi az egyes napokat. Minden l-re keresd meg a legnagyobb olyan r >= l napot, amelynek fedettsége nulla. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Szegmensfa: intervallum-összeadás, és a legjobboldalibb nulla érték keresése.
// mn[v]: a v részfa minimuma, a v csúcson lévő lazy értékkel együtt (az ősökét nem tartalmazza).
struct SegTree {
    int n;
    vector<int> mn, lz;

    explicit SegTree(int size) : n(size), mn(4 * size + 4, 0), lz(4 * size + 4, 0) {}

    void add(int v, int l, int r, int ql, int qr, int delta) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            mn[v] += delta;
            lz[v] += delta;
            return;
        }
        int mid = (l + r) / 2;
        add(2 * v, l, mid, ql, qr, delta);
        add(2 * v + 1, mid + 1, r, ql, qr, delta);
        mn[v] = min(mn[2 * v], mn[2 * v + 1]) + lz[v];
    }

    // legnagyobb olyan index >= ql, ahol az érték 0; acc: a v ősein halmozott lazy összeg
    int rightmostZero(int v, int l, int r, int ql, int acc) {
        if (r < ql || mn[v] + acc > 0) return -1;
        if (l == r) return l;
        int mid = (l + r) / 2;
        int nacc = acc + lz[v];
        int res = rightmostZero(2 * v + 1, mid + 1, r, ql, nacc);
        if (res != -1) return res;
        return rightmostZero(2 * v, l, mid, ql, nacc);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n, k;
    cin >> m >> n >> k;
    vector<int> a(m + 1);
    for (int i = 1; i <= m; i++) cin >> a[i];

    // occ[x]: x jelentkezési napjai növekvő sorrendben; idx[i]: az i. nap helye x listájában
    vector<vector<int>> occ(n + 1);
    vector<int> idx(m + 1);
    for (int i = 1; i <= m; i++) {
        idx[i] = (int)occ[a[i]].size();
        occ[a[i]].push_back(i);
    }

    SegTree st(m);
    vector<int> curL(n + 1, 0), curR(n + 1, 0);  // személyenként az aktuálisan felvett tiltott intervallum
    int ans = 0;
    for (int l = m; l >= 1; l--) {
        int x = a[l];
        if (curL[x] != 0) st.add(1, 1, m, curL[x], curR[x], -1);

        int j = idx[l];
        int last = (j + k - 1 < (int)occ[x].size()) ? occ[x][j + k - 1] - 1 : m;
        curL[x] = l;
        curR[x] = last;
        st.add(1, 1, m, l, last, +1);

        int r = st.rightmostZero(1, 1, m, l, 0);
        if (r != -1) ans = max(ans, r - l + 1);
    }

    cout << ans << "\n";
    return 0;
}
