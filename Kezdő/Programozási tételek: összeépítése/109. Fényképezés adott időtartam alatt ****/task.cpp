/*
Megoldás lényege: a perceket egész időpontoknak tekintjük: egy ember az [Érki, Távi] percekben van jelen, a fényképész pedig a [t, t+P-1] perceket tölti.
Egy ember akkor fotózható, ha ez a két zárt intervallum metszi egymást. A nem fotózható emberek vagy később érkeztek (érkezés > t+P-1),
vagy korábban távoztak (távozás < t); ez a két csoport nem fedi át egymást. Így a fotózható emberek száma:
(érkezők, akik érkezése <= t+P-1) mínusz (távozók, akik távozása < t), ami prefixösszegekből minden t-re O(1) alatt adódik.
A t lehetséges értékei: [legkorábbi érkezés, legkésőbbi távozás - P + 1]; döntetlennél a későbbi t-t írjuk ki.
Időigény: O(N + T), ahol T = 10 000.
*/
/*
Hint 1: || Számold meg a nem fotózható embereket is: akik a t+P-1 perc után érkeztek, illetve akik t előtt távoztak. Ez a két csoport diszjunkt. ||
Hint 2: || Az érkezési és távozási időpontok darabszámát prefixösszegekbe rendezve bármely t-re megkapod a fotózható emberek számát. A t-t a lehetséges tartományban keresd, döntetlennél a későbbit választva! ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int T = 10000;  // legnagyobb időpont
    int n, p;
    cin >> n >> p;

    vector<int> startAt(T + 2, 0), endAt(T + 2, 0);
    int firstArrival = INT_MAX, lastDeparture = INT_MIN;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        startAt[a]++;
        endAt[b]++;
        firstArrival = min(firstArrival, a);
        lastDeparture = max(lastDeparture, b);
    }

    // arrivedBy[x]: hányan érkeztek x-ig (x-et is beleértve); leftBy[x]: hányan távoztak x-ig
    vector<int> arrivedBy(T + 2, 0), leftBy(T + 2, 0);
    for (int x = 1; x <= T; x++) {
        arrivedBy[x] = arrivedBy[x - 1] + startAt[x];
        leftBy[x] = leftBy[x - 1] + endAt[x];
    }

    int bestT = -1, bestCount = -1;
    for (int t = firstArrival; t + p - 1 <= lastDeparture; t++) {
        int last = t + p - 1;
        int photographed = arrivedBy[last] - leftBy[t - 1];
        if (photographed >= bestCount) {
            bestCount = photographed;
            bestT = t;
        }
    }
    cout << bestT << "\n" << bestCount << "\n";
    return 0;
}
