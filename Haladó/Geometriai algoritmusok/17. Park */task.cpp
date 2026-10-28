/*
Megoldás lényege:
Minden háromszögbe pontosan egy facsemete kerülhet, és a háromszögek nem fedhetik egymást, ezért a maximum egy teljes háromszögelés háromszögeinek száma. Ha a fák száma N, a konvex burok éleinek (a közbeeső, egy egyenesre eső pontokat is beleértve) pontszámát b jelöli, akkor minden háromszögelés 2N - b - 2 háromszögből áll. A burkot egy csúcsából húzott átlókkal háromszögekre bontjuk, majd a belső pontokat véletlen sorrendben egyenként beszúrjuk: a pontot tartalmazó háromszöget három részre osztjuk, ha a pont egy élen van, akkor a két szomszédos háromszöget is. A pont helyét egy háromszögekből álló keresőfa adja.
*/
/*
Hint 1: || Minden háromszögbe pontosan egy facsemete kerül, és a háromszögek nem fedhetik egymást, így a kérdés a fák teljes háromszögelésének háromszögszáma. Gondold át, hogyan függ ez a fák számától és a burkon lévő pontok számától (Euler-formula). ||
Hint 2: || Építs háromszögelést fokozatosan: a burkot egy csúcsából húzott átlókkal bontsd háromszögekre, majd a belső pontokat egyenként szúrd be. Egy pont beszúrása azt a háromszöget osztja fel, amelyben (vagy amelyen) van; a keresést érdemes egy fában tárolni. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
    int id;
};

static int orient(const Pt& a, const Pt& b, const Pt& c) {
    __int128 v = (__int128)(b.x - a.x) * (c.y - a.y) - (__int128)(b.y - a.y) * (c.x - a.x);
    if (v < 0) return -1;
    if (v > 0) return 1;
    return 0;
}

static vector<int> convexHullStrict(const vector<Pt>& pts) {
    vector<int> ord(pts.size());
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) {
        if (pts[i].x != pts[j].x) return pts[i].x < pts[j].x;
        if (pts[i].y != pts[j].y) return pts[i].y < pts[j].y;
        return pts[i].id < pts[j].id;
    });
    ord.erase(unique(ord.begin(), ord.end(), [&](int i, int j) {
        return pts[i].x == pts[j].x && pts[i].y == pts[j].y;
    }), ord.end());

    if (ord.size() < 3) return ord;

    vector<int> lower, upper;
    for (int idx : ord) {
        while (lower.size() >= 2 && orient(pts[lower[lower.size() - 2]], pts[lower.back()], pts[idx]) <= 0) lower.pop_back();
        lower.push_back(idx);
    }
    for (int k = (int)ord.size() - 1; k >= 0; --k) {
        int idx = ord[k];
        while (upper.size() >= 2 && orient(pts[upper[upper.size() - 2]], pts[upper.back()], pts[idx]) <= 0) upper.pop_back();
        upper.push_back(idx);
    }

    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

struct Node {
    int a, b, c;
    array<int, 3> child{{-1, -1, -1}};
    int childCount = 0;
};

static vector<Pt> pts;
static vector<Node> nodes;
static unordered_map<unsigned long long, vector<int>> edgeLeaves;

static unsigned long long edgeKey(int u, int v) {
    if (u > v) swap(u, v);
    return (unsigned long long)(unsigned int)u << 32 | (unsigned int)v;
}

static int makeNode(int a, int b, int c) {
    nodes.push_back(Node{a, b, c});
    return (int)nodes.size() - 1;
}

static int makeCCW(int a, int b, int c) {
    if (orient(pts[a], pts[b], pts[c]) < 0) swap(b, c);
    return makeNode(a, b, c);
}

static void addLeafEdges(int nodeId) {
    const Node& node = nodes[nodeId];
    for (int i = 0; i < 3; ++i) {
        int u = (i == 0 ? node.a : (i == 1 ? node.b : node.c));
        int v = (i == 0 ? node.b : (i == 1 ? node.c : node.a));
        edgeLeaves[edgeKey(u, v)].push_back(nodeId);
    }
}

static void removeLeafEdges(int nodeId) {
    const Node& node = nodes[nodeId];
    for (int i = 0; i < 3; ++i) {
        int u = (i == 0 ? node.a : (i == 1 ? node.b : node.c));
        int v = (i == 0 ? node.b : (i == 1 ? node.c : node.a));
        unsigned long long key = edgeKey(u, v);
        auto it = edgeLeaves.find(key);
        if (it == edgeLeaves.end()) continue;
        auto& vec = it->second;
        vec.erase(remove(vec.begin(), vec.end(), nodeId), vec.end());
        if (vec.empty()) edgeLeaves.erase(it);
    }
}

static bool containsPoint(int nodeId, const Pt& p) {
    const Node& node = nodes[nodeId];
    return orient(pts[node.a], pts[node.b], p) >= 0 &&
           orient(pts[node.b], pts[node.c], p) >= 0 &&
           orient(pts[node.c], pts[node.a], p) >= 0;
}

static int locateLeaf(int rootId, const Pt& p) {
    int cur = rootId;
    while (nodes[cur].childCount != 0) {
        bool moved = false;
        for (int i = 0; i < nodes[cur].childCount; ++i) {
            int nxt = nodes[cur].child[i];
            if (containsPoint(nxt, p)) {
                cur = nxt;
                moved = true;
                break;
            }
        }
        if (!moved) break;
    }
    return cur;
}

static void splitInteriorLeaf(int nodeId, int pIdx) {
    int a = nodes[nodeId].a, b = nodes[nodeId].b, c = nodes[nodeId].c;
    removeLeafEdges(nodeId);
    int c0 = makeCCW(a, b, pIdx);
    int c1 = makeCCW(b, c, pIdx);
    int c2 = makeCCW(c, a, pIdx);
    nodes[nodeId].child = {c0, c1, c2};
    nodes[nodeId].childCount = 3;
    addLeafEdges(c0);
    addLeafEdges(c1);
    addLeafEdges(c2);
}

static int splitEdgeLeaf(int nodeId, int leftIdx, int rightIdx, int pIdx) {
    int a = nodes[nodeId].a, b = nodes[nodeId].b, c = nodes[nodeId].c;
    int third = -1;
    if (a != leftIdx && a != rightIdx) third = a;
    if (b != leftIdx && b != rightIdx) third = b;
    if (c != leftIdx && c != rightIdx) third = c;

    removeLeafEdges(nodeId);
    int leftTri = makeCCW(leftIdx, pIdx, third);
    int rightTri = makeCCW(pIdx, rightIdx, third);
    nodes[nodeId].child = {leftTri, rightTri, -1};
    nodes[nodeId].childCount = 2;
    addLeafEdges(leftTri);
    addLeafEdges(rightTri);
    return rightTri;
}

static bool onSegment(const Pt& a, const Pt& b, const Pt& p) {
    if (orient(a, b, p) != 0) return false;
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    pts.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> pts[i].x >> pts[i].y;
        pts[i].id = i + 1;
    }

    vector<int> hull = convexHullStrict(pts);
    if (hull.size() < 3) {
        cout << "0\n";
        return 0;
    }

    vector<char> onHull(n, 0);
    for (int idx : hull) onHull[idx] = 1;
    vector<int> interior;
    interior.reserve(n);

    for (int i = 0; i < n; ++i) {
        if (!onHull[i]) interior.push_back(i);
    }

    nodes.reserve(2 * n + 8);
    vector<int> roots;
    for (int i = 1; i + 1 < (int)hull.size(); ++i) {
        int root = makeCCW(hull[0], hull[i], hull[i + 1]);
        roots.push_back(root);
        addLeafEdges(root);
    }

    mt19937_64 rng(712367821ULL);
    shuffle(interior.begin(), interior.end(), rng);

    for (int idx : interior) {
        int sector = -1;
        const Pt& a0 = pts[hull[0]];
        if (orient(a0, pts[hull[1]], pts[idx]) >= 0 && orient(a0, pts[hull.back()], pts[idx]) <= 0) {
            int lo = 1, hi = (int)hull.size() - 1;
            while (hi - lo > 1) {
                int mid = (lo + hi) >> 1;
                if (orient(a0, pts[hull[mid]], pts[idx]) >= 0) lo = mid;
                else hi = mid;
            }
            sector = lo - 1;
        }
        if (sector < 0 || sector >= (int)roots.size()) continue;
        int leaf = locateLeaf(roots[sector], pts[idx]);
        const Node& node = nodes[leaf];
        int splitU = -1, splitV = -1;
        if (onSegment(pts[node.a], pts[node.b], pts[idx])) {
            splitU = node.a; splitV = node.b;
        } else if (onSegment(pts[node.b], pts[node.c], pts[idx])) {
            splitU = node.b; splitV = node.c;
        } else if (onSegment(pts[node.c], pts[node.a], pts[idx])) {
            splitU = node.c; splitV = node.a;
        }

        if (splitU != -1) {
            unsigned long long key = edgeKey(splitU, splitV);
            auto it = edgeLeaves.find(key);
            vector<int> affected;
            if (it != edgeLeaves.end()) affected = it->second;
            if (affected.empty()) {
                splitInteriorLeaf(leaf, idx);
            } else {
                for (int leafId : affected) {
                    splitEdgeLeaf(leafId, splitU, splitV, idx);
                }
            }
        } else {
            splitInteriorLeaf(leaf, idx);
        }
    }

    vector<array<int, 3>> answer;
    answer.reserve(2 * n);
    vector<int> stack;
    stack.reserve(nodes.size());
    for (int root : roots) stack.push_back(root);

    while (!stack.empty()) {
        int cur = stack.back();
        stack.pop_back();
        if (nodes[cur].childCount == 0) {
            answer.push_back({pts[nodes[cur].a].id, pts[nodes[cur].b].id, pts[nodes[cur].c].id});
        } else {
            for (int i = 0; i < nodes[cur].childCount; ++i) stack.push_back(nodes[cur].child[i]);
        }
    }

    cout << answer.size() << '\n';
    for (const auto& t : answer) {
        cout << t[0] << ' ' << t[1] << ' ' << t[2] << '\n';
    }

    return 0;
}
