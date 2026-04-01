/*
A barátság reláció tranzitív lezárása miatt az összefüggő komponensek gyermekei nem választhatók szét: egy komponens
egészben kerül az egyik vagy a másik csoportba. Így a feladat a komponensméretek két részre osztásává egyszerűsödik,
ahol a cél a két összeg különbségének minimalizálása. Egy klasszikus részösszeg-DP megadja, mely összeg érhető el, és a
szülőtáblából az egyik optimális csoport komponensei visszafejthetők.
*/
/*
Hint 1: || Először vond össze azokat, akiknek mindenképp együtt kell maradniuk. ||
Hint 2: || Ezután már csak komponensméreteket kell két halmazba szétosztani. ||
Hint 3: || A nagyobbik csoportot kell kiírni, ezért a végén lehet, hogy a kiválasztott részhalmaz komplementjét kell venned. ||
*/

#include <bits/stdc++.h>

using namespace std;

struct DSU {
    vector<int> parent, sz;

    explicit DSU(int n) : parent(n + 1), sz(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return;
        }
        if (sz[a] < sz[b]) {
            swap(a, b);
        }
        parent[b] = a;
        sz[a] += sz[b];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        dsu.unite(a, b);
    }

    vector<vector<int>> comps;
    unordered_map<int, int> id;
    for (int v = 1; v <= n; ++v) {
        int root = dsu.find(v);
        if (!id.count(root)) {
            id[root] = (int)comps.size();
            comps.push_back({});
        }
        comps[id[root]].push_back(v);
    }

    int c = (int)comps.size();
    vector<char> reach(n + 1, 0);
    vector<int> from_sum(n + 1, -1), from_comp(n + 1, -1);
    reach[0] = 1;

    for (int i = 0; i < c; ++i) {
        int sz = (int)comps[i].size();
        for (int s = n; s >= sz; --s) {
            if (!reach[s] && reach[s - sz]) {
                reach[s] = 1;
                from_sum[s] = s - sz;
                from_comp[s] = i;
            }
        }
    }

    int best_sum = 0;
    int best_diff = n;
    for (int s = 0; s <= n; ++s) {
        if (!reach[s]) {
            continue;
        }
        int diff = abs(n - 2 * s);
        if (diff < best_diff) {
            best_diff = diff;
            best_sum = s;
        }
    }

    vector<char> chosen_comp(c, 0);
    for (int s = best_sum; s > 0; s = from_sum[s]) {
        chosen_comp[from_comp[s]] = 1;
    }

    vector<int> group_a, group_b;
    for (int i = 0; i < c; ++i) {
        if (chosen_comp[i]) {
            group_a.insert(group_a.end(), comps[i].begin(), comps[i].end());
        } else {
            group_b.insert(group_b.end(), comps[i].begin(), comps[i].end());
        }
    }

    vector<int>& answer = (group_a.size() >= group_b.size() ? group_a : group_b);
    cout << best_diff << '\n';
    for (int i = 0; i < (int)answer.size(); ++i) {
        if (i) {
            cout << ' ';
        }
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}
