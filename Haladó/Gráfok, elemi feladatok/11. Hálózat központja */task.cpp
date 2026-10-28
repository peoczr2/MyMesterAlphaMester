/*
Megoldás lényege:
Fában bármely csúcs legtávolabbi csúcsa az átmérő valamelyik végpontja, így a c csúcs excentricitása max(d(c,a), d(c,b)), ahol a és b egy legnagyobb távolságú csúcspár. A központ ennek az a–b útnak a közepén van: az út D hosszú, és a D/2 távolságra lévő csúcs excentricitása a legkisebb. Az a és b csúcsokat két szélességi bejárással keressük: az 1-es csúcsból a legtávolabbi a, abból a legtávolabbi b adódik, közben a szülőket is megjegyezzük. A b csúcsból a szülőkön visszalépve a közepet megtaláljuk. Az idő O(N).
*/
/*
Hint 1: || Egy csúcs legtávolabbi csúcsa mindig a fa egyik átmérő-végpontja. Keress tehát két olyan csúcsot, amelyek távolsága a legnagyobb. ||
Hint 2: || Két szélességi bejárás elég: az 1-esből a legtávolabbi a, abból a legtávolabbi b. A b-ből a szülők mentén D - D/2 lépést visszafelé menve (D az a és b távolsága) a központot kapod. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Szélességi bejárás: a távolságokat és a bejárási fában a szülőket adja vissza.
void bfs(int start, const vector<vector<int>>& adj, vector<int>& dist, vector<int>& parent) {
    int n = (int)adj.size() - 1;
    dist.assign(n + 1, -1);
    parent.assign(n + 1, 0);
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : adj[v]) {
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                parent[u] = v;
                q.push(u);
            }
        }
    }
}

int farthest(const vector<int>& dist) {
    int best = 1;
    for (int v = 2; v < (int)dist.size(); v++) {
        if (dist[v] > dist[best]) best = v;
    }
    return best;
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

    vector<int> dist, parent;
    bfs(1, adj, dist, parent);
    int a = farthest(dist);

    bfs(a, adj, dist, parent);
    int b = farthest(dist);
    int D = dist[b];

    int center = b;
    for (int s = 0; s < D - D / 2; s++) center = parent[center];

    cout << center << "\n";
    return 0;
}
