/*
Megoldás lényege:
Ha a K küszöbnél kisebb macskák házimacskák, a legalább K méretűek pedig
vadmacskák, akkor kétféle téves besorolás létezik: a házimacskák közül a K-nál
nagyobbak rossz helyre kerülnek, a vadmacskák közül a K-nál kisebbek rossz helyre
kerülnek. Mindkét szám monoton változik K függvényében, ezért végig tudjuk
söpörni az összes lehetséges küszöböt, és kiválasztani a legkisebb maximális hiba
mellett a lehető legnagyobb K-t.
Az időigény O(H + V + legnagyobb méret), ami legfeljebb 10^5 körüli.
*/
/*
Hint 1: || Próbáld ki K minden lehetséges értékét 1-től a legnagyobb méretig, és K-nként számold ki a két hibaszámot. ||
Hint 2: || A K-nál kisebb házimacskák és a K-nál kisebb vadmacskák száma K növelésével csak nőhet. Egy K-hoz a rossz házimacskák száma a házimacskák összes számának és a K-nál kisebbek számának különbsége, a rossz vadmacskák száma pedig a K-nál kisebb vadmacskák száma. ||
Hint 3: || Két mutatóval, a K-nál kisebb házimacskák és vadmacskák számát követve, K-ról K-ra haladva minden K-ra O(1) munkával kiszámolható a két hiba. Egyenlő maximumnál a nagyobb K-t jegyezd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h;
    cin >> h;
    vector<int> hazi(h);
    for (int i = 0; i < h; ++i) cin >> hazi[i];

    int v;
    cin >> v;
    vector<int> vad(v);
    for (int i = 0; i < v; ++i) cin >> vad[i];

    int maxVal = max(hazi.back(), vad.back());

    int i = 0, j = 0;
    int bestK = 1;
    int bestErr = INT_MAX;

    for (int k = 1; k <= maxVal; ++k) {
        while (i < h && hazi[i] < k) ++i;
        while (j < v && vad[j] < k) ++j;

        int rosszHazi = h - i;
        int rosszVad = j;
        int err = max(rosszHazi, rosszVad);
        if (err < bestErr || (err == bestErr && k > bestK)) {
            bestErr = err;
            bestK = k;
        }
    }

    cout << bestK << '\n';
    return 0;
}
