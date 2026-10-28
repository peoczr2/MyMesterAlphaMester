/*
Megoldás lényege:
Minden kupachoz kiszámoljuk, mennyivel tér el az átlagtól (K_i - átlag), és ezek prefixösszegét vesszük.
Az i. prefixösszeg azt mutatja, hogy az i. és az (i+1). kupac közötti határon mennyi követ kell nettó módon átvinni, így ezen a határon csak akkor kell mozgatás, ha a prefixösszeg nem nulla.
Egy mozgatás tetszőleges számú követ vihet át, ezért minden ilyen határon pontosan egy mozgatás elég, a válasz tehát a nem nulla prefixösszegek száma; az időigény O(N).
*/
/*
Hint 1: || Egy mozgatás tetszőleges számú követ vihet át, így két szomszédos kupac közötti határon egyetlen mozgatás is elég. Gondold végig, mikor nincs szükség mozgatásra ezen a határon. ||
Hint 2: || Számold ki minden kupacra a K_i - (a kövek összege / N) különbséget, és ezek prefixösszegét; a válasz azon 1..N-1 indexek száma, ahol a prefixösszeg nem nulla. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> k(n);
    long long osszeg = 0;
    for (int i = 0; i < n; i++) {
        cin >> k[i];
        osszeg += k[i];
    }
    long long atlag = osszeg / n;
    long long prefix = 0;
    int mozgatas = 0;
    for (int i = 0; i + 1 < n; i++) {
        prefix += k[i] - atlag;
        if (prefix != 0) {
            mozgatas++;
        }
    }
    cout << mozgatas << "\n";
    return 0;
}
