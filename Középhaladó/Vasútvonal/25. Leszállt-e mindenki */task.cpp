/*
Megoldás lényege:
Követjük a vonaton lévő utasok számát: minden állomáson először leszállnak az utasok, utána felszállnak, így a létszám a leszállók levonásával és a felszállók hozzáadásával változik.
Székesfehérvár az utolsó állomás, ahol nincs felszálló, és leszállt mindenki akkor, ha az ide érkezéskor a vonaton lévő utasok száma pontosan megegyezik az itt leszállók számával.
Ezért az utolsó állomás előtti létszámot és az utolsó állomás leszállóinak számát tároljuk el, és a végén ezt a kettőt hasonlítjuk össze.
Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Követd végig a vonaton lévő utasok számát: minden állomáson a létszám a leszállók számával csökken, a felszállók számával nő. ||
Hint 2: || Az utolsó állomásra érkezéskor a vonaton lévő utasok számát hasonlítsd össze az ott leszállók számával, mielőtt az állomáson a felszállók hozzáadódnának. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long cur = 0;      // a vonaton lévő utasok száma
    long long arriving = 0; // az utolsó állomásra érkezéskor a vonaton lévők száma
    long long leaving = 0;  // az utolsó állomáson leszállók száma
    for (int i = 0; i < n; i++) {
        long long le, fel;
        cin >> le >> fel;
        arriving = cur;
        leaving = le;
        cur = cur - le + fel;
    }

    cout << (arriving == leaving ? 1 : 0) << "\n";
    return 0;
}
