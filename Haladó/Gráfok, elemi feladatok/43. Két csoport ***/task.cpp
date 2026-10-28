/*
Megoldás lényege: kezdetben mindenki ugyanabban a csoportban van, majd addig javítgatunk, amíg van olyan résztvevő, akinek legalább két nem kedvelt társa van a saját csoportjában.
Az ilyen résztvevőt átrakjuk a másik csoportba. Ekkor az azonos csoportban lévő nem kedvelés-párok száma legalább eggyel csökken, mert a fokszám legfeljebb 3, így a folyamat véges.
A javítás után minden résztvevőnek legfeljebb egy nem kedvelt társa marad a csoportjában. Minden áthelyezés néhány művelet, és legfeljebb M áthelyezés történik, így az időigény O(N+M).
*/
/*
Hint 1: || Kezdjük azzal, hogy mindenki ugyanabba a csoportba kerül. Számoljuk meg minden résztvevőre, hány nem kedvelt társa van ugyanabban a csoportban. ||
Hint 2: || Ha valakinek legalább két ilyen társa van, vigyük át a másik csoportba. Ekkor az azonos csoportbeli nem kedvelés-párok száma csökken, ezért a folyamat véget ér. Tartsunk egy listát azokról, akiknek a száma már legalább kettő. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // A nemkedvelések kölcsönösek; a bemenet mégis tartalmazhat aszimmetriát,
    // ezért minden párt egyszer, mindkét irányból vesszük figyelembe.
    vector<long long> keys;
    keys.reserve(3 * (size_t)n);
    for (int i = 1; i <= n; i++) {
        while (true) {
            int x;
            cin >> x;
            if (x == 0) break;
            long long a = min(i, x), b = max(i, x);
            keys.push_back(a * (n + 1) + b);
        }
    }
    sort(keys.begin(), keys.end());
    keys.erase(unique(keys.begin(), keys.end()), keys.end());

    vector<pair<int, int>> edges;
    edges.reserve(keys.size());
    vector<int> deg(n + 2, 0);
    for (long long k : keys) {
        int a = (int)(k / (n + 1)), b = (int)(k % (n + 1));
        edges.push_back({a, b});
        deg[a]++;
        deg[b]++;
    }

    // Szomszédsági lista tömbben (CSR): a v csúcs szomszédai adj[start[v] .. start[v+1]-1].
    vector<int> start(n + 2, 0);
    for (int v = 1; v <= n; v++) start[v + 1] = start[v] + deg[v];
    vector<int> adj(start[n + 1]);
    vector<int> fillp(start.begin(), start.end());
    for (auto [a, b] : edges) {
        adj[fillp[a]++] = b;
        adj[fillp[b]++] = a;
    }

    vector<int> color(n + 1, 0);
    vector<int> same(n + 1, 0);  // azonos csoportban lévő nem kedvelt társak száma
    for (int v = 1; v <= n; v++) same[v] = deg[v];

    vector<int> stk;
    for (int v = 1; v <= n; v++) {
        if (same[v] >= 2) stk.push_back(v);
    }
    while (!stk.empty()) {
        int v = stk.back();
        stk.pop_back();
        if (same[v] < 2) continue;

        color[v] ^= 1;
        same[v] = deg[v] - same[v];
        for (int e = start[v]; e < start[v + 1]; e++) {
            int u = adj[e];
            if (color[u] == color[v]) {
                if (++same[u] >= 2) stk.push_back(u);
            } else {
                same[u]--;
            }
        }
    }

    vector<int> group;
    for (int v = 1; v <= n; v++) {
        if (color[v] == 0) group.push_back(v);
    }
    cout << group.size() << '\n';
    for (size_t i = 0; i < group.size(); i++) {
        if (i) cout << ' ';
        cout << group[i];
    }
    cout << '\n';
    return 0;
}
