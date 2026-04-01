/*
Megoldás lényege:
A feladat a pontok minimális külső határának meghatározására vezethető vissza. Ehhez a konvex burok és a határpontok rendezése adja a kulcsot.
*/
#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
};

struct DSU {
    vector<int> parent, rnk;
    DSU() = default;
    explicit DSU(int n) : parent(n), rnk(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int a) {
        if (parent[a] == a) return a;
        return parent[a] = find(parent[a]);
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (rnk[a] < rnk[b]) swap(a, b);
        parent[b] = a;
        if (rnk[a] == rnk[b]) ++rnk[a];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long h;
    if (!(cin >> n >> h)) return 0;

    vector<Pt> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i].x >> p[i].y;

    vector<int> aboveId(n, -1), belowId(n, -1);
    int nodeCount = 0;
    auto getAboveId = [&](int idx) {
        if (aboveId[idx] == -1) aboveId[idx] = nodeCount++;
        return aboveId[idx];
    };
    auto getBelowId = [&](int idx) {
        if (belowId[idx] == -1) belowId[idx] = nodeCount++;
        return belowId[idx];
    };

    // First pass: count needed nodes.
    for (int i = 0; i < n; ++i) {
        const Pt& a = p[i];
        const Pt& b = p[(i + 1) % n];
        if (a.y > h) getAboveId(i);
        if (a.y < h) getBelowId(i);
        if (a.x == b.x && (a.y - h) * (b.y - h) < 0) ++nodeCount;
    }

    // Rebuild with a compact node count.
    fill(aboveId.begin(), aboveId.end(), -1);
    fill(belowId.begin(), belowId.end(), -1);
    vector<pair<long long, int>> crossings; // (x, nodeId)
    crossings.reserve(n);

    int nextNode = 0;
    for (int i = 0; i < n; ++i) {
        if (p[i].y > h && aboveId[i] == -1) aboveId[i] = nextNode++;
        if (p[i].y < h && belowId[i] == -1) belowId[i] = nextNode++;
    }
    // Crossing nodes are appended after original-side nodes.
    vector<int> crossNodeOfEdge(n, -1);
    for (int i = 0; i < n; ++i) {
        const Pt& a = p[i];
        const Pt& b = p[(i + 1) % n];
        if (a.x == b.x && (a.y - h) * (b.y - h) < 0) {
            crossNodeOfEdge[i] = nextNode++;
        }
    }

    DSU dsuAbove(nextNode), dsuBelow(nextNode);
    vector<int> activeAbove(nextNode, 0), activeBelow(nextNode, 0);

    for (int i = 0; i < n; ++i) {
        const Pt& a = p[i];
        const Pt& b = p[(i + 1) % n];

        if (a.y > h) activeAbove[aboveId[i]] = 1;
        if (a.y < h) activeBelow[belowId[i]] = 1;

        if (a.y > h && b.y > h) {
            dsuAbove.unite(aboveId[i], aboveId[(i + 1) % n]);
        } else if (a.y < h && b.y < h) {
            dsuBelow.unite(belowId[i], belowId[(i + 1) % n]);
        } else if (a.x == b.x && (a.y - h) * (b.y - h) < 0) {
            int c = crossNodeOfEdge[i];
            crossings.push_back({a.x, c});
            if (a.y > h) {
                activeAbove[c] = 1;
                dsuAbove.unite(c, aboveId[i]);
                activeBelow[belowId[(i + 1) % n]] = 1;
                dsuBelow.unite(c, belowId[(i + 1) % n]);
            } else {
                activeAbove[c] = 1;
                dsuAbove.unite(c, aboveId[(i + 1) % n]);
                activeBelow[belowId[i]] = 1;
                dsuBelow.unite(c, belowId[i]);
            }
        }
    }

    sort(crossings.begin(), crossings.end());
    for (int i = 0; i + 1 < (int)crossings.size(); i += 2) {
        int a = crossings[i].second;
        int b = crossings[i + 1].second;
        dsuAbove.unite(a, b);
        dsuBelow.unite(a, b);
        activeAbove[a] = activeAbove[b] = 1;
        activeBelow[a] = activeBelow[b] = 1;
    }

    unordered_set<int> rootsAbove, rootsBelow;
    rootsAbove.reserve(nextNode * 2 + 16);
    rootsBelow.reserve(nextNode * 2 + 16);

    for (int i = 0; i < nextNode; ++i) {
        if (activeAbove[i]) rootsAbove.insert(dsuAbove.find(i));
        if (activeBelow[i]) rootsBelow.insert(dsuBelow.find(i));
    }

    cout << rootsAbove.size() << ' ' << rootsBelow.size() << '\n';
    return 0;
}
