/*
Megoldás lényege:
A városok azok a települések, amelyek valamilyen körön rajta vannak: ezek között
bármely két városhoz két élükben különböző út vezet. A tanyák ezen kívül esnek,
és mindegyik egyetlen úton keresztül csatlakozik egy városhoz. A városokat úgy
kapjuk meg, hogy a legfeljebb egy élű csomópontokat (leveleket) ismételten
eltávolítjuk; ami a végén marad, az a városok halmaza. Az eltávolított
csomópontok mindegyike egy fa-szerű ágon csatlakozik egyetlen városhoz, ezért a
városokból indított többforrásos szélességi bejárás megmutatja, melyik városhoz
tartozik minden tanya. A kimenet a városok sorszáma szerint rendezett, minden
sorban a tanyák sorszámai növekvő sorrendben szerepelnek.
Az időigény O(N + összes út).
*/
/*
Hint 1: || A városok olyan települések, amelyek valamilyen körben benne vannak; a tanyák nem tartoznak körbe, és egyetlen úton kapcsolódnak egy városhoz. ||
Hint 2: || Ismételten távolítsd el azokat a csomópontokat, amelyekből legfeljebb egy út indul ki, és ami a végén marad, az lesz a városok halmaza. ||
Hint 3: || Az eltávolított csomópontokból mindig egyetlen út vezet egy városba, ezért a városokból indított többforrásos szélességi bejárás a tanyákat a helyes városhoz rendeli. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; ++i) {
        int d;
        cin >> d;
        for (int j = 0; j < d; ++j) {
            int s;
            cin >> s;
            adj[i].push_back(s);
            adj[s].push_back(i);
        }
    }
    for (int i = 1; i <= n; ++i) {
        sort(adj[i].begin(), adj[i].end());
        adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
    }

    // Levélnyesés: a körökön kívüli csomópontok eltávolítása.
    vector<int> deg(n + 1);
    for (int i = 1; i <= n; ++i) deg[i] = adj[i].size();

    vector<char> farm(n + 1, 0);
    queue<int> leaves;
    for (int i = 1; i <= n; ++i) {
        if (deg[i] <= 1) {
            farm[i] = 1;
            leaves.push(i);
        }
    }
    while (!leaves.empty()) {
        int u = leaves.front();
        leaves.pop();
        for (int v : adj[u]) {
            if (!farm[v] && --deg[v] <= 1) {
                farm[v] = 1;
                leaves.push(v);
            }
        }
    }

    // Többforrásos szélességi bejárás a városokból: minden tanya a hozzá tartozó városhoz kerül.
    vector<int> owner(n + 1, 0);
    queue<int> bfs;
    for (int i = 1; i <= n; ++i) {
        if (!farm[i]) {
            owner[i] = i;
            bfs.push(i);
        }
    }
    while (!bfs.empty()) {
        int u = bfs.front();
        bfs.pop();
        for (int v : adj[u]) {
            if (owner[v] == 0) {
                owner[v] = owner[u];
                bfs.push(v);
            }
        }
    }

    vector<vector<int>> ranch(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (farm[i] && owner[i] != 0) ranch[owner[i]].push_back(i);
    }

    for (int c = 1; c <= n; ++c) {
        if (farm[c]) continue;
        cout << c << ' ' << ranch[c].size();
        for (int t : ranch[c]) cout << ' ' << t;
        cout << '\n';
    }
    return 0;
}
