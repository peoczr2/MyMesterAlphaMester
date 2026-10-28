/*
Megoldás lényege:
Egy megállóban akkor állt meg a villamos, ha az érkezési idő kisebb az indulási időnél (Erki < Indi); egyenlő időknél nem állt meg. Az induló (0.) és a végállomás (N.) sorszámát nem írjuk ki, így csak az 1. és N-1. megállókat vizsgáljuk. Egy bejárásban összegyűjtjük a megállások sorszámait növekvő sorrendben, majd először a darabszámot, utána a sorszámokat írjuk ki. A példában az 1., 3. és 4. megállónál volt megállás, így a kimenet 3 1 3 4. Időigény O(N).
*/
/*
Hint 1: || A megállás feltétele: az érkezési idő kisebb az indulási időnél. Ha a kettő egyenlő, a villamos ott nem állt meg. ||
Hint 2: || Olvasd be mind az N sort, de a feltételt csak az 1-től N-1-ig terjedő sorszámú megállókra vizsgáld. A talált sorszámokat egy vektorba tedd, és a kiírásnál a darabszám kerüljön elsőnek. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> megallasok;
    for (int i = 1; i <= n; i++) {
        int tav, erk, ind;
        cin >> tav >> erk >> ind;
        if (i < n && erk < ind) {
            megallasok.push_back(i);
        }
    }
    cout << megallasok.size();
    for (int s : megallasok) {
        cout << ' ' << s;
    }
    cout << '\n';
    return 0;
}
