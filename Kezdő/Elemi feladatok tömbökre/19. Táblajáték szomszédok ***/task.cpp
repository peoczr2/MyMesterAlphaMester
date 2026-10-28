/*
Megoldás lényege:
A négy módszer két kérdésben tér el: a szomszédság lehet sarkos (8 irány, a távolság a maximum-norma), vagy csak oldalas (4 irány, a távolság az összeg-norma), és a tábla széle lehet körbeérő (C és D). Mind a négy esetet ugyanaz a bejárás adja: a (dx, dy) eltolásokat -T és T között végigpróbáljuk, és csak azokat tartjuk meg, amelyek a választott távolságon belül vannak és nem az eredeti mező. Körbeérésnél a koordinátát a 100-zal vett maradékkal visszük a táblára, így a szélen túlnyúló szomszédok a túloldalon jelennek meg. A dx külső, dy belső ciklusa adja a mintának megfelelő sorrendet, az egész számítás O(T^2) lépés, ami a korláton belül van.
*/
/*
Hint 1: || A négy eset két kapcsolóval írható le: sarkos vagy oldalas a szomszédság (A és C sarkos, B és D oldalas), és körbeérő vagy nem (C és D körbeér). Mind a négy kimenetet ugyanígy állítsd elő. ||
Hint 2: || Járd végig a (dx, dy) eltolásokat -T-től T-ig mindkét irányban, a (0, 0) párt hagyd ki; sarkos esetben a távolság max(|dx|, |dy|), oldalas esetben |dx| + |dy|, és csak a T-nél nem nagyobb távolságúakat vedd. ||
Hint 3: || Körbeérő esetben az új koordináta ((x − 1) mod 100) + 1, ügyelve a negatív maradékra; nem körbeérő esetben az 1 és 100 közötti tartományon kívüli párokat dobd el. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int MERET = 100;

// A koordinátát a táblán belülre igazítja (körbeérés): 1..MERET közé tesz
int korbe(int x) {
    return ((x - 1) % MERET + MERET) % MERET + 1;
}

int main() {
    int x, y, t;
    cin >> x >> y >> t;

    for (int m = 0; m < 4; m++) {
        bool sarkos = (m == 0 || m == 2);   // A és C: sarokkal is szomszéd
        bool korbeer = (m >= 2);            // C és D: a tábla széle körbeér

        for (int dx = -t; dx <= t; dx++) {
            for (int dy = -t; dy <= t; dy++) {
                if (dx == 0 && dy == 0) continue;

                int tav = sarkos ? max(abs(dx), abs(dy)) : abs(dx) + abs(dy);
                if (tav > t) continue;

                int nx = x + dx;
                int ny = y + dy;
                if (korbeer) {
                    nx = korbe(nx);
                    ny = korbe(ny);
                } else if (nx < 1 || nx > MERET || ny < 1 || ny > MERET) {
                    continue;
                }
                cout << "(" << nx << "," << ny << ");";
            }
        }
        cout << "\n";
    }
    return 0;
}
