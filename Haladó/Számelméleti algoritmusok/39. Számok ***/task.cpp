/*
 * Az A*x + B*y = Z egyenlet nemnegatív megoldhatóságát vizsgáljuk minden lekérdezésre. Legyen g = lnko(A,B):
 * ha g nem osztja Z-t, nincs megoldás; különben A, B és Z értékét g-vel osztjuk. Legyen a a kisebb, b a nagyobb
 * együttható: a b*y = z (mod a) kongruencia legkisebb nemnegatív y megoldását a b moduláris inverzével számoljuk ki
 * (kiterjesztett euklideszi algoritmus). Nemnegatív megoldás akkor van, ha b*y <= z. Lekérdezésenként O(log(A+B)).
*/
/*
Hint 1: || Ha lnko(A,B) nem osztja Z-t, a válasz biztosan „Nem”. Egyébként A, B és Z leosztása után relatív prím együtthatókkal dolgozhatsz. ||
Hint 2: || Relatív prím A' és B' esetén a B'*y ≡ Z' (mod A') egyenlet legkisebb nemnegatív y megoldásából ellenőrizd, hogy B'*y <= Z'. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 a, b;
    int n;
    cin >> a >> b >> n;
    int64 g = gcdll(a, b);
    a /= g;
    b /= g;
    if (a > b) swap(a, b);
    auto ext = [&](auto self, int64 x, int64 y) -> pair<int64,int64> {
        if (y == 0) return {1, 0};
        auto [u, v] = self(self, y, x % y);
        return {v, u - (x / y) * v};
    };
    auto [inv, dummy] = ext(ext, b, a);
    inv = (inv % a + a) % a;
    while (n--) {
        int64 z;
        cin >> z;
        if (z % g != 0) {
            cout << "Nem\n";
            continue;
        }
        z /= g;
        int64 y = (z % a) * inv % a;
        cout << (y * b <= z ? "Igen" : "Nem") << '\n';
    }
    return 0;
}
