/*
Megoldási ötlet:
Tekintsük a táblázat sorait permutációknak. Egy sor bármely kitöltése az 1..N számok egy permutációja,
és két egymást követő sor között pontosan az a feltétel, hogy azonos oszlopban nem állhat ugyanaz a szám.

Az első ismert sor bal felső L elemének rögzítése után az első sor kitöltése egyszerűen (N-L)! féle.
Nehéznek az látszik, hogyan számoljuk meg két egymást követő, részben ismert sor együttes kiegészítését.

Rögzítsünk egy már teljesen kitöltött i. sort, és számoljuk meg, hányféleképpen egészíthető ki az (i+1). sor,
ha annak első L eleme adott. Az (i+1). sor prefixében szereplő számok közül néhány már benne van az i. sor
prefixében, a többi biztosan az i. sor utolsó N-L oszlopaiban található. Jelölje t ezeknek a "kívülről jövő"
számoknak a darabszámát, vagyis

    t = |{A(i+1,1), ..., A(i+1,L)} \ {A(i,1), ..., A(i,L)}|.

Ez csak a két szomszédos prefix halmazától függ, a konkrét kiegészítéstől nem.

Az (i+1). sor első L eleme után pontosan m = N-L hely marad. Ezekre m számot kell letenni. Az i. sor utolsó m
oszlopában pontosan t olyan szám áll, amelyet már elhasznált az (i+1). sor prefixe, ezért ezekben az oszlopokban
nincs tiltás. A maradék m-t oszlopban viszont pontosan 1-1 tiltott szám van: oda nem kerülhet ugyanaz, mint az i.
sorban. Így a feladat arra redukálódik, hogy m helyre m számot rendezzünk úgy, hogy pontosan m-t megadott helyen
tilos legyen egy-egy konkrét érték.

Ezt inklúzió-kizárással lehet megszámolni:

    ways[t] = sum_{s=0..m-t} (-1)^s * C(m-t, s) * (m-s)!

ahol s azt jelenti, hány tiltást sértünk meg egyszerre. Ezt minden t-re előre kiszámoljuk O(m^2)-ben.

Ezután a teljes válasz szorzat alakú:
1. az első sor kiegészítése: (N-L)!
2. minden két egymást követő ismert sor között: ways[t_i]
3. a még teljesen ismeretlen utolsó N-K sor mindegyike az előző sorhoz képest tetszőleges derangement lehet,
   ezek száma D(N), ezért innen D(N)^(N-K) szorzó jön.

Így az algoritmus O(N^2 + K*L), ami bőven elég N <= 2000 mellett.
*/
/*
Hint 1: || Először ne a teljes táblázatot nézd, hanem csak két szomszédos sort: mindkettő permutáció, és oszloponként különbözniük kell. ||
Hint 2: || Egy rögzített sor mellett a következő sor prefixének csak az számít, hány eleme hiányzik az előző prefix halmazából. ||
Hint 3: || A maradék N-L helyre már egy olyan permutációszámlálás marad, ahol bizonyos oszlopokban egyetlen konkrét érték tiltott. ||
Hint 4: || Az ilyen számlálást természetesen inklúzió-kizárással lehet megkapni: válaszd ki, mely tiltásokat sérted meg. ||
*/

#include <bits/stdc++.h>

using namespace std;

static constexpr long long MOD = 1000000007LL;

long long mod_pow(long long base, long long exponent) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent & 1LL) {
            result = result * base % MOD;
        }
        base = base * base % MOD;
        exponent >>= 1LL;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, l;
    if (!(cin >> n >> k >> l)) {
        return 0;
    }

    const int m = n - l;

    vector<long long> fact(n + 1, 1), inv_fact(n + 1, 1), derangement(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    inv_fact[n] = mod_pow(fact[n], MOD - 2);
    for (int i = n; i >= 1; --i) {
        inv_fact[i - 1] = inv_fact[i] * i % MOD;
    }

    derangement[0] = 1;
    if (n >= 1) {
        derangement[1] = 0;
    }
    for (int i = 2; i <= n; ++i) {
        derangement[i] = (i - 1) * ((derangement[i - 1] + derangement[i - 2]) % MOD) % MOD;
    }

    vector<long long> ways_by_outside(m + 1, 0);
    for (int outside = 0; outside <= m; ++outside) {
        const int constrained = m - outside;
        long long ways = 0;
        for (int broken = 0; broken <= constrained; ++broken) {
            long long combinations = fact[constrained] * inv_fact[broken] % MOD * inv_fact[constrained - broken] % MOD;
            long long term = combinations * fact[m - broken] % MOD;
            if (broken % 2 == 0) {
                ways += term;
            } else {
                ways -= term;
            }
            ways %= MOD;
        }
        if (ways < 0) {
            ways += MOD;
        }
        ways_by_outside[outside] = ways;
    }

    vector<int> previous_prefix(l), current_prefix(l);
    vector<char> previous_in_prefix(n + 1, false), current_in_prefix(n + 1, false);

    bool valid = true;
    for (int column = 0; column < l; ++column) {
        int value;
        cin >> value;
        previous_prefix[column] = value;
        if (value < 1 || value > n || previous_in_prefix[value]) {
            valid = false;
        } else {
            previous_in_prefix[value] = true;
        }
    }

    long long answer = fact[m];

    for (int row = 1; row < k; ++row) {
        fill(current_in_prefix.begin(), current_in_prefix.end(), false);
        int outside = 0;

        for (int column = 0; column < l; ++column) {
            int value;
            cin >> value;
            current_prefix[column] = value;

            if (value < 1 || value > n || current_in_prefix[value]) {
                valid = false;
            }
            if (value == previous_prefix[column]) {
                valid = false;
            }

            if (1 <= value && value <= n) {
                if (!previous_in_prefix[value]) {
                    ++outside;
                }
                current_in_prefix[value] = true;
            }
        }

        if (valid) {
            answer = answer * ways_by_outside[outside] % MOD;
        }

        swap(previous_prefix, current_prefix);
        swap(previous_in_prefix, current_in_prefix);
    }

    if (!valid) {
        cout << 0 << '\n';
        return 0;
    }

    answer = answer * mod_pow(derangement[n], n - k) % MOD;
    cout << answer % MOD << '\n';
    return 0;
}