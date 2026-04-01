/*
Megoldás lényege:
A fa olyan mappákat tartalmaz, ahol a hiányzó értékek a gyökértől lefelé, az egygyerekes
láncokon keresztül rögzülnek. A végül fix értéket kapó levelek összegét levonjuk a gyökér
értékéből, a többi hiányzó levél pedig szabad változó marad. Ezek elosztásainak száma
egy stars-and-bars kombináció.

*/

// Hint 1: || Az egygyerekes, ismert értékű csomópontok csak továbbadják a fix értéket. ||
// Hint 2: || A végső szabadságfokok a valóban ismeretlen levelekből jönnek. ||
// Hint 3: || A maradékot egyszer kell kombinatorikusan elosztani a szabad levelek között. ||

#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 1000000007LL;

static long long modPow(long long a, long long e) {
    long long r = 1;
    while (e > 0) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<int> parent(N + 1);
    vector<long long> val(N + 1);
    vector<vector<int>> children(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> parent[i] >> val[i];
        if (parent[i] != 0) children[parent[i]].push_back(i);
    }

    vector<long long> inv(N + 5, 1);
    for (int i = 2; i < (int)inv.size(); ++i) {
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
    }

    auto chooseSmallK = [&](long long n, int k) -> long long {
        if (k < 0 || n < k) return 0;
        if (k == 0) return 1;
        long long res = 1;
        for (int i = 1; i <= k; ++i) {
            res = res * ((n - k + i) % MOD) % MOD;
            res = res * inv[i] % MOD;
        }
        return res;
    };

    auto choose = [&](long long n, int k) -> long long {
        if (k < 0 || n < k) return 0;
        long long ans = 1;
        long long nn = n;
        int kk = k;
        while (nn > 0 || kk > 0) {
            long long ni = nn % MOD;
            int ki = kk % (int)MOD;
            if (ki > ni) return 0;
            ans = ans * chooseSmallK(ni, ki) % MOD;
            nn /= MOD;
            kk /= (int)MOD;
        }
        return ans;
    };

    struct Form {
        // delta=true: a részfa összértéke fix, fixed az érték, ways a kitöltések száma.
        // delta=false: s>=base esetén ways*C(s-base+freeCnt-1, freeCnt-1).
        bool ok = true;
        bool delta = true;
        long long fixed = 0;
        long long ways = 1;
        long long base = 0;
        int freeCnt = 0;
    };

    function<Form(int)> dfs = [&](int u) -> Form {
        Form cur;

        if (children[u].empty()) {
            if (val[u] == -1) {
                cur.delta = false;
                cur.base = 0;
                cur.freeCnt = 1;
                cur.ways = 1;
            } else {
                cur.delta = true;
                cur.fixed = val[u];
                cur.ways = 1;
            }
            return cur;
        }

        if ((int)children[u].size() == 1) {
            cur = dfs(children[u][0]);
            if (!cur.ok) return cur;
        } else {
            Form a = dfs(children[u][0]);
            Form b = dfs(children[u][1]);
            if (!a.ok || !b.ok) {
                cur.ok = false;
                return cur;
            }

            cur.ways = a.ways * b.ways % MOD;
            if (a.delta && b.delta) {
                cur.delta = true;
                cur.fixed = a.fixed + b.fixed;
            } else if (a.delta && !b.delta) {
                cur.delta = false;
                cur.base = a.fixed + b.base;
                cur.freeCnt = b.freeCnt;
            } else if (!a.delta && b.delta) {
                cur.delta = false;
                cur.base = a.base + b.fixed;
                cur.freeCnt = a.freeCnt;
            } else {
                cur.delta = false;
                cur.base = a.base + b.base;
                cur.freeCnt = a.freeCnt + b.freeCnt;
            }
        }

        if (val[u] == -1) return cur;

        long long need = val[u];
        if (cur.delta) {
            if (cur.fixed != need) {
                cur.ok = false;
                return cur;
            }
            return cur;
        }

        if (need < cur.base) {
            cur.ok = false;
            return cur;
        }

        long long n = (need - cur.base) + (cur.freeCnt - 1);
        int k = cur.freeCnt - 1;
        long long waysHere = choose(n, k);
        cur.delta = true;
        cur.fixed = need;
        cur.ways = cur.ways * waysHere % MOD;
        cur.base = 0;
        cur.freeCnt = 0;
        return cur;
    };

    Form root = dfs(1);
    if (!root.ok || !root.delta || val[1] == -1 || root.fixed != val[1]) {
        cout << 0 << '\n';
        return 0;
    }

    cout << root.ways % MOD << '\n';
    return 0;
}
