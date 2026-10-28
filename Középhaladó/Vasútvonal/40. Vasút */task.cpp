/*
Megoldás lényege:
Egy bejárásban követjük, hány utas van a vonaton. Egy állomáson akkor szállt le mindenki, ha az érkezéskor volt utas a vonaton, és a leszállók száma legalább ekkora volt.
Az érkezéskori létszámot az állomás feldolgozása előtt vizsgáljuk meg, a felszállókat csak utána vesszük figyelembe.
Az üres vonat (például a Budapest-állomás) nem számít, mert ott nem volt, aki leszálljon.
Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Az állomáson a leszállás előtt a vonaton lévő utasok számát kell összevetni a leszállók számával. ||
Hint 2: || Tartsd a futó létszámot: a leszállók levonásával és a felszállók hozzáadásával frissítsd, és a számlálást csak akkor végezd, ha az állomás előtt volt utas a vonaton. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long cur = 0;  // a vonaton lévő utasok száma az állomás előtt
    int count = 0;      // azon állomások száma, ahol mindenki leszállt
    for (int i = 0; i < n; i++) {
        long long le, fel;
        cin >> le >> fel;
        if (cur > 0 && le >= cur) count++;
        cur = cur - le + fel;
    }

    cout << count << "\n";
    return 0;
}
