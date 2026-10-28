/*
Megoldás lényege:
Az állomások távolságát az induló állomástól az eddigi távolságok összegzésével kapjuk, így a távolságok sorrendben növekvők. Az útközbeni állomások közül azokat gyűjtjük, ahol az érkezési és az indulási idő egyenlő, azaz a villamos nem állt meg. Ezek közül az induló állomáshoz legközelebbi az első, a végállomáshoz legközelebbi az utolsó, és a két távolság összehasonlításából dől el a válasz. Egyenlő távolság vagy üres halmaz esetén Egyikhez sem a válasz, a végállomás nem számít megállónak. Időigény O(N).
*/
/*
Hint 1: || Egy állomás távolsága az induló állomástól az addig megtett távolságok összege. Egy bejárásban gyűjtsd össze az útközbeni, nem megálló állomások távolságát. ||
Hint 2: || A gyűjtött távolságok növekvő sorrendben vannak, így az induló oldalhoz legközelebbi az első, a végállomáshoz legközelebbi pedig az utolsó. Ennek a végállomástól mért távolsága az összes hossz és a távolsága különbsége. Hasonlítsd össze a két értéket. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long osszHossz = 0;
    vector<long long> nemMegallo;
    for (int i = 0; i < n; i++) {
        long long tav, erk, ind;
        cin >> tav >> erk >> ind;
        osszHossz += tav;
        if (i < n - 1 && erk == ind) {
            nemMegallo.push_back(osszHossz);
        }
    }
    if (nemMegallo.empty()) {
        cout << "Egyikhez sem\n";
        return 0;
    }
    long long elejeTavolsag = nemMegallo.front();
    long long vegeTavolsag = osszHossz - nemMegallo.back();
    if (elejeTavolsag < vegeTavolsag) {
        cout << "Elejehez\n";
    } else if (vegeTavolsag < elejeTavolsag) {
        cout << "Vegehez\n";
    } else {
        cout << "Egyikhez sem\n";
    }
    return 0;
}
