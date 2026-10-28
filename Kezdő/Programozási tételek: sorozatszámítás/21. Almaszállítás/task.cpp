/*
Megoldás lényege:
Mivel minden konténer súlya pozitív, egy egymás melletti szakasz összege bővítéskor nő, szűkítéskor csökken.
Ezért kétmutatós (csúszóablakos) módszerrel egyetlen menetben végigmehetünk az összes szakaszon: a jobb mutatóval bővítjük az ablakot, és amíg az összeg nagyobb K-nál, a bal mutatóval szűkítünk.
Ha az aktuális összeg pontosan K, és az ablak rövidebb a korábbi legjobbnál, eltároljuk a hosszát és a kezdő sorszámát.
Minden elem legfeljebb egyszer kerül be és ki az ablakból, így az időigény O(N).
*/
/*
Hint 1: || Mivel minden súly pozitív, a szakasz összege a jobb végpont növelésével nő, a bal végpont léptetésével csökken. ||
Hint 2: || Tartsd nyilván az aktuális ablak összegét: a jobb mutatóval bővíts, és amíg az összeg nagyobb K-nál, a bal mutatóval szűkíts. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> s(n);
    for (auto &x : s) cin >> x;

    long long sum = 0;
    int best = INT_MAX, start = 0;
    int l = 0;
    for (int r = 0; r < n; r++) {
        sum += s[r];
        while (l <= r && sum > k) {
            sum -= s[l];
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
