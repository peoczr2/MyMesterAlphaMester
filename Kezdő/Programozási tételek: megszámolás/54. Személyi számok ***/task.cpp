/*
Megoldás lényege:
A személyi szám első számjegye (M) egyszerre kódolja a nemet és az évszázadot: a páratlan érték férfit, a páros nőt jelent. Az M = 1, 2, 5, 6 esetén a születési év 19ÉÉ, az M = 3, 4 esetén 20ÉÉ (18xx-es születés a bemenetben nincs). Az ÉV évnél később született személyek nem számítanak. Egy 13×32-es tömbben (hónap, nap) szerint számoljuk a fiúk és a lányok születésnapjait, majd az év napjain végigmenve megszámoljuk azokat a napokat, ahol több a lány. A február 29-i születésnapot csak szökőévben vesszük figyelembe. Az időigény O(N + 366), a tárigény O(1).
*/
/*
Hint 1: || Az első számjegy (M) kódolja a nemet és a születési évszázadot is. Páratlan érték férfit, páros nőt jelent; az 1, 2, 5, 6 a 1900-as, a 3 és 4 a 2000-es évekhez tartozik. ||
Hint 2: || Egy 13×32-es tömbben (hónap, nap) szerint számold, hány fiú és hány lány születésnapja esik az adott napra. Csak azokat vedd figyelembe, akik az ÉV évben vagy korábban születtek. ||
Hint 3: || Az év napjain végigmenve hasonlítsd össze a lányok és a fiúk számát, és számold a lányokkal teli napokat. A február 29. csak szökőévben számít, ezért ezt külön ellenőrizd. ||
*/
#include <bits/stdc++.h>
using namespace std;

bool szokoev(int ev) {
    return (ev % 4 == 0 && ev % 100 != 0) || ev % 400 == 0;
}

int main() {
    int n, ev;
    cin >> n >> ev;

    // fiu[h][nap], lany[h][nap]: hány fiú/lány születésnapja esik az adott (hó, nap) napra
    int fiu[13][32] = {}, lany[13][32] = {};

    for (int i = 0; i < n; i++) {
        string szam;
        cin >> szam;
        int m = szam[0] - '0';
        int ee = stoi(szam.substr(1, 2));
        int hh = stoi(szam.substr(3, 2));
        int nn = stoi(szam.substr(5, 2));

        int szuletes_ev;
        if (m == 1 || m == 2 || m == 5 || m == 6) szuletes_ev = 1900 + ee;
        else if (m == 3 || m == 4) szuletes_ev = 2000 + ee;
        else szuletes_ev = 1800 + ee;

        if (szuletes_ev > ev) continue;

        if (m % 2 == 1) fiu[hh][nn]++;
        else lany[hh][nn]++;
    }

    int honap_napjai[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int napok_szama = 0;
    for (int h = 1; h <= 12; h++) {
        for (int nap = 1; nap <= honap_napjai[h]; nap++) {
            if (lany[h][nap] > fiu[h][nap]) napok_szama++;
        }
    }
    // február 29-én csak szökőévben van születésnap
    if (szokoev(ev) && lany[2][29] > fiu[2][29]) napok_szama++;

    cout << napok_szama << "\n";
    return 0;
}
