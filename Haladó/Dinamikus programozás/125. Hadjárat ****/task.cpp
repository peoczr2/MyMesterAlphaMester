/*
Magyar megoldás:
A keresett hadjárat olyan várossorozat, amelyben az indexek növekednek, és közben a rabszolgák száma is,
meg az arany mennyisége is szigorúan nő. Ez tehát egy 3 dimenziós részbenrendezési feladat:
index, rabszolgaszám és aranymennyiség szerint kell a leghosszabb láncot megtalálni.

Legyen dp[i] az i-edik városban végződő optimális lánc hossza. Ekkor az átmenet:
dp[i] = 1 + max(dp[j]) minden olyan j < i-re, ahol R[j] < R[i] és A[j] < A[i].

Ezt közvetlenül O(N^2)-ben nem lehet kiszámolni. A trükk a CDQ divide-and-conquer az index szerint:
egy rekurziós lépésben a bal fél eredményei hathatnak a jobb félre, ha a másik két koordinátában is kisebbek.
A merge során a bal felet rabszolgaszám szerint rendezzük, és egy Fenwick-fában az aranymennyiségre eltároljuk
a legjobb dp értéket. Így minden összeolvasztás O(len log N), a teljes futás O(N log^2 N).

Az előd indexét is eltároljuk, ezért a végén vissza tudjuk fejteni az egyik optimális várossorozatot.
*/
/*
Hint 1: || A három feltétel közül az index szerinti növekedés miatt ez nem sima 2D rendezés, hanem részbenrendezési lánc. ||
Hint 2: || A `j < i`, `R[j] < R[i]`, `A[j] < A[i]` feltételekhez jól illik a CDQ felosztás az index mentén. ||
Hint 3: || A merge-ben a bal oldali pontokat add a Fenwick-fához `R` szerint, és a jobb oldali pontra kérdezd le az `A` szerinti prefixmaximumot. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct City {
    int r;
    int a;
    int ca;
    int idx;
};

struct FenwickMax {
    int n;
    vector<pair<int, int>> bit;
    vector<int> touched;

    explicit FenwickMax(int n_) : n(n_), bit(n_ + 1, {0, -1}) {}

    void update(int idx, pair<int, int> val) {
        for (int i = idx; i <= n; i += i & -i) {
            if (val.first > bit[i].first) {
                bit[i] = val;
            }
            touched.push_back(i);
        }
    }

    pair<int, int> query(int idx) const {
        pair<int, int> res = {0, -1};
        for (int i = idx; i > 0; i -= i & -i) {
            if (bit[i].first > res.first) {
                res = bit[i];
            }
        }
        return res;
    }

    void clear() {
        for (int idx : touched) {
            bit[idx] = {0, -1};
        }
        touched.clear();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<City> cities(n);
    vector<int> allA;
    allA.reserve(n);
    for (int i = 0; i < n; ++i) {
        cin >> cities[i].r >> cities[i].a;
        cities[i].idx = i;
        allA.push_back(cities[i].a);
    }

    sort(allA.begin(), allA.end());
    allA.erase(unique(allA.begin(), allA.end()), allA.end());
    for (int i = 0; i < n; ++i) {
        cities[i].ca = (int)(lower_bound(allA.begin(), allA.end(), cities[i].a) - allA.begin()) + 1;
    }

    vector<int> dp(n, 1), parent(n, -1);
    FenwickMax fenwick((int)allA.size());

    function<void(int, int)> cdq = [&](int l, int r) {
        if (l >= r) return;
        int mid = (l + r) >> 1;
        cdq(l, mid);

        vector<City> left(cities.begin() + l, cities.begin() + mid + 1);
        vector<City> right(cities.begin() + mid + 1, cities.begin() + r + 1);
        sort(left.begin(), left.end(), [](const City &x, const City &y) {
            if (x.r != y.r) return x.r < y.r;
            if (x.a != y.a) return x.a < y.a;
            return x.idx < y.idx;
        });
        sort(right.begin(), right.end(), [](const City &x, const City &y) {
            if (x.r != y.r) return x.r < y.r;
            if (x.a != y.a) return x.a < y.a;
            return x.idx < y.idx;
        });

        int i = 0;
        for (const City &cur : right) {
            while (i < (int)left.size() && left[i].r < cur.r) {
                int idx = left[i].idx;
                fenwick.update(left[i].ca, {dp[idx], idx});
                ++i;
            }
            pair<int, int> best = fenwick.query(cur.ca - 1);
            if (best.first + 1 > dp[cur.idx]) {
                dp[cur.idx] = best.first + 1;
                parent[cur.idx] = best.second;
            }
        }
        fenwick.clear();

        cdq(mid + 1, r);
    };

    cdq(0, n - 1);

    int bestEnd = 0;
    for (int i = 1; i < n; ++i) {
        if (dp[i] > dp[bestEnd]) {
            bestEnd = i;
        }
    }

    vector<int> answer;
    for (int cur = bestEnd; cur != -1; cur = parent[cur]) {
        answer.push_back(cur + 1);
    }
    reverse(answer.begin(), answer.end());

    cout << answer.size() << '\n';
    for (int i = 0; i < (int)answer.size(); ++i) {
        if (i) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}