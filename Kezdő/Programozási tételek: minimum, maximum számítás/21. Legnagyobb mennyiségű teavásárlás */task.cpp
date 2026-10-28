/*
Megoldás lényege:
A vásárlásokat sorban olvassuk, és csak a mennyiség számít: egy menetes maximumkiválasztással nyilvántartjuk az eddigi legnagyobb mennyiséget és annak sorszámát. A teafajta nevét beolvassuk, de nem használjuk. Szigorú „>” összehasonlítást alkalmazunk, így több azonos maximum esetén a legkisebb sorszám marad. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || A kérdés egyetlen vásárlás mennyiségére vonatkozik, nem a cégek összesített vásárlására: elég a legnagyobb egyedi mennyiséget keresni. ||
Hint 2: || Egy menetes maximumkiválasztás: a teafajta nevét olvasd be és dobd el, a mennyiséget tartsd nyilván, és csak szigorúan nagyobb értéknél frissíts. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int bestIdx = 0;
    int bestQty = -1;
    for (int i = 1; i <= n; i++) {
        string tea;
        int qty;
        cin >> ws;
        getline(cin, tea);
        cin >> qty;
        if (qty > bestQty) {
            bestQty = qty;
            bestIdx = i;
        }
    }

    cout << bestIdx << "\n";
    return 0;
}
