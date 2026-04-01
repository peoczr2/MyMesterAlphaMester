#include <bits/stdc++.h>
using namespace std;

/*
  A minimum toronyszám megegyezik a sorozat LIS-hosszával.
  Egy lekérdezésben csak az K-adik elem változik H-ra, ezért két esetet nézünk:
  - a toronyhasználat tartalmazza az új elemet,
  - vagy teljesen elkerüli K-t.

  Legyenek a prefixben (K előtt) és suffixben (K után) a legjobb, adott értékre végződő/
  induló LIS-hosszak eltárolva. Azokat értékkompresszió után egy szegmensfában tartjuk,
  ahol minden értékhez eltesszük a prefix-beli legjobb hosszt (A), a suffix-beli legjobb
  hosszt (B), és ezekből a fa csomópontjában a legjobb A[x] + B[y] párt (x < y).

  Így egy lekérdezésre:
    - az új H-val átmenő LIS hossza: max prefix < H + 1 + max suffix > H,
    - az H-t nem használó megoldás: a fa gyökerének A/B/best értékeiből.

  A K-t balról jobbra söpörve csak egy prefix- és egy suffix-érték változik lépésenként,
  ezért minden frissítés O(log V), a lekérdezés pedig O(log V).
*/

struct FastScanner {
    static const int SZ = 1 << 20;
    int idx = 0, size = 0;
    char buf[SZ];

    inline char getChar() {
        if (idx >= size) {
            size = (int)fread(buf, 1, SZ, stdin);
            idx = 0;
            if (size == 0) return 0;
        }
        return buf[idx++];
    }

    template <class T>
    bool readInt(T &out) {
        char c;
        T sign = 1, val = 0;
        c = getChar();
        if (!c) return false;
        while (c != '-' && (c < '0' || c > '9')) {
            c = getChar();
            if (!c) return false;
        }
        if (c == '-') {
            sign = -1;
            c = getChar();
        }
        for (; c >= '0' && c <= '9'; c = getChar()) val = val * 10 + (c - '0');
        out = val * sign;
        return true;
    }
};

struct FenwickMax {
    int n;
    vector<int> bit;
    FenwickMax() : n(0) {}
    FenwickMax(int n_) { init(n_); }
    void init(int n_) { n = n_; bit.assign(n + 1, 0); }
    void update(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] = max(bit[idx], val);
    }
    int query(int idx) const {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) res = max(res, bit[idx]);
        return res;
    }
};

struct Query {
    int k;
    int h;
    int hid;
    int id;
    bool operator<(const Query &other) const { return k < other.k; }
};

