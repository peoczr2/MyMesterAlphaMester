/*
Megoldás lényege: minden hajításra közvetlenül alkalmazzuk a képletet: s = v0² · sin(2α) / g, ahol g = 9,81. A C++ sin függvény radiánt vár, ezért a 2α szöget előbb radiánba váltjuk (szög · π / 180). Mivel 0 és 90 fok között van a szög, a sin(2α) nem lehet negatív, így az eredmény sem; a kiírás előtt ezt egy egyszerű védelemmel is biztosítjuk, hogy ne jelenjen meg felesleges „-0.00” érték. A kiírás két tizedesjegyű, fix pontos formában történik. Minden hajítás O(1) időben számolható, így az egész program O(N) időben fut, ami N ≤ 10^4 esetén bőven belefér az időlimitbe.
*/
/*
Hint 1: || A képlet minden hajításra közvetlenül egy számot ad, tehát csak a bemenet beolvasása és a képlet helyes lefordítása a feladat. Figyelj arra, hogy a szög fokban van, a C++ sin függvény viszont radiánt vár. ||
Hint 2: || A számítást valós típusban végezd, a v0 négyzetét és a g-vel való osztást a képlet szerinti sorrendben írd le. A kiíráskor állítsd be a tizedesjegyek számát kettőre (fixed és setprecision). ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const double g = 9.81;
    const double pi = acos(-1.0);

    int n;
    cin >> n;
    cout << fixed << setprecision(2);
    for (int i = 0; i < n; i++) {
        double v0, alpha;
        cin >> v0 >> alpha;
        double s = v0 * v0 * sin(2 * alpha * pi / 180.0) / g;
        if (s < 0) s = 0;
        cout << s << '\n';
    }
    return 0;
}
