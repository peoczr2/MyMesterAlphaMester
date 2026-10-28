/*
Megoldás lényege:
Differenciatömbbel minden 1..100 000 időpontra kiszámoljuk a jelenlevők számát: érkezéskor +1, a távozás utáni időpontban −1, majd prefixösszeggel megkapjuk a létszámot. Egy időpontban akkor készül kép, ha legalább egy ember jelen van és a létszám legfeljebb F; az üres időpontról nem készül kép, ezt a második minta igazolja. A képes időpontokból prefixösszeg-tömböt építünk, így egy [K, V] videó villanásainak száma két kivonással, O(1) időben adódik. Az időigény O(maxT + N + M), a memóriaigény O(maxT).
*/
/*
Hint 1: || Az időpontok száma legfeljebb 100 000, ezért érdemes minden időpontra előre kiszámolni, hány ember van jelen. Az érkezés időpontjában növeld, a távozás utáni időpontban csökkentsd egy differenciatömböt, majd prefixösszeggel megkapod a létszámot. ||
Hint 2: || Egy időpontban akkor készül kép, ha a létszám legalább 1 és legfeljebb F. Ezekből az időpontokból építs egy prefixösszeg-tömböt, amely megmutatja, hány képes időpont van 1-től t-ig. ||
Hint 3: || Egy [K, V] videó alatti villanások száma a prefixösszegből két kivonással adódik: P[V] − P[K − 1]. A videó végpontja is beleszámít. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXT = 100000;

int main() {
    int n, f;
    cin >> n >> f;

    vector<int> diff(MAXT + 2, 0);
    for (int i = 0; i < n; i++) {
        int e, t;
        cin >> e >> t;
        diff[e]++;
        diff[t + 1]--;
    }

    // photoPref[t]: a képes időpontok száma az 1..t intervallumon
    vector<int> photoPref(MAXT + 1, 0);
    int jelen = 0;
    for (int t = 1; t <= MAXT; t++) {
        jelen += diff[t];
        bool kep = (jelen >= 1 && jelen <= f);
        photoPref[t] = photoPref[t - 1] + (kep ? 1 : 0);
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int k, v;
        cin >> k >> v;
        cout << photoPref[v] - photoPref[k - 1] << "\n";
    }
    return 0;
}
