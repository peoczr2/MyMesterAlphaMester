/*
Megoldási ötlet:
Az elfogadható felfedezési sorrendek pontosan a gyökerezett fa topologikus sorrendjei, ahol minden sziget csak azután
jelenhet meg, hogy az őt felfedező szigetek már megjelentek. A gyökér, az 1-es sziget eleve első.

Egy részfára a sorrendek száma rekurzívan számolható. Ha egy csúcs gyerekeinek részfái rendre s1, s2, ..., sk méretűek,
akkor a gyerekek sorrendjei egymás között tetszőlegesen összefonhatók, ami egy multinomiális tényezőt ad.
A részfák belső sorrendjeit ezekhez szorozzuk hozzá.
*/
/*
Hint 1: || Minden szigetet csak azután lehet felfedezni, hogy az őt felfedező sziget már ismert. ||
Hint 2: || Egy csúcs gyerekei saját részfáikkal együtt egymás között tetszőlegesen összekeverhetők. ||
Hint 3: || A megoldás egy részfára: gyerekek részfa-méreteiből multinomiális szorzó, majd a gyerekek megoldásainak szorzata. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

static const long long MOD = 1000000007LL;

long long modPow(long long a, long long e) {
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

    int n;
    cin >> n;
    vector<vector<int>> children(n + 1);
    for (int node = 1; node <= n; ++node) {
        int count;
        cin >> count;
        children[node].resize(count);
        for (int i = 0; i < count; ++i) cin >> children[node][i];
    }

    vector<int> order;
    order.reserve(n);
    vector<int> stack = {1};
    while (!stack.empty()) {
        int node = stack.back();
        stack.pop_back();
        order.push_back(node);
        for (int child : children[node]) stack.push_back(child);
    }

    vector<int> size(n + 1, 1);
    vector<long long> ways(n + 1, 1);
    vector<long long> fact(n + 1, 1), invFact(n + 1, 1);
    for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i % MOD;
    invFact[n] = modPow(fact[n], MOD - 2);
    for (int i = n; i > 0; --i) invFact[i - 1] = invFact[i] * i % MOD;

    for (int idx = n - 1; idx >= 0; --idx) {
        int node = order[idx];
        int childTotal = 0;
        long long cur = 1;
        for (int child : children[node]) {
            childTotal += size[child];
            cur = cur * ways[child] % MOD;
            cur = cur * invFact[size[child]] % MOD;
            size[node] += size[child];
        }
        cur = cur * fact[childTotal] % MOD;
        ways[node] = cur;
    }

    cout << ways[1] % MOD << '\n';
    return 0;
}
