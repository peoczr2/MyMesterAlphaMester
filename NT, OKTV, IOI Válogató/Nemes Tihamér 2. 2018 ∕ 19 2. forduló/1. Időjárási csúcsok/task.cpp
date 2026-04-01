#include <bits/stdc++.h>
using namespace std;

/*
    Előre kiszámoljuk, hogy mely napok lokális csúcsok és mélypontok.
    Ezután prefixösszegekkel megszámoljuk, hány olyan intervallum van,
    amelyben pontosan K csúcs és L mélypont szerepel.
*/

struct Key {
    int a, b;
    bool operator==(const Key& other) const { return a == other.a && b == other.b; }
};

struct Hash {
    size_t operator()(const Key& k) const {
        return (static_cast<size_t>(k.a) << 32) ^ static_cast<unsigned>(k.b);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, l;
    cin >> n >> k >> l;
    vector<int> h(n + 1);
    for (int i = 1; i <= n; ++i) cin >> h[i];

    vector<int> peak(n + 1, 0), valley(n + 1, 0);
    for (int i = 2; i <= n - 1; ++i) {
        if (h[i] > h[i - 1] && h[i] > h[i + 1]) peak[i] = 1;
        if (h[i] < h[i - 1] && h[i] < h[i + 1]) valley[i] = 1;
    }

    unordered_map<Key, long long, Hash> cnt;
    cnt.reserve(n * 2 + 10);
    cnt[{0, 0}] = 1;

    long long ans = 0;
    int cp = 0, cv = 0;
    for (int i = 1; i <= n - 1; ++i) {
        cp += peak[i];
        cv += valley[i];
        Key need{cp - k, cv - l};
        auto it = cnt.find(need);
        if (it != cnt.end()) ans += it->second;
        cnt[{cp, cv}]++;
    }

    cout << ans << '\n';
    return 0;
}