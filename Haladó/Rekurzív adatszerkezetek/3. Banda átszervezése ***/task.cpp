#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
Egyetlen bandatagot kell áthelyezni úgy, hogy a fa magassága (a legmélyebb tag
mélysége) minél kisebb legyen. N legfeljebb 1000, ezért minden lehetséges
(áthelyezendő x, új főnök y) párt kipróbálunk. Az y nem lehet x részfájában, és
y-nak még legalább egy szabad helye kell legyen (kevesebb mint K beosztottja van).

Ha x-et y alá helyezzük, akkor x részfájának minden tagja ugyanannyival kerül
mélyebbre vagy sekélyebbre. Az új magasság ezért:
  max(az x részfáján kívüli legnagyobb mélység,
      depth[y] + 1 + subtreeHeight[x])
ahol subtreeHeight[x] az x alatti részfa magassága x-hez képest.
Ha a legjobb pár sem csökkenti az eredeti magasságot, nincs áthelyezendő tag, és a válasz 0 0.

Az x részfáján kívüli legnagyobb mélységet Euler-sorrendben egy szegmensfával
gyorsan lekérdezzük. Így O(N^2 log N) időben megkapjuk a választ.
*/
/*
Hint 1: || Egy mozgatás csak egy részfát érint, így a többi csomópont mélysége nem változik. ||
Hint 2: || Az új magasság két részből áll: a mozgatott részfa legmélyebb pontjából és minden más csomópontból. ||
Hint 3: || Euler-sorrendben a részfa egy intervallum, ezért a részfán kívüli maximumot gyorsan ki lehet szedni egy RMQ/segment tree szerkezettel. ||
*/

struct SegTree {
    int n;
    vector<int> tree;

    SegTree() = default;
    explicit SegTree(const vector<int>& a) {
        n = (int)a.size() - 1;
        tree.assign(4 * n + 4, 0);
        build(1, 1, n, a);
    }

    void build(int node, int l, int r, const vector<int>& a) {
        if (l == r) {
            tree[node] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(node * 2, l, mid, a);
        build(node * 2 + 1, mid + 1, r, a);
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }

    int query(int node, int l, int r, int ql, int qr) const {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return max(query(node * 2, l, mid, ql, qr), query(node * 2 + 1, mid + 1, r, ql, qr));
    }

    int query(int l, int r) const {
        if (l > r) return 0;
        return query(1, 1, n, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<int> parent(N + 1, 0), deg(N + 1, 0);
    vector<vector<int>> children(N + 1);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        parent[v] = u;
        children[u].push_back(v);
        ++deg[u];
    }

    vector<int> tin(N + 1), tout(N + 1), depth(N + 1), subtreeHeight(N + 1);
    vector<int> euler(N + 1);
    int timer = 0;

    function<void(int)> dfs = [&](int u) {
        tin[u] = ++timer;
        euler[timer] = u;
        subtreeHeight[u] = 0;
        for (int v : children[u]) {
            depth[v] = depth[u] + 1;
            dfs(v);
            subtreeHeight[u] = max(subtreeHeight[u], subtreeHeight[v] + 1);
        }
        tout[u] = timer;
    };
    dfs(1);

    vector<int> depthOnEuler(N + 1);
    for (int i = 1; i <= N; ++i) depthOnEuler[i] = depth[euler[i]];
    SegTree st(depthOnEuler);

    int bestHeight = subtreeHeight[1];
    int bestMove = 0, bestBoss = 0;

    for (int x = 2; x <= N; ++x) {
        for (int y = 1; y <= N; ++y) {
            if (y == x) continue;
            if (tin[y] >= tin[x] && tin[y] <= tout[x]) continue;
            if (deg[y] >= K) continue;

            int outsideLeft = st.query(1, tin[x] - 1);
            int outsideRight = st.query(tout[x] + 1, N);
            int outsideMax = max(outsideLeft, outsideRight);
            int movedHeight = depth[y] + 1 + subtreeHeight[x];
            int newHeight = max(outsideMax, movedHeight);

            if (newHeight < bestHeight || (newHeight == bestHeight && bestMove != 0 && (x < bestMove || (x == bestMove && y < bestBoss)))) {
                bestHeight = newHeight;
                bestMove = x;
                bestBoss = y;
            }
        }
    }

    if (bestMove == 0) {
        cout << "0 0\n";
    } else {
        cout << bestMove << ' ' << bestBoss << '\n';
    }
    return 0;
}