/*
Megoldás lényege:
A települések fája (N − 1 él, összefüggő, körmentes), a feladat tehát a fa legnagyobb független csúcshalmazának keresése: két szomszédos településen nem lehet üzlet.
Az 1-es településből szélességi bejárással rendezzük a csúcsokat, majd a fordított sorrendben dinamikus programozással számolunk.
take[v] a legnagyobb üzletszám a v részfájában, ha v-ben van üzlet: 1 + a gyerekek skip-értékeinek összege.
skip[v] ugyanez, ha v-ben nincs üzlet: a gyerekek max(take, skip) értékeinek összege.
A gyökér optimumából fentről lefelé haladva visszafejtjük a kiválasztott településeket; több megoldás lehet, a feladat szerint bármelyik megadható.
Az időigény O(N).
*/
/*
Hint 1: || A települések fája, ezért gyökérből (például az 1-es településből) indulva a levelektől a gyökér felé haladva a részfák egymástól függetlenül számolhatók. ||
Hint 2: || Minden településhez két értéket tarts nyilván: a legnagyobb üzletszámot, ha ott van üzlet (akkor a gyerekeknél nincs), és ha nincs (akkor a gyerekeknél szabadon dönthetsz). ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Gyökérből (1) szélességi bejárás: szülők és feldolgozási sorrend
    vector<int> order, parent(n + 1, 0);
    vector<char> seen(n + 1, 0);
    order.reserve(n);
    order.push_back(1);
    seen[1] = 1;
    for (size_t idx = 0; idx < order.size(); ++idx) {
        int u = order[idx];
        for (int v : adj[u]) {
            if (!seen[v]) {
                seen[v] = 1;
                parent[v] = u;
                order.push_back(v);
            }
        }
    }

    // take[v]: legnagyobb üzletszám a v részfájában, ha v-ben van üzlet
    // skip[v]: ugyanez, ha v-ben nincs üzlet
    vector<int> take(n + 1, 0), skip(n + 1, 0);
    for (int idx = n - 1; idx >= 0; --idx) {
        int u = order[idx];
        take[u] = 1;
        skip[u] = 0;
        for (int v : adj[u]) {
            if (v == parent[u]) continue;
            take[u] += skip[v];
            skip[u] += max(take[v], skip[v]);
        }
    }

    // Fentről lefelé visszafejtés
    vector<char> chosen(n + 1, 0);
    chosen[1] = take[1] >= skip[1];
    vector<int> res;
    for (int u : order) {
        if (chosen[u]) res.push_back(u);
        for (int v : adj[u]) {
            if (v == parent[u]) continue;
            chosen[v] = chosen[u] ? 0 : (take[v] >= skip[v]);
        }
    }
    sort(res.begin(), res.end());

    cout << res.size() << '\n';
    for (size_t i = 0; i < res.size(); ++i) {
        if (i) cout << ' ';
        cout << res[i];
    }
    cout << '\n';
    return 0;
}
