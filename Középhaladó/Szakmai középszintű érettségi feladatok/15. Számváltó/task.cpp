/*
Megoldás lényege:
Egy decimális szám hexadecimális alakját a 16-tal való maradékos osztással kapjuk meg: az osztás maradéka adja az utolsó számjegyet, a hányadossal pedig ugyanígy haladunk tovább, amíg nulla nem lesz. A 10–15 közötti maradékokat az A–F betűk jelölik. A kapott számjegyeket fordított sorrendben kapjuk, ezért a végén meg kell fordítani őket. A 0 speciális eset, mert ekkor a ciklus egyáltalán nem fut le, így a „0” kiírást külön kezeljük. Mivel D ≤ 2 000 000 000, egy szám legfeljebb 8 hexadecimális jegyű, így az N ≤ 100 000 szám átváltása gyorsan lefut.
*/
/*
Hint 1: || Egy szám hexadecimális alakjának utolsó jegyét a 16-tal való osztás maradéka adja, a további jegyeket pedig a hányados ugyanilyen átalakításával kapod meg. ||
Hint 2: || A maradékokat (0–15) gyűjtsd egy szövegbe a „0123456789ABCDEF” karaktersorozat indexelésével, majd a kész szöveget fordítsd meg. Figyelj arra, hogy a 0 esetén a ciklus nem ad jegyet, ezt külön kell kezelni. ||
*/
#include <bits/stdc++.h>
using namespace std;

string toHex(long long x) {
    if (x == 0) return "0";

    const string digits = "0123456789ABCDEF";
    string s;
    while (x > 0) {
        s += digits[x % 16];
        x /= 16;
    }
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        long long d;
        cin >> d;
        cout << toHex(d) << "\n";
    }

    return 0;
}
