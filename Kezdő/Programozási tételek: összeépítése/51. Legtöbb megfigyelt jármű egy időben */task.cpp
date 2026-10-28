/*
Megoldás lényege:
Minden megfigyelés egy járművet jelent, a megfigyelési hely sorszáma az eredményt nem befolyásolja. A megfigyelések időrendben érkeznek, így az azonos időpontúak egymás utáni futamot alkotnak. Végigmegyünk a bemeneten, és minden futam végén összehasonlítjuk a hosszát az eddigi legnagyobbal. Csak szigorúan hosszabb futam írja felül az eredményt, így egyenlőség esetén az időrendben korábbi időpont marad. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Minden megfigyelés egy járművet jelent, a hely sorszáma most nem számít. A megfigyelések időrendben érkeznek, így az azonos időpontúak egymás után állnak. ||
Hint 2: || Egy futamot az azonos időpontú, egymás utáni megfigyelések alkotnak: számold a futam hosszát, és a bejárásnál csak szigorúan hosszabb futamnál írd felül az eddigi eredményt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    vector<int> ido(n);     // az időpont a nap elejétől eltelt percben
    for (int i = 0; i < n; i++) {
        int hely, ora, perc;
        cin >> hely >> ora >> perc;
        ido[i] = ora * 60 + perc;
    }

    // Az azonos időpontú megfigyelések egymás utáni futamot alkotnak.
    int legtobb = 0, legkorabbi = -1;
    int i = 0;
    while (i < n) {
        int j = i;
        while (j < n && ido[j] == ido[i]) j++;
        if (j - i > legtobb) {
            legtobb = j - i;
            legkorabbi = ido[i];
        }
        i = j;
    }
    cout << legkorabbi / 60 << " " << legkorabbi % 60 << endl;
    return 0;
}
