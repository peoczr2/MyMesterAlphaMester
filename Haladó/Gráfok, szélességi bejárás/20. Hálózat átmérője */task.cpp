/*
Megoldás lényege:
A hálózat N csúcsú fa (N-1 él, bármely két csúcs között pontosan egy út), ezért az átmérő két szélességi bejárással meghatározható. Először egy tetszőleges csúcsból (például 1-ből) bejárjuk a fát, és megkeressük a tőle legtávolabbi csúcsot; ez biztosan az átmérő egyik végpontja. Ezután erről a csúcsról újra bejárást végzünk, és a kapott legnagyobb távolság lesz a keresett átmérő. Mindkét bejárás O(N) időt igényel, ami N ≤ 10 000 mellett messze belefér az időlimitbe.
*/
/*
Hint 1: || Mivel a hálózat fa, két csomópont távolsága egyszerű szélességi bejárással kiszámítható egy kiinduló csomópontból. ||
Hint 2: || Egy tetszőleges csomópontból indított bejárásban a legtávolabbi csomópont az átmérő egyik végpontja; a második bejárást már innen indítsd, és a legnagyobb távolságot írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Szélességi bejárás a fában: visszaadja a legtávolabbi csúcsot és a távolságát.
pair<int, int> farthest(int start, const vector<vector<int>>& adj, int n) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    int best = start;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (dist[v] > dist[best]) best = v;
        for (int u : adj[v]) {
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
    return {best, dist[best]};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int endpoint = farthest(1, adj, n).first;
    int diameter = farthest(endpoint, adj, n).second;
    cout << diameter << "\n";
    return 0;
}
