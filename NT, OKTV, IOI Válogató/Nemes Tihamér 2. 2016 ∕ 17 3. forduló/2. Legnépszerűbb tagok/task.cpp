/*
Megoldás lényege:
Mindenki pontosan egy másik tagot tart a legismertebbnek, így minden csúcsból egyetlen él indul: a gráf funkcionális gráf, amelyben a körök egymástól függetlenek. Ha egy csúcsba nem vezet bejövő él, rajta biztosan nincs kör, ezért ezeket sorban eltávolítjuk, és közben a kivezető él célcsúcsának bejövő fokszámát csökkentjük. A megmaradó csúcsok mind körön vannak, és mindegyikből egyetlen kimenő él vezet a maradékban, így minden kör egyszer bejárható. A köröket bejárjuk, és a leghosszabbat írjuk ki; az időigény O(N), mert minden csúcs legfeljebb egyszer kerül a sorba.
*/
/*
Hint 1: || Ha egy tagra senki nem mutat, akkor rajta nem lehet népszerűségi kör. Ilyen tagokat nyugodtan elhagyhatsz, a körök csak a maradékban lehetnek. ||
Hint 2: || Egy elhagyott tag kivezető élének célcsúcsától levonsz egyet a bejövő élek számából; ha ez nullára csökken, az a csúcs is elhagyható. Egy sor (queue) segítségével ezt sorban megteheted. ||
Hint 3: || A maradékban minden tagnak pontosan egy kimenő éle van, így egy tagból indulva a legismertebb tagokat követve előbb-utóbb visszaérsz a kiindulóhoz. Jelöld a bejárt tagokat, hogy minden kört egyszer számolj, és a leghosszabbat tartsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> f(n + 1), indeg(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> f[i];
        ++indeg[f[i]];
    }

    queue<int> q;
    vector<char> alive(n + 1, 1);
    for (int i = 1; i <= n; ++i) if (indeg[i] == 0) q.push(i);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        alive[v] = 0;
        if (--indeg[f[v]] == 0) q.push(f[v]);
    }

    vector<char> vis(n + 1, 0);
    vector<int> best;
    for (int i = 1; i <= n; ++i) {
        if (!alive[i] || vis[i]) continue;
        vector<int> cyc;
        int v = i;
        while (!vis[v]) {
            vis[v] = 1;
            cyc.push_back(v);
            v = f[v];
        }
        if (cyc.size() > best.size()) best = cyc;
    }

    cout << best.size() << '\n';
    for (int i = 0; i < (int)best.size(); ++i) {
        if (i) cout << ' ';
        cout << best[i];
    }
    cout << '\n';
    return 0;
}