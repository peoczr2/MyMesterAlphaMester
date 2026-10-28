/*
Megoldás lényege:
A kérdés csak az árakra vonatkozik, a bor mennyisége az eredményt nem befolyásolja. Az évenkénti árakat egy halmazba (set) gyűjtjük, mert a halmaz minden értéket csak egyszer tárol. A halmaz elemszáma adja a különböző áron árult borok számát. Az időigény O(N log N), N ≤ 100 mellett elhanyagolható.
*/
/*
Hint 1: || A bor mennyisége a feladat szempontjából nem számít: csak az árat kell figyelembe venni. ||
Hint 2: || Gyűjtsd az árakat egy halmazba (set), mert ott minden érték csak egyszer szerepel. Az eredmény a halmaz mérete. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    set<int> prices;
    for (int i = 0; i < n; i++) {
        int quantity, price;
        cin >> quantity >> price;
        prices.insert(price);
    }

    cout << prices.size() << "\n";
    return 0;
}
