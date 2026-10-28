/*
Megoldás lényege:
Egy háború csak akkor biztosan rövidebb egy évnél, ha a kezdő és a befejező éve ugyanaz. Ha az évszámok különböznek, a háború lehet rövidebb egy évnél, de ez nem biztos, ezért nem számít. A feladat tehát a kezdő és befejező évük egyező háborúk számát kérdezi. Egyetlen beolvasás és egy számlálás, az idő O(K).
*/
/*
Hint 1: || Az évszámokból csak akkor lehet biztosan tudni, hogy a háború egy évnél rövidebb, ha a kezdő és a befejező évszám egyezik. ||
Hint 2: || Olvasd be a háborúkat, és minden sornál ellenőrizd, hogy a negyedik és a harmadik szám egyenlő-e. Az egyezők számát írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int db = 0;
    for (int i = 0; i < k; i++) {
        int a, b, kezdet, vege;
        cin >> a >> b >> kezdet >> vege;
        if (kezdet == vege) db++;
    }
    cout << db << "\n";
    return 0;
}
