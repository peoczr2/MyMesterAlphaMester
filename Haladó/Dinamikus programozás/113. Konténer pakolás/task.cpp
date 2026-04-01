/*
Magyar megoldás:
A minimális toronyszám megegyezik a sorozat leghosszabb szigorúan növekvő részsorozatának hosszával.
Ennek oka, hogy a konténereket jobbról balra mozgatva minden torony egy nemnövekvő részsorozatnak felel meg,
és a legkevesebb nemnövekvő részsorozatra bontás száma pontosan az LIS hossza.

Egy lekérdezésben csak a K-adik elem változik H-ra. Két lehetőség van:
1. Az optimális LIS átmegy az új H elemen.
2. Az optimális LIS teljesen elkerüli a K-adik pozíciót.

Balról jobbra kiszámítjuk minden elemre az ott végződő LIS-hosszt, jobbról balra pedig az ott induló LIS-hosszt.
Az értékeket kompresszió után egy szegmensfában tartjuk: minden értékhez a prefixből ismert legjobb bal oldali hossz,
illetve az aktuális suffixből ismert legjobb jobb oldali hossz tartozik. Ebből egy lekérdezésre gyorsan megkapjuk
az új H-n átmenő LIS-t, és azt is, hogy mekkora a legjobb LIS, ha a K-adik pozíciót nem használjuk.
Így az összes válasz O((N+M) log(N+M)) időben kiszámítható.
*/
/*
Hint 1: || A tornyok száma nem közvetlenül mohó kérdés, hanem a sorozat LIS-hosszával azonos. ||
Hint 2: || Egy pontcsere után külön kezeld azt az esetet, amikor az új elem része az optimális LIS-nek, és azt, amikor nem. ||
Hint 3: || Prefixből a `< H`, suffixből a `> H` értékekre kell a legjobb LIS-hossz; ehhez érték szerint rendezett adatszerkezet kell. ||
*/

#include <bits/stdc++.h>
using namespace std;

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
        char c = getChar();
        if (!c) return false;
        T sign = 1, val = 0;
        while (c != '-' && (c < '0' || c > '9')) {
            c = getChar();
            if (!c) return false;
        }
        if (c == '-') {
            sign = -1;
            c = getChar();
        }
        while (c >= '0' && c <= '9') {
            val = val * 10 + (c - '0');
            c = getChar();
        }
        out = val * sign;
        return true;
    }
};

struct FenwickMax {
    int n;
    vector<int> bit;

    FenwickMax() : n(0) {}
    explicit FenwickMax(int n_) { init(n_); }

    void init(int n_) {
        n = n_;
        bit.assign(n + 1, 0);
    }

    void update(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) {
            bit[idx] = max(bit[idx], val);
        }
    }

    int query(int idx) const {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) {
            res = max(res, bit[idx]);
        }
        return res;
    }
};

struct Query {
    int k;
    int h;
    int hid;
    int id;

    bool operator<(const Query &other) const {
        return k < other.k;
    }
};

