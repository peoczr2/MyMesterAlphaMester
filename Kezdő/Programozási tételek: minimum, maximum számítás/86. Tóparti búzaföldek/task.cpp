/*
Megoldás lényege:
Egy szomszédos szakasz haszna a benne lévő birtokok (B_i - A_i) értékeinek összege, ezért a feladat a körkörös sorozat legnagyobb összegű, legfeljebb N hosszú folytonos szakaszának megkeresése. A sorozatot kétszer egymás után írjuk, így a körbe érő szakaszok is egyenes szakaszként szerepelnek. A prefixösszegekkel a [s, e) szakasz haszna P[e] - P[s]; rögzített e végponthoz a legjobb kezdőpont a [e-N, e) ablakban az, ahol P[s] a legkisebb. Ezt a csúszó minimumot monoton deque-kel tartjuk karban, így az egész O(N) időben fut. Ha a legjobb haszon nem pozitív, nincs megfelelő szakasz, és -1-et írunk.
*/
/*
Hint 1: || Egy szomszédos szakasz haszna a benne lévő birtokok (bevétel - költség) értékeinek összege. Gondold át, hogyan lehet a körbe érő szakaszokat közönséges, egyenes tömbön kezelni. ||
Hint 2: || Ha a sorozatot kétszer egymás után írod le, a körbe érő szakaszok is folytonos részsorozatok lesznek. Prefixösszegekkel egy [s, e) szakasz haszna P[e] - P[s], és a hossz legfeljebb N lehet. ||
Hint 3: || Rögzített e végpontnál a legjobb s az a kezdőpont a [e-N, e) ablakban, ahol P[s] a legkisebb. Ezt a csúszó ablakos minimumot monoton deque-kel tarthatod karban, így az egész O(N) időben megvan. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];

    // p[t] a kétszer leírt sorozat első t elemének összege
    vector<long long> p(2 * n + 1, 0);
    for (int t = 0; t < 2 * n; t++) {
        int i = t % n;
        p[t + 1] = p[t] + (b[i] - a[i]);
    }

    long long best = LLONG_MIN;
    int bestS = 0, bestE = 0;  // a legjobb szakasz: [bestS, bestE) a kétszer leírt sorozatban
    deque<int> dq;             // kezdőpontok, P szerint növekvő sorrendben
    for (int e = 1; e <= 2 * n; e++) {
        int s = e - 1;
        while (!dq.empty() && p[dq.back()] >= p[s]) dq.pop_back();
        dq.push_back(s);
        while (dq.front() < e - n) dq.pop_front();

        long long profit = p[e] - p[dq.front()];
        if (profit > best) {
            best = profit;
            bestS = dq.front();
            bestE = e;
        }
    }

    if (best <= 0) {
        cout << -1 << "\n";
        return 0;
    }
    cout << best << "\n";
    cout << bestS % n + 1 << " " << (bestE - 1) % n + 1 << "\n";
    return 0;
}
