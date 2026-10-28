/*
Megoldás lényege:
Minden állomást külön kell megvizsgálni: az számít, hogy ott egyszerre volt-e leszálló és felszálló, a vonaton lévő utasok száma nem fontos.
Egy állomás akkor jó, ha a leszállók száma és a felszállók száma is nagyobb nullánál.
Az állomásokat egyesével beolvassuk, és ha mindkét szám pozitív, növeljük a számlálót.
Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Minden állomást külön kell nézni, és az érdekel, hogy ott egyszerre van-e leszálló és felszálló. A vonaton lévő teljes utasszám most nem számít. ||
Hint 2: || Olvasd be az állomásokat egymás után, és minden állomásnál ellenőrizd, hogy a leszállók száma és a felszállók száma is nagyobb-e nullánál. Ha igen, növeld a számlálót. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int count = 0;  // azon állomások száma, ahol volt leszálló és felszálló is
    for (int i = 0; i < n; i++) {
        int le, fel;
        cin >> le >> fel;
        if (le > 0 && fel > 0) count++;
    }

    cout << count << "\n";
    return 0;
}
