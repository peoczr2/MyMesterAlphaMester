/*
Megoldás lényege:
Az autó tankjának állapotát egyetlen változóban követjük: ez az utoljára elhagyott benzinkútnál maradt benzin mennyisége.
Kezdetben ez B, mert az induló hely is benzinkútnak számít. Egy kúthoz érve az előző kút óta megtett utat (a két
távolság különbségét) szorozzuk L-lel és osztjuk 100-zal, ez a szakaszon elfogyasztott benzin.
Az új mennyiség: előző mennyiség - fogyasztás + tankolt benzin. Ha ez kisebb, mint az előző kút elhagyásakor volt,
ezen kút sorszámát kiírjuk és befejezzük. Mivel a távolságok 100-zal oszthatók, a fogyasztás egész szám.
Az időigény O(N).
*/
/*
Hint 1: || Nem kell a teljes tankállapotot tömbben tárolni: elég egy változóban az aktuális mennyiséget és az utolsó kút helyét nyilvántartani. ||
Hint 2: || Egy kúthoz érve a fogyasztás a távolságkülönbség osztva 100-zal, szorozva L-lel. A tankolás utáni mennyiség: az előző mennyiség, mínusz a fogyasztás, plusz a tankolt benzin. Ha ez kisebb az előzőnél, ezt a kutat keresed. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long k, n, b, l;
    cin >> k >> n >> b >> l;   // a K értéke a számításban nem szerepel
    long long elozo_hely = 0;
    long long elozo_mennyiseg = b;   // az induló helyen (0. kút) elhagyáskor B liter van
    for (long long i = 1; i <= n; i++) {
        long long hely, tankolt;
        cin >> hely >> tankolt;
        long long fogyasztas = (hely - elozo_hely) * l / 100;
        long long mennyiseg = elozo_mennyiseg - fogyasztas + tankolt;
        if (mennyiseg < elozo_mennyiseg) {
            cout << i << "\n";
            return 0;
        }
        elozo_mennyiseg = mennyiseg;
        elozo_hely = hely;
    }
    cout << 0 << "\n";
    return 0;
}
