/*
Megoldás lényege:
A tanulók jegyeit sorban, egyesével olvassuk be, és minden tanulónál megnézzük, hogy a jegy legalább K-e. Ha igen, a tanuló sorszámát (1-től indulva) egy vektorba tesszük, így a sorszámok a bejárás miatt már növekvő sorrendben lesznek. A végén kiírjuk a vektor méretét, majd a sorszámokat egy-egy szóközzel elválasztva, a sor végén szóköz nélkül. Az időigény O(N), ami a korlátok mellett triviális.
*/
/*
Hint 1: || Egyetlen bejárás elég: minden tanulónál csak a jegyét kell összevetni K-val. A "K-t vagy annál jobb" azt jelenti, hogy a jegy legyen nagyobb vagy egyenlő K-nál. ||
Hint 2: || A feltételnek megfelelő tanulók sorszámait gyűjtsd egy vektorba, a sorszám a beolvasás sorrendjéből adódik. A kiírt darabszám a vektor mérete. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> jo;
    for (int i = 1; i <= n; i++) {
        int jegy;
        cin >> jegy;
        if (jegy >= k) {
            jo.push_back(i);
        }
    }

    cout << jo.size();
    for (int sorszam : jo) {
        cout << " " << sorszam;
    }
    cout << "\n";
    return 0;
}
