/*
Megoldás lényege:
Termenként külön nézzük a napokat. Minden foglalásnál megjelöljük a foglalt napokat egy
logikai tömbben, így az egy terem napjait egyetlen tömb tárolja. Ezután termenként
egyszer végigmegyünk a napokon, és megkeressük a szabad napok összefüggő szakaszait.
Egy szakasz hossza a két határ különbségéből adódik. A legjobb időszakot akkor frissítjük,
ha a talált szakasz szigorúan hosszabb a korábbinál. Mivel a termeket sorszám szerint,
a napokat pedig növekvő sorrendben nézzük, a döntetlennél a kisebb sorszámú terem és a
korábbi kezdés marad meg. Az időigény O(N·M + K·M), ami a korlátok mellett bőven belefér.
*/
/*
Hint 1: || Egy teremhez elég egy tömb, amely minden napról megmondja, hogy foglalt-e. ||
Hint 2: || Termekenként egyszer haladj végig a napokon, és keresd az összefüggő szabad szakaszokat. ||
Hint 3: || A döntetlen eseteket a bejárás sorrendje intézi el: a szigorú összehasonlítás a kisebb sorszámú termet és a korábbi kezdő napot tartja meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<bool>> booked(n + 1, vector<bool>(m + 2, false));
    for (int i = 0; i < k; i++) {
        int t, e, u;
        cin >> t >> e >> u;
        for (int d = e; d <= u; d++) booked[t][d] = true;
    }

    int bestLen = 0, bestRoom = 0, bestStart = 0, bestEnd = 0;

    for (int r = 1; r <= n; r++) {
        int d = 1;
        while (d <= m) {
            if (booked[r][d]) {
                d++;
                continue;
            }
            int s = d;
            while (d <= m && !booked[r][d]) d++;
            int e = d - 1;  // a szabad szakasz: [s, e]
            int len = e - s + 1;
            if (len > bestLen) {
                bestLen = len;
                bestRoom = r;
                bestStart = s;
                bestEnd = e;
            }
        }
    }

    if (bestLen == 0) {
        cout << 0 << "\n\n";
    } else {
        cout << bestRoom << '\n' << bestStart << ' ' << bestEnd << '\n';
    }
    return 0;
}
