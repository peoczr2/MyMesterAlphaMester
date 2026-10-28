/*
Megoldás lényege:
Bármely feszítőfa mélységi bejárásából (Euler-séta) kapunk megfelelő sétát: a csúcsra belépéskor kiírjuk a csúcsot, és minden gyerekből való visszatérés után újra kiírjuk. Egy csúcs ilyenkor annyiszor szerepel, ahány gyereke van, plusz egyszer. Mivel a kiindulási részleg foka legfeljebb 2, a többi részleg foka pedig legfeljebb 3, a gyerekek száma legfeljebb 2, így minden részleg legfeljebb háromszor szerepel. Az út az 1-es részlegnél kezdődik és végződik, a szomszédos elemek között pedig fél út van. Az időigény O(N+M).
*/
/*
Hint 1: || Nem kell optimális útvonal, elég egy olyan séta, amely a feszítőfa éleit használja. Egy fa Euler-bejárása, vagyis a gyerekekből való visszatérés kiírása, már önmagában megfelelő lehet. ||
Hint 2: || Ha a DFS-fában a csúcsnak c gyereke van, akkor a csúcs c+1-szer szerepel a sétában, és egy nem-gyökér csúcsnak legfeljebb két gyereke lehet, a gyökérnek is legfeljebb kettő. Használj mélységi bejárást, és minden gyerekből visszatérve írd ki a szülő sorszámát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;
vector<char> vis;
vector<int> walk;

void dfs(int u) {
    walk.push_back(u);
    for (int v : adj[u]) {
        if (vis[v]) continue;
        vis[v] = 1;
        dfs(v);
        walk.push_back(u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    adj.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vis.assign(n + 1, 0);
    vis[1] = 1;
    dfs(1);
    for (size_t i = 0; i < walk.size(); i++) cout << walk[i] << (i + 1 < walk.size() ? ' ' : '\n');
    return 0;
}
