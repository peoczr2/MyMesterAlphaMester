/*
Megoldás lényege:
Minden dátumot napsorszámra alakítunk: az előző évek napjait (évenként 365 nap és a szökőnapok), ehhez hozzáadjuk az év előző hónapjainak napjait, a szökőévi plusz napot és a nap sorszámát. Így két születésnap távolsága napokban egy egész szám különbsége lesz.
Peti napsorszámához viszonyítva azokat a táborozókat számoljuk meg, akiknek a napsorszáma legfeljebb 365 nappal tér el (abszolút értékben). Minden dátum átalakítása állandó idejű, így az időigény O(N).
*/
/*
Hint 1: || Két dátum között a napok száma egyszerű különbség lesz, ha mindkét dátumot egyetlen egész számmá alakítod, például az 1. évi január 1-jétől számolt napok számává. ||
Hint 2: || Egy év akkor szökőév, ha 4-gyel osztható, kivéve a 100-zal osztható éveket, amelyek csak akkor szökőévek, ha 400-zal is oszthatók. Szökőévben március 1-jétől kezdve a dátumokhoz egy nappal több jár. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A dátum napsorszáma: az 1. évi január 1-jétől számolt napok sorszáma.
long long napsorszam(int ev, int ho, int nap) {
    static const int honap_napjai[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool szokoev = (ev % 4 == 0 && ev % 100 != 0) || ev % 400 == 0;

    long long elozo_evek = ev - 1;
    long long eddig = 365 * elozo_evek + elozo_evek / 4 - elozo_evek / 100 + elozo_evek / 400;
    for (int h = 1; h < ho; h++) {
        eddig += honap_napjai[h];
    }
    if (szokoev && ho > 2) {
        eddig++;
    }
    return eddig + nap;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int ev, ho, nap;
    cin >> ev >> ho >> nap;
    long long peti = napsorszam(ev, ho, nap);

    int db = 0;
    for (int i = 0; i < n; i++) {
        cin >> ev >> ho >> nap;
        long long masik = napsorszam(ev, ho, nap);
        if (abs(masik - peti) <= 365) {
            db++;
        }
    }

    cout << db << "\n";
    return 0;
}
