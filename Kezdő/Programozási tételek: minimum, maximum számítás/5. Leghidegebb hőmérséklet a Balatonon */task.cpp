/*
Megoldás lényege:
A hőmérsékleteket egy menetben olvassuk be, és közben egyetlen változóban tároljuk az eddigi legkisebb értéket. Minden új hőmérsékletet összehasonlítunk a tárolt minimummal, és ha kisebb, felülírjuk. Mivel a napok száma legfeljebb 100, az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Nem kell a teljes sorozatot eltárolni: elég egy változó, amely a látott legkisebb hőmérsékletet tartalmazza. ||
Hint 2: || A kezdőértéket úgy válaszd meg, hogy az első beolvasott hőmérséklet biztosan felülírja, például egy nála nagyobb számot állíts be kezdetben. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int leghidegebb = INT_MAX;
    for (int i = 0; i < n; i++) {
        int h;
        cin >> h;
        leghidegebb = min(leghidegebb, h);
    }

    cout << leghidegebb << "\n";
    return 0;
}
