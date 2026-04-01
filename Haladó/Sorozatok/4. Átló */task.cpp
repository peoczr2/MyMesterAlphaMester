/*
Megoldas lenyege:
Az N csucsot egy korvonal menten 1..N sorrendben tekintjuk. Két átló akkor metszi egymást,
hogyha a csúcspárjaik körben felváltva helyezkednek el. Az újonnan beolvasott átlót minden
korábbival összevetjük, és az első metsző helyen megállunk.
*/
/*
Hint 1: || Két átló metszéséhez az kell, hogy a két végpontpár körben felváltva álljon. ||
Hint 2: || Ha két átló ugyanazt a két csúcsot köti össze, azt is ütközésnek kell tekinteni. ||
Hint 3: || M=1000 mellett a páronkénti ellenőrzés is kényelmesen belefér. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Diagonal {
    int a, b;
};

static bool between(int n, int a, int x, int b) {
    int ab = (b - a + n) % n;
    int ax = (x - a + n) % n;
    return 0 < ax && ax < ab;
}

static bool intersects(int n, const Diagonal &p, const Diagonal &q) {
    if ((p.a == q.a && p.b == q.b) || (p.a == q.b && p.b == q.a)) {
        return true;
    }
    bool qa = between(n, p.a, q.a, p.b);
    bool qb = between(n, p.a, q.b, p.b);
    bool pa = between(n, q.a, p.a, q.b);
    bool pb = between(n, q.a, p.b, q.b);
    return qa != qb && pa != pb;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Diagonal> prev;
    prev.reserve(m);

    for (int i = 1; i <= m; ++i) {
        Diagonal cur;
        cin >> cur.a >> cur.b;
        for (const auto &old : prev) {
            if (intersects(n, old, cur)) {
                cout << i << '\n';
                return 0;
            }
        }
        prev.push_back(cur);
    }

    cout << 0 << '\n';
    return 0;
}
