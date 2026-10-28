/*
Megoldás lényege:
Egy A-ból B-be vezető úton a hajó szélessége a csatornák legkeskenyebbjének szélessége. Mivel egyetlen csatornát tetszőleges szélesre kiszélesíthetünk, az úton a legkeskenyebb csatorna szélessége nem számít: az út értéke a legkeskenyebb csatorna kihagyása után megmaradó legkeskenyebb csatorna szélessége. Keressük tehát azt a legnagyobb x szélességet, amelyre létezik A-B út, amelyen legfeljebb egy x-nél keskenyebb csatorna van. Ez a tulajdonság x-ben monoton, ezért x-et bináris kereséssel határozzuk meg (0 és 10001 között). Egy adott x-re egy BFS-t futtatunk, amelynek csomópontjai kétállapotúak: a kiszélesítést még nem használtuk, illetve már felhasználtuk. Egy x-nél keskenyebb csatornát csak akkor lépünk át, ha még nem használtuk fel a kiszélesítést. Az időigény O((N + M) log W), ahol W = 10000 a legnagyobb szélesség.
*/
/*
Hint 1: || Egy út szélessége a rajta lévő csatornák legkeskenyebbje, de egyetlen csatornát kiszélesíthetünk. Gondold meg, hogy így az út értéke az a legnagyobb szélesség, amely mellett legfeljebb egy csatorna keskenyebb a kívánt szélességnél. ||
Hint 2: || Ez a tulajdonság monoton: ha x szélességű hajó átfér, akkor kisebb szélességű is. Ezért a válasz bináris kereséssel megtalálható, és minden lépésben csak egy igen/nem kérdést kell megválaszolni. ||
Hint 3: || Egy adott x-re futtass BFS-t, ahol minden csomóponthoz két állapot tartozik: a kiszélesítést még nem használtuk, vagy már felhasználtuk. Egy keskeny csatorna (x-nél kisebb szélesség) csak a még nem használt állapotból léphető át, és az átlépés után az állapot már felhasznált lesz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, m, a, b;
vector<int> startIdx, adjTo, adjW;   // csúcsonként összefüggő tömbszerkezet
vector<char> vis;
vector<int> q;

// Van-e A-ból B-be út, amelyen legfeljebb egy x-nél keskenyebb csatorna van?
bool feasible(int x) {
    fill(vis.begin(), vis.end(), 0);
    q.clear();
    vis[2 * a] = 1;
    q.push_back(2 * a);
    for (size_t i = 0; i < q.size(); i++) {
        int u = q[i] >> 1, used = q[i] & 1;
        for (int j = startIdx[u]; j < startIdx[u + 1]; j++) {
            int nextUsed = used;
            if (adjW[j] < x) {
                if (used) continue;
                nextUsed = 1;
            }
            int s = 2 * adjTo[j] + nextUsed;
            if (!vis[s]) {
                vis[s] = 1;
                q.push_back(s);
            }
        }
    }
    return vis[2 * b] || vis[2 * b + 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> a >> b;
    vector<int> eu(m), ev(m), ew(m);
    startIdx.assign(n + 2, 0);
    for (int i = 0; i < m; i++) {
        cin >> eu[i] >> ev[i] >> ew[i];
        startIdx[eu[i] + 1]++;
        startIdx[ev[i] + 1]++;
    }
    for (int v = 1; v <= n + 1; v++) startIdx[v] += startIdx[v - 1];
    adjTo.assign(2 * m, 0);
    adjW.assign(2 * m, 0);
    vector<int> pos(startIdx.begin(), startIdx.end());
    for (int i = 0; i < m; i++) {
        adjTo[pos[eu[i]]] = ev[i];
        adjW[pos[eu[i]]++] = ew[i];
        adjTo[pos[ev[i]]] = eu[i];
        adjW[pos[ev[i]]++] = ew[i];
    }
    vis.assign(2 * (n + 1), 0);

    // lo: mindig teljesül (0), hi: nem teljesül (A és B nincs közvetlenül összekötve)
    int lo = 0, hi = 10001;
    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        if (feasible(mid)) lo = mid;
        else hi = mid;
    }
    cout << lo << '\n';
    return 0;
}
