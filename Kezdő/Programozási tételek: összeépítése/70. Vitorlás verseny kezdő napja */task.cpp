/*
Megoldás lényege:
Egy menetben olvassuk a napokat, és egy futó számlálóval nyilvántartjuk, hány egymás utáni nap esik 10 és 100 km/óra közé. Ha a különbség nem teljesül, a számláló nullázódik. Amint a számláló eléri a K-t, az aktuális nap sorszámából visszaszámolva megkapjuk az első megfelelő szakasz kezdő napját, és azt kiírjuk. Ha a számláló végig nem éri el a K-t, nincs ilyen nap, és -1-et írunk. Az időigény O(N), a memóriaigény O(1), mert a szélsebességeket sem kell eltárolni.
*/
/*
Hint 1: || Nem kell az összes lehetséges kezdőnapot külön vizsgálni: elég azt figyelni, hány egymás utáni nap felel meg a feltételnek, és egy rossz nap után újra kezdeni a számolást. ||
Hint 2: || Ha a futó számláló eléri a K-t az i. napnál, a szakasz kezdő napja i - K + 1, és ez az első ilyen szakasz, így azonnal kiírható. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    int futo = 0;
    for (int i = 1; i <= n; i++) {
        int s;
        cin >> s;
        if (s >= 10 && s <= 100) {
            futo++;
            if (futo == k) {
                cout << i - k + 1 << "\n";
                return 0;
            }
        } else {
            futo = 0;
        }
    }

    cout << -1 << "\n";
    return 0;
}
