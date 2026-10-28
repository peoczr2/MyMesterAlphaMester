/*
Megoldás lényege:
Először minden mérésre eldöntjük, hogy csúcs-e: a csúcs köztes pont (nem az első és nem az utolsó), amelynek értéke nagyobb mind az előző, mind a következő mérésnél. A csúcsok 0/1 jelzőit előtagösszegben tároljuk, így bármely K hosszú [A, A+K-1] ablakban lévő csúcsok száma két érték különbsége. Mivel az ablakok száma legfeljebb N, mindegyiket végigpróbáljuk, és a legtöbb csúcsot tartalmazót írjuk ki (egyenlőség esetén a legkisebb A-t). Ha egyetlen csúcs sincs, a válasz -1 -1. Az időigény O(N), ami a korlátok mellett bőven elég.
*/
/*
Hint 1: || Egy mérés pontosan akkor csúcs, ha nem az első vagy az utolsó, és nagyobb mindkét szomszédjánál. Ezt minden pontra egyszer, előre megnézheted. ||
Hint 2: || Készíts előtagösszeget a csúcsok számáról: az [A, B] ablakban lévő csúcsok száma így pref[B] - pref[A-1]. Az ablakok száma legfeljebb N, ezért mindet végigpróbálhatod. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> m(n + 2, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> m[i];
    }

    // pref[i] = a csúcsok száma az 1..i mérések között
    vector<int> pref(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        bool csucs = (i > 1 && i < n && m[i] > m[i - 1] && m[i] > m[i + 1]);
        pref[i] = pref[i - 1] + (csucs ? 1 : 0);
    }

    int legtobb = 0;
    int legjobbA = -1;
    for (int a = 1; a + k - 1 <= n; ++a) {
        int b = a + k - 1;
        int db = pref[b] - pref[a - 1];
        if (db > legtobb) {
            legtobb = db;
            legjobbA = a;
        }
    }

    if (legtobb == 0) {
        cout << "-1 -1\n";
    } else {
        cout << legjobbA << ' ' << legjobbA + k - 1 << '\n';
    }

    return 0;
}
