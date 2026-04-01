/*
Megoldás lényege:
Egy téglalap jó akkor és csak akkor, ha a kiválasztott A-sorok minimuma legalább a kiválasztott
B-oszlopok maximuma. Ha egy küszöbértéket t fixálunk, akkor az A-ban a t-nél nem kisebb elemek,
a B-ben pedig a t-nél nem nagyobb elemek aktívak.

Az aktív pozíciók leghosszabb összefüggő szakaszát union-finddel követjük, és minden küszöbre
összeszorozzuk az A és B oldali leghosszabb szakaszhosszt.
*/
// Hint 1: || Egy jó téglalap feltétele: min(A a sorokban) >= max(B az oszlopokban). ||
// Hint 2: || Fix küszöb mellett az aktív helyek leghosszabb összefüggő szakasza kell mindkét sorozatban. ||
// Hint 3: || A küszöböket az értékek szerint rendezve lehet végigaktiválni. ||

#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, sz;
    int best = 0;
    void init(int n) {
        p.assign(n + 2, 0);
        sz.assign(n + 2, 0);
        best = 0;
    }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void activate(int x) {
        p[x] = x;
        sz[x] = 1;
        best = max(best, 1);
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        best = max(best, sz[a]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<long long> A(N + 1), B(M + 1);
    for (int i = 1; i <= N; ++i) cin >> A[i];
    for (int j = 1; j <= M; ++j) cin >> B[j];

    vector<long long> vals;
    vals.reserve(N + M);
    for (int i = 1; i <= N; ++i) vals.push_back(A[i]);
    for (int j = 1; j <= M; ++j) vals.push_back(B[j]);
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    vector<pair<long long,int>> ordA, ordB;
    ordA.reserve(N); ordB.reserve(M);
    for (int i = 1; i <= N; ++i) ordA.push_back({A[i], i});
    for (int j = 1; j <= M; ++j) ordB.push_back({B[j], j});
    sort(ordA.begin(), ordA.end(), greater<>());
    sort(ordB.begin(), ordB.end());

    unordered_map<long long,int> bestA, bestB;
    bestA.reserve(vals.size() * 2 + 1);
    bestB.reserve(vals.size() * 2 + 1);

    DSU dA, dB;
    dA.init(N);
    dB.init(M);
    vector<char> actA(N + 2, 0), actB(M + 2, 0);

    int pa = 0;
    for (auto it = vals.rbegin(); it != vals.rend(); ++it) {
        long long t = *it;
        while (pa < N && ordA[pa].first >= t) {
            int idx = ordA[pa].second;
            actA[idx] = 1;
            dA.activate(idx);
            if (idx > 1 && actA[idx - 1]) dA.unite(idx, idx - 1);
            if (idx < N && actA[idx + 1]) dA.unite(idx, idx + 1);
            ++pa;
        }
        bestA[t] = dA.best;
    }

    int pb = 0;
    for (long long t : vals) {
        while (pb < M && ordB[pb].first <= t) {
            int idx = ordB[pb].second;
            actB[idx] = 1;
            dB.activate(idx);
            if (idx > 1 && actB[idx - 1]) dB.unite(idx, idx - 1);
            if (idx < M && actB[idx + 1]) dB.unite(idx, idx + 1);
            ++pb;
        }
        bestB[t] = dB.best;
    }

    long long ans = 0;
    for (long long t : vals) ans = max(ans, 1LL * bestA[t] * bestB[t]);
    cout << ans << '\n';
    return 0;
}