/*
Megoldás lényege:
Csúcs az a köztes mérés, amely nagyobb az előző és a következő méresnél is, ezért egyetlen
végigmenéssel összegyűjthetjük a csúcsok sorszámait növekvő sorrendben. Egy K elemű csúcs-sorozat
legtávolabbi tagjainak távolsága az első és az utolsó sorszám különbsége, és a legkisebb ilyen
távolságú K elemű csoport mindig a csúcslistában egymás utáni elemekből áll (ha a csoport
elemei között kihagyunk egy csúcsot, a csoport szélessége nem lehet kisebb). Ezért a szomszédos
K-as csoportokat egyetlen menetben végigpróbáljuk, és megtartjuk a legkisebb távolságút.
Ha kevesebb mint K csúcs van, a válasz -1. Időigény O(N), memóriaigény O(N).
*/
/*
Hint 1: || Csúcs csak a sorozat belső pontja lehet, és akkor, ha mérése nagyobb az előző és a következő mérésnél is; ezeket egyetlen végigmenéssel, növekvő sorrendben gyűjtsd össze. ||
Hint 2: || A csúcsok sorszámait tömbben tárolva egy K csúcsból álló csoport legtávolabbi tagjainak távolsága az első és az utolsó sorszám különbsége, ezért elég a szomszédos, K hosszú részeket megnézni. ||
Hint 3: || Ha az i-edik csúcstól kezdődő K csúcs távolsága p[i+K-1] - p[i], ezt minden i-re kiszámolva megjegyezheted a minimumot és a kezdőindexét; ha kevesebb csúcs van, mint K, a válasz -1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<int> m(N);
    for (int i = 0; i < N; i++)
        cin >> m[i];

    // a csúcsok sorszámai (1-től számozva), növekvő sorrendben
    vector<int> peaks;
    for (int i = 1; i + 1 < N; i++)
        if (m[i] > m[i - 1] && m[i] > m[i + 1])
            peaks.push_back(i + 1);

    int cnt = peaks.size();
    if (cnt < K) {
        cout << -1 << '\n';
        return 0;
    }

    int bestDist = INT_MAX, bestStart = 0;
    for (int s = 0; s + K <= cnt; s++) {
        int d = peaks[s + K - 1] - peaks[s];
        if (d < bestDist) {
            bestDist = d;
            bestStart = s;
        }
    }

    cout << bestDist << '\n';
    for (int i = 0; i < K; i++)
        cout << peaks[bestStart + i] << (i + 1 < K ? ' ' : '\n');
    return 0;
}
