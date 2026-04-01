/*
Az i-edik tárgyig tartó optimális bontásnál az utolsó menet egy [j,i] blokk, amelynek költsége a blokkban szereplő
égetési idők maximuma, és a blokksúly nem lépheti túl K-t. A naiv átmenet túl lassú lenne, ezért a j kezdőpontokhoz a
jelenlegi blokkmaximumot szegmensfában tartjuk karban: amikor új tárgy érkezik, csak azoknak a kezdőpontoknak nő meg
a költsége, amelyeknél az új idő nagyobb a korábbi blokkmakszumnál. Így a DP O(NlogN) időben kiszámolható, és a legjobb
utolsó blokk kezdete minden i-re eltárolható.
*/
/*
Hint 1: || Az utolsó menet kezdőpontját kell optimalizálni, de csak a súlykorlátot teljesítő kezdések jöhetnek szóba. ||
Hint 2: || Egy rögzített kezdőponthoz az átmenet értéke: dp[j-1] + max(Ej..Ei). ||
Hint 3: || Az új tárgy csak azoknál a kezdőpontoknál változtatja meg a blokk maximumát, ahol nagyobb a korábbi maximumnál. ||
*/

#include <bits/stdc++.h>

using namespace std;

struct Node {
    long long value;
    int pos;
};

struct SegTree {
    int n;
    vector<Node> tree;
    vector<long long> lazy;

    explicit SegTree(int size) {
        n = 1;
        while (n < size) {
            n <<= 1;
        }
        tree.assign(2 * n, Node{(long long)4e18, -1});
        lazy.assign(2 * n, 0);
        for (int i = 0; i < n; ++i) {
            tree[n + i].pos = i;
        }
        for (int i = n - 1; i >= 1; --i) {
            tree[i] = min_node(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    static Node min_node(const Node& a, const Node& b) {
        if (a.value != b.value) {
            return a.value < b.value ? a : b;
        }
        return a.pos < b.pos ? a : b;
    }

    void apply(int node, long long add) {
        tree[node].value += add;
        lazy[node] += add;
    }

    void push(int node) {
        if (lazy[node] != 0) {
            apply(node << 1, lazy[node]);
            apply(node << 1 | 1, lazy[node]);
            lazy[node] = 0;
        }
    }

    void point_set(int node, int left, int right, int pos, long long value) {
        if (left == right) {
            tree[node].value = value;
            tree[node].pos = pos;
            return;
        }
        push(node);
        int mid = (left + right) >> 1;
        if (pos <= mid) {
            point_set(node << 1, left, mid, pos, value);
        } else {
            point_set(node << 1 | 1, mid + 1, right, pos, value);
        }
        tree[node] = min_node(tree[node << 1], tree[node << 1 | 1]);
    }

    void point_set(int pos, long long value) {
        point_set(1, 1, n, pos, value);
    }

    void range_add(int node, int left, int right, int ql, int qr, long long add) {
        if (ql > right || qr < left || ql > qr) {
            return;
        }
        if (ql <= left && right <= qr) {
            apply(node, add);
            return;
        }
        push(node);
        int mid = (left + right) >> 1;
        range_add(node << 1, left, mid, ql, qr, add);
        range_add(node << 1 | 1, mid + 1, right, ql, qr, add);
        tree[node] = min_node(tree[node << 1], tree[node << 1 | 1]);
    }

    void range_add(int left, int right, long long add) {
        range_add(1, 1, n, left, right, add);
    }

    Node query(int node, int left, int right, int ql, int qr) {
        if (ql > right || qr < left || ql > qr) {
            return Node{(long long)4e18, -1};
        }
        if (ql <= left && right <= qr) {
            return tree[node];
        }
        push(node);
        int mid = (left + right) >> 1;
        return min_node(query(node << 1, left, mid, ql, qr), query(node << 1 | 1, mid + 1, right, ql, qr));
    }

    Node query(int left, int right) {
        return query(1, 1, n, left, right);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K;
    cin >> n >> K;
    vector<int> weight(n + 1), heat(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> weight[i] >> heat[i];
    }

    vector<long long> prefix(n + 1, 0), dp(n + 1, (long long)4e18);
    vector<int> prev_start(n + 1, -1);
    for (int i = 1; i <= n; ++i) {
        prefix[i] = prefix[i - 1] + weight[i];
    }

    dp[0] = 0;
    SegTree seg(n + 2);
    vector<pair<int, int>> st;
    int left_limit = 1;

    for (int i = 1; i <= n; ++i) {
        seg.point_set(i, dp[i - 1]);

        int left = i;
        while (!st.empty() && st.back().second <= heat[i]) {
            int l = st.back().first;
            int prev_max = st.back().second;
            seg.range_add(l, left - 1, heat[i] - prev_max);
            left = l;
            st.pop_back();
        }
        st.push_back({left, heat[i]});
        seg.range_add(i, i, heat[i]);

        while (left_limit <= i && prefix[i] - prefix[left_limit - 1] > K) {
            ++left_limit;
        }

        Node best = seg.query(left_limit, i);
        dp[i] = best.value;
        prev_start[i] = best.pos;
    }

    vector<pair<int, int>> groups;
    for (int i = n; i > 0; i = prev_start[i] - 1) {
        groups.push_back({prev_start[i], i});
    }
    reverse(groups.begin(), groups.end());

    cout << dp[n] << '\n';
    for (auto [l, r] : groups) {
        cout << l << ' ' << r << '\n';
    }
    return 0;
}