int main() {
    FastScanner fs;
    int n, m;
    if (!fs.readInt(n)) return 0;
    fs.readInt(m);

    vector<int> a(n + 1);
    vector<int> all;
    all.reserve(n + m);
    for (int i = 1; i <= n; ++i) {
        fs.readInt(a[i]);
        all.push_back(a[i]);
    }

    vector<Query> queries(m);
    for (int i = 0; i < m; ++i) {
        fs.readInt(queries[i].k);
        fs.readInt(queries[i].h);
        queries[i].id = i;
        all.push_back(queries[i].h);
    }

    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    int valueCount = (int)all.size();

    auto getId = [&](int x) {
        return (int)(lower_bound(all.begin(), all.end(), x) - all.begin()) + 1;
    };

    vector<int> aid(n + 1), rid(n + 1);
    for (int i = 1; i <= n; ++i) {
        aid[i] = getId(a[i]);
        rid[i] = valueCount - aid[i] + 1;
    }
    for (auto &query : queries) {
        query.hid = getId(query.h);
    }

    vector<int> leftLis(n + 1), rightLis(n + 1);
    FenwickMax fenwick(valueCount);
    for (int i = 1; i <= n; ++i) {
        leftLis[i] = fenwick.query(aid[i] - 1) + 1;
        fenwick.update(aid[i], leftLis[i]);
    }
    fenwick.init(valueCount);
    for (int i = n; i >= 1; --i) {
        rightLis[i] = fenwick.query(rid[i] - 1) + 1;
        fenwick.update(rid[i], rightLis[i]);
    }

    vector<int> countByValue(valueCount + 1, 0);
    for (int i = 1; i <= n; ++i) {
        ++countByValue[aid[i]];
    }

    vector<int> start(valueCount + 2, 0);
    for (int v = 1; v <= valueCount; ++v) {
        start[v + 1] = start[v] + countByValue[v];
    }

    vector<int> occPos(n), occRight(n), occIdx(n + 1);
    vector<int> fillPos = start;
    for (int i = 1; i <= n; ++i) {
        int v = aid[i];
        int at = fillPos[v]++;
        occPos[at] = i;
        occRight[at] = rightLis[i];
        occIdx[i] = at - start[v];
    }

    vector<int> suffixMax(n);
    for (int v = 1; v <= valueCount; ++v) {
        int s = start[v], e = start[v + 1];
        int best = 0;
        for (int i = e - 1; i >= s; --i) {
            best = max(best, occRight[i]);
            suffixMax[i] = best;
        }
    }

    vector<int> ptr(valueCount + 1, 0), curB(valueCount + 1, 0);
    for (int v = 1; v <= valueCount; ++v) {
        int s = start[v], e = start[v + 1];
        while (ptr[v] < e - s && occPos[s + ptr[v]] <= 1) {
            ++ptr[v];
        }
        curB[v] = (ptr[v] < e - s ? suffixMax[s + ptr[v]] : 0);
    }

    int base = 1;
    while (base < valueCount) {
        base <<= 1;
    }
    const int NEG = -1000000000;
    vector<int> segA(2 * base, 0), segB(2 * base, 0), segBest(2 * base, NEG);

    for (int v = 1; v <= valueCount; ++v) {
        segB[base + v - 1] = curB[v];
    }

    auto pull = [&](int p) {
        segA[p] = max(segA[p << 1], segA[p << 1 | 1]);
        segB[p] = max(segB[p << 1], segB[p << 1 | 1]);
        int cross = (segA[p << 1] > 0 && segB[p << 1 | 1] > 0 ? segA[p << 1] + segB[p << 1 | 1] : NEG);
        segBest[p] = max({segBest[p << 1], segBest[p << 1 | 1], cross});
    };

    for (int i = base - 1; i >= 1; --i) {
        pull(i);
    }

    auto updateA = [&](int v, int val) {
        int p = base + v - 1;
        if (segA[p] >= val) return;
        segA[p] = val;
        for (p >>= 1; p; p >>= 1) {
            pull(p);
        }
    };

    auto updateB = [&](int v, int val) {
        int p = base + v - 1;
        if (segB[p] == val) return;
        segB[p] = val;
        for (p >>= 1; p; p >>= 1) {
            pull(p);
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

    sort(queries.begin(), queries.end());
    vector<int> ans(m);
    int qi = 0;
    for (int k = 1; k <= n; ++k) {
        while (qi < m && queries[qi].k == k) {
            int hid = queries[qi].hid;
            int left = rangeMax(segA, 1, hid - 1);
            int right = rangeMax(segB, hid + 1, valueCount);
            int through = left + 1 + right;
            int avoid = max({segA[1], segB[1], segBest[1]});
            ans[queries[qi].id] = max(through, avoid);
            ++qi;
        }
        if (k == n) break;

        updateA(aid[k], leftLis[k]);

        int pos = k + 1;
        int v = aid[pos];
        if (occIdx[pos] == ptr[v]) {
            ++ptr[v];
            int s = start[v], e = start[v + 1];
            int newB = (ptr[v] < e - s ? suffixMax[s + ptr[v]] : 0);
            updateB(v, newB);
        }
    }

    string out;
    out.reserve((size_t)m * 4);
    for (int i = 0; i < m; ++i) {
        out += to_string(ans[i]);
        out += '\n';
    }
    fwrite(out.c_str(), 1, out.size(), stdout);
    return 0;
}