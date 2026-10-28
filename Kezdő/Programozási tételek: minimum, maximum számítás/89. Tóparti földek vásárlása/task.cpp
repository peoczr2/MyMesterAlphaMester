/*
Megoldás lényege:
Egy szakasz haszna K év alatt K * (a belőle évente elérhető bevételek összege) - (a vételárak összege). Ezért birtokonként a v_i = K * B_i - A_i érték adja a birtok hozzájárulását, és a feladat a körbe érő, legfeljebb N hosszú folytonos szakasz legnagyobb összegének keresése. A sorozatot kétszer egymás után írjuk, a prefixösszegek különbsége adja a szakasz összegét, a kezdőpontot pedig monoton deque-kel kezelt csúszó minimummal találjuk meg. Az összeg akár 10^10 nagyságrendű is lehet, ezért 64 bites egészekkel számolunk. Az időigény O(N). Ha a legjobb haszon negatív, minden vásárlás veszteséges, és -1-et írunk.
*/
/*
Hint 1: || Egy szakasz haszna K év alatt a bevételek K-szorosának és a vételárak összegének különbsége. Birtokonként számold ki, mennyivel járul hozzá ez egy szakaszhoz. ||
Hint 2: || A feladat ezután egy körbe érő, legfeljebb N hosszú folytonos szakasz legnagyobb összege. Ha a sorozatot kétszer egymás után írod le, a körbe érő szakaszok egyenes szakaszként kezelhetők, és egy szakasz összege két prefixösszeg különbsége. ||
Hint 3: || Rögzített végpontnál a legjobb kezdőpont az az index az [e-N, e) ablakban, ahol a prefixösszeg a legkisebb. Ezt csúszó ablakos minimummal, monoton deque-kel tartsd karban, és használj 64 bites egészeket. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> v(n);
    for (int i = 0; i < n; i++) {
        long long a, b;
        cin >> a >> b;
        v[i] = k * b - a;
    }

    // p[t] a kétszer leírt sorozat első t elemének összege
    vector<long long> p(2 * n + 1, 0);
    for (int t = 0; t < 2 * n; t++) {
        p[t + 1] = p[t] + v[t % n];
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

    if (best < 0) {
        cout << -1 << "\n";
        return 0;
    }
    cout << best << "\n";
    cout << bestS % n + 1 << " " << (bestE - 1) % n + 1 << "\n";
    return 0;
}
