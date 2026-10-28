/*
Megoldás lényege:
A magasságoknak a kérdés szempontjából nincs szerepe: minden bejegyzés egy világcsúcs-esemény (a beállítások is ide tartoznak), így csak azt kell tudni, mely években volt legalább egy ilyen esemény. Az ismétlődő éveket a halmaz (set) egyszerűen kiszűri, és ugyanez a halmaz rendezi is az éveket. Ezután az éveken egyszer végigmenve nyilvántartjuk az aktuális, folytonos évekből álló szakasz kezdetét: ha a következő év az előzőnek a rákövetkezője, a szakasz folytatódik, különben új szakasz kezdődik. Minden évnél összevetjük az aktuális szakasz hosszát a legjobbal, és csak szigorúan nagyobb hossznál cseréljük, így a legkorábbi leghosszabb szakasz marad meg. A futásidő O(N log N), ami N ≤ 100 mellett bőven belefér.
*/
/*
Hint 1: || A magasság ebben a feladatban nem számít: minden sor egy világcsúcs-esemény, így csak azt kell tudni, mely években volt legalább egy ilyen esemény. ||
Hint 2: || Az évek halmazát rendezve, ismétlődések nélkül tárold, majd egyszer végigmenve kövesd a folytonos évekből álló szakaszt: ha az aktuális év pont az előző után következik, a szakasz folytatódik. ||
Hint 3: || Tartsd nyilván az aktuális szakasz kezdetét, valamint a legjobb szakasz kezdetét, végét és hosszát; egy szakasz hossza az aktuális év mínusz a szakasz kezdete plusz egy, és csak szigorúan nagyobb hossznál írd felül a legjobbat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    // A magasságot be kell olvasni, de a megoldáshoz nem kell. A set rendezi az éveket és kiszűri az ismétlődéseket.
    set<int> evek;
    for (int i = 0; i < n; ++i) {
        int ev, magassag;
        cin >> ev >> magassag;
        evek.insert(ev);
    }

    int legjobb_kezdet = 0, legjobb_veg = 0, legjobb_hossz = 0;
    int kezdet = 0, elozo = 0;
    bool elso = true;

    for (int ev : evek) {
        if (elso || ev != elozo + 1) {
            kezdet = ev; // új szakasz indul
        }
        elso = false;
        elozo = ev;

        int hossz = ev - kezdet + 1;
        if (hossz > legjobb_hossz) {
            legjobb_hossz = hossz;
            legjobb_kezdet = kezdet;
            legjobb_veg = ev;
        }
    }

    cout << legjobb_kezdet << ' ' << legjobb_veg << '\n';
    return 0;
}
