/*
Megoldás lényege:
A villamos a 0. állomásról a 0. percben indul, ezért a legutóbbi valódi megállás indulási idejét kezdetben 0-nak tekintjük. Egyetlen bejárásban végigmegyünk az állomásokon: ha egy állomáson az érkezési és az indulási idő különbözik, az valódi megállás, ezért a legutóbbi megállás indulása és ennek érkezése közötti idő egy megállás nélküli szakasz. Ezt összevetjük az eddigi legnagyobbal, majd az utolsó indulási időt frissítjük. A nem megálló állomások (érkezés = indulás) nem szakítják meg a szakaszt, így a szakasz a következő valódi megállóig tart. Ha az utolsó állomáson nem álltunk meg, a végállomás érkezéséig tartó szakaszt is figyelembe vesszük. Az időigény O(N).
*/
/*
Hint 1: || Az idő a 0. állomás indulásától (0. perc) folyamatosan telik. Egy megállás nélküli szakasz az utolsó valódi megálló indulásától a következő valódi megálló érkezéséig tart, a közbeeső nem megálló állomások ebbe a szakaszba beletartoznak. ||
Hint 2: || Egyetlen bejárásban tartsd nyilván az utolsó valódi megálló indulási idejét (kezdetben 0) és az eddigi legnagyobb szakaszt. Az utolsó állomásra külön figyelj: ha ott nem álltunk meg, a szakasz a végállomás érkezési idejéig tart. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long lastDep = 0;    // az utolsó valódi megállás indulási ideje (a 0. állomásról 0-kor indul)
    long long best = 0;       // a legnagyobb megállás nélküli időtartam
    long long lastArr = 0;    // az utolsó állomás érkezési ideje
    bool lastStops = false;   // az utolsó állomáson megállt-e a villamos

    for (int i = 1; i <= n; i++) {
        long long t, arr, dep;
        cin >> t >> arr >> dep;
        lastArr = arr;
        lastStops = arr < dep;
        if (lastStops) {
            best = max(best, arr - lastDep);
            lastDep = dep;
        }
    }
    if (!lastStops) {
        best = max(best, lastArr - lastDep);
    }

    cout << best << '\n';
    return 0;
}