int main() {
    FastScanner fs;
    int N, M;
    if (!fs.readInt(N)) return 0;
    fs.readInt(M);

    vector<int> a(N + 1);
    vector<int> all;
    all.reserve(N + M);
    for (int i = 1; i <= N; ++i) {
        fs.readInt(a[i]);
        all.push_back(a[i]);
    }

    vector<Query> qs(M);
    for (int i = 0; i < M; ++i) {
        fs.readInt(qs[i].k);
        fs.readInt(qs[i].h);
        qs[i].id = i;
        all.push_back(qs[i].h);
    }

    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    int V = (int)all.size();

    auto getId = [&](int x) {
        return (int)(lower_bound(all.begin(), all.end(), x) - all.begin()) + 1;
    };

    vector<int> aid(N + 1), rid(N + 1);
    for (int i = 1; i <= N; ++i) {
        aid[i] = getId(a[i]);
        rid[i] = V - aid[i] + 1;
    }
    for (auto &q : qs) q.hid = getId(q.h);

    vector<int> L(N + 1), R(N + 1);
    FenwickMax fw(V);
    for (int i = 1; i <= N; ++i) {
        L[i] = fw.query(aid[i] - 1) + 1;
        fw.update(aid[i], L[i]);
    }
    fw.init(V);
    for (int i = N; i >= 1; --i) {
        R[i] = fw.query(rid[i] - 1) + 1;
        fw.update(rid[i], R[i]);
    }

    // Occurrence storage grouped by value, in one flat array.
    vector<int> cnt(V + 1, 0);
    for (int i = 1; i <= N; ++i) ++cnt[aid[i]];
    vector<int> start(V + 2, 0);
    for (int v = 1; v <= V; ++v) start[v + 1] = start[v] + cnt[v];

    vector<int> occPos(N), occR(N), occIdx(N + 1);
    vector<int> fillPos = start;
    for (int i = 1; i <= N; ++i) {
        int v = aid[i];
        int at = fillPos[v]++;
        occPos[at] = i;
        occR[at] = R[i];
        occIdx[i] = at - start[v];
    }

    vector<int> sufMax(N);
    for (int v = 1; v <= V; ++v) {
        int s = start[v], e = start[v + 1];
        int best = 0;
        for (int i = e - 1; i >= s; --i) {
            best = max(best, occR[i]);
            sufMax[i] = best;
        }
    }

    vector<int> ptr(V + 1, 0);
    vector<int> curB(V + 1, 0);
    for (int v = 1; v <= V; ++v) {
        int s = start[v], e = start[v + 1];
        while (ptr[v] < e - s && occPos[s + ptr[v]] <= 1) ++ptr[v];
        curB[v] = (ptr[v] < e - s ? sufMax[s + ptr[v]] : 0);
    }

    int base = 1;
    while (base < V) base <<= 1;
    const int NEG = -1000000000;
    vector<int> segA(2 * base, 0), segB(2 * base, 0), segBest(2 * base, NEG);

    for (int v = 1; v <= V; ++v) {
        segA[base + v - 1] = 0;
        segB[base + v - 1] = curB[v];
    }
    for (int i = base - 1; i >= 1; --i) {
        segA[i] = max(segA[i << 1], segA[i << 1 | 1]);
        segB[i] = max(segB[i << 1], segB[i << 1 | 1]);
        int cross = (segA[i << 1] > 0 && segB[i << 1 | 1] > 0) ? segA[i << 1] + segB[i << 1 | 1] : NEG;
        segBest[i] = max({segBest[i << 1], segBest[i << 1 | 1], cross});
    }

    auto pull = [&](int p) {
        segA[p] = max(segA[p << 1], segA[p << 1 | 1]);
        segB[p] = max(segB[p << 1], segB[p << 1 | 1]);
        int cross = (segA[p << 1] > 0 && segB[p << 1 | 1] > 0) ? segA[p << 1] + segB[p << 1 | 1] : NEG;
        segBest[p] = max({segBest[p << 1], segBest[p << 1 | 1], cross});
    };

    auto updateA = [&](int v, int val) {
        int p = base + v - 1;
        if (segA[p] < val) {
            segA[p] = val;
            for (p >>= 1; p; p >>= 1) pull(p);
        }
    };

    auto updateB = [&](int v, int val) {
        int p = base + v - 1;
        if (segB[p] != val) {
            segB[p] = val;
            for (p >>= 1; p; p >>= 1) pull(p);
        }
    };

    auto rangeMax = [&](const vector<int> &seg, int l, int r) {
        if (l > r) return 0;
        l = base + l - 1;
        r = base + r - 1;
        int res = 0;
        while (l <= r) {
            if (l & 1) res = max(res, seg[l++]);
            if (!(r & 1)) res = max(res, seg[r--]);
            l >>= 1;
            r >>= 1;
        }
        return res;
    };

    sort(qs.begin(), qs.end());
    vector<int> ans(M);
    int qi = 0;
    for (int K = 1; K <= N; ++K) {
        while (qi < M && qs[qi].k == K) {
            int hid = qs[qi].hid;
            int left = rangeMax(segA, 1, hid - 1);
            int right = rangeMax(segB, hid + 1, V);
            int through = left + 1 + right;
            int avoid = max({segA[1], segB[1], segBest[1]});
            ans[qs[qi].id] = max(through, avoid);
            ++qi;
        }
        if (K == N) break;

        // Position K enters the prefix.
        updateA(aid[K], L[K]);

        // Position K+1 leaves the suffix.
        int p = K + 1;
        int v = aid[p];
        if (occIdx[p] == ptr[v]) {
            ++ptr[v];
            int s = start[v], e = start[v + 1];
            int newB = (ptr[v] < e - s ? sufMax[s + ptr[v]] : 0);
            updateB(v, newB);
        }
    }

    string out;
    out.reserve((size_t)M * 4);
    for (int i = 0; i < M; ++i) {
        out += to_string(ans[i]);
        out += '\n';
    }
    fwrite(out.c_str(), 1, out.size(), stdout);
    return 0;
}