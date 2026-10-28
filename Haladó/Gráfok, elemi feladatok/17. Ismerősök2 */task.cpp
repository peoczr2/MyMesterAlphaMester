/*
Megoldás lényege:
Az ismeretségeket szomszédsági bitsetekben tároljuk (N ≤ 200), így két ember közös ismerőseit a két halmaz metszete adja.
A-hoz minden ismerős (u, v) párra ellenőrizzük, hogy a metszet üres-e: ha igen, nincs más közös ismerősük.
B-hez minden nem ismerős (u, v) párra azt nézzük, hogy a két szomszédsági halmaz egyenlő-e: ekkor minden ismerősük közös (az üres halmaz is megfelel).
A párokat u, majd v szerint növekvő sorrendben járjuk be, így a kimenet lexikografikusan rendezett.
Az idő O(N^2 · N/64 + M), ami bőven belefér a 0,1 mp-be.
*/
/*
Hint 1: || Két ember közös ismerőseit úgy kapod meg, hogy a szomszédsági halmazaikat bitenként ÉS-eled; ehhez bitset<256> jól használható. ||
Hint 2: || A B részfeladatnál egy nem ismerős pár akkor jó, ha a két szomszédsági halmaz pontosan megegyezik, és az üres halmaz is megfelel. ||
Hint 3: || A párokat u, majd v szerinti növekvő sorrendben végigjárva a kimenet már rendezett lesz, külön rendezésre nincs szükség. ||
*/
#include <bits/stdc++.h>
using namespace std;

void printPairs(const vector<pair<int, int>>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        if (i) cout << ' ';
        cout << v[i].first << ' ' << v[i].second;
    }
    cout << '\n';
}

int main() {
    int n;
    long long m;
    cin >> n >> m;
    vector<bitset<256>> nb(n + 1);
    vector<vector<bool>> adj(n + 1, vector<bool>(n + 1, false));
    for (long long i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (u == v) continue;
        adj[u][v] = adj[v][u] = true;
        nb[u][v] = 1;
        nb[v][u] = 1;
    }

    vector<pair<int, int>> a, b;
    for (int u = 1; u <= n; u++) {
        for (int v = u + 1; v <= n; v++) {
            if (adj[u][v]) {
                if ((nb[u] & nb[v]).none()) a.push_back({u, v});
            } else {
                if (nb[u] == nb[v]) b.push_back({u, v});
            }
        }
    }

    cout << a.size() << '\n';
    printPairs(a);
    cout << b.size() << '\n';
    printPairs(b);
    return 0;
}
