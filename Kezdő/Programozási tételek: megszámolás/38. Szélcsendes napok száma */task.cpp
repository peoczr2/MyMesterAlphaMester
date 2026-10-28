/*
Megoldás lényege:
Szélcsendes az a nap, amikor a mért szélsebesség pontosan 0. A napok sorrendje a kérdésre nem hat, ezért minden értéket beolvasás után azonnal megvizsgálunk, és nulla esetén növeljük a számlálót. A versenynapok száma (K) a kimenetet nem befolyásolja, ezért a számításban nem használjuk. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Szélcsendes az a nap, amikor a mért szélsebesség pontosan nulla. A versenynapok száma (K) ehhez nem kell. ||
Hint 2: || Nem kell eltárolni a méréseket: egyetlen ciklusban olvasd be az értékeket, és minden nulla értéknél növeld a számlálót. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int db = 0;
    for (int i = 0; i < n; i++) {
        int s;
        cin >> s;
        if (s == 0) db++;
    }
    cout << db << "\n";
    return 0;
}
