/*
Megoldás lényege:
Minden tanulót a pontszáma alapján sorolunk osztályzatba: a KH-nál kisebb pont 1-es, a KH és HH közötti pont 2-es, a HH és NH közötti pont 3-as, az NH és OH közötti pont 4-es, az OH-val egyenlő vagy annál nagyobb pont 5-ös. Osztályzatonként egy elemben tároljuk az eddig látott legnagyobb pontszámot, kezdetben -1-et, így a nem született osztályzat -1 marad. A tanulókat egyszer végigolvassuk, és minden pontszámnál frissítjük a megfelelő osztályzat maximumát. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Nem kell az összes pontszámot tárolni: osztályzatonként elég az eddig látott legnagyobb értéket nyilvántartani. ||
Hint 2: || Az osztályzatot a küszöbök sorrendjében határozd meg: az első olyan küszöb (KH, HH, NH, OH), amelynél a pont kisebb, megadja az osztályzatot (KH: 1, HH: 2, NH: 3, OH: 4); ha egyik sem, akkor ötöst kapott. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    int kh, hh, nh, oh;
    cin >> kh >> hh >> nh >> oh;

    array<int, 6> legjobb;
    legjobb.fill(-1);

    for (int i = 0; i < n; ++i) {
        int pont;
        cin >> pont;
        int osztalyzat;
        if (pont < kh) osztalyzat = 1;
        else if (pont < hh) osztalyzat = 2;
        else if (pont < nh) osztalyzat = 3;
        else if (pont < oh) osztalyzat = 4;
        else osztalyzat = 5;
        legjobb[osztalyzat] = max(legjobb[osztalyzat], pont);
    }

    for (int osztalyzat = 1; osztalyzat <= 5; ++osztalyzat) {
        cout << legjobb[osztalyzat] << '\n';
    }
    return 0;
}
