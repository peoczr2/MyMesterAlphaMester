/*
Megoldás lényege:
Mindkét időpontot átváltjuk a nap kezdete óta eltelt másodpercek számára: t = ó * 3600 + p * 60 + mp. Mivel a második időpont nem korábbi az elsőnél, a d = t2 - t1 különbség nemnegatív, és ez adja a keresett eltelt időt másodpercben. Ezt visszaalakítjuk órákra, percekre és másodpercekre: az órák száma d / 3600, a maradék másodpercekből a percek száma (maradék / 60), a végső maradék pedig a másodpercek száma. A kiíráskor minden mezőt két karakter szélesre töltünk nullákkal, így a formátum ÓÓ:PP:MM lesz. Az időigény O(N), ahol N legfeljebb 10 000; a memóriaigény O(1).
*/
/*
Hint 1: || Ne próbáld óránként, percenként és másodpercenként kivonni az időpontokat, mert a visszakölcsönzés könnyen hibás lesz. Alakítsd mindkét időpontot egyetlen egész számmá: az éjféltől eltelt másodpercek számává. ||
Hint 2: || A két szám különbsége adja az eltelt másodpercek számát. Ebből osztással és maradékképzéssel (először 3600-zal, majd 60-nal) kapod meg az órák, percek és másodpercek számát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int h1, m1, s1, h2, m2, s2;
        cin >> h1 >> m1 >> s1 >> h2 >> m2 >> s2;

        int t1 = h1 * 3600 + m1 * 60 + s1;
        int t2 = h2 * 3600 + m2 * 60 + s2;
        int d = t2 - t1;

        int h = d / 3600;
        int m = (d % 3600) / 60;
        int s = d % 60;

        cout << setw(2) << setfill('0') << h << ":"
             << setw(2) << setfill('0') << m << ":"
             << setw(2) << setfill('0') << s << "\n";
    }

    return 0;
}
