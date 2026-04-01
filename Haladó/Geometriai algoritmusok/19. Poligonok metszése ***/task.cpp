/*
Megoldás lényege:
Két sokszög metszetét kell kiszámítani, majd ennek a területét vagy peremét meghatározni. A megoldás a poligon-klippelés klasszikus lépéseire épül.
*/
#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
};

static int orient(const Pt& a, const Pt& b, const Pt& c) {
    __int128 v = (__int128)(b.x - a.x) * (c.y - a.y) - (__int128)(b.y - a.y) * (c.x - a.x);
    if (v < 0) return -1;
    if (v > 0) return 1;
    return 0;
}

static bool onSegment(const Pt& a, const Pt& b, const Pt& p) {
    if (orient(a, b, p) != 0) return false;
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

static bool segIntersect(const Pt& a, const Pt& b, const Pt& c, const Pt& d) {
    int o1 = orient(a, b, c);
    int o2 = orient(a, b, d);
    int o3 = orient(c, d, a);
    int o4 = orient(c, d, b);
    if (o1 == 0 && o2 == 0 && o3 == 0 && o4 == 0) {
        return max(min(a.x, b.x), min(c.x, d.x)) <= min(max(a.x, b.x), max(c.x, d.x)) &&
               max(min(a.y, b.y), min(c.y, d.y)) <= min(max(a.y, b.y), max(c.y, d.y));
    }
    return 1LL * o1 * o2 <= 0 && 1LL * o3 * o4 <= 0;
}

struct Chain {
    vector<int> verts;
    vector<int> edges;
};

static pair<Chain, Chain> splitChains(const vector<Pt>& poly) {
    int n = (int)poly.size();
    int left = 0, right = 0;
    for (int i = 1; i < n; ++i) {
        if (poly[i].x < poly[left].x || (poly[i].x == poly[left].x && poly[i].y < poly[left].y)) left = i;
        if (poly[i].x > poly[right].x || (poly[i].x == poly[right].x && poly[i].y < poly[right].y)) right = i;
    }

    Chain forward, backward;
    for (int i = left; ; i = (i + 1) % n) {
        forward.verts.push_back(i);
        if (i == right) break;
    }
    for (int i = left; ; i = (i - 1 + n) % n) {
        backward.verts.push_back(i);
        if (i == right) break;
    }

    for (int i = 0; i + 1 < (int)forward.verts.size(); ++i) {
        forward.edges.push_back(forward.verts[i]);
    }
    for (int i = 0; i + 1 < (int)backward.verts.size(); ++i) {
        backward.edges.push_back(backward.verts[i + 1]);
    }
    return {forward, backward};
}

static optional<pair<int, int>> mergeChains(const vector<Pt>& A, const Chain& aChain,
                                            const vector<Pt>& B, const Chain& bChain) {
    int i = 0, j = 0;
    while (i + 1 < (int)aChain.verts.size() && j + 1 < (int)bChain.verts.size()) {
        int ai = aChain.verts[i], an = aChain.verts[i + 1];
        int bi = bChain.verts[j], bn = bChain.verts[j + 1];
        if (segIntersect(A[ai], A[an], B[bi], B[bn])) {
            return make_pair(aChain.edges[i] + 1, bChain.edges[j] + 1);
        }
        long long ar = max(A[ai].x, A[an].x);
        long long br = max(B[bi].x, B[bn].x);
        if (ar < br) {
            ++i;
        } else if (br < ar) {
            ++j;
        } else {
            ++i;
            ++j;
        }
    }
    return nullopt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    if (!(cin >> m >> n)) return 0;

    vector<Pt> P(m), Q(n);
    for (int i = 0; i < m; ++i) cin >> P[i].x >> P[i].y;
    for (int i = 0; i < n; ++i) cin >> Q[i].x >> Q[i].y;

    auto [Pup, Plow] = splitChains(P);
    auto [Qup, Qlow] = splitChains(Q);

    for (const auto& aChain : {Pup, Plow}) {
        for (const auto& bChain : {Qup, Qlow}) {
            if (auto ans = mergeChains(P, aChain, Q, bChain)) {
                cout << ans->first << ' ' << ans->second << '\n';
                return 0;
            }
        }
    }

    cout << "0 0\n";
    return 0;
}
