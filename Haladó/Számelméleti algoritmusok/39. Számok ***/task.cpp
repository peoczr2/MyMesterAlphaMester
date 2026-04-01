/*
 * Két számra eldöntjük, hogy a query értékek előállíthatók-e nemnegatív
 * együtthatókkal.
 
Hint 1: || Ez ugyanaz az alapötlet, mint a diofantoszi feladatnál: `Z = A*x + B*y` nemnegatív megoldhatóságát kell eldönteni. ||
Hint 2: || Előbb szűrj gcd-vel, utána egy moduláris feltételből ellenőrizd, hogy marad-e nemnegatív másik együttható is. ||
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
