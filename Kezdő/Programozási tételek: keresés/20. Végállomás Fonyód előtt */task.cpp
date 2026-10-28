/*
Megoldás lényege:
A bemenet indulási idő szerint van rendezve, a sorok sorrendje pedig a "Fonyód előtt" viszonyt is megadja.
Egyetlen bejárással haladunk végig a soron, és mindig megjegyezzük az eddig talált utolsó végállomás-sor érkezési idejét.
Végállomás az a sor, amelynek indulási ideje 9999. Amint a Fonyód nevű sorhoz érünk, megállunk, mert a további sorok
már nem Fonyód előtti állomások. A keresett érték a megjegyzett érték; ha nem volt ilyen sor, marad a -1.
Az időigény O(N), ahol N legfeljebb 100.
*/
/*
Hint 1: || Elég egyszer végigolvasni a bemenetet, tömbre nincs szükség. Figyelj arra, mely sorok jelölik a végállomást: ezeknek az indulási ideje 9999. ||
Hint 2: || Tartsd nyilván az eddigi utolsó végállomás érkezési idejét, és ha a Fonyód nevű sorhoz érsz, a ciklust szakítsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int valasz = -1;
    for (int i = 0; i < n; i++) {
        string varos;
        int erkezes, indulas;
        cin >> varos >> erkezes >> indulas;
        if (varos == "Fonyod") break;
        if (indulas == 9999) valasz = erkezes;
    }
    cout << valasz << "\n";
    return 0;
}
