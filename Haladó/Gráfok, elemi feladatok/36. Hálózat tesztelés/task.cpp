/*
Megoldás lényege:
A törlések sorozata helyett fordított sorrendben dolgozunk: a végső gráfból indulva, a törölt éleket az utolsótól az elsőig visszaadjuk.
Unió-keresés (DSU) segítségével követjük az élek összevonását, és komponensenként tároljuk a csúcsok listáját.
Ha a visszaadott él az 1-es csúcs komponensét egy másik komponenssel köti össze, akkor a másik komponens csúcsai a megfelelő törlés során pontosan ebben a lépésben váltak elérhetetlenné.
Az összevonásnál a kisebb listát a nagyobbhoz fűzzük, így az összes művelet időigénye O((N + M) * alfa(N) + N log N).
*/
/*
Hint 1: || Ne a törléseket szimuláld előre, hanem fordítva gondolkodj: a végső gráfból indulva, a törölt éleket az utolsótól az elsőig adod vissza. Egy él visszaadásakor azok a csúcsok csatlakoznak az 1-es csúcs komponenséhez, amelyek a megfelelő törlés után nem voltak elérhetők. ||
Hint 2: || Használj unió-keresés (DSU) struktúrát, és minden komponenshez tárold a csúcsainak listáját. Ha a visszaadott él két komponenst köt össze és az egyik az 1-es csúcsé, akkor a másik komponens listáját kell kiírni az adott sorba. ||
Hint 3: || Ha az él két végpontja már ugyanabban a komponensben van, az adott sor 0. A kiírás sorrendje a kérdések sorrendje, ezért a válaszokat tárold el a törlés indexe szerint, és csak a végén írd ki őket. A kisebb listát mindig a nagyobbhoz fűzd, hogy az összevonás gyors maradjon. ||
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> par;
vector<vector<int>> members;

int findRoot(int x) {
    while (par[x] != x) {
        par[x] = par[par[x]];
        x = par[x];
    }
    return x;
}

// ra, rb: két különböző gyökér; a kisebb listát a nagyobbhoz fűzzük
void unite(int ra, int rb) {
    if (members[ra].size() < members[rb].size()) swap(ra, rb);
    par[rb] = ra;
    members[ra].insert(members[ra].end(), members[rb].begin(), members[rb].end());
    vector<int>().swap(members[rb]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> removed(k);
    vector<char> isRemoved(m + 1, 0);
    for (int i = 0; i < k; ++i) {
        cin >> removed[i];
        isRemoved[removed[i]] = 1;
    }
    vector<int> ea(m + 1), eb(m + 1);
    for (int i = 1; i <= m; ++i) cin >> ea[i] >> eb[i];

    par.resize(n + 1);
    members.assign(n + 1, {});
    for (int v = 1; v <= n; ++v) {
        par[v] = v;
        members[v] = {v};
    }

    // a végső gráf: azok az élek, amelyeket egyáltalán nem kapcsolnak le
    for (int i = 1; i <= m; ++i) {
        if (isRemoved[i]) continue;
        int ra = findRoot(ea[i]), rb = findRoot(eb[i]);
        if (ra != rb) unite(ra, rb);
    }

    // visszafelé: az utolsó törléstől az elsőig visszaadjuk az éleket
    vector<vector<int>> answer(k);
    for (int i = k - 1; i >= 0; --i) {
        int e = removed[i];
        int ra = findRoot(ea[e]), rb = findRoot(eb[e]);
        if (ra == rb) continue;
        int r1 = findRoot(1);
        if (ra == r1) answer[i] = members[rb];
        else if (rb == r1) answer[i] = members[ra];
        unite(ra, rb);
    }

    for (int i = 0; i < k; ++i) {
        cout << answer[i].size();
        for (int v : answer[i]) cout << ' ' << v;
        cout << '\n';
    }
    return 0;
}
