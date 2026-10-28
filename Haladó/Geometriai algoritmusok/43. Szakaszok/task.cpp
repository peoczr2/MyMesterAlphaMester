/*
Megoldás lényege:
X-szerinti söpréssel haladunk. A vízszintes szakaszokat a bal végpontjuknál aktiváljuk,
jobb végpontjuknál eltávolítjuk. Az aktív szakaszok y-koordinátáit Fenwick-fával tartjuk
nyilván, így minden függőleges szakaszra megkapható, hány aktív vízszintes esik a
[y1, y2] intervallumba.

Lépések:
1) a vízszintes szakaszok y-koordinátáit összegyűjtjük és rendezve kompresszáljuk,
2) eseményeket készítünk: aktiválás, lekérdezés, törlés,
3) x szerint rendezve feldolgozzuk őket; azonos x-nél a sorrend: aktiválás, lekérdezés, törlés,
4) minden függőleges szakaszhoz kiszámítjuk a metsző vízszintesek számát, és a maximumot
   a legkisebb indexű szakaszra emlékezzük.

Idő: O((M + N) log M)
*/
/*
Hint 1: || Söpörd végig a síkot x szerint: a vízszintes szakaszok bal és jobb végpontja aktiválási,
illetve törlési esemény, a függőleges szakaszok pedig lekérdezési események. Azonos x-nél előbb az
aktiválás, aztán a lekérdezés, végül a törlés jön, mert a közös végpont is metszésnek számít. ||
Hint 2: || A lekérdezés pillanatában azt kell megszámolni, hány aktív vízszintes y-koordinátája esik
a függőleges szakasz [y1, y2] intervallumába. Az y-koordinátákat rendezve tömörítsd, és egy Fenwick-fában
tartsd nyilván az aktív szakaszokat, így egy intervallum darabszáma O(log M) alatt megkapható. ||
Hint 3: || A söprés x szerint halad, nem sorszám szerint, ezért a legkisebb sorszámú maximumot külön
kell kezelni: egyenlő darabszámnál a kisebb sorszámút tartsd meg. Ha minden lekérdezés 0-t ad,
a válasz 0. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;

    Fenwick(int size = 0) { init(size); }

    void init(int n_) {
        n = n_;
        bit.assign(n + 1, 0);
    }

    void add(int idx, int val) {
        for (++idx; idx <= n; idx += idx & -idx) bit[idx] += val;
    }

    int sumPrefix(int idx) const {
        int res = 0;
        for (++idx; idx > 0; idx -= idx & -idx) res += bit[idx];
        return res;
    }

    int sumRange(int l, int r) const {
        if (l > r) return 0;
        return sumPrefix(r) - (l ? sumPrefix(l - 1) : 0);
    }
};

struct Event {
    long long x;
    int type;
    int a, b;
    int id;

    bool operator<(const Event& other) const {
        if (x != other.x) return x < other.x;
        return type < other.type;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    if (!(cin >> M >> N)) return 0;

    struct Horizontal {
        long long x1, x2, y;
    };

    vector<Horizontal> horizontals;
    horizontals.reserve(M);
    vector<long long> ys;
    ys.reserve(M);

    for (int i = 0; i < M; ++i) {
        long long x1, x2, y;
        cin >> x1 >> x2 >> y;
        if (x1 > x2) swap(x1, x2);
        horizontals.push_back({x1, x2, y});
        ys.push_back(y);
    }

    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    vector<Event> events;
    events.reserve(2 * M + N);

    for (const auto& h : horizontals) {
        int yIdx = (int)(lower_bound(ys.begin(), ys.end(), h.y) - ys.begin());
        events.push_back({h.x1, 0, yIdx, 0, -1});
        events.push_back({h.x2, 2, yIdx, 0, -1});
    }

    for (int i = 0; i < N; ++i) {
        long long x, y1, y2;
        cin >> x >> y1 >> y2;
        if (y1 > y2) swap(y1, y2);
        int l = (int)(lower_bound(ys.begin(), ys.end(), y1) - ys.begin());
        int r = (int)(upper_bound(ys.begin(), ys.end(), y2) - ys.begin()) - 1;
        events.push_back({x, 1, l, r, i + 1});
    }

    sort(events.begin(), events.end());

    Fenwick fw((int)ys.size());
    int bestIdx = 0;
    int bestCnt = 0;

    for (const auto& e : events) {
        if (e.type == 0) {
            fw.add(e.a, 1);
        } else if (e.type == 2) {
            fw.add(e.a, -1);
        } else {
            int cur = fw.sumRange(e.a, e.b);
            if (cur > bestCnt || (cur == bestCnt && cur > 0 && e.id < bestIdx)) {
                bestCnt = cur;
                bestIdx = e.id;
            }
        }
    }

    if (bestCnt == 0) cout << 0 << '\n';
    else cout << bestIdx << '\n';

    return 0;
}