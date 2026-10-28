/*
Megoldás lényege:
Mivel minden útszakasz hossza pozitív, egymás melletti szakaszok összege bővítéskor nő, szűkítéskor csökken.
Ezért kétmutatós (csúszóablakos) módszerrel egyetlen menetben végigmehetünk az összes folytonos szakaszon: a jobb mutatóval bővítjük, és amíg az összeg nagyobb K-nál, a bal mutatóval szűkítünk.
Ha az aktuális összeg pontosan K, és a szakasz rövidebb a korábbi legjobbnál, eltároljuk az útszakaszok számát és a kezdő sorszámát.
A kimenet a verseny első lezárt útszakaszának sorszáma, a minta szerint az A. és az A+U-1. szakasz összhossza K.
Minden elem legfeljebb egyszer kerül be és ki az ablakból, így az időigény O(N).
*/
/*
Hint 1: || Mivel minden távolság pozitív, a szakasz hossza a jobb végpont növelésével nő, a bal végpont léptetésével csökken. ||
Hint 2: || Tartsd nyilván az aktuális szakasz összhosszát: a jobb mutatóval bővíts, és amíg az összeg nagyobb K-nál, a bal mutatóval szűkíts. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> t(n);
    for (auto &x : t) cin >> x;

    long long sum = 0;
    int best = INT_MAX, start = 0;
    int l = 0;
    for (int r = 0; r < n; r++) {
        sum += t[r];
        while (l <= r && sum > k) {
            sum -= t[l];
            l++;
        }
        if (sum == k && r - l + 1 < best) {
            best = r - l + 1;
            start = l + 1;
        }
    }

    if (best == INT_MAX) {
        cout << 0 << "\n" << 0 << "\n";
    } else {
        cout << best << "\n" << start << "\n";
    }
    return 0;
}
