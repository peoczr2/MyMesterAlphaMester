/*
Megoldás lényege:
A feltétel: 2*max(a[L..R]) >= sum(a[L..R]).
Az optimumot oszd-meg-és-uralkodj módszerrel keressük:
1) megoldjuk bal és jobb felet rekurzívan,
2) feldolgozzuk a középet átlépő intervallumokat.

Középen átlépő [L..R] (L<=mid<R) esetén két eset van:
- bal oldali maximum >= jobb oldali maximum,
- jobb oldali maximum > bal oldali maximum.

Mindkét esetben az egyenlőtlenség egy "sum <= küszöb" alakú lekérdezéssé alakul, amit Fenwick-fával
kezelünk (prefix maximum / prefix minimum index lekérdezés), így a középső rész O(szegmens*log szegmens).
Teljesen: O(N log^2 N).
*/
// Hint 1: || A hosszra nincs monotonitás, ezért sima bináris keresés nem jó. ||
// Hint 2: || Oszd ketté a tömböt, és külön kezeld a középen átnyúló intervallumokat. ||
// Hint 3: || A középső részben a feltétel "sum <= küszöb" lekérdezésekre redukálható Fenwick-fával. ||

#include <bits/stdc++.h>
using namespace std;

struct Best {
    int len = 0;
    int L = 1;
    int R = 1;
};

static inline void upd(Best &best, int L, int R) {
    if (L > R) return;
    int len = R - L + 1;
    if (len > best.len || (len == best.len && L < best.L)) {
        best.len = len;
        best.L = L;
        best.R = R;
    }
}

struct FenwickMax {
    int n;
    vector<int> bit;
    explicit FenwickMax(int n = 0) { init(n); }
    void init(int n_) { n = n_; bit.assign(n + 1, -1); }
    void add(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] = max(bit[idx], val);
    }
    int pref(int idx) const {
        int res = -1;
        for (; idx > 0; idx -= idx & -idx) res = max(res, bit[idx]);
        return res;
    }
};

struct FenwickMin {
    int n;
    vector<int> bit;
    static constexpr int INF = 1e9;
    explicit FenwickMin(int n = 0) { init(n); }
    void init(int n_) { n = n_; bit.assign(n + 1, INF); }
    void add(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] = min(bit[idx], val);
    }
    int pref(int idx) const {
        int res = INF;
        for (; idx > 0; idx -= idx & -idx) res = min(res, bit[idx]);
        return res;
    }
};

int N;
vector<long long> a, pref;

void solve(int l, int r, Best &best) {
    if (l == r) {
        if (a[l] >= 0) upd(best, l, l);
        return;
    }

    int m = (l + r) >> 1;
    solve(l, m, best);
    solve(m + 1, r, best);

    vector<int> Lidx;
    vector<long long> Lmx, Lsum;
    Lidx.reserve(m - l + 1);
    Lmx.reserve(m - l + 1);
    Lsum.reserve(m - l + 1);

    long long curMx = LLONG_MIN;
    for (int i = m; i >= l; --i) {
        curMx = max(curMx, a[i]);
        Lidx.push_back(i);
        Lmx.push_back(curMx);
        Lsum.push_back(pref[m] - pref[i - 1]);
    }

    vector<int> Ridx;
    vector<long long> Rmx, Rsum;
    Ridx.reserve(r - m);
    Rmx.reserve(r - m);
    Rsum.reserve(r - m);

    curMx = LLONG_MIN;
    for (int j = m + 1; j <= r; ++j) {
        curMx = max(curMx, a[j]);
        Ridx.push_back(j);
        Rmx.push_back(curMx);
        Rsum.push_back(pref[j] - pref[m]);
    }

    // A eset: Lmx >= Rmx
    {
        vector<long long> vals = Rsum;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        FenwickMax fw((int)vals.size());
        int p = 0;
        for (int i = 0; i < (int)Lidx.size(); ++i) {
            while (p < (int)Ridx.size() && Rmx[p] <= Lmx[i]) {
                int pos = (int)(lower_bound(vals.begin(), vals.end(), Rsum[p]) - vals.begin()) + 1;
                fw.add(pos, Ridx[p]);
                ++p;
            }
            long long thr = 2LL * Lmx[i] - Lsum[i];
            int up = (int)(upper_bound(vals.begin(), vals.end(), thr) - vals.begin());
            if (up <= 0) continue;
            int rr = fw.pref(up);
            if (rr != -1) upd(best, Lidx[i], rr);
        }
    }

    // B eset: Rmx > Lmx
    {
        vector<long long> vals = Lsum;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        FenwickMin fw((int)vals.size());
        int p = 0;
        for (int j = 0; j < (int)Ridx.size(); ++j) {
            while (p < (int)Lidx.size() && Lmx[p] < Rmx[j]) {
                int pos = (int)(lower_bound(vals.begin(), vals.end(), Lsum[p]) - vals.begin()) + 1;
                fw.add(pos, Lidx[p]);
                ++p;
            }
            long long thr = 2LL * Rmx[j] - Rsum[j];
            int up = (int)(upper_bound(vals.begin(), vals.end(), thr) - vals.begin());
            if (up <= 0) continue;
            int ll = fw.pref(up);
            if (ll != FenwickMin::INF) upd(best, ll, Ridx[j]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    a.assign(N + 1, 0);
    for (int i = 1; i <= N; ++i) cin >> a[i];

    pref.assign(N + 1, 0);
    for (int i = 1; i <= N; ++i) pref[i] = pref[i - 1] + a[i];

    Best best;
    best.len = 0;
    best.L = 1;
    best.R = 1;

    solve(1, N, best);
    cout << best.L << ' ' << best.R << '\n';
    return 0;
}
