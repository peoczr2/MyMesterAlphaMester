/*
Megoldás lényege:
A rácsháló legfeljebb 200 pontot tartalmaz, ezért minden új él felvétele után egyszerűen kiszámolható az összes pontpár távolsága. Egy pontból szélességi bejárással (BFS) a többi pont legkisebb lépésszáma kapható meg, a keresett érték pedig az összes pontból mért legnagyobb távolság (az átmérő). A pontok sorfolytonos számozásából a sor és oszlop szomszédai egyszerűen adódnak, az új éleket mindkét irányban felvesszük. Az időigény K·NM·(NM + él), ami legfeljebb kb. 2·10^7 lépés, így az 0.5 mp-es korlát bőven teljesül.
*/
/*
Hint 1: || Mivel legfeljebb 200 pont van, minden új él után kiszámolhatod az összes pont közötti távolságot, nem kell okos gyorsítás. ||
Hint 2: || Egy pontból a szélességi bejárás (BFS) adja meg a többi pont legkisebb lépésszámát; az összes kiindulópontra futtatva a legnagyobb talált távolság lesz a keresett szám. ||
Hint 3: || A v pont (1-től számozva) sorát a (v−1) / M, oszlopát a (v−1) % M adja; a jobbra és lefelé lévő szomszédokat rácsélként vedd fel, az új éleket pedig mindkét irányban. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    const int total = n * m;
    vector<vector<int>> adj(total);
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            int v = r * m + c;
            if (c + 1 < m) {
                adj[v].push_back(v + 1);
                adj[v + 1].push_back(v);
            }
            if (r + 1 < n) {
                adj[v].push_back(v + m);
                adj[v + m].push_back(v);
            }
        }
    }

    vector<int> dist(total);
    vector<int> queue_(total);
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        adj[x].push_back(y);
        adj[y].push_back(x);

        int diameter = 0;
        for (int s = 0; s < total; s++) {
            fill(dist.begin(), dist.end(), -1);
            int head = 0, tail = 0;
            queue_[tail++] = s;
            dist[s] = 0;
            while (head < tail) {
                int u = queue_[head++];
                for (int v : adj[u]) {
                    if (dist[v] < 0) {
                        dist[v] = dist[u] + 1;
                        queue_[tail++] = v;
                    }
                }
            }
            for (int v = 0; v < total; v++)
                diameter = max(diameter, dist[v]);
        }
        cout << diameter << '\n';
    }
    return 0;
}
