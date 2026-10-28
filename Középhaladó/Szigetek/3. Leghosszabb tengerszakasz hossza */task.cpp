/*
Megoldás lényege:
A tengerszakasz egymást követő, 0 magasságú mérések szakasza. Egyetlen bejárással követjük az aktuális tengerszakasz hosszát: egy 0 méréshez növeljük a futó számlálót, egy szárazföldi méréshez nullázzuk. Közben nyilvántartjuk a számláló eddigi legnagyobb értékét, ez lesz a leghosszabb tengerszakasz hossza. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || A tengerszakasz egymás utáni 0 magasságú mérésekből áll. Egy bejárás elég: egy futó számlálóval mérd, hány nulla áll egymás után. ||
Hint 2: || Ha nem nulla mérést látsz, nullázd a futó számlálót. A legnagyobb értéket egy külön változóban tartsd nyilván, és a végén azt írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int aktualis = 0;  // az aktuális tengerszakasz hossza
    int leghosszabb = 0;
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        if (m == 0) {
            aktualis++;
            leghosszabb = max(leghosszabb, aktualis);
        } else {
            aktualis = 0;
        }
    }

    cout << leghosszabb << "\n";
    return 0;
}
