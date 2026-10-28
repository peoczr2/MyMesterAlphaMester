/*
Megoldás lényege:
A dátumokat közös napszámra váltjuk: egy dátum sorszáma az évek hosszából (a szökőéveket is figyelembe véve) és a hónapok napjaiból adódik, így két dátum távolsága egyszerű kivonással kapható meg. Egy embernél a legközelebbi névnap lehet az előző, az aktuális vagy a következő évben is, ezért mindhárom évben kiszámoljuk a névnap napszámát, és a születésnaptól vett legkisebb távolságot tartjuk meg. Végül egy menetben megkeressük az összes ember közül a legkisebb távolságot, és kiírjuk azokat, akiknél ez előfordul, növekvő sorrendben. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || A dátumokkal nehéz közvetlenül számolni: rendelj minden dátumhoz egy egész számot (a napok sorszámát), így a távolság két szám különbsége lesz. Figyelj a szökőévre. ||
Hint 2: || Egy embernél a névnap az előző, az aktuális vagy a következő évben lehet a legközelebb, ezért mindhárom évben számold ki a névnap sorszámát, és vedd a születésnaptól mért legkisebb távolságot. ||
Hint 3: || Az embereket egy menetben dolgozd fel: tartsd nyilván az eddigi legkisebb távolságot és a hozzá tartozó sorszámokat; ha kisebb távolság jön, a listát üresítsd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

bool szokoev(long long y) {
    return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
}

// A dátum sorszáma egy közös kezdőponttól, napokban.
long long napSorszam(long long y, int honap, int nap) {
    static const int hossz[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    long long elozoEvek = (y - 1) * 365 + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400;
    long long napok = 0;
    for (int h = 1; h < honap; h++) {
        napok += hossz[h];
    }
    if (honap > 2 && szokoev(y)) {
        napok++;
    }
    return elozoEvek + napok + nap - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long ev;
    cin >> n >> ev;

    long long legkisebb = LLONG_MAX;
    vector<int> talalatok;

    for (int i = 1; i <= n; i++) {
        int szHo, szNap, nevHo, nevNap;
        cin >> szHo >> szNap >> nevHo >> nevNap;

        long long szulinap = napSorszam(ev, szHo, szNap);
        long long tav = LLONG_MAX;
        // a névnap lehet az előző, az aktuális vagy a következő évben is
        for (long long y = ev - 1; y <= ev + 1; y++) {
            tav = min(tav, llabs(napSorszam(y, nevHo, nevNap) - szulinap));
        }

        if (tav < legkisebb) {
            legkisebb = tav;
            talalatok.clear();
        }
        if (tav == legkisebb) {
            talalatok.push_back(i);
        }
    }

    cout << talalatok.size() << "\n";
    for (size_t i = 0; i < talalatok.size(); i++) {
        if (i > 0) cout << ' ';
        cout << talalatok[i];
    }
    cout << "\n";
    return 0;
}
