/*
Megoldás lényege:
N legfeljebb 8, ezért minden küldöttséghez megpróbálhatjuk az intervallumok
összes sorrendjét. Ha egy adott sorrendre a leszállási időpontok növekvő sorrendben
választhatók úgy, hogy a szomszédos időpontok között legalább d másodperc legyen,
akkor az a d biztonságos.

A feasibility teszt egyszerű greedy: az aktuális időpontot mindig a lehető
legkorábbira tesszük, amely még belefér az adott intervallumba és legalább d-vel
követi az előzőt. Bináris kereséssel megkapjuk a maximum d értéket, majd másodperc
pontossággal kiírjuk perc:másodperc formában.
*/
/*
Hint 1: || Bináris keresést végezz a biztonsági idő (∆t, másodpercben) értékén: ha egy d érték megvalósítható, akkor minden kisebb is az, így a keresés helyes. ||
Hint 2: || Egy adott d-hez és egy adott leszállási sorrendhez az időpontokat mohón a lehető legkorábbra tedd: a következő időpont max(az intervallum kezdete, az előző + d), és ellenőrizd, hogy nem lépi-e túl az intervallum végét. ||
Hint 3: || Mivel N legfeljebb 8, az összes sorrend (legfeljebb 8! = 40320) végigpróbálható; elég, ha valamelyik sorrend működik. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Interval {
    long double l, r;
};

static bool feasible(const vector<Interval>& a, long double d) {
    vector<int> p(a.size());
    iota(p.begin(), p.end(), 0);
    do {
        long double cur = a[p[0]].l;
        if (cur > a[p[0]].r) continue;
        bool ok = true;
        for (size_t i = 1; i < p.size(); ++i) {
            cur = max(a[p[i]].l, cur + d);
            if (cur > a[p[i]].r + 1e-12L) {
                ok = false;
                break;
            }
        }
        if (ok) return true;
    } while (next_permutation(p.begin(), p.end()));
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<Interval> a(n);
    for (int i = 0; i < n; ++i) {
        long double x, y;
        cin >> x >> y;
        a[i].l = x * 60.0L;
        a[i].r = y * 60.0L;
    }

    long double lo = 0, hi = 24.0L * 60.0L * 60.0L;
    for (int it = 0; it < 80; ++it) {
        long double mid = (lo + hi) / 2.0L;
        if (feasible(a, mid)) lo = mid;
        else hi = mid;
    }

    long long ans = llround(lo);
    cout << ans / 60 << ':' << setw(2) << setfill('0') << (ans % 60) << '\n';
    return 0;
}