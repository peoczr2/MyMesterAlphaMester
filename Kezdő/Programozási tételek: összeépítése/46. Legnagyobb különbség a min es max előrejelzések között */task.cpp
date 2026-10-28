/*
Megoldás lényege:
Minden település sorát egyszer végigolvassuk, és közben nyilvántartjuk a napi hőmérsékletek minimumát és maximumát.
A település eltérése a maximum és a minimum különbsége, amelyet a sor beolvasása után azonnal összehasonlítunk az eddigi legnagyobb eltéréssel.
Ha az új eltérés szigorúan nagyobb, frissítjük a legnagyobb eltérést és a település sorszámát; egyenlőség esetén a korábbi marad, mert az elsőt kell kiírni.
A K hőmérsékletkorlát a kérdésben nem szerepel, ezért nem használjuk.
Az időigény O(N·M), a memóriaigény O(1), mert a hőmérsékleteket nem tároljuk.
*/
/*
Hint 1: || Egy település eltérését csak a saját napi adataiból számold ki: a legnagyobb és a legkisebb napi hőmérséklet különbsége. A települések napjait nem kell egymással összevetni. ||
Hint 2: || Egy menetben haladj a települések között, és tartsd nyilván az eddigi legnagyobb eltérést és a hozzá tartozó sorszámot. Csak szigorúan nagyobb eltérésnél frissíts, így egyenlőség esetén a korábbi település marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;  // a K korlát nem befolyásolja a kimenetet

    int legnagyobbEltérés = -1;
    int legjobbTelepules = 0;
    for (int i = 1; i <= n; i++) {
        int legkisebb = INT_MAX, legnagyobb = INT_MIN;
        for (int j = 0; j < m; j++) {
            int h;
            cin >> h;
            legkisebb = min(legkisebb, h);
            legnagyobb = max(legnagyobb, h);
        }
        if (legnagyobb - legkisebb > legnagyobbEltérés) {
            legnagyobbEltérés = legnagyobb - legkisebb;
            legjobbTelepules = i;
        }
    }

    cout << legjobbTelepules << endl;
    return 0;
}
