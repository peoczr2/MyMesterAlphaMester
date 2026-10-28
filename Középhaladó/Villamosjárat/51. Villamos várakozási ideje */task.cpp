/*
Megoldás lényege:
Egy megállóban a várakozás az indulási és az érkezési idő különbsége (Indi - Erki); ha a két idő egyenlő, a villamos ott nem állt meg, így a várakozás nulla. A feladat a villamos összes várakozását kéri, de a 0. állomásnak nincs érkezési ideje, a végállomás (N.) utáni indulás pedig nem az útközbeni várakozáshoz tartozik, ezért az 1. és N-1. megállók várakozásait összegezzük. A példában 5 + 0 + 2 + 10 = 17. Egy bejárásban ezt egyetlen összeggel kapjuk meg. Időigény O(N).
*/
/*
Hint 1: || Egy megállóban a várakozás az indulási és az érkezési idő különbsége. Ha a két idő egyenlő, a várakozás nulla. ||
Hint 2: || Egy ciklusban olvasd be az összes sort, és az i. megállónál csak akkor add hozzá az Indi - Erki értéket az összeghez, ha i kisebb N-nél. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long osszes = 0;
    for (int i = 1; i <= n; i++) {
        long long tav, erk, ind;
        cin >> tav >> erk >> ind;
        if (i < n) {
            osszes += ind - erk;
        }
    }
    cout << osszes << '\n';
    return 0;
}
