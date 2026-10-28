/*
Megoldás lényege:
Egy megállóban akkor nem áll meg a villamos, ha az érkezési és az indulási idő megegyezik. Az ilyen megállók sorszámát a beolvasás sorrendjében kell vizsgálni, és az elsőt kell kiírni. A 0. állomás nem számít bele, a megállók sorszáma 1-től N-ig tart. Ha egyetlen megállóban sem áll meg a villamos, a válasz -1. A megoldás egyetlen menetben működik, és az első találat után már nincs szükség a további adatokra, így az időigény O(N).
*/
/*
Hint 1: || Azt a megállót keresd, ahol az érkezési idő és az indulási idő egyenlő. A távolság ebben a feladatban nem számít. ||
Hint 2: || Olvasd be a megállókat sorban, és tárold az aktuális sorszámot. Az első olyan megállónál, ahol a két idő egyenlő, írd ki a sorszámot. Ha nincs ilyen, az alapértelmezett érték -1 maradjon. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int answer = -1;
    for (int i = 1; i <= n; i++) {
        int dist, arr, dep;
        cin >> dist >> arr >> dep;
        if (answer == -1 && arr == dep) {
            answer = i;
        }
    }

    cout << answer << '\n';
    return 0;
}
