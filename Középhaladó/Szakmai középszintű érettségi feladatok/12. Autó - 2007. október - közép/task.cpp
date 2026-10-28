/*
Megoldás lényege:
A tankolt mennyiségeket egyetlen változóban összegezzük, ez lesz az első részfeladat eredménye: az összes felhasznált üzemanyag. Mivel egy liter üzemanyag K kilométert visz, a második részfeladat eredménye ennek K-szorosa. Az összeg legfeljebb 50 000 * 5000 = 2,5 * 10^8, a megtett kilométer pedig legfeljebb 2,5 * 10^10, ezért long long típust használunk. A kimenetben minden részfeladat eredménye előtt egy # sor áll. Az időigény O(N), a memóriaigény O(1), mert a tankolásokat nem kell tárolni.
*/
/*
Hint 1: || Az első részfeladathoz nincs szükség a tankolások tárolására: a beolvasás közben elég egy változóban gyűjteni az összeget. ||
Hint 2: || A második részfeladat eredménye az első K-szorosa, mert 1 liter K kilométert tesz meg. A kimenetben a # sorokat a részfeladatok eredménye elé kell írni, a kilométer-szám pedig nagy lehet, ezért long long kell. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    long long total = 0;
    for (int i = 0; i < n; i++) {
        long long t;
        cin >> t;
        total += t;
    }

    cout << "#\n" << total << "\n";
    cout << "#\n" << total * k << "\n";

    return 0;
}
