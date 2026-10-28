/*
Megoldás lényege:
A lekapcsolásokat fordított sorrendben dolgozzuk fel. Kezdetben csak azok a vonalak vannak a hálózatban, amelyeket a teszt
nem kapcsol le, ezeket egy DSU (Union-Find) struktúrával egyesítjük. Ezután K-tól 1-ig visszaadjuk a lekapcsolt vonalakat: ha
egy vonal az 1-es csomópont komponensét egy olyan komponenssel köti össze, amelyben nincs 1, akkor annak minden csomópontja
éppen az adott lekapcsolás után vált elérhetetlenné, ezek kerülnek az i-edik sorba.
Minden komponens tagjait láncolt listában tartjuk, így két komponens összefűzése O(1), és minden csomópont legfeljebb egyszer
kerül kiírásra. Az időigény O((N + M + K) · alfa(N)), ami a korlátok mellett bőven belefér.
*/
/*
Hint 1: || Ne szimuláld előre a lekapcsolásokat, mert minden lépésnél új bejárás kellene. Fordítsd meg a folyamatot: a végállapotból
indulva a lekapcsolt vonalakat K-tól 1-ig egyenként visszaadod, és figyeled, mely csomópontok lesznek ilyenkor elérhetők. ||
Hint 2: || Egy visszaadott vonal pontosan akkor "hoz be" új csomópontokat, ha az 1-es csomópontot tartalmazó komponenst egy
olyan komponenssel köti össze, amelyben nincs 1. Ezt a DSU-val gyorsan eldöntheted: a két végpont gyökerét kell összehasonlítani. ||
Hint 3: || A komponensek tagjait láncolt listában tárold (minden gyökérnek van eleje és vége), így két lista összefűzése konstans
idejű. Mivel minden csomópont egyszer kerül az 1-es komponensbe, a kiírt csomópontok száma összesen legfeljebb N. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> par, compSize, firstV, lastV, nextV;

int findRoot(int x) {
    while (par[x] != x) {
        par[x] = par[par[x]];
        x = par[x];
    }
    return x;
}

void unite(int a, int b) {
    a = findRoot(a);
    b = findRoot(b);
    if (a == b) return;
    if (compSize[a] < compSize[b]) swap(a, b);
    par[b] = a;
    compSize[a] += compSize[b];
    nextV[lastV[a]] = firstV[b];
    lastV[a] = lastV[b];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> s(k);
    for (int &x : s) cin >> x;

    vector<int> ea(m + 1), eb(m + 1);
    vector<char> removed(m + 1, 0);
    for (int x : s) removed[x] = 1;
    for (int i = 1; i <= m; i++) cin >> ea[i] >> eb[i];

    par.resize(n + 1);
    compSize.assign(n + 1, 1);
    firstV.resize(n + 1);
    lastV.resize(n + 1);
    nextV.assign(n + 1, 0);
    for (int v = 1; v <= n; v++) {
        par[v] = v;
        firstV[v] = v;
        lastV[v] = v;
    }

    for (int i = 1; i <= m; i++) {
        if (!removed[i]) unite(ea[i], eb[i]);
    }

    vector<vector<int>> answer(k);
    for (int i = k - 1; i >= 0; i--) {
        int id = s[i];
        int ra = findRoot(ea[id]);
        int rb = findRoot(eb[id]);
        if (ra != rb) {
            int root1 = findRoot(1);
            if ((ra == root1) != (rb == root1)) {
                int other = (ra == root1) ? rb : ra;
                for (int v = firstV[other]; v != 0; v = nextV[v]) answer[i].push_back(v);
            }
            unite(ra, rb);
        }
    }

    for (int i = 0; i < k; i++) {
        // A sorrend tetszőleges; az első csomópont marad elöl, a többi fordítva kerül ki (a mintának megfelelően).
        if (answer[i].size() > 1) reverse(answer[i].begin() + 1, answer[i].end());
        cout << answer[i].size();
        for (int v : answer[i]) cout << ' ' << v;
        cout << '\n';
    }
    return 0;
}
