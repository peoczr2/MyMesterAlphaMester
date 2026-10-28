/*
Megoldás lényege:
Egy feljegyzés egy (gyártó, generáció) párt jelent, és ugyanaz a pár nem fordul elő kétszer. Ezért generációnként elég a feljegyzések számát tárolni: ez megadja, hány különböző gyártó készített konzolt abban a generációban.
Egy generáció akkor felel meg, ha ez a szám legalább a gyártók felének felel meg, vagyis 2 * db >= N. Így a törtes N/2 és a páratlan N esete is egész számokkal kezelhető.
A feljegyzéseket egyenként beolvassuk, majd a 8 generációt végignézve megszámoljuk a megfelelőket. Az időigény O(M), a tárigény konstans.
*/
/*
Hint 1: || Ne a gyártókat, hanem a generációkat számold: minden generációhoz legyen egy számláló, amely azt mutatja, hány gyártó termékét találtad meg abban a generációban. ||
Hint 2: || Egy gyártó-generáció pár legfeljebb egyszer szerepel a feljegyzésekben, ezért minden beolvasott feljegyzésnél a hozzá tartozó generáció számlálóját egyszerűen növelheted. ||
Hint 3: || A „legalább fele” feltételt egész számokkal írd fel: egy generáció megfelel, ha 2 * (számláló) >= N. A végén az 1. és 8. generáció számlálóit nézd végig, és számold meg a megfelelőket. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> gyartok(9, 0);
    for (int i = 0; i < m; i++) {
        int s, g;
        cin >> s >> g;
        gyartok[g]++;
    }
    int db = 0;
    for (int g = 1; g <= 8; g++) {
        if (2 * gyartok[g] >= n) {
            db++;
        }
    }
    cout << db << endl;
    return 0;
}
