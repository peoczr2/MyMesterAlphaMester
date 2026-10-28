/*
Megoldás lényege: L és R legmagasabb eltérő bitjét B jelöli; e fölötti közös rész a három szám xorjában egyszer marad meg, így csak az alsó B+1 bit számít.
Az eredmény legnagyobb bitje 1 lehet, ha egy felső (B-edik bitű 1) és két alsó számot választunk, vagy három felső számot. Az első esetben az alsó számokat t = 2^B-1-x alakban véve a két alsó szám xorja bármely 1…2^(k+1)-1 érték lehet, ahol k a q = 2^B-1-(L alsó része) legmagasabb bitje; így a legjobb eredmény r | (2^(k+1)-1), ahol r = R-2^B. A második esetben a [0, r] tartomány legnagyobb hármas-xorja 2^(b+1)-1, ahol b az r legmagasabb bitje (r >= 2).
Ha csak három szám van, az egyetlen hármas adja a választ. A két jelölt közül a nagyobbat írjuk ki, a három számot növekvő sorrendben.
Időigény: O(T * log R), ami T <= 50 000 és R <= 10^18 mellett bőven belül van.
*/
/*
Hint 1: || A közös felső rész háromszoros xorja egyszer marad meg, így a döntés csak az első eltérő bit és az alatti bitek között van. Az eredmény legfelső bitjét érdemes először maximalizálni. ||
Hint 2: || A legfelső bit 1 lesz, ha vagy egy felső és két alsó számot, vagy három felső számot választasz. Egy alsó számot érdemes a 2^B-1-gyel való tükrözött értékével nézni, mert a két alsó szám xorja ettől nem változik. ||
Hint 3: || Egy felső és két alsó szám esetén a tükrözött alsó értékek egy [0, q] tartományból valók, így a páros xor minden 1…2^(k+1)-1 értéket felvehet, ahol k = log2(q). Az egész eredmény alsó része ilyenkor r | (2^(k+1)-1) lehet a legjobb. ||
Hint 4: || Három felső szám esetén ugyanaz a feladat a [0, r] tartományra, ahol a legnagyobb hármas-xor 2^(b+1)-1 (b = log2(r), r >= 2). Számold ki mindkét jelöltet, válaszd a nagyobbat, és a három számot rendezve írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Megadja a [L, R] tartomány egy olyan x, y, z hármasát, amelyre x^y^z maximális (sorrend nélkül).
void legjobbHarmas(ll L, ll R, ll &x, ll &y, ll &z) {
    int B = 63 - __builtin_clzll(L ^ R);     // legmagasabb eltérő bit
    ll P = (L >> (B + 1)) << (B + 1);         // közös felső rész
    ll a = L - P, c = R - P;                  // a < 2^B <= c < 2^(B+1)
    ll H = 1LL << B;
    ll r = c - H;                             // a felső számok alsó része: 0..r
    ll q = H - 1 - a;                         // alsó számok tükrözve: t = H-1-l, t in [0, q]
    ll best = -1, tx = 0, ty = 0, tz = 0;

    if (q >= 1) {                             // egy felső + két alsó szám
        int k = 63 - __builtin_clzll(q);
        ll K = 1LL << (k + 1);
        best = H + (r | (K - 1));
        tx = H + (r & ~(K - 1));              // felső szám
        ty = H - 1 - (1LL << k);              // alsó párok: t = 2^k és t = 2^k - 1
        tz = H - (1LL << k);
    }
    if (r >= 2) {                             // három felső szám
        int b = 63 - __builtin_clzll(r);
        ll val = H + ((1LL << (b + 1)) - 1);
        if (val > best) {
            best = val;
            tx = H + (1LL << (b - 1)) - 1;
            ty = H + (1LL << (b - 1));
            tz = H + (1LL << b);
        }
    }
    if (best < 0) {                           // pontosan három szám van
        tx = H - 1;
        ty = H;
        tz = H + 1;
    }
    x = P + tx;
    y = P + ty;
    z = P + tz;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    string out;
    while (T--) {
        ll L, R;
        cin >> L >> R;
        ll v[3];
        legjobbHarmas(L, R, v[0], v[1], v[2]);
        sort(v, v + 3);
        out += to_string(v[0]) + " " + to_string(v[1]) + " " + to_string(v[2]) + "\n";
    }
    cout << out;
    return 0;
}
