/*
Megoldás lényege:
Az épületek unióját kell feldolgozni, majd ebből komponenseket, lyukakat vagy peremeket számolni. A klasszikus sweep és interval-kezelés adja a megoldás magját.
*/
#include <bits/stdc++.h>
using namespace std;

struct Event {
    long long x;
    long long y1, y2;
    int delta;
    bool operator<(const Event& other) const {
        return x < other.x;
    }
};

struct Node {
    int cover = 0;
    long long len = 0;
    int segs = 0;
    bool leftCov = false;
    bool rightCov = false;
};

struct SegTree {
    int n;
    vector<Node> st;
    vector<long long> ys;

    SegTree(const vector<long long>& coords) : ys(coords) {
        n = (int)ys.size() - 1;
        st.resize(4 * max(1, n));
    }

    void pull(int p, int l, int r) {
        if (st[p].cover > 0) {
            st[p].len = ys[r + 1] - ys[l];
            st[p].segs = 1;
            st[p].leftCov = st[p].rightCov = true;
            return;
        }

        if (l == r) {
            st[p].len = 0;
            st[p].segs = 0;
            st[p].leftCov = st[p].rightCov = false;
            return;
        }

        int lc = p << 1, rc = lc | 1;
        st[p].len = st[lc].len + st[rc].len;
        st[p].segs = st[lc].segs + st[rc].segs - (st[lc].rightCov && st[rc].leftCov ? 1 : 0);
        st[p].leftCov = st[lc].leftCov;
        st[p].rightCov = st[rc].rightCov;
    }

    void add(int p, int l, int r, int ql, int qr, int delta) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            st[p].cover += delta;
            pull(p, l, r);
            return;
        }
        int m = (l + r) >> 1;
        add(p << 1, l, m, ql, qr, delta);
        add(p << 1 | 1, m + 1, r, ql, qr, delta);
        pull(p, l, r);
    }

    void add(long long y1, long long y2, int delta) {
        if (n <= 0 || y1 >= y2) return;
        int l = (int)(lower_bound(ys.begin(), ys.end(), y1) - ys.begin());
        int r = (int)(lower_bound(ys.begin(), ys.end(), y2) - ys.begin()) - 1;
        if (l <= r) add(1, 0, n - 1, l, r, delta);
    }

    long long coveredLen() const { return n > 0 ? st[1].len : 0; }
    int segmentCount() const { return n > 0 ? st[1].segs : 0; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<Event> ev;
    ev.reserve(2 * N);
    vector<long long> ys;
    ys.reserve(2 * N);

    for (int i = 0; i < N; ++i) {
        long long x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        ev.push_back({x1, y1, y2, +1});
        ev.push_back({x2, y1, y2, -1});
        ys.push_back(y1);
        ys.push_back(y2);
    }

    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    sort(ev.begin(), ev.end());

    SegTree st(ys);

    long long perimeter = 0;
    long long prevX = ev.empty() ? 0 : ev[0].x;
    int i = 0;

    while (i < (int)ev.size()) {
        long long x = ev[i].x;
        long long dx = x - prevX;
        if (dx > 0) {
            perimeter += 2LL * st.segmentCount() * dx;
            prevX = x;
        }

        long long before = st.coveredLen();
        while (i < (int)ev.size() && ev[i].x == x) {
            st.add(ev[i].y1, ev[i].y2, ev[i].delta);
            ++i;
        }
        long long after = st.coveredLen();
        perimeter += llabs(after - before);
    }

    cout << perimeter << '\n';
    return 0;
}