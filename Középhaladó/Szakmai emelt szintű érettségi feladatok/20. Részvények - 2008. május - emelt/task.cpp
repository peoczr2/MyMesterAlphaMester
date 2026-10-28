/*
Megoldás lényege:
Az összes záróárat egyetlen bejárásban összegezzük. Az első részfeladat eredménye az összeg N-nel vett egész osztása, ami a pozitív számok miatt pontosan a lefelé kerekítést adja. Egy nap akkor van az átlag felett, ha ár · N > összeg, így az összehasonlítás egész számokkal, törtek nélkül elvégezhető. Egész záróárak esetén ez ugyanazt az eredményt adja, mint a lefelé kerekített átlaggal való összehasonlítás. Az összeg legfeljebb 10^11 lehet, ezért long long típust használunk. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Az első részfeladathoz elég az összes záróárat egyszer beolvasni és összegezni; az átlag az összeg és a napok számának hányadosa. ||
Hint 2: || A második részfeladatnál ne számolj törtekkel: egy nap akkor nagyobb az átlagnál, ha ár · N > összeg, így az összehasonlítás egész számokkal elvégezhető. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> ar(n);
    long long osszeg = 0;
    for (auto &x : ar) {
        cin >> x;
        osszeg += x;
    }
    long long felette = 0;
    for (long long x : ar) {
        if (x * n > osszeg) {
            felette++;
        }
    }
    cout << "#\n" << osszeg / n << "\n#\n" << felette << "\n";
    return 0;
}
