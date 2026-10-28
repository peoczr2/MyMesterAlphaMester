/*
Megoldás lényege:
A sípályákat sorban, egyetlen ciklusban olvassuk be, és az első olyan pályánál, ahol a hóréteg legalább 100 cm, eltároljuk a sorszámát. Mivel a legkisebb sorszámú pályát kell megadni, az első találat már a jó válasz, a további pályák az eredményt nem befolyásolják. Ha egyik pályán sincs elég hó, a kezdeti -1 marad, és ezt írjuk ki. Az időigény O(N), ami N ≤ 100 esetén nagyon gyors.
*/
/*
Hint 1: || Egyetlen ciklus elég: menj végig a sípályák hóvastagságán sorban, és figyeld az első olyan értéket, amely legalább 100. ||
Hint 2: || A talált sorszámot tárold el egy változóban, és csak az első találatnál írd felül; ha a ciklus végéig nincs találat, a kezdeti érték -1 marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int answer = -1;
    for (int i = 1; i <= n; i++) {
        int v;
        cin >> v;
        if (answer == -1 && v >= 100) {
            answer = i;
        }
    }
    cout << answer << "\n";
    return 0;
}
