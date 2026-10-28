/*
Megoldás lényege:
Először g = gcd(A, B) szerint osztunk, így az együtthatók relatív prímek, az X pedig csak g többszöröse lehet. A kérdés ekkor az, hogy mi a legkisebb C' = ceil(C / g) feletti vagy egyenlő szám, amely K*a + L*b alakban előáll (a = A / g, b = B / g). Ezt bináris kereséssel határozzuk meg: egy D eltolásra floor_sum-os számlálással (O(log) időben) eldöntjük, van-e előállítható szám a [C', C' + D] tartományban. A második kimeneti sorba a felbontás kerül: L a [0, a - 1] tartományba eső, egyértelmű együttható (a B-hez tartozik), K pedig (Y - L * b) / a. Az idő O(log^2(max(A, B))).
*/
/*
Hint 1: || A kérdés nem az, hogy C előállítható-e, hanem hogy mi a legkisebb előállítható szám C fölött vagy egyenlő vele. ||
Hint 2: || Érdemes a kisebb együttható szerinti maradékosztályokat vizsgálni, és ezekből meghatározni, mekkora a legkisebb elérhető felkerekítés. ||
Hint 3: || Ha egy maradékosztályban tudod a legkisebb jó értéket, akkor minden nagyobb, ugyanolyan maradékú szám egyszerűen ennek egy többszörössel való eltolása. ||
Hint 4: || A felbontáshoz L-et a kisebb együttható modulusában keresd: L ≡ Y · b^(-1) (mod a), ahol b^(-1) a b moduló-inverze a szerint; utána K = (Y - L · b) / a adódik maradék nélkül. ||
*/

#include "../common.hpp"

static long long floor_div(long long a, long long b) {
    long long q = a / b;
    long long r = a % b;
    if (r < 0) --q;
    return q;
}

static long long mod_floor(long long a, long long b) {
    long long r = a % b;
    if (r < 0) r += b;
    return r;
}

static long long floor_sum(long long n, long long m, long long a, long long b) {
    long long ans = 0;
    while (true) {
        if (a >= m) {
            ans += (n - 1) * n * (a / m) / 2;
            a %= m;
        }
        if (b >= m || b < 0) {
            ans += n * floor_div(b, m);
            b = mod_floor(b, m);
        }
        long long y_max = a * n + b;
        if (y_max < m) break;
        n = y_max / m;
        b = y_max % m;
        swap(m, a);
    }
    return ans;
}

static long long modinv(long long a, long long m) {
    long long r0 = a, r1 = m, s0 = 1, s1 = 0;
    while (r1) {
        long long q = r0 / r1;
        long long t = r0 - q * r1;
        r0 = r1;
        r1 = t;
        t = s0 - q * s1;
        s0 = s1;
        s1 = t;
    }
    return ((s0 % m) + m) % m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b, c;
    cin >> a >> b >> c;
    long long g = gcdll(a, b);
    a /= g;
    b /= g;
    long long a0 = a, b0 = b;
    c = (c + g - 1) / g;
    if (a > b) swap(a, b);

    long long high = ((c + a - 1) / a) * a;
    long long M = c / a;
    long long s = mod_floor(-c, b);

    auto exists_residue_le = [&](long long D) {
        long long n = M + 1;
        long long c1 = floor_sum(n, b, a, s);
        long long c2 = floor_sum(n, b, a, s - D - 1);
        return c1 - c2 > 0;
    };

    long long lo = 0, hi = b - 1;
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        if (exists_residue_le(mid)) hi = mid; else lo = mid + 1;
    }
    long long candidate = c + lo;
    long long Y = min(high, candidate);
    cout << g * Y << '\n';
    long long L = a0 > 1 ? (Y % a0) * modinv(b0 % a0, a0) % a0 : 0;
    long long K = (Y - L * b0) / a0;
    cout << K << ' ' << L << '\n';
    return 0;
}
