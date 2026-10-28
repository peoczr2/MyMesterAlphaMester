/*
Megoldás lényege:
A tengerszakaszok a 0 magasságú mérések, így a teljes hosszuk a 0 értékű mérések száma. Nem kell külön szakaszokat keresni: elég egyszer végigmenni a méréseken, és minden nulla mérésnél növelni egy számlálót. A végén a számláló értékét írjuk ki. Az időigény O(N), a memóriaigény O(1), mert a számok nem kell tárolni.
*/
/*
Hint 1: || A tengerszakasz olyan mérés, ahol a magasság 0. A teljes hosszba minden ilyen mérés beleszámít, nem csak a leghosszabb szakasz. ||
Hint 2: || Nem kell tömböt tárolnod: olvasd be a számokat egyesével, és egy számlálóban gyűjtsd a 0 értékű méréseket. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int osszhossz = 0;  // a tengerszakaszok teljes hossza
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        if (m == 0) osszhossz++;
    }

    cout << osszhossz << "\n";
    return 0;
}
