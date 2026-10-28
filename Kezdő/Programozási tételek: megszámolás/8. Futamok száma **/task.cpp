/*
Megoldás lényege:
Egy futamon belül a szomszédos elemek különbségének előjele mindig ugyanaz. Egyszer végigmegyünk a sorozaton, és minden előjelváltásnál új futam kezdődik. Az előjelváltás helyén álló elem mindkét futamhoz tartozik, ezért a következő futam már abban az elemben kezdődik. Egyenlő szomszédos elemeknél a futam megszakad, és a következő futam a második egyenlő elemnél kezdődik. Így a sorozat egy menetben feldolgozható, az időigény O(N).
*/
/*
Hint 1: || Egy futamon belül a szomszédos elemek különbségének előjele nem változik. Figyeld, hol változik meg ez az előjel. ||
Hint 2: || Az előjelváltás helyén álló elem az előző és a következő futamnak is része (pl. 1 2 3 2 esetén a 3 mindkét futamban benne van). Egyenlő szomszédos elemeknél a futam megszakad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int sgn(int x) {
    return (x > 0) - (x < 0);
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    int futamok = 0;
    int start = 0;  // az aktuális futam kezdőindexe
    while (true) {
        ++futamok;
        if (start == n - 1) break;

        if (a[start + 1] == a[start]) {  // egyenlő szomszédok: új futam a következő elemtől
            start = start + 1;
            continue;
        }

        int irany = sgn(a[start + 1] - a[start]);
        int end = start;
        while (end + 1 < n && sgn(a[end + 1] - a[end]) == irany) ++end;

        if (end == n - 1) break;
        // előjelváltásnál az end. elem közös a két futamban, egyenlő párnál nem
        start = (a[end + 1] == a[end]) ? end + 1 : end;
    }

    cout << futamok << "\n";
    return 0;
}
