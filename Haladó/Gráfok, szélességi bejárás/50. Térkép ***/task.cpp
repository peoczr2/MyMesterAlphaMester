/*
Megoldás lényege:
A feladat két független minimumot kér, mindkettőt a térkép mezőin keresett legrövidebb úttal.
Az érintett országok számához egy országgráfot építünk: két ország között él van, ha a térképen határosak, és az országgráfon BFS adja a legkevesebb országot érintő út távolságát; az érintett országok száma ez a távolság plusz egy, mert a kezdő és a végső országot is számoljuk.
Az útlevél-ellenőrzéses határok minimumához a rácsmezőkön 0-1 BFS-t futtatunk: két szomszédos mező közötti lépés költsége 0, ha azonos országban vannak vagy a határukon nincs útlevél-ellenőrzés, egyébként 1.
A 0-1 BFS deque-val fut, így az egész megoldás a térkép méretével arányos időben, a 0.1 mp-es időlimiten belül marad.
*/
/*
Hint 1: || Két külön kérdés van: az érintett országok számát és az ellenőrzött határok számát kell minimalizálni, és mindkettőt egy szomszédsági gráf legrövidebb útjával kapod meg. ||
Hint 2: || Az országok számához tekintsd az országokat csúcsoknak: két ország között él van, ha a térképen határosak. Ha az országgráfon a kezdő és a cél ország távolsága d, akkor az érintett országok száma d+1. ||
Hint 3: || Az ellenőrzött határok számához a mezőkön futtass 0-1 BFS-t. Egy lépés költsége 0, ha a két mező azonos országhoz tartozik vagy a két ország határán nincs ellenőrzés; különben 1. A 0 költségű lépéseket a deque elejére tedd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, sz;
    cin >> n >> m >> sz;

    vector<vector<int>> c(n, vector<int>(m));
    int maxId = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> c[i][j];
            maxId = max(maxId, c[i][j]);
        }
    }

    set<pair<int, int>> freeBorder;
    for (int i = 0; i < sz; i++) {
        int a, b;
        cin >> a >> b;
        freeBorder.insert({min(a, b), max(a, b)});
    }

    int ks, ko, vs, vo;
    cin >> ks >> ko >> vs >> vo;
    ks--; ko--; vs--; vo--;

    const int di[4] = {1, -1, 0, 0};
    const int dj[4] = {0, 0, 1, -1};

    // 1. feladat: országgráf és BFS rajta.
    vector<vector<int>> cadj(maxId + 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 4; k++) {
                int x = i + di[k], y = j + dj[k];
                if (x < 0 || x >= n || y < 0 || y >= m) continue;
                if (c[i][j] != c[x][y]) cadj[c[i][j]].push_back(c[x][y]);
            }
        }
    }
    int sc = c[ks][ko], tc = c[vs][vo];
    vector<int> cdist(maxId + 1, -1);
    queue<int> q;
    cdist[sc] = 0;
    q.push(sc);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : cadj[u]) {
            if (cdist[v] == -1) {
                cdist[v] = cdist[u] + 1;
                q.push(v);
            }
        }
    }
    int countries = cdist[tc] + 1;

    // 2. feladat: 0-1 BFS a mezőkön, az útlevél-ellenőrzéses határok száma a költség.
    auto noCheck = [&](int a, int b) {
        if (a == b) return true;
        return freeBorder.count({min(a, b), max(a, b)}) > 0;
    };
    const int INF = INT_MAX;
    vector<vector<int>> d(n, vector<int>(m, INF));
    deque<pair<int, int>> dq;
    d[ks][ko] = 0;
    dq.push_back({ks, ko});
    while (!dq.empty()) {
        auto [i, j] = dq.front();
        dq.pop_front();
        for (int k = 0; k < 4; k++) {
            int x = i + di[k], y = j + dj[k];
            if (x < 0 || x >= n || y < 0 || y >= m) continue;
            int w = noCheck(c[i][j], c[x][y]) ? 0 : 1;
            if (d[i][j] + w < d[x][y]) {
                d[x][y] = d[i][j] + w;
                if (w == 0) dq.push_front({x, y});
                else dq.push_back({x, y});
            }
        }
    }

    cout << countries << '\n';
    cout << d[vs][vo] << '\n';
    return 0;
}
