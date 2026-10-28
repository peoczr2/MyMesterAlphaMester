/*
Megoldás lényege:
Termékenként kiszámoljuk az első héten elért hasznot: (alapár - beszerzési ár) · első heti eladott darab. Ugyanígy kiszámoljuk a második héten elért hasznot: (kedvezményes ár - beszerzési ár) · második heti eladott darab. A leértékelés akkor nem érte meg, ha a második heti haszon nem nagyobb az elsőnél, vagyis egyenlőség esetén is a termék nem érte meg. Ilyenkor a termék sorszámát eltároljuk. A termékeket a bemenet sorrendjében dolgozzuk fel, így a kiválasztott sorszámok növekvő sorrendben lesznek. Az időigény O(N), ami N ≤ 100 esetén bőven elég.
*/
/*
Hint 1: || Egy termék haszna egy héten: (eladási ár - beszerzési ár) szorozva az eladott darabszámmal. Termékenként a két hetet kell összehasonlítani. ||
Hint 2: || Az első héten az alapárat, a másodikban a kedvezményes árat kell használni. Ha a második heti haszon kisebb vagy egyenlő az elsőnél, a termék sorszámát el kell tárolni. ||
Hint 3: || A termékek már sorszám szerint vannak, így elég egy menet. A kiválasztott sorszámokat egy vektorban gyűjtsd, és a kiírásnál előbb a darabszámot, utána a sorszámokat add ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> valasztott;
    for (int i = 1; i <= n; i++) {
        int beszerzes, alap, kedvezmeny, ad, kd;
        cin >> beszerzes >> alap >> kedvezmeny >> ad >> kd;

        int elso_het = (alap - beszerzes) * ad;
        int masodik_het = (kedvezmeny - beszerzes) * kd;

        if (masodik_het <= elso_het) valasztott.push_back(i);
    }

    cout << valasztott.size() << '\n';
    for (size_t i = 0; i < valasztott.size(); i++) {
        if (i > 0) cout << ' ';
        cout << valasztott[i];
    }
    cout << '\n';

    return 0;
}
