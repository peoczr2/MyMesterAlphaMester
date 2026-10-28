/*
Megoldás lényege: egy i indexhez a legtávolabbi inverzió-társ a legnagyobb j > i index,
amelyre S_j < S_i. Az indexeket jobbról balra járjuk be, és egy Fenwick-fában (prefix
maximum) az értékekhez tároljuk a hozzájuk tartozó legnagyobb indexet: így S_i-nél kisebb
értékek közül a legnagyobb index egy lekérdezéssel megkapható. Minden i-re ezt számoljuk,
és a legnagyobb j - i távolságot választjuk. Az idő O(N log N), a memória O(N).
*/
/*
Hint 1: || Rögzíts egy i indexet: melyik j > i jöhet szóba, hogy inverzió legyen? Az, amelyre S_j < S_i. Keresd a legnagyobb ilyen j-t. ||
Hint 2: || Jobbról balra haladva minden értékhez eltárolhatod a hozzá tartozó indexet, és a „kisebb értékek” maximumát prefix-lekérdezéssel kaphatod meg. ||
Hint 3: || Egy Fenwick-fa (bináris indexelt fa) prefix-maximumot tud frissíteni és lekérdezni O(log N) időben, ezzel minden i-re egy lekérdezés elég. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;
    Fenwick(int n = 0) : n(n), bit(n + 1, -1) {}
    void update(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] = max(bit[idx], val);
    }
    int query(int idx) {
        int res = -1;
        for (; idx > 0; idx -= idx & -idx) res = max(res, bit[idx]);
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> a(N + 1);
    for (int i = 1; i <= N; ++i) cin >> a[i];

    Fenwick fw(N);
    int bestI = -1, bestJ = -1, bestD = -1;
    for (int i = N; i >= 1; --i) {
        int j = fw.query(a[i] - 1);
        if (j != -1 && j - i > bestD) {
            bestD = j - i;
            bestI = i;
            bestJ = j;
        }
        fw.update(a[i], i);
    }

    if (bestI == -1) cout << -1 << '\n';
    else cout << bestI << ' ' << bestJ << '\n';
    return 0;
}