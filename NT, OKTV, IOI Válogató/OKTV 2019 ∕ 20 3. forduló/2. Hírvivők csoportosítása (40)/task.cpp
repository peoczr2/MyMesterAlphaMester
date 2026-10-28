/*
Megoldás lényege:
A rácson két kereszteződés közötti legrövidebb út hossza a Manhattan-távolság, vagyis a két koordináta-különbség abszolút értékeinek összege. Két hírvivő akkor közeli, ha a távolságuk legfeljebb L, a csoportok pedig a közeli párok összefüggő komponensei. Ha az összes hírvivőpárra kiszámoljuk a távolságot, és ezeket növekvő sorrendben vesszük, a Kruskal-algoritmussal (diszjunkt halmazok, unió-keresés) pontosan akkor kapunk legfeljebb K komponenst, amikor a H-K legkisebb, összekötést adó él már benne van. A válasz tehát a (H-K)-adik sikeres unióhoz tartozó él súlya, ha H = K, akkor nincs szükség élre és a válasz 0. Az élek száma kb. H^2/2 = 500 000, így a rendezéssel az időigény O(H^2 log H), ami bőven belefér.
*/
/*
Hint 1: || A rácson a legrövidebb út hossza két kereszteződés között a koordináták különbségeinek abszolút értékének összege. Két hírvivő közelisége tehát egyszerűen kiszámolható, és a csoportok olyan összefüggő komponensek, amelyek a közeli párokból állnak. ||
Hint 2: || Számold ki az összes hírvivőpár távolságát, rendezd növekvő sorrendbe, és építs diszjunkt halmaz (unió-keresés) struktúrát: egy él összeköt két csoportot, ha a két végpont még különböző csoportban van. Minden sikeres összekötés csökkenti a csoportok számát eggyel. ||
Hint 3: || Kezdetben H csoport van, és K csoportot szeretnénk, ezért pontosan H-K sikeres összekötésre van szükséged. Az utolsó ilyen összekötés éle súlya adja a legkisebb L értéket. Ha H = K, a válasz 0. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> parent_;

int findRoot(int x) {
    while (parent_[x] != x) {
        parent_[x] = parent_[parent_[x]];
        x = parent_[x];
    }
    return x;
}

bool unite(int a, int b) {
    a = findRoot(a);
    b = findRoot(b);
    if (a == b) return false;
    parent_[a] = b;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, h, k;
    cin >> n >> m >> h >> k;
    vector<int> row(h), col(h);
    for (int i = 0; i < h; ++i) cin >> row[i] >> col[i];

    struct Edge {
        int w, a, b;
    };
    vector<Edge> edges;
    edges.reserve((size_t)h * (h - 1) / 2);
    for (int i = 0; i < h; ++i)
        for (int j = i + 1; j < h; ++j)
            edges.push_back({abs(row[i] - row[j]) + abs(col[i] - col[j]), i, j});
    sort(edges.begin(), edges.end(), [](const Edge& x, const Edge& y) { return x.w < y.w; });

    parent_.resize(h);
    for (int i = 0; i < h; ++i) parent_[i] = i;

    // H - K sikeres összekötés kell ahhoz, hogy K csoport maradjon.
    int need = h - k;
    int answer = 0;
    int merged = 0;
    for (const Edge& e : edges) {
        if (merged == need) break;
        if (unite(e.a, e.b)) {
            ++merged;
            answer = e.w;
        }
    }

    cout << answer << "\n";
    return 0;
}
