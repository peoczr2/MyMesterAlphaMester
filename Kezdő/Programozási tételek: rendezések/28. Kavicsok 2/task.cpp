/*
Megoldás lényege:
Egy kupacból minden elvétellel a kupac eggyel csökken, így egy d kavicsos kupacból a kavicsok értéke sorban d, d-1, ..., 1 forint.
Mindig a jelenleg legnagyobb értékű kavicsot véve a végeredmény a K legnagyobb érték összege lesz.
Elég a K legnagyobb kupacot megtartani: egy kisebb kupac értékei nem nagyobbak a K-adik legnagyobb kupacméretnél, az pedig már K darab legalább ekkora értéket ad.
A K-adik legnagyobb érték (T) bináris kereséssel keresendő: a T-nél nem kisebb értékek száma egy d kupacnál max(0, d-T+1).
A T-nél nagyobb értékek összegét számtani sorozat képletével adjuk össze, a hiányzó darabokat pedig T forintért vesszük el.
Az időigény O(N log K + m log D), ahol m = min(N, K) és D a legnagyobb kupacméret.
*/
/*
Hint 1: || Minden elvétel után a kupac eggyel kisebb lesz, így egy kupac kavicsai sorban d, d-1, ..., 1 forintot érnek. Mindig a legnagyobb aktuális értékű kavicsot érdemes elvenni. ||
Hint 2: || Válassz egy T értéket, és számold meg, hány kavics ér legalább T forintot: egy d kavicsos kupacból ez max(0, d-T+1). Ez a szám T-ben csökkenő, így a K-adik legnagyobb értéket bináris kereséssel megtalálhatod. ||
Hint 3: || A T-nél nagyobb értékek összegét számtani sorozat összegeként add össze kupaconként: d(d+1)/2 - T(T+1)/2. A maradék (K - darabszám) kavicsot T forintért vedd el. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k;
    cin >> n >> k;

    // A K legnagyobb kupacot tartjuk meg min-kupacban
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    for (long long i = 0; i < n; i++) {
        long long d;
        cin >> d;
        if ((long long)pq.size() < k) {
            pq.push(d);
        } else if (d > pq.top()) {
            pq.pop();
            pq.push(d);
        }
    }

    vector<long long> kupac;
    while (!pq.empty()) {
        kupac.push_back(pq.top());
        pq.pop();
    }

    // Hány kavics értéke legalább t
    auto darab_ge = [&](long long t) {
        long long c = 0;
        for (long long d : kupac)
            if (d >= t) c += d - t + 1;
        return c;
    };

    // A legnagyobb t, amelyre legalább K kavics értéke nem kisebb t-nél
    long long lo = 0, hi = *max_element(kupac.begin(), kupac.end());
    while (lo < hi) {
        long long mid = (lo + hi + 1) / 2;
        if (darab_ge(mid) >= k) lo = mid;
        else hi = mid - 1;
    }
    long long t = lo;

    // A t-nél nagyobb értékek összege, plusz a hiányzó kavicsok t forintonként
    long long osszeg = 0, elvett = 0;
    for (long long d : kupac) {
        if (d > t) {
            osszeg += d * (d + 1) / 2 - t * (t + 1) / 2;
            elvett += d - t;
        }
    }
    osszeg += (k - elvett) * t;

    cout << osszeg << '\n';
    return 0;
}
