/*
Megoldás lényege:
Egy útvonal átviteli sebessége a leglassabb élének sebessége, így a keresett érték a P és Q közötti legnagyobb ilyen minimum.
Az éleket csökkenő sebesség szerint dolgozzuk fel, és Union-Find segítségével építjük a feszítőerdőt; amint P és Q egy halmazba kerül, az éppen beépített él sebessége a válasz, mert addig minden beépített él legalább ekkora volt.
Az útvonalat a beépített fa-élek között BFS-sel keressük meg, így az útvonal leglassabb éle pontosan a válasz.
Mivel a sebességek kis egészek (legfeljebb 200), az éleket számlálórendezéssel rendezzük, így az időigény O(M + N).
*/
/*
Hint 1: || Egy útvonal sebessége a leglassabb éle, tehát azt keresd, melyik útvonalon lehet ezt a minimumot a legnagyobbra vinni. ||
Hint 2: || Ha az éleket sebesség szerint csökkenő sorrendben veszed be egy Union-Find struktúrába, az első pillanat, amikor P és Q egy halmazba kerül, már megadja a választ. ||
Hint 3: || Az útvonalhoz csak a már beépített élekből álló fát kell bejárnod P-től Q-ig, például BFS-sel, a szülőkből pedig visszafelé rakhatod össze az utat. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> dsu;

int findRoot(int x) {
    while (dsu[x] != x) {
        dsu[x] = dsu[dsu[x]];
        x = dsu[x];
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int p, q;
    cin >> p >> q;

    vector<int> eu(m), ev(m), es(m);
    int maxS = 0;
    for (int i = 0; i < m; i++) {
        cin >> eu[i] >> ev[i] >> es[i];
        maxS = max(maxS, es[i]);
    }

    // Számlálórendezés: az élek sebesség szerint csökkenő sorrendben
    vector<int> cnt(maxS + 1, 0);
    for (int i = 0; i < m; i++) cnt[es[i]]++;
    vector<int> startPos(maxS + 1, 0);
    int acc = 0;
    for (int s = maxS; s >= 0; s--) {
        startPos[s] = acc;
        acc += cnt[s];
    }
    vector<int> order(m);
    for (int i = 0; i < m; i++) order[startPos[es[i]]++] = i;

    dsu.resize(n + 1);
    iota(dsu.begin(), dsu.end(), 0);
    vector<vector<int>> tree(n + 1);

    int answer = 0;
    bool connected = false;
    for (int idx : order) {
        int a = findRoot(eu[idx]);
        int b = findRoot(ev[idx]);
        if (a == b) continue;
        dsu[a] = b;
        tree[eu[idx]].push_back(ev[idx]);
        tree[ev[idx]].push_back(eu[idx]);
        if (findRoot(p) == findRoot(q)) {
            answer = es[idx];
            connected = true;
            break;
        }
    }

    if (!connected) {
        cout << 0 << '\n';
        return 0;
    }

    // BFS a feszítőerdőn P-ből, szülő-tömbbel az út visszafejtéséhez
    vector<int> from(n + 1, 0);
    vector<bool> seen(n + 1, false);
    queue<int> qu;
    qu.push(p);
    seen[p] = true;
    while (!qu.empty()) {
        int u = qu.front();
        qu.pop();
        if (u == q) break;
        for (int v : tree[u]) {
            if (!seen[v]) {
                seen[v] = true;
                from[v] = u;
                qu.push(v);
            }
        }
    }

    vector<int> path;
    for (int v = q; v != p; v = from[v]) path.push_back(v);
    path.push_back(p);
    reverse(path.begin(), path.end());

    cout << answer << '\n';
    for (size_t i = 0; i < path.size(); i++) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << '\n';
    return 0;
}
