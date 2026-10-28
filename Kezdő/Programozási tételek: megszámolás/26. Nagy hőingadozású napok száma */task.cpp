/*
Megoldás lényege:
Minden naphoz beolvassuk a várható legkisebb és legnagyobb hőmérsékletet, és kiszámoljuk a kettő különbségét.
Ha a különbség legalább 10, a nap beleszámít a végső darabszámba. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Egy naphoz elég a két érték különbségét vizsgálni, a konkrét hőmérsékletek külön nem számítanak. ||
Hint 2: || A feltétel: a legnagyobb és a legkisebb érték különbsége legalább 10, vagyis max - min >= 10. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int db = 0;
    for (int i = 0; i < n; i++) {
        int mn, mx;
        cin >> mn >> mx;
        if (mx - mn >= 10) db++;
    }
    cout << db << endl;
    return 0;
}
