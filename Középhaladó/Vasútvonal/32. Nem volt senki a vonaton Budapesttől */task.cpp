/*
Megoldás lényege:
Állomásról állomásra követjük a vonaton lévő utasok számát: minden állomás után hozzáadjuk a felszállókat és kivonjuk a leszállókat. Azt keressük, hogy melyik az első olyan állomás, ahol az állomás elhagyása után már van utas; a vonat az ezt megelőző állomásokig, az érkezéskor is üres volt, így ez a sorszám a válasz. Ha a létszám végig nulla marad, az utolsó állomás sorszámát kell kiírni. Egyetlen bejárás elég, az első találatot megjegyezzük, a későbbieket már nem írjuk felül. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Számold végig az állomásokat, és kövesd a vonaton lévő utasok létszámát: minden állomás után hozzáadod a felszállókat, és levonod a leszállókat. ||
Hint 2: || Az első olyan sorszámot keresd, ahol a létszám először nem nulla. Ezt az első találatnál rögzítsd, a későbbieket már ne írd felül; ha sosem lesz nem nulla, az utolsó állomás sorszáma a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long cur = 0;   // a vonaton lévő utasok száma az aktuális állomás elhagyása után
    int answer = n;      // ha végig nulla marad a létszám, az utolsó állomásig üres a vonat
    bool found = false;
    for (int i = 1; i <= n; i++) {
        long long le, fel;
        cin >> le >> fel;
        cur += fel - le;
        if (!found && cur != 0) {
            answer = i;
            found = true;
        }
    }

    cout << answer << "\n";
    return 0;
}
