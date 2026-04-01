/*
 * A két generátor által előállítható számok között keressük a legkisebb X >= C
 * értéket. A megoldás a maradékok ciklikus vizsgálatára és floor-sum számlálásra
 * épül.
 
Hint 1: || A kérdés nem az, hogy C előállítható-e, hanem hogy mi a legkisebb előállítható szám C fölött vagy egyenlő vele. ||
Hint 2: || Érdemes a kisebb együttható szerinti maradékosztályokat vizsgálni, és ezekből meghatározni, mekkora a legkisebb elérhető felkerekítés. ||
Hint 3: || Ha egy maradékosztályban tudod a legkisebb jó értéket, akkor minden nagyobb, ugyanolyan maradékú szám egyszerűen ennek egy többszörössel való eltolása. ||
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b, c;
    cin >> a >> b >> c;
    long long g = gcdll(a, b);
    a /= g;
    b /= g;
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
    cout << g * min(high, candidate) << '\n';
    return 0;
}
