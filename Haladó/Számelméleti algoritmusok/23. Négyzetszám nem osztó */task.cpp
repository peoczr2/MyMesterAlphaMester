/*
Megoldás lényege:
Egy szám akkor nem osztható egyetlen p^2 alakú számmal sem (1 kivételével), ha négyzetmentes, ezért az [A,B] intervallum négyzetmentes elemeit kell kiírni.
Mivel B-A legfeljebb 10^4, elég egy logikai tömb az intervallum elemeihez: minden p prímre, amelyre p^2 nem nagyobb B-nél, megjelöljük az intervallumban a p^2 többszöröseit.
Az első megjelölendő többszöröst az A-hoz legközelebbi p^2-es többszörös adja, innen p^2-es lépésekkel haladunk; a prímeket szitával állítjuk elő a sqrt(B) határig.
A meg nem jelölt számokat növekvő sorrendben írjuk ki. Az időigény O((B-A) + sqrt(B)), ami bőven belefér az időlimitbe.
*/
/*
Hint 1: || A keresett számok a négyzetmentes számok, vagyis amelyeket nem oszt semelyik `p^2` alakú szám. ||
Hint 2: || Az `[A,B]` intervallumban jelöld meg minden prímszám négyzetének többszöröseit, és ami nem lett megjelölve, azt kell kiírni. ||
*/
#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;
    vector<char> bad(b - a + 1, false);
    vector<int> primes = sieve_primes((int)sqrt(b) + 1);
    for (int p : primes) {
        long long sq = 1LL * p * p;
        long long first = (a + sq - 1) / sq * sq;
        for (long long x = first; x <= b; x += sq) bad[x - a] = true;
    }
    bool first = true;
    for (int x = a; x <= b; ++x) if (!bad[x - a]) {
        if (!first) cout << ' ';
        first = false;
        cout << x;
    }
    cout << '\n';
    return 0;
}
