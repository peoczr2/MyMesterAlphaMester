/*
Megoldás lényege:
Ha K háznál mindenki szolgáltatása elérhető, akkor van olyan K hosszú [x; x+K-1] szakasz, amelyet minden szolgáltató lefed, és egy bővebb szakasz sosem olcsóbb, ezért pontosan K hosszút érdemes nézni. Egy [L;R] szolgáltató a [x; y] szakaszt max(0; L-x) + max(0; y-R) petákért fedi le. Az összköltség f(x) x-ben konvex függvény, ezért bináris kereséssel megkeressük azt az x-et, ahol a szomszédos értékek különbsége először nem negatív. Egy f(x) kiértékelése O(N), a teljes időigény O(N log(maxR)).
*/
/*
Hint 1: || A közös lefedés egy szakasz. Ha legalább K ház közös, akkor van olyan K hosszú [x; x+K-1] szakasz, amelyet mindenki lefed, és ezt kell a legolcsóbban kialakítani. ||
Hint 2: || Egy [L;R] szolgáltatónak a [x; y] szakaszhoz a bal oldalon max(0; L-x), a jobb oldalon max(0; y-R) lépés hiányzik. Ezek összege adja az adott x-re a teljes költséget. ||
Hint 3: || Az x szerinti költségfüggvény konvex, ezért nem kell minden x-et végigpróbálni: bináris keresést futtathatsz a x és x+1 pozíciók költségének különbségén, a keresési tartomány a legkisebb L és a legnagyobb R között van. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k;
    cin >> n >> k;
    vector<long long> l(n), r(n);
    for (int i = 0; i < n; i++) cin >> l[i] >> r[i];

    auto cost = [&](long long x) {
        long long y = x + k - 1;
        long long s = 0;
        for (int i = 0; i < n; i++) {
            if (l[i] > x) s += l[i] - x;
            if (y > r[i]) s += y - r[i];
        }
        return s;
    };

    long long lo = *min_element(l.begin(), l.end());
    long long hi = *max_element(r.begin(), r.end());
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (cost(mid + 1) - cost(mid) >= 0) hi = mid;
        else lo = mid + 1;
    }

    cout << cost(lo) << "\n";
    return 0;
}
