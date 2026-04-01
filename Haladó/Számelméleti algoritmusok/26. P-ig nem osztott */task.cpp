/*
 * A legkisebb N számot keressük, amely osztható P-vel, és minden kisebb, 1-től
 * különböző számmal osztva 1 maradékot ad. Ez a CRT alapján oldható meg.
 
Hint 1: || A feltétel azt mondja, hogy `N ≡ 1 (mod d)` minden `2 <= d < P` esetén, miközben `P | N`. ||
Hint 2: || Ez kínai maradéktételes feladat: a `lcm(2,3,...,P-1)` moduluson kell az 1 maradékos feltételt összehangolni a `0 mod P` feltétellel. ||
*/

#include "../common.hpp"

static __int128 abs128(__int128 x) { return x < 0 ? -x : x; }

static __int128 extgcd128(__int128 a, __int128 b, __int128& x, __int128& y) {
    if (b == 0) {
        x = 1; y = 0; return a;
    }
    __int128 x1, y1;
    __int128 g = extgcd128(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

static string to_string_i128(__int128 x) {
    if (x == 0) return "0";
    bool neg = x < 0;
    if (neg) x = -x;
    string s;
    while (x > 0) {
        s.push_back(char('0' + int(x % 10)));
        x /= 10;
    }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int p;
    cin >> p;
    __int128 l = 1;
    for (int i = 2; i < p; ++i) {
        __int128 g = gcdll((long long)l, i);
        l = l / g * i;
    }
    __int128 x, y;
    extgcd128(p, l, x, y);
    x %= l;
    if (x < 0) x += l;
    __int128 ans = p * x;
    cout << to_string_i128(ans) << '\n';
    return 0;
}
