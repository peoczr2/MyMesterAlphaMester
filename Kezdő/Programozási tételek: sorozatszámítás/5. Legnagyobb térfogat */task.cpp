/*
Megoldás lényege:
Az épület térfogata a felhasznált kockák térfogatainak összege, mert a legnagyobb épület minden kockát felhasznál. Egy H élhosszúságú kocka térfogata H * H * H, ezért a kockákat egyenként beolvassuk, és a köbüket egy összeg-változóhoz adjuk. Minden kockát pontosan egyszer dolgozunk fel, így az időigény O(N), ami N <= 100 esetén messze az időlimit alatt marad. A térfogat legfeljebb 100 * 100^3 = 10^8, ezért long long típust használunk.
*/
/*
Hint 1: || Az épület térfogata a kockák térfogatainak összege. Hogyan számolható ki egy H élhosszúságú kocka térfogata? ||
Hint 2: || Egy összeg-változóba gyűjtsd a kockák térfogatát: minden beolvasott H után add hozzá a H * H * H értéket. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long osszeg = 0;
    for (int i = 0; i < n; i++) {
        long long h;
        cin >> h;
        osszeg += h * h * h;
    }

    cout << osszeg << "\n";
    return 0;
}
