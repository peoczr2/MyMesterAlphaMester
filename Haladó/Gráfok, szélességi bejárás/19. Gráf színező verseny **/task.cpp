/*
Megoldás lényege:
A játékot közvetlenül szimuláljuk. Mindkét játékosnak egy sorban (FIFO) tároljuk az elért pontjait, így a legrégebben elért pont van elöl. Minden lépésben mindkét játékos megkeresi a legrégebbi olyan saját pontját, amelynek van festetlen szomszédja, és ennek a legkisebb sorszámú festetlen szomszédját választja. Ha a két választás különbözik, mindkettőt a saját színére festjük és a sorába tesszük; ha egyezik, a pont fehér lesz. Ha az egyik játékos sora kiürül, a másik egyedül folytatja. Minden pont legfeljebb egyszer kerül festésre, így a futásidő O(N·M) alatt marad.
*/
/*
Hint 1: || Mindkét játékosnak egy FIFO sort érdemes tartani, amelynek az elején a legrégebbi pont van; a jelölt mindig az első olyan pont szomszédja, amelynek még van festetlen szomszédja. ||
Hint 2: || A két jelöltet a lépés elején állapítsd meg, és csak utána fess: így a két választás egyszerre történik, és az egyező jelölt könnyen felismerhető. ||
Hint 3: || Ha az egyik sor kiürül, a másik játékos ugyanúgy választ, de ellenfél nélkül: a lépésben csak a saját jelöltjét festi. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, p, z;
    cin >> n >> m >> p >> z;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (auto& nb : adj) sort(nb.begin(), nb.end());

    // 0: festetlen, 1: piros (P), 2: zöld (Z), 3: fehér (semleges)
    vector<int> color(n + 1, 0);
    deque<int> redQ, greenQ;   // elért pontok, a legrégebbi van elöl
    color[p] = 1;
    redQ.push_back(p);
    color[z] = 2;
    greenQ.push_back(z);

    // A sor legrégebbi pontjának legkisebb festetlen szomszédja (vagy -1).
    // A kimerült pontokat (nincs festetlen szomszédjuk) véglegesen kivesszük a sorból.
    auto candidate = [&](deque<int>& q) -> int {
        while (!q.empty()) {
            for (int v : adj[q.front()]) {
                if (color[v] == 0) return v;
            }
            q.pop_front();
        }
        return -1;
    };

    while (true) {
        int cr = candidate(redQ);
        int cg = candidate(greenQ);
        if (cr == -1 && cg == -1) break;

        if (cr != -1 && cg != -1 && cr == cg) {
            color[cr] = 3;   // mindkét játékos ugyanazt választotta: fehér lesz
        } else {
            if (cr != -1) {
                color[cr] = 1;
                redQ.push_back(cr);
            }
            if (cg != -1) {
                color[cg] = 2;
                greenQ.push_back(cg);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        char c = color[i] == 1 ? 'P' : (color[i] == 2 ? 'Z' : 'F');
        cout << c << (i == n ? '\n' : ' ');
    }
    return 0;
}
