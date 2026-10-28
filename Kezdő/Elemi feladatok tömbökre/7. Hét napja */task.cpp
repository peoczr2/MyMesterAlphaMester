/*
Megoldás lényege:
Az év első napjának ismeretében azt kell megtalálni, hány nap telt el az év első napja és a megadott dátum között. Ehhez összeadjuk a megelőző hónapok hosszát, és hozzáadjuk a nap sorszámát mínusz egyet. A hét napjait hétfőtől vasárnapig tömbben tároljuk, a kezdő nap indexéhez hozzáadjuk az eltelt napok számát, majd a 7-tel vett maradék adja a keresett nap indexét. A hónapok hosszánál a február szökőévben 29 nap, a szökőévet a Gregorián-naptár szabálya szerint állapítjuk meg. A hónapok és a napok nevét a tömbökben keressük meg, a művelet így állandó idejű.
*/
/*
Hint 1: || A hét napjai 7 naponként ismétlődnek, ezért elég megszámolnod, hány nap telt el az év első napja óta, és a 7-tel vett maradékkal dolgoznod. ||
Hint 2: || Tárold a hónapok neveit és a hét napjainak neveit tömbben, és keresd meg bennük a beolvasott szavak indexét. A hónapok hosszát tömbben tárold, a februárnál pedig szökőévben 29 nappal számolj. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int ev, nap;
    string honapNev, elsoNap;
    cin >> ev >> honapNev >> nap >> elsoNap;

    vector<string> honapok = {"januar", "februar", "marcius", "aprilis", "majus", "junius",
                              "julius", "augusztus", "szeptember", "oktober", "november", "december"};
    vector<string> napok = {"hetfo", "kedd", "szerda", "csutortok", "pentek", "szombat", "vasarnap"};

    bool szokoev = (ev % 4 == 0 && ev % 100 != 0) || ev % 400 == 0;
    int honapHossz[12] = {31, szokoev ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int honapIndex = find(honapok.begin(), honapok.end(), honapNev) - honapok.begin();
    int eltelt = nap - 1;
    for (int i = 0; i < honapIndex; i++) eltelt += honapHossz[i];

    int kezdoIndex = find(napok.begin(), napok.end(), elsoNap) - napok.begin();
    cout << napok[(kezdoIndex + eltelt) % 7] << '\n';
    return 0;
}
