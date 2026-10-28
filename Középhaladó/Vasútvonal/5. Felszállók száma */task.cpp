/*
Megoldás lényege:
A kérdés a felszállók teljes számára vonatkozik, ezért a leszállókat nem kell figyelembe venni.
Az állomások számát beolvassuk, majd minden állomásnál beolvassuk a leszállók és a felszállók számát, és csak a felszállókat adjuk hozzá egy összegző változóhoz.
Az összeg legfeljebb 1000 · 800 = 800 000 lehet, így egy egyszerű összegzés egyetlen bejárásban megoldja a feladatot.
Az időigény O(N), ami N ≤ 1000 esetén az időlimit (0,1 mp) alatt van.
*/
/*
Hint 1: || A kérdés csak a felszállókról szól, a leszállók számával nem kell számolni. ||
Hint 2: || Egy összegző változóba gyűjtsd az összes állomás felszállóinak számát, és a végén írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long felszallok = 0;
    for (int i = 0; i < n; i++) {
        int leszallo, felszallo;
        cin >> leszallo >> felszallo;
        felszallok += felszallo;
    }
    cout << felszallok << endl;
    return 0;
}
