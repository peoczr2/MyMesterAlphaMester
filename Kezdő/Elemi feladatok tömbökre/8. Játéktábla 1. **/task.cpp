/*
Megoldás lényege:
A bábu helyzete két egész szám: a sor sorszáma (1-től 11-ig) és a sorban elfoglalt hely (1-től 2^(sor-1)-ig). Kezdetben a bábu az (1, 1) helyen áll. Minden lépés ezt a párt módosítja: BL esetén a sor eggyel nő, a hely 2p-1 lesz; JL esetén a sor eggyel nő, a hely 2p; F esetén a sor eggyel csökken, a hely (p+1)/2 (egész osztás); B és J esetén a sor marad, a hely eggyel csökken, illetve nő. Lépés előtt ellenőrizzük, hogy az új sor 1 és 11 közé esik-e, és az új hely a sorban lévő elemek közé. Ha nem, a bábu lelépett a tábláról, ezért a program az addigi utolsó helyet írja ki, és befejezi a feldolgozást. A lépéseket egyenként végezzük, így az idő O(K), ami K ≤ 10 mellett nyilvánvalóan belefér az időlimitbe.
*/
/*
Hint 1: || A bábu helyzete két szám: a sor, és hogy a sorban hányadik elemen áll. Minden lépés után ezt a két számot kell frissítened, az egész táblát nem kell tárolnod. ||
Hint 2: || Lefelé lépésnél a sor eggyel nő, a hely BL esetén 2p-1, JL esetén 2p lesz. Felfelé lépésnél a sor eggyel csökken, a hely (p+1)/2 (egész osztás). Lépés előtt nézd meg, hogy az új sor 1 és 11 közé, az új hely pedig 1 és 2^(sor-1) közé esik-e; ha nem, a lépést már nem végzed el, és az addigi helyet írod ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    const int SOROK = 11;   // a tábla sorainak száma

    int k;
    cin >> k;

    int sor = 1, hely = 1;  // a bábu jelenlegi sora és helye a sorban (1-től számozva)
    for (int i = 0; i < k; i++) {
        string lepes;
        cin >> lepes;

        int uj_sor = sor, uj_hely = hely;
        if (lepes == "BL") {
            uj_sor = sor + 1;
            uj_hely = 2 * hely - 1;
        } else if (lepes == "JL") {
            uj_sor = sor + 1;
            uj_hely = 2 * hely;
        } else if (lepes == "F") {
            uj_sor = sor - 1;
            uj_hely = (hely + 1) / 2;
        } else if (lepes == "B") {
            uj_hely = hely - 1;
        } else if (lepes == "J") {
            uj_hely = hely + 1;
        }

        // ha a lépés kivinne a tábláról, a bábu az addigi utolsó helyén marad
        if (uj_sor < 1 || uj_sor > SOROK || uj_hely < 1 || uj_hely > (1 << (uj_sor - 1)))
            break;

        sor = uj_sor;
        hely = uj_hely;
    }

    cout << sor << " " << hely << "\n";
    return 0;
}
