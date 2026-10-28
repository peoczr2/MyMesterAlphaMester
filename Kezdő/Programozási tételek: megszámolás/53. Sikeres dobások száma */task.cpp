/*
Megoldás lényege:
Minden versenyzőhöz hat dobás tartozik, a sikertelen dobást a -1 érték jelöli. A sikeres dobások száma tehát azoknak a dobásoknak a száma, amelyek értéke nem -1. Versenyzőnként egy ciklusban beolvassuk a hat értéket, és minden nem -1 értéknél növeljük a számlálót. A kész számlálókat a bemenet sorrendjében, egy sorba írjuk ki. Az időigény O(N), a tárigény O(1).
*/
/*
Hint 1: || Egy versenyzőnek pontosan hat dobása van, és a sikertelen dobás a -1 érték. Azt kell megszámolni, hány dobás nem -1. ||
Hint 2: || Versenyzőnként egy számlálót nullázz, a hat dobást olvasd be egymás után, és ha az érték nem -1, növeld a számlálót. A számlálókat szóközzel elválasztva írd ki egy sorba. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int sikeres = 0;
        for (int j = 0; j < 6; j++) {
            int d;
            cin >> d;
            if (d != -1) sikeres++;
        }
        if (i > 0) cout << " ";
        cout << sikeres;
    }
    cout << "\n";
    return 0;
}
