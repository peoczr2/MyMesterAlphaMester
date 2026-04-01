#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
A főnök az egyetlen olyan tag, akinek nincs közvetlen felettese. Ezt egyszerűen
az összes kapcsolatból ki lehet olvasni.

A legtöbb közvetlen beosztottal rendelkező tag a legnagyobb kifokú csúcs. A
„legmesszebb” levő tag pedig a főnöktől mért legnagyobb mélységű csúcs.

Hint 1: || A főnök az egyetlen, aki nem szerepel felettesként máshol. ||
Hint 2: || A legtöbb beosztottat a közvetlen gyerekek száma adja. ||
Hint 3: || A legmesszebb levő tag a fa legmélyebb pontja. ||
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> boss(N + 1, 0), deg(N + 1, 0);
    vector<vector<int>> children(N + 1);
    for (int i = 0; i < N - 1; ++i) {
        int s, f;
        cin >> s >> f;
        boss[s] = f;
        children[f].push_back(s);
        ++deg[f];
    }

    int root = 1;
    for (int i = 1; i <= N; ++i) if (boss[i] == 0) root = i;

    int bestDegNode = 1;
    for (int i = 1; i <= N; ++i) {
        if (deg[i] > deg[bestDegNode] || (deg[i] == deg[bestDegNode] && i < bestDegNode)) bestDegNode = i;
    }

    vector<int> depth(N + 1, -1);
    queue<int> q;
    depth[root] = 0;
    q.push(root);
    int farNode = root;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (depth[u] > depth[farNode] || (depth[u] == depth[farNode] && u < farNode)) farNode = u;
        for (int v : children[u]) {
            depth[v] = depth[u] + 1;
            q.push(v);
        }
    }

    cout << root << '\n' << bestDegNode << '\n' << farNode << '\n';
    return 0;
}