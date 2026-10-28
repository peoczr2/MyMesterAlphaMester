/*
Megoldás lényege:
A négyzetrácsos utcahálózatban két kereszteződés legrövidebb úthossza a sor- és oszlopkoordináták különbségének
összege (Manhattan-távolság), ezért nem kell a rácsot bejárni. Két hírvivő akkor közeli, ha távolságuk legfeljebb L.
A H ≤ 1000 hírvivő között minden párra kiszámoljuk a távolságot, a párokat távolság szerint növekvően rendezzük, és
egy uniót-keresőt (DSU) használva élenként összevonjuk a hírvivőket. Minden tényleges összevonás csökkenti a
csoportok számát; amint a csoportok száma legfeljebb K, az aktuális él távolsága lesz a keresett L. Ha már
kezdetben H ≤ K, a válasz 0. Az időigény O(H² log H), ami H ≤ 1000 mellett bőven belül van.
*/
/*
Hint 1: || Az utcák teljes rácsot alkotnak, így két kereszteződés távolsága a sor- és oszlopkoordináták különbségének összege. A rácsot nem kell bejárnod, elég a hírvivők pozícióit használni. ||
Hint 2: || Növeld L-t fokozatosan: minden L-hez tartozik egy gráf, amelyben a közeli hírvivők össze vannak kötve, és a csoportok száma csak csökken, ha L nő. Keresd azt a legkisebb L-t, ahol a csoportok száma legfeljebb K. ||
Hint 3: || Az összes páros távolságot rendezd növekvő sorrendbe, és az élek hozzáadásakor a DSU-ban kövesd a csoportok számát. Az első olyan él távolsága lesz a válasz, amelynél a csoportok száma K alá vagy egyenlő K-ra csökken. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> parent, sz;

int findRoot(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

bool unite(int a, int b) {
    a = findRoot(a);
    b = findRoot(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) swap(a, b);
    parent[b] = a;
    sz[a] += sz[b];
    return true;
}

struct Pair {
    int dist, a, b;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, h, k;
    cin >> n >> m >> h >> k;

    vector<int> r(h), c(h);
    for (int i = 0; i < h; ++i) cin >> r[i] >> c[i];

    if (h <= k) {
        cout << 0 << '\n';
        return 0;
    }

    vector<Pair> pairs;
    pairs.reserve((size_t)h * (h - 1) / 2);
    for (int i = 0; i < h; ++i) {
        for (int j = i + 1; j < h; ++j) {
            int d = abs(r[i] - r[j]) + abs(c[i] - c[j]);
            pairs.push_back({d, i, j});
        }
    }
    sort(pairs.begin(), pairs.end(), [](const Pair &x, const Pair &y) { return x.dist < y.dist; });

    parent.resize(h);
    sz.assign(h, 1);
    for (int i = 0; i < h; ++i) parent[i] = i;

    int groups = h;
    for (const Pair &p : pairs) {
        if (unite(p.a, p.b)) {
            --groups;
            if (groups <= k) {
                cout << p.dist << '\n';
                return 0;
            }
        }
    }

    cout << 0 << '\n';
    return 0;
}
