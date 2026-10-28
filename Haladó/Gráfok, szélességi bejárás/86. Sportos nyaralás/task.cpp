/*
Megoldás lényege:
Az utak kétirányúak, ezért egy eszközzel akkor lehet S-ből T-be és T-ből S-be is eljutni, ha S és T ugyanabban az összefüggő komponensben van abban a gráfban. A feladat szerint az oda- és a visszaút két különböző eszközzel történik, így T pontosan akkor jó S-nek, ha S és T a bicikli-gráfban és a vízi-gráfban is ugyanabban a komponensben van. Mindkét gráfra DSU-val (diszjunkt halmazok) meghatározzuk a komponenseket, majd minden településhez a (bicikli-komponens, vízi-komponens) párt rendeljük. Az azonos párú települések egy csoportot alkotnak, és egy S település válasza a saját csoportjának mérete mínusz 1, mert S maga nem számít. Az időigény O((N+M+K)·α(N)), a memóriaigény O(N).
*/
/*
Hint 1: || Két külön gráf van: a bicikliutaké és a vízi útvonalaké. Gondold végig, mikor tud S és T mindkét irányban, két különböző eszközzel oda-vissza eljutni. ||
Hint 2: || Használj DSU-t mindkét gráfra. Egy T település akkor jó, ha S-sel mindkét gráfban ugyanaz a komponens; így minden településhez elég a komponens-azonosítók párját eltárolni és megszámolni. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, sz;

    DSU(int n) : p(n + 1), sz(n + 1, 1) {
        iota(p.begin(), p.end(), 0);
    }

    int find(int x) {
        while (p[x] != x) {
            p[x] = p[p[x]];
            x = p[x];
        }
        return x;
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    DSU bike(n), water(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        bike.unite(a, b);
    }
    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        water.unite(a, b);
    }

    vector<pair<int, int>> key(n + 1);
    map<pair<int, int>, int> cnt;
    for (int i = 1; i <= n; i++) {
        key[i] = {bike.find(i), water.find(i)};
        cnt[key[i]]++;
    }

    for (int i = 1; i <= n; i++) {
        cout << cnt[key[i]] - 1 << (i == n ? '\n' : ' ');
    }
    return 0;
}
