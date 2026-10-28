/*
Megoldás lényege:
A városok azok a csúcsok, amelyek a fokszám-1-es csúcsok ismételt eltávolítása után megmaradnak (2-mag): ezek egy kétszeresen összefüggő részt alkotnak, a tanyák pedig fa-szerű ágak, amelyek egyetlen városhoz kapcsolódnak. A törölt csúcsok mindegyike így egyetlen városhoz tartozik. Ezért a városokból egyszerre indított BFS-sel járjuk be a tanyákat, és csak a törölt csúcsokon megyünk tovább, így minden tanyához a hozzá tartozó város kerül. A kimenetben a városok és a tanyák sorszám szerint növekvő sorrendben szerepelnek. Az időigény O(N + összes út), ami bőven belefér a korlátba.
*/
/*
Hint 1: || Egy tanya olyan csúcs, amely nincs benne egyetlen körben sem. Ha a fokszám-1 csúcsokat egymás után eltávolítod, a körökben lévő csúcsok nem fogynak el. ||
Hint 2: || Az eltávolítás után megmaradó csúcsok a városok. Egy törölt csúcs ahhoz a városhoz tartozik, amelyikhez a fa-szerű ága csatlakozik. ||
Hint 3: || Indíts BFS-t egyszerre minden városból, de csak a törölt (tanya) csúcsokra lépj tovább, és minden csúcsnál jegyezd fel, melyik városból érkeztél. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for (int i = 1; i <= n; i++) {
        int d;
        cin >> d;
        g[i].resize(d);
        for (int& x : g[i]) cin >> x;
    }

    // 1. lépés: a levelek ismételt eltávolítása; a maradék csúcsok a városok
    vector<int> deg(n + 1, 0), removed(n + 1, 0);
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        deg[i] = (int)g[i].size();
        if (deg[i] <= 1) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (removed[u]) continue;
        removed[u] = 1;
        for (int v : g[u]) {
            if (!removed[v] && --deg[v] == 1) q.push(v);
        }
    }

    // 2. lépés: többforrású BFS a városokból, csak a tanyákon (törölt csúcsokon) át
    vector<int> owner(n + 1, 0);
    queue<int> bq;
    for (int i = 1; i <= n; i++) {
        if (!removed[i]) {
            owner[i] = i;
            bq.push(i);
        }
    }
    while (!bq.empty()) {
        int u = bq.front();
        bq.pop();
        for (int v : g[u]) {
            if (removed[v] && owner[v] == 0) {
                owner[v] = owner[u];
                bq.push(v);
            }
        }
    }

    vector<vector<int>> farms(n + 1);
    for (int i = 1; i <= n; i++) {
        if (removed[i] && owner[i] != 0) farms[owner[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        if (removed[i]) continue;
        cout << i << ' ' << farms[i].size();
        for (int f : farms[i]) cout << ' ' << f;
        cout << '\n';
    }
    return 0;
}
