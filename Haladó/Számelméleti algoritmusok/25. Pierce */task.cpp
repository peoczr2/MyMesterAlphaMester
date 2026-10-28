/*
Megoldás lényege:
A minta szerint a bemenet első száma a nevezők felső határa (1-től ennyiig), a második szám a törtek értékének zárt felső határa; a `2 3` mintából 11 tört adódik.
Mivel mindkét korlát kicsi, a sorozat elemei nyersen felsorolhatók: minden q nevezőre és minden 0 ≤ p ≤ V·q számlálóra felvesszük a p/q törtet, ahol V a második szám.
A törteket egész számokkal rendezzük: p1/q1 akkor kisebb p2/q2-nél, ha p1·q2 < p2·q1, egyenlő értéknél pedig a nagyobb nevező kerül előre.
A törtek száma kb. V·D²/2, ahol D az első szám, ez a korlátok mellett néhány ezer, így a rendezés időigénye elhanyagolható.
*/
/*
Hint 1: || A minta szerint az első szám a nevezők felső határa: a `2 3` bemenetből 11 tört adódik, nevezők 1 és 2, értékek 0 és 3 között. ||
Hint 2: || Sorold fel az összes `p/q` törtet, ahol `q` 1-től az első számig megy, `p` pedig 0-tól a második szám·q-ig, majd rendezd őket egész számos összehasonlítással; egyenlő értéknél a nagyobb nevező jöjjön előre. ||
*/
#include "../common.hpp"

struct Frac {
    int p, q;
};

static bool cmp(const Frac& a, const Frac& b) {
    long long lhs = 1LL * a.p * b.q;
    long long rhs = 1LL * b.p * a.q;
    if (lhs != rhs) return lhs < rhs;
    return a.q > b.q;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int d, v;
    cin >> d >> v;
    vector<Frac> fracs;
    for (int q = 1; q <= d; ++q) {
        for (int p = 0; p <= v * q; ++p) {
            fracs.push_back({p, q});
        }
    }
    sort(fracs.begin(), fracs.end(), cmp);
    for (auto [p, q] : fracs) cout << p << '/' << q << '\n';
    return 0;
}
