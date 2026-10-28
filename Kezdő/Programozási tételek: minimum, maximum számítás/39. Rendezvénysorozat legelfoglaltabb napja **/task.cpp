/*
Megoldás lényege:
Minden foglalás a [E, U] napokon pontosan egy termet köt le, így az adott napon foglalt termek száma azt adja, hány foglalási intervallum fedi le a napot. Ezt egy különbségi tömbbel számoljuk: az E. napnál +1-et, az U+1. napnál -1-et írunk, majd a prefixösszeg adja a napi darabszámot. Mivel egy teremben nincs átfedés, a napi darabszám valóban a lefoglalt termek számát jelenti. A napokat sorban bejárva a szigorú összehasonlítás miatt a legkisebb sorszámú maximális nap marad meg. Az időigény O(M + K), a tárigény O(M).
*/
/*
Hint 1: || Egy nap lefoglalt termeinek száma megegyezik azzal, hány foglalási intervallum tartalmazza az adott napot. Nem kell minden napra külön végigmenni az összes foglaláson: gondolkodj azon, hogyan változik a darabszám, amikor a napokat sorban haladva átlépünk egy foglalás kezdő- vagy végnapján. ||
Hint 2: || Használj különbségi tömböt: egy foglalás kezdőnapjánál növeld a számlálót 1-gyel, a végnapja utáni napnál csökkentsd 1-gyel. A napi értékeket a prefixösszegek adják. A maximumot úgy keresd, hogy csak szigorú növekedésnél frissíts, így a legkisebb sorszám marad meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> diff(m + 2, 0);
    for (int i = 0; i < k; i++) {
        int t, e, u;
        cin >> t >> e >> u;
        diff[e]++;
        diff[u + 1]--;
    }
    int cur = 0, best = -1, bestDay = 1;
    for (int d = 1; d <= m; d++) {
        cur += diff[d];
        if (cur > best) {
            best = cur;
            bestDay = d;
        }
    }
    cout << bestDay << "\n";
    return 0;
}
