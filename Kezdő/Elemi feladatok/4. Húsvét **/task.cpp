/*
Megoldás lényege:
Két holdtölte között 29,5 nap telik el, ezért a napokat félnapos egységben számoljuk: egy holdtölte 59 féllel van később, mint az előző. A januári holdtöltétől kezdve ilyen lépésekkel haladunk előre, amíg a holdtölte napja március 21-e vagy későbbi nem lesz (a március 21-i holdtölte is számít). A hét napját az év első napjának ismeretében maradékos osztással kapjuk, így a holdtölte napjától az első vasárnap lesz a húsvétvasárnap, a következő nap a húsvéthétfő. Pünkösdvasárnap a húsvétvasárnap után 49 nappal, pünkösdhétfő 50 nappal van. A napsorszámokat végül a hónapok hosszának tömbjével alakítjuk vissza hónapnév és nap alakra, szökévben a februárt 29 naposnak véve. A lépések száma legfeljebb néhány, így az időigény konstans.
*/
/*
Hint 1: || Két holdtölte között 29,5 nap telik el, így érdemes félnapokban számolni: a januári holdtölte délelőtt vagy délután van, és minden következő holdtölte 59 féllel később jön. Lépkedj előre, amíg március 21-e utáni holdtöltét nem találsz. ||
Hint 2: || Számozd az évnapokat 0-tól, és a hét napját a január 1-jei nap alapján számold: (ELSO - 1 + napsorszám) maradéka 7-tel adja a hét napját, ahol a 6 a vasárnap. A holdtölte napjától az első vasárnapig ((6 - a holdtölte hétnapja) + 7) maradéka 7-tel vett nap telik el. ||
Hint 3: || A húsvéthétfő a húsvétvasárnap utáni nap, pünkösdvasárnap 49, pünkösdhétfő 50 nappal van a húsvétvasárnap után. A napsorszámot a hónapok hosszainak tömbjével alakítsd vissza hónapnév és nap alakra, a februárt szökévben 29 naposnak véve. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int ev, elso, hold;
    string resz;
    cin >> ev >> elso >> hold >> resz;

    // A hónapok hossza (szökévben a február 29 napos)
    bool szokev = (ev % 4 == 0 && ev % 100 != 0) || ev % 400 == 0;
    int honapHossz[12] = {31, szokev ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    string honapNev[12] = {"januar", "februar", "marcius", "aprilis", "majus", "junius",
                           "julius", "augusztus", "szeptember", "oktober", "november", "december"};

    // Március 21. napsorszáma (január 1. a 0. nap)
    int marciusHuszonegy = 31 + (szokev ? 29 : 28) + 20;

    // A holdtölteket félnapokban számoljuk: 0 a délelőtt, 1 a délután
    // Két holdtölte között 29,5 nap, vagyis 59 fél nap telik el
    int felnap = 2 * (hold - 1) + (resz == "du" ? 1 : 0);
    while (felnap / 2 < marciusHuszonegy) {
        felnap += 59;
    }
    int holdtolte = felnap / 2;

    // A hét napja: 0 hétfő, 1 kedd, ..., 6 vasárnap
    int hetnap = (elso - 1 + holdtolte) % 7;
    int husvetVasarnap = holdtolte + (6 - hetnap + 7) % 7;
    int husvetHetfo = husvetVasarnap + 1;
    int pinkosdVasarnap = husvetVasarnap + 49;
    int pinkosdHetfo = husvetVasarnap + 50;

    // Napsorszámból "hónapnév nap." alak
    auto datum = [&](int nap) {
        int i = 0;
        while (nap >= honapHossz[i]) {
            nap -= honapHossz[i];
            i++;
        }
        return honapNev[i] + " " + to_string(nap + 1) + ".";
    };

    cout << datum(husvetVasarnap) << "\n";
    cout << datum(husvetHetfo) << "\n";
    cout << datum(pinkosdVasarnap) << "\n";
    cout << datum(pinkosdHetfo) << "\n";
    return 0;
}
