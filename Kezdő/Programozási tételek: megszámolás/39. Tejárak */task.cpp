/*
Megoldás lényege:
Egy ciklusban beolvassuk a tejek árait, és mindegyiket azonnal összevetjük a [P, Q] zárt intervallummal. Ha az ár legalább P és legfeljebb Q, egy számlálót növelünk. Nincs szükség tömbre, mert az árak sorrendje nem számít, és minden árat pontosan egyszer vizsgálunk. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Nem kell az összes árat egyszerre tárolni: minden árat beolvasás után rögtön meg tudsz vizsgálni. ||
Hint 2: || Az ár akkor esik a keresett tartományba, ha P ≤ ár és ár ≤ Q. Ezt a két feltételt egy logikai kifejezésben kell egyszerre igazolni, és minden találatnál egy számlálót kell növelni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, p, q;
    cin >> n >> p >> q;
    int darab = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (p <= a && a <= q) darab++;
    }
    cout << darab << "\n";
    return 0;
}
