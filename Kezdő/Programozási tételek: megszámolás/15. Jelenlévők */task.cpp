/*
Megoldás lényege:
Egy vendég pontosan akkor van jelen a K. percben, ha az érkezési ideje nem későbbi K-nál, a távozási ideje pedig K-nál későbbi. Az érkező tehát már benne van, a távozó már nincs benne.
Az éjfél utáni távozás értéke 24*60-nál nagyobb, ezekre is ugyanaz a feltétel működik, külön esetet nem kell kezelni.
A vendégeket egyenként beolvassuk és ellenőrizzük, így az időigény O(N).
*/
/*
Hint 1: || Egy vendég akkor számít, ha a K. időpont az érkezése és a távozása közé esik: az érkezés beleszámít, a távozás már nem. ||
Hint 2: || Nem kell a vendégeket tárolni: beolvasás közben ellenőrizd a feltételt, és ha teljesül, növeld a számlálót. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int db = 0;
    for (int i = 0; i < n; i++) {
        int erkezes, tavozas;
        cin >> erkezes >> tavozas;
        if (erkezes <= k && k < tavozas) {
            db++;
        }
    }
    cout << db << endl;
    return 0;
}
