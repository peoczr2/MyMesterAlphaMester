/*
Megoldás lényege:
A bevétel és a költség csak azon múlik, hány utas utazik az egyes szakaszokon. Egy szakasz utasszáma az előző
állomás utasszámából indul: hozzáadjuk az ott felszállók számát, és levonjuk a leszállók számát. Az utolsó állomás
kivételével minden állomás után az aktuális utasszámot hozzáadjuk az összeghez, így megkapjuk az összes utas által
megtett szakaszok számát. A bevétel ennek N-szerese, a költség pedig M * (állomásszám - 1). A két értéket 64 bites
egészben hasonlítjuk össze. Az időigény O(S), ahol S az állomások száma.
*/
/*
Hint 1: || Nem kell utasonként nyilvántartani az utazásokat: elég tudni, hány utas van az egyes szakaszokon. ||
Hint 2: || A bevétel N-szerese a szakaszonkénti utasszámok összegének, a költség M-szerese a szakaszok számának. Mindkettőt érdemes 64 bites egészben számolni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int s; // az állomások száma
    cin >> s;

    long long n, m; // egy utas díja egy állomásnyi úton, a vonat költsége egy állomásnyi úton
    cin >> n >> m;

    long long onboard = 0; // a vonaton lévő utasok száma az aktuális állomás után
    long long segments = 0; // az összes utas által megtett szakaszok száma
    for (int i = 0; i < s; i++) {
        long long off, on; // leszállók és felszállók száma
        cin >> off >> on;
        onboard += on - off;
        if (i < s - 1)
            segments += onboard;
    }

    long long revenue = n * segments;
    long long cost = m * (s - 1);
    cout << (revenue >= cost ? 1 : 0) << '\n';
    return 0;
}
