/*
Feladat: A lehető legkevesebb embert kell kiválasztani úgy, hogy mindenki legalább egy kiválasztott emberrel átfedésben legyen.
Ötlet: Ez intervallumgráf minimum domináló halmaz feladat. Mohó stratégia: mindig vesszük a legkisebb jobb végpontú még nem dominált intervallumot v, majd v szomszédai közül azt választjuk u-nak, amelyiknek a jobb vége a legnagyobb. Ezután u minden szomszédját domináljuk, és ismétlünk. A szomszéd-keresést bináris kereséssel, a dominálást szegmensfával gyorsítjuk, így az idő O(N log N).
*/
/*
Hint 1: || A „hír eljut” feltétel pontosan azt jelenti, hogy minden intervallum metszi valamelyik kiválasztottat. ||
Hint 2: || A legkorábban „lejáró” még lefedetlen intervallum jó kapaszkodó egy mohó lépéshez. ||
Hint 3: || Ha ebből annak a szomszédját választod, amelyik jobbra a legtovább nyúlik, tipikusan több jövőbeli intervallumot is lefedsz. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Interval {
    int l, r, id;
};

// Szegmensfa a még nem dominált intervallumok bal végpontjaira (dominált elem értéke INT_MAX).
struct MinTree {
    int n;
    vector<int> t;

    explicit MinTree(const vector<int>& v) : n((int)v.size()), t(4 * v.size(), INT_MAX) {
        build(1, 0, n - 1, v);
    }
    void build(int node, int lo, int hi, const vector<int>& v) {
        if (lo == hi) {
            t[node] = v[lo];
            return;
        }
        int mid = (lo + hi) / 2;
        build(2 * node, lo, mid, v);
        build(2 * node + 1, mid + 1, hi, v);
        t[node] = min(t[2 * node], t[2 * node + 1]);
    }
    void erase(int node, int lo, int hi, int pos) {
        if (lo == hi) {
            t[node] = INT_MAX;
            return;
        }
        int mid = (lo + hi) / 2;
        if (pos <= mid) erase(2 * node, lo, mid, pos);
        else erase(2 * node + 1, mid + 1, hi, pos);
        t[node] = min(t[2 * node], t[2 * node + 1]);
    }
    // Az első olyan index, amely >= from és értéke <= x; -1, ha nincs.
    int firstLE(int node, int lo, int hi, int from, int x) const {
        if (hi < from || t[node] > x) return -1;
        if (lo == hi) return lo;
        int mid = (lo + hi) / 2;
        int res = firstLE(2 * node, lo, mid, from, x);
        return res != -1 ? res : firstLE(2 * node + 1, mid + 1, hi, from, x);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Interval> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].l >> a[i].r;
        a[i].id = i + 1;
    }

    sort(a.begin(), a.end(), [](const Interval& x, const Interval& y) {
        if (x.r != y.r) return x.r < y.r;
        return x.l < y.l;
    });

    vector<int> ls(n), rs(n);
    for (int k = 0; k < n; ++k) {
        ls[k] = a[k].l;
        rs[k] = a[k].r;
    }
    // sufmin[k]: a k-tól jobbra lévő bal végpontok minimuma (k szerint nemcsökkenő).
    vector<int> sufmin(n + 1, INT_MAX);
    for (int k = n - 1; k >= 0; --k) sufmin[k] = min(sufmin[k + 1], ls[k]);
    // groupStart[k]: az a[k].r jobb végpontú csoport első indexe.
    vector<int> groupStart(n);
    for (int k = 0; k < n; ++k) groupStart[k] = (k > 0 && rs[k] == rs[k - 1]) ? groupStart[k - 1] : k;

    MinTree tree(ls);
    vector<char> dominated(n, 0);
    vector<int> ans;
    int dominatedCnt = 0;
    int start = 0;

    while (dominatedCnt < n) {
        while (dominated[start]) ++start;
        int i = start;
        Interval v = a[i];

        // Utolsó k, amelyre l_k <= v.r: ez a legjobb végpontú szomszéd (a csoportján belül a legkisebb index).
        int kLast = int(upper_bound(sufmin.begin(), sufmin.begin() + n, v.r) - sufmin.begin()) - 1;
        int best = max(i, groupStart[kLast]);

        Interval u = a[best];
        ans.push_back(u.id);

        // u-val átfedő, még nem dominált intervallumok: r >= u.l (ezek indexe >= p) és l <= u.r.
        int p = int(lower_bound(rs.begin(), rs.end(), u.l) - rs.begin());
        int from = max(start, p);
        for (int k = tree.firstLE(1, 0, n - 1, from, u.r); k != -1;
             k = tree.firstLE(1, 0, n - 1, from, u.r)) {
            tree.erase(1, 0, n - 1, k);
            dominated[k] = 1;
            ++dominatedCnt;
        }
    }

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
