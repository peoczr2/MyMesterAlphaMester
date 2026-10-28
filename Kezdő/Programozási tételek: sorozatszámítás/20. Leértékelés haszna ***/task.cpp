/*
Megoldás lényege:
Nincs szükség tömbre: minden termék sorát beolvasás után azonnal feldolgozzuk és hozzáadjuk az összegekhez.
Az első héten a bevétel az alapár és az első heti eladott darabszám szorzata, a másodikon a kedvezményes ár és a második heti darabszám szorzata.
A haszon ugyanez, csak az árból előbb levonjuk a beszerzési árat, mert a haszon az ár feletti rész.
Az összegek legfeljebb 10^9 nagyságúak, ezért long long típust használunk.
Az első sorba az első és második heti bevétel különbsége, a másodikba a két hét haszna kerül. Az időigény O(N).
*/
/*
Hint 1: || Nincs szükség tömbre: minden termék sorát beolvasás után azonnal feldolgozhatod, és hozzáadhatod a fut összegekhez. ||
Hint 2: || A bevétel az ár és az eladott darabszám szorzata, a haszon pedig ugyanez, de az árból előbb a beszerzési árat kell kivonni. ||
Hint 3: || Hét szerint külön-külön két bevétel- és két haszon-összeg kell, az első sorba a bevételek különbsége (első - második) kerül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long bev1 = 0, bev2 = 0, haszon1 = 0, haszon2 = 0;
    for (int i = 0; i < n; i++) {
        long long beszerzes, ar1, ar2, db1, db2;
        cin >> beszerzes >> ar1 >> ar2 >> db1 >> db2;
        bev1 += ar1 * db1;
        bev2 += ar2 * db2;
        haszon1 += (ar1 - beszerzes) * db1;
        haszon2 += (ar2 - beszerzes) * db2;
    }
    cout << bev1 - bev2 << "\n";
    cout << haszon1 << " " << haszon2 << "\n";
    return 0;
}
