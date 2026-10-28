/*
Megoldás lényege:
Minden vízszintes autópályát egy sor (azonos második koordináta), minden függőlegeset egy oszlop (azonos első koordináta) egyszer kell megépíteni, ez összesen b·(R+C) költség, ahol R a különböző Y-értékek, C a különböző X-értékek száma. A bejárt városok száma a fix költségtől függetlenül minimalizálandó: a városok lesznek a kétoldalú gráf (oszlopok – sorok) élei, és egy halmaz akkor jó, ha minden sort és minden oszlopot lefed. Minimális élefedés mérete = csúcsok száma − maximális párosítás, ezért a válasz a·(R+C−ν) + b·(R+C), ahol ν a maximális párosítás. A párosítást Hopcroft–Karp algoritmussal számoljuk, O(E·√V) időben, ami 50 000 városra bőven belefér.
*/
/*
Hint 1: || Gondolj a városokra úgy, mint élekre egy kétoldalú gráfban: a bal oldalon az X-értékek, a jobb oldalon az Y-értékek állnak, és a város az (X_i, Y_i) pár éle. Azt kell megnézned, hogy a bejárt városok hány sort és oszlopot fednek le. ||
Hint 2: || Minden sorhoz és oszlophoz pontosan egy autópálya kell, ezért az építési költség b·(R+C) fix. A változó rész a bejárt városok száma: a legkevesebb élből álló élefedést keresd. Ennek mérete a csúcsok száma mínusz a maximális párosítás. ||
Hint 3: || A maximális párosítást Hopcroft–Karp algoritmussal számold ki: BFS-sel rétegezed a gráfot, DFS-sel keresel növelő utakat. Az X- és Y-értékeket előbb tömörítsd 0-tól induló indexekre (sort/lower_bound). ||
*/
#include <bits/stdc++.h>
using namespace std;

int nL, nR;
vector<vector<int>> g;
vector<int> pairL, pairR, dist_, itp;

bool bfs() {
    queue<int> q;
    bool found = false;
    for (int u = 0; u < nL; u++) {
        if (pairL[u] == -1) {
            dist_[u] = 0;
            q.push(u);
        } else {
            dist_[u] = -1;
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            int w = pairR[v];
            if (w == -1) {
                found = true;
            } else if (dist_[w] == -1) {
                dist_[w] = dist_[u] + 1;
                q.push(w);
            }
        }
    }
    return found;
}

bool dfs(int u) {
    for (int &k = itp[u]; k < (int)g[u].size(); k++) {
        int v = g[u][k];
        int w = pairR[v];
        if (w == -1 || (dist_[w] == dist_[u] + 1 && dfs(w))) {
            pairL[u] = v;
            pairR[v] = u;
            k++;
            return true;
        }
    }
    dist_[u] = -1;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long a, b;
    cin >> n >> a >> b;

    vector<int> xs(n), ys(n);
    for (int i = 0; i < n; i++) {
        cin >> xs[i] >> ys[i];
    }

    vector<int> sx = xs, sy = ys;
    sort(sx.begin(), sx.end());
    sx.erase(unique(sx.begin(), sx.end()), sx.end());
    sort(sy.begin(), sy.end());
    sy.erase(unique(sy.begin(), sy.end()), sy.end());

    nL = sx.size();
    nR = sy.size();
    g.assign(nL, {});
    for (int i = 0; i < n; i++) {
        int x = lower_bound(sx.begin(), sx.end(), xs[i]) - sx.begin();
        int y = lower_bound(sy.begin(), sy.end(), ys[i]) - sy.begin();
        g[x].push_back(y);
    }

    pairL.assign(nL, -1);
    pairR.assign(nR, -1);
    dist_.assign(nL, -1);
    itp.assign(nL, 0);

    int matching = 0;
    while (bfs()) {
        fill(itp.begin(), itp.end(), 0);
        for (int u = 0; u < nL; u++) {
            if (pairL[u] == -1 && dfs(u)) {
                matching++;
            }
        }
    }

    long long cover = (long long)(nL + nR) - matching;
    long long ans = a * cover + b * (long long)(nL + nR);
    cout << ans << "\n";
    return 0;
}
