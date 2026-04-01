/*
 * A mintában látható sorrend alapján a feladat az összes q < N nevezőjű és
 * 0 <= p/q <= M+1 alakú tört felsorolása, rendezve érték szerint, egyenlő értéknél
 * a nagyobb nevező előre kerül.
 
Hint 1: || A nevező felső korlátja nagyon kicsi, ezért a törtlista nyersen is legenerálható. ||
Hint 2: || Készítsd el az összes `p/q` törtet a megadott határok között, majd rendezd érték szerint; egyenlő értéknél a nagyobb nevező jöjjön előre. ||
Hint 3: || Ha a mintában látszó sorrend nem tisztán numerikus, a rendezés másodlagos kulcsa pontosan ezt a tie-breaket fogja visszaadni. ||
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

    int m, n;
    cin >> m >> n;
    vector<Frac> fracs;
    for (int q = 1; q < n; ++q) {
        for (int p = 0; p <= (m + 1) * q; ++p) {
            fracs.push_back({p, q});
        }
    }
    sort(fracs.begin(), fracs.end(), cmp);
    for (auto [p, q] : fracs) cout << p << '/' << q << '\n';
    return 0;
}
