/*
Megoldás lényege:
Egyszer végigmegyünk a méréseken, és nyilvántartjuk az előző nem nulla mérés erősségét és másodpercét. Egy nem nulla S mérés visszhang, ha legfeljebb K másodperc telt el az előző nem nulla méréshez képest és S kisebb az előző erősségnél; ilyenkor a visszhangok számlálóját növeljük. Minden nem nulla mérés után az előző erősséget és másodpercet felülírjuk, így az előzőnél erősebb vagy vele egyforma hang új hangadás lesz, és nem számít visszhangnak. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Csak azokat a méréseket kell számolni, amelyek visszhangok: vagyis gyengébbek az előző nem nulla mérésnél, és legfeljebb K másodperccel az előző nem nulla mérés után következnek. ||
Hint 2: || Egyetlen bejárással elég: tárold az előző nem nulla mérés erősségét és másodpercét. Ha az időkülönbség legfeljebb K, és az erősség kisebb az előzőnél, növeld a visszhangok számlálóját. ||
Hint 3: || Minden nem nulla mérés után írd felül az előző erősséget és másodpercet, akkor is, ha nem volt visszhang, a végén pedig a számlálót írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int elozo = 0;                 // az előző nem nulla mérés erőssége
    int utolso = -1000000;         // az előző nem nulla mérés másodperce
    int db = 0;                    // a hallott visszhangok száma
    for (int i = 1; i <= n; i++) {
        int s;
        cin >> s;
        if (s == 0) continue;
        if (i - utolso <= k && s < elozo) db++;
        elozo = s;
        utolso = i;
    }
    cout << db << "\n";
    return 0;
}
