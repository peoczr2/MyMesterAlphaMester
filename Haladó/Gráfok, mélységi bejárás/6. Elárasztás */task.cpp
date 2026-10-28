/*
Megoldás lényege:
A sziget szegélyéről indulva min-max bejárással (prioritásos sorral) minden cellához kiszámoljuk lb(x) értékét: a legkisebb szintet, amelyen x-ből a víz lefolyhat a szigetről. A forrás vízszintje legfeljebb lam = lb(forrás) lehet, mert ennél magasabbra emelkedve a víz kifolyik. A forrásból csak a lam-nál nem magasabb cellákon át jut el a víz, ezekben a cellákban a víz szintje min(lb(x), lam), a vízoszlop magassága pedig ennek és a cella magasságának a különbsége. Az összes vízoszlopot összegezzük, a különböző vízszintek számát pedig halmazba gyűjtjük. Az időigény O(NM log(NM)).
*/
/*
Hint 1: || Gondolj a szigetre tartályok halmazaként: a szegélyen túl a víz lefolyik. Minden cellához az számít, hogy a szegélyig vezető utak közül melyiken a legmagasabb pont a legalacsonyabb. ||
Hint 2: || Ezt prioritásos sorral számold ki a szegélyről befelé: egy szomszéd szintje max(saját magassága, az éppen kivett cella szintje). A víz a forrás szintjénél magasabbra nem emelkedik, ezért a forrásból a lam-nál nem magasabb cellákon át BFS-sel gyűjtsd össze az elárasztott cellákat, és mindegyikben a víz mennyisége min(szint, lam) mínusz a magasság. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> h((size_t)n * m);
    for (int& x : h) cin >> x;
    int sr, sc;
    cin >> sr >> sc;
    int s = (sr - 1) * m + (sc - 1);

    // 1. min-max bejárás a szegélyről: lb[x] = legkisebb szint, amelyen x-ből a víz lefolyhat
    vector<int> lb(h.size());
    vector<char> vis(h.size(), 0);
    // kulcs: (szint << 20) | cella-azonosító, így egy egész szám a prioritásos sor eleme
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    const long long MASK = (1LL << 20) - 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                int id = i * m + j;
                vis[id] = 1;
                lb[id] = h[id];
                pq.push(((long long)h[id] << 20) | id);
            }
        }
    }
    const int di[4] = {1, -1, 0, 0};
    const int dj[4] = {0, 0, 1, -1};
    while (!pq.empty()) {
        long long key = pq.top();
        pq.pop();
        int lv = (int)(key >> 20);
        int id = (int)(key & MASK);
        int i = id / m, j = id % m;
        for (int d = 0; d < 4; d++) {
            int ni = i + di[d], nj = j + dj[d];
            if (ni < 0 || nj < 0 || ni >= n || nj >= m) continue;
            int nid = ni * m + nj;
            if (vis[nid]) continue;
            vis[nid] = 1;
            lb[nid] = max(h[nid], lv);
            pq.push(((long long)lb[nid] << 20) | nid);
        }
    }

    // 2. a forrás vízszintje legfeljebb lam; ide csak a lam-nál nem magasabb cellákon át jut a víz
    const int lam = lb[s];
    vector<char> fed(h.size(), 0);
    vector<int> q;
    q.push_back(s);
    fed[s] = 1;
    for (size_t qi = 0; qi < q.size(); qi++) {
        int id = q[qi];
        int i = id / m, j = id % m;
        for (int d = 0; d < 4; d++) {
            int ni = i + di[d], nj = j + dj[d];
            if (ni < 0 || nj < 0 || ni >= n || nj >= m) continue;
            int nid = ni * m + nj;
            if (!fed[nid] && h[nid] <= lam) {
                fed[nid] = 1;
                q.push_back(nid);
            }
        }
    }

    // 3. vízmennyiség és a különböző vízszintek száma
    long long water = 0;
    vector<int> levels;
    for (int id : q) {
        int lvl = min(lb[id], lam);
        if (lvl > h[id]) {
            water += lvl - h[id];
            levels.push_back(lvl);
        }
    }
    sort(levels.begin(), levels.end());
    levels.erase(unique(levels.begin(), levels.end()), levels.end());

    cout << water << '\n';
    cout << levels.size() << '\n';
    return 0;
}
