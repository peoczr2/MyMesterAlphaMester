/*
Legyen dp[x] a [1,x] intervallum minimális lefedési költsége. Ha az utolsó felhasznált intervallum [a,b], akkor a
korábbi lefedésnek valameddig el kellett jutnia az [a-1,b-1] tartományban, mert csak így nem marad rés a lefedésben.
Ezért dp[b] az összes b-ben végződő intervallumra egy tartományminimum-kérdezéssel számolható, amit szegmensfa
szolgál ki O((N+M)logN) időben.
*/
/*
Hint 1: || Ha az utolsó intervallum [a,b], akkor előtte legalább az a-1 pontig már le kellett fedni mindent. ||
Hint 2: || Ugyanarra a b végpontra több intervallum is érkezhet, ezek közül a legjobb dönti el dp[b]-t. ||
Hint 3: || A "korábbi lefedés meddig jutott el" kérdés tartományminimumra vezet. ||
*/

#include <bits/stdc++.h>

using namespace std;

struct SegTree {
    int n;
    vector<int> tree;

    explicit SegTree(int size) {
        n = 1;
        while (n < size) {
            n <<= 1;
        }
        tree.assign(2 * n, (int)1e9);
    }

    void set_value(int pos, int value) {
        pos += n;
        tree[pos] = value;
        for (pos >>= 1; pos > 0; pos >>= 1) {
            tree[pos] = min(tree[pos << 1], tree[pos << 1 | 1]);
        }
    }

    int query(int left, int right) const {
        if (left > right) {
            return (int)1e9;
        }
        int res = (int)1e9;
        left += n;
        right += n;
        while (left <= right) {
            if (left & 1) {
                res = min(res, tree[left++]);
            }
            if (!(right & 1)) {
                res = min(res, tree[right--]);
            }
            left >>= 1;
            right >>= 1;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    vector<vector<pair<int, int>>> by_right(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        by_right[b].push_back({a, b});
    }

    const int INF = 1e9;
    vector<int> dp(n + 1, INF);
    SegTree seg(n + 1);
    dp[0] = 0;
    seg.set_value(0, 0);

    for (int x = 1; x <= n; ++x) {
        int best = INF;
        for (auto [a, b] : by_right[x]) {
            int prev = seg.query(a - 1, b - 1);
            best = min(best, prev + (b - a + 1));
        }
        dp[x] = best;
        seg.set_value(x, best);
    }

    cout << (dp[n] >= INF ? 0 : dp[n]) << '\n';
    return 0;
}
