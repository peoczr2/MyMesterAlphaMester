/*
Megoldás lényege:
Egy új vonal két gép között kört zár le: a köztük lévő úton álló kritikus összekötések többé nem lesznek kritikusak, a többi marad. Ezért olyan két gépet kell választani, amelyek közötti úton a lehető legtöbb kritikus összekötés van. A kritikus összekötések (hidak) és a hidak nélkül összefüggő részek (kétélű-összefüggő komponensek) Tarjan-algoritmussal, egyetlen mélységi bejárásban kaphatók meg. A komponensek a hidakkal fát alkotnak, ennek átmérőjének két végpontja adja a választ: a két végpont gépei közé vont vonal a legtöbb hidat szünteti meg. A fa átmérőjét két szélességi bejárással kapjuk. Az időigény O(N + M).
*/
/*
Hint 1: || Egy új vonal a köztük lévő utat kört zár be: a körben lévő kritikus összekötések többé nem lesznek kritikusak. Érdemes tehát olyan két gépet keresni, amelyek között a lehető legtöbb kritikus összekötés van. ||
Hint 2: || A kritikus összekötéseket (hidakat) egy mélységi bejárással, a low-értékek segítségével találhatod meg. A hidak nélkül összefüggő részek (kétélű-összefüggő komponensek) a hidakkal fát alkotnak, amelyben a hidak az élek. ||
Hint 3: || A fában a legtávolabbi csúcspárt két szélességi bejárással kapod meg: az elsőből a legtávolabbi csúcs az egyik vég, a második bejárás erről a csúcsról megadja a másik véget. A két végpont egy-egy komponensének egy-egy gépe a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> ea(m), eb(m), start(n + 2, 0);
    for (int i = 0; i < m; ++i) {
        cin >> ea[i] >> eb[i];
        ++start[ea[i] + 1];
        ++start[eb[i] + 1];
    }
    for (int v = 1; v <= n + 1; ++v) start[v] += start[v - 1];

    vector<int> adjTo(2 * (size_t)m), adjId(2 * (size_t)m), pos(start.begin(), start.end());
    for (int i = 0; i < m; ++i) {
        adjTo[pos[ea[i]]] = eb[i];
        adjId[pos[ea[i]]++] = i;
        adjTo[pos[eb[i]]] = ea[i];
        adjId[pos[eb[i]]++] = i;
    }

    // Tarjan-féle kétélű-összefüggő komponensek (a párhuzamos élek miatt élsorszámmal szűrünk)
    vector<int> tin(n + 1, -1), low(n + 1, 0), pe(n + 1, -1), it(n + 1, 0), comp(n + 1, -1);
    vector<int> stk, call;
    int timer = 0, cid = 0;
    auto enter = [&](int v, int edge) {
        tin[v] = low[v] = timer++;
        pe[v] = edge;
        it[v] = start[v];
        stk.push_back(v);
        call.push_back(v);
    };
    for (int s = 1; s <= n; ++s) {
        if (tin[s] != -1) continue;
        enter(s, -1);
        while (!call.empty()) {
            int v = call.back();
            if (it[v] < start[v + 1]) {
                int idx = it[v]++;
                int to = adjTo[idx], id = adjId[idx];
                if (id == pe[v]) continue;
                if (tin[to] != -1) {
                    low[v] = min(low[v], tin[to]);
                } else {
                    enter(to, id);
                }
            } else {
                call.pop_back();
                if (low[v] == tin[v]) {
                    int w;
                    do {
                        w = stk.back();
                        stk.pop_back();
                        comp[w] = cid;
                    } while (w != v);
                    ++cid;
                }
                if (!call.empty()) low[call.back()] = min(low[call.back()], low[v]);
            }
        }
    }

    // A komponensfa: az élek, amelyek különböző komponensek közt vannak, a hidak.
    vector<vector<int>> tr(cid);
    for (int i = 0; i < m; ++i) {
        int x = comp[ea[i]], y = comp[eb[i]];
        if (x != y) {
            tr[x].push_back(y);
            tr[y].push_back(x);
        }
    }
    vector<int> rep(cid, -1);
    for (int v = 1; v <= n; ++v)
        if (rep[comp[v]] == -1) rep[comp[v]] = v;

    // Szélességi bejárás: visszaadja a legtávolabbi komponenst s-től.
    auto farthest = [&](int s, vector<int> &dist) {
        dist.assign(cid, -1);
        queue<int> q;
        q.push(s);
        dist[s] = 0;
        int far = s;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            if (dist[x] > dist[far]) far = x;
            for (int y : tr[x])
                if (dist[y] == -1) {
                    dist[y] = dist[x] + 1;
                    q.push(y);
                }
        }
        return far;
    };

    vector<int> dist;
    int x = farthest(comp[1], dist);
    int y = farthest(x, dist);
    if (x == y) {  // nincs híd: a gráf már kétélűen összefüggő
        cout << 1 << ' ' << 2 << '\n';
        return 0;
    }
    cout << rep[x] << ' ' << rep[y] << '\n';
    return 0;
}
