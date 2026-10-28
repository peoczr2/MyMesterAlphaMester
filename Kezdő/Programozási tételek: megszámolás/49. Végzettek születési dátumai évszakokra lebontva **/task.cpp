/*
Megoldás lényege:
Az évszakot csak a születési hónap alapján határozzuk meg: a március–május hónapban születettek tavaszi, a június–augusztusiak nyári, a szeptember–novemberiek őszi, a december–februárban születettek pedig téliek.
Az év, a kezdés és a befejezés adatai a feladathoz nem kellenek, ezeket beolvassuk, de nem használjuk fel.
Minden végzettnél egy elágazással a négy számláló egyikét növeljük, a végén ebben a sorrendben írjuk ki őket.
Az időigény O(N), a tárigény O(1).
*/
/*
Hint 1: || Minden végzettet egyedül a születési hónap alapján kell besorolni, a többi szám ehhez nem kell. ||
Hint 2: || Használj négy számlálót (tavasz, nyár, ősz, tél). Az évszakok a hónapok alapján: a tavasz márciusban kezdődik, a nyár júniusban, az ősz szeptemberben, a tél decemberben. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int tavasz = 0, nyar = 0, osz = 0, tel = 0;
    for (int i = 0; i < n; i++) {
        int ev, honap, nap, kezdes, veges;
        cin >> ev >> honap >> nap >> kezdes >> veges;
        if (honap >= 3 && honap <= 5) {
            tavasz++;
        } else if (honap >= 6 && honap <= 8) {
            nyar++;
        } else if (honap >= 9 && honap <= 11) {
            osz++;
        } else {
            tel++;
        }
    }
    cout << tavasz << " " << nyar << " " << osz << " " << tel << endl;
    return 0;
}
