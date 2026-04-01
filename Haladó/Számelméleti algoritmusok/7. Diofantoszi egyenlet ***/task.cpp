/*
 * Minden lekérdezett Z-re eldöntjük, hogy felírható-e A és B nemnegatív
 * többszöröseinek összegeként. A gcd-szűrés után egyetlen moduláris megoldást
 * vizsgálunk.
 
Hint 1: || Először nézd meg, hogy Z osztható-e gcd(A,B)-vel, mert ha nem, biztosan nem állítható elő. ||
Hint 2: || A gcd-szűrés után egy moduláris egyenletet kell megoldanod, hogy legyen nemnegatív x és y is az Ax+By=Z felírásban. ||
*/

#include "../common.hpp"

static pair<int64,int64> extgcd(int64 a, int64 b) {
    if (b == 0) return {1, 0};
    auto [x, y] = extgcd(b, a % b);
    return {y, x - (a / b) * y};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 a, b;
    int n;
    cin >> a >> b >> n;
    int64 g = gcdll(a, b);
    a /= g;
    b /= g;
    auto [x0, y0] = extgcd(a, b);
    int64 inv_a = (x0 % b + b) % b;
    while (n--) {
        int64 z;
        cin >> z;
        if (z % g != 0) {
            cout << "Nem\n";
            continue;
        }
        z /= g;
        int64 x = (z % b) * inv_a % b;
        int64 rem = z - a * x;
        if (rem < 0 || rem % b != 0) {
            cout << "Nem\n";
            continue;
        }
        int64 y = rem / b;
        cout << (y >= 0 ? "Igen" : "Nem") << '\n';
    }
    return 0;
}
