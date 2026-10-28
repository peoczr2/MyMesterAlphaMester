/*
Megoldás lényege:
A birtokok területei növekvő sorrendben vannak, ezért egy X birtokhoz tartozó két másik birtok területe mindig kisebb X-nél, sorszámuk tehát X sorszáma előtt van. Ezért a legnagyobb sorszámú birtoktól visszafelé haladunk, és az első olyan birtoknál állunk meg, amelyhez van megfelelő pár. Egy X birtokra a kétmutatós keresés az első birtoktól és az X-et megelőző birtoktól indul: ha a két terület összege kisebb a célnál, a bal mutatót léptetjük, ha nagyobb, a jobbat. Egy X-re O(N) lépés kell, így a legrosszabb eset O(N^2), ami N<=10 000 mellett a 0,2 mp időlimitbe várhatóan belefér.
*/
/*
Hint 1: || Mivel a területek növekvők, a megvásárolt birtok csak akkor lehet jó, ha a két másik birtok sorszáma nála kisebb. Ezért a legnagyobb területtől lefelé vizsgáld a birtokokat, és az első jó lesz a válasz. ||
Hint 2: || Egy X birtokra a tömb elejétől és az X-et megelőző elemtől indulva keress párt két mutatóval: ha az összeg kisebb a területnél, a bal mutatót léptesd előre, ha nagyobb, a jobbat hátrébb. Az első egyező összegnél kiírhatod a két sorszámot. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = n - 1; i >= 2; i--) {
        int l = 0, r = i - 1;
        while (l < r) {
            int s = a[l] + a[r];
            if (s == a[i]) {
                cout << i + 1 << " " << a[i] << "\n";
                cout << l + 1 << " " << r + 1 << "\n";
                return 0;
            }
            if (s < a[i]) {
                l++;
            } else {
                r--;
            }
        }
    }

    cout << -1 << "\n";
    return 0;
}
