/*
Megoldás lényege:
Egy nap akkor számít, ha a reggeli és az esti érték is nagyobb az előző napi megfelelő értéknél. Ezt a két feltételt egyszerre, ÉS-kapcsolattal kell vizsgálni.
Elég az előző nap két értékét megjegyezni, így nincs szükség a teljes sorozat tárolására. A bejárás egyszer megy végig az N napon, az időigény O(N), a tárigény konstans.
*/
/*
Hint 1: || Minden napot csak az őt megelőző nappal kell összehasonlítani, ezért nem kell a teljes sorozatot tárolni: elég az előző nap két értékét megjegyezni. ||
Hint 2: || Egy nap akkor növeli a számlálót, ha a reggeli érték nagyobb az előzőnél, és az esti érték is nagyobb az előzőnél. Az első napnak nincs előző napja, ezért a számolást a 2. nappal kezdd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int elozo_reggel, elozo_este;
    cin >> elozo_reggel >> elozo_este;
    int db = 0;
    for (int i = 2; i <= n; i++) {
        int reggel, este;
        cin >> reggel >> este;
        if (reggel > elozo_reggel && este > elozo_este) {
            db++;
        }
        elozo_reggel = reggel;
        elozo_este = este;
    }
    cout << db << endl;
    return 0;
}
