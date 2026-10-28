/*
Megoldás lényege:
Az első sorban álló N után N adatpárt (cégnév és mennyiség) olvasunk be. Az első beolvasott cég nevét eltároljuk, a többi sornál pedig csak azoknak a mennyiségét adjuk az összeghez, akiknek a neve megegyezik ezzel. Nem kell az összes adatot tárolni, mert minden sort egyszer, a beolvasás pillanatában dolgozunk fel. Az algoritmus O(N) időben fut, ami N ≤ 100 esetén messze az időlimit alatt van.
*/
/*
Hint 1: || Nem kell az összes adatot eltárolni: elég egy összeg-változó és az első cég nevének megjegyzése. ||
Hint 2: || A ciklus első körében (i = 0) mentsd el az első cég nevét, a további köröknél pedig csak az egyező nevűek mennyiségét add az összeghez. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    string elso_ceg;
    long long osszeg = 0;
    for (int i = 0; i < n; i++) {
        string ceg;
        long long mennyiseg;
        cin >> ceg >> mennyiseg;
        if (i == 0) {
            elso_ceg = ceg;
        }
        if (ceg == elso_ceg) {
            osszeg += mennyiseg;
        }
    }

    cout << osszeg << "\n";
    return 0;
}
