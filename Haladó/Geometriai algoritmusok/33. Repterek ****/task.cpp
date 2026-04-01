/*
Megoldás lényege:
A feladat távolságoptimalizálási jellegű: a pontok közti legfontosabb viszonyt kell meghatározni. A megoldás a legközelebbi pontpár vagy egy minimax típusú geometriai számítás köré épül.
*/
#include <bits/stdc++.h>
using namespace std;

struct Pt {
    int x, y, id;
};

struct Node {
    int l = -1, r = -1;
    int idx = -1;
    int cnt = 0;
    int minx, maxx, miny, maxy;
    bool leaf = false;
    bool dead = false;
};

static vector<Pt> pts;
static vector<Node> tree;
static vector<char> active;

static int build(vector<int>& ids, int depth) {
    int nodeId = (int)tree.size();
    tree.push_back(Node{});
    Node& node = tree.back();

    int minx = pts[ids[0]].x, maxx = pts[ids[0]].x;
    int miny = pts[ids[0]].y, maxy = pts[ids[0]].y;
    for (int id : ids) {
        minx = min(minx, pts[id].x);
        maxx = max(maxx, pts[id].x);
        miny = min(miny, pts[id].y);
        maxy = max(maxy, pts[id].y);
    }
    node.minx = minx;
    node.maxx = maxx;
    node.miny = miny;
    node.maxy = maxy;
    node.cnt = (int)ids.size();

    if (ids.size() == 1) {
        node.leaf = true;
        node.idx = ids[0];
        return nodeId;
    }

    int axis = depth & 1;
    int mid = (int)ids.size() / 2;
    nth_element(ids.begin(), ids.begin() + mid, ids.end(), [&](int a, int b) {
        if (axis == 0) {
            if (pts[a].x != pts[b].x) return pts[a].x < pts[b].x;
            return pts[a].y < pts[b].y;
        } else {
            if (pts[a].y != pts[b].y) return pts[a].y < pts[b].y;
            return pts[a].x < pts[b].x;
        }
    });

    vector<int> left(ids.begin(), ids.begin() + mid);
    vector<int> right(ids.begin() + mid, ids.end());
    node.l = build(left, depth + 1);
    node.r = build(right, depth + 1);
    node.cnt = tree[node.l].cnt + tree[node.r].cnt;
    return nodeId;
}

static bool insideNE(const Node& node, const Pt& p) {
    return node.maxx >= p.x && node.maxy >= p.y;
}

static bool outsideNE(const Node& node, const Pt& p) {
    return node.maxx < p.x || node.maxy < p.y;
}

static bool fullNE(const Node& node, const Pt& p) {
    return node.minx >= p.x && node.miny >= p.y;
}

static bool outsideSW(const Node& node, const Pt& p) {
    return node.minx > p.x || node.miny > p.y;
}

static bool fullSW(const Node& node, const Pt& p) {
    return node.maxx <= p.x && node.maxy <= p.y;
}

static void collectAll(int nodeId, vector<int>& out) {
    Node& node = tree[nodeId];
    if (node.dead || node.cnt == 0) return;
    if (node.leaf) {
        if (active[node.idx]) {
            active[node.idx] = 0;
            out.push_back(node.idx);
        }
        node.cnt = 0;
        node.dead = true;
        return;
    }
    collectAll(node.l, out);
    collectAll(node.r, out);
    node.cnt = 0;
    node.dead = true;
}

static int removeOrthant(int nodeId, const Pt& p, bool northeast, vector<int>& out) {
    Node& node = tree[nodeId];
    if (node.dead || node.cnt == 0) return 0;

    if (northeast) {
        if (outsideNE(node, p)) return 0;
        if (fullNE(node, p)) {
            int removedBefore = (int)out.size();
            collectAll(nodeId, out);
            return (int)out.size() - removedBefore;
        }
    } else {
        if (outsideSW(node, p)) return 0;
        if (fullSW(node, p)) {
            int removedBefore = (int)out.size();
            collectAll(nodeId, out);
            return (int)out.size() - removedBefore;
        }
    }

    if (node.leaf) {
        if (active[node.idx]) {
            bool ok = northeast ? (pts[node.idx].x >= p.x && pts[node.idx].y >= p.y)
                                : (pts[node.idx].x <= p.x && pts[node.idx].y <= p.y);
            if (ok) {
                active[node.idx] = 0;
                node.cnt = 0;
                node.dead = true;
                out.push_back(node.idx);
                return 1;
            }
        }
        return 0;
    }

    int removedLeft = removeOrthant(node.l, p, northeast, out);
    int removedRight = removeOrthant(node.r, p, northeast, out);
    node.cnt -= removedLeft + removedRight;
    if (node.cnt == 0) node.dead = true;
    return removedLeft + removedRight;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    pts.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> pts[i].x >> pts[i].y;
        pts[i].id = i + 1;
    }

    active.assign(n, 1);
    vector<int> ids(n);
    iota(ids.begin(), ids.end(), 0);
    tree.reserve(2 * n + 8);
    int root = build(ids, 0);

    vector<int> dist(n, -1);
    queue<int> q;

    for (int i = 0; i < n; ++i) {
        if (pts[i].x == 0 && pts[i].y == 0) {
            dist[i] = 0;
            active[i] = 0;
        }
    }

    vector<int> discovered;
    removeOrthant(root, {0, 0, 0}, true, discovered);
    removeOrthant(root, {0, 0, 0}, false, discovered);
    for (int idx : discovered) {
        if (dist[idx] == -1) {
            dist[idx] = 1;
            q.push(idx);
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (dist[v] == k) continue;

        discovered.clear();
        removeOrthant(root, pts[v], true, discovered);
        removeOrthant(root, pts[v], false, discovered);
        for (int idx : discovered) {
            if (dist[idx] == -1) {
                dist[idx] = dist[v] + 1;
                q.push(idx);
            }
        }
    }

    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        if (dist[i] == -1 || dist[i] > k) ans.push_back(pts[i].id);
    }

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';

    return 0;
}