/*
Megoldás lényege:
Viharnak számít az a nap, amikor a szélsebesség nagyobb, mint 100 km/óra, vagyis a pontosan 100 km/óra még nem vihar. A K érték (legalább hány versenynap kell) a kérdésre nincs hatással, ezért csak az N napi mérést kell végigolvasni.
Minden beolvasott szélsebességnél eldöntjük a feltételt, és a viharos napok számlálóját növeljük, ha teljesül.
Az időigény O(N), a tárigény O(1).
*/
/*
Hint 1: || Figyelj a feltétel szigorúságára: vihar a 100 km/óránál nagyobb szélsebesség, a pontosan 100 már nem az. A K szám a kérdés megválaszolásához nem kell. ||
Hint 2: || Elég egy számlálót tartani. Minden beolvasott szélsebességre egy elágazással döntsd el, hogy viharos napról van-e szó, és ha igen, növeld a számlálót. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int viharos_napok = 0;
    for (int i = 0; i < n; i++) {
        int szelsebesseg;
        cin >> szelsebesseg;
        if (szelsebesseg > 100) {
            viharos_napok++;
        }
    }
    cout << viharos_napok << endl;
    return 0;
}
