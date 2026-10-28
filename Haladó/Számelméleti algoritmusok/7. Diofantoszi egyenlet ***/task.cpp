/*
Megoldás lényege:
Ha g = gcd(A,B), akkor minden előállítható Z osztható g-vel, ezért először ezt ellenőrizzük. Ezután legyen a = A/g, b = B/g, z = Z/g, ekkor gcd(a,b) = 1, és az ax + by = z egyenletnek akkor van nemnegatív megoldása, ha a legkisebb nemnegatív x-re (ami x ≡ z·a^(-1) mod b) még a·x ≤ z. Ilyenkor y = (z − a·x)/b már egész és nemnegatív, különben nincs megoldás. A bővített euklideszi algoritmus adja az a inverzét, így egy lekérdezés O(log(max(A,B))) időben fut, és a legfeljebb 10 000 lekérdezés is gyorsan megvan.
*/
/*
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
