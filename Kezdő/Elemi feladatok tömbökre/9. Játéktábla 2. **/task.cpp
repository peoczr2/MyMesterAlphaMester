/*
Megoldás lényege:
Egy lépés legfeljebb egy sorral változtatja a bábu sorát, ezért a gyökérből r sorba legalább r-1 lépés kell. Ezt a hosszt elérjük, ha csak lefelé lépünk, mert ilyenkor minden lépés pontosan eggyel növeli a sort. Ilyen úton a cél egyértelmű: a hely (p-1) bináris alakjának bitjei adják a lépéseket a legnagyobb helyiértéktől kezdve, ahol a 0 a BL, az 1 a JL lépés. Ezért a legrövidebb út hossza a cél sorának és a gyökérnek a távolsága, azaz a bitek száma, és a megoldás az eredeti lépéseket követve ezt a bitsorozatot tartja nyilván: lefelé lépéskor a végére fűz egy bitet, felfelé lépéskor levesz egy bitet, balra vagy jobbra lépéskor a bitekben tárolt számot eggyel csökkenti vagy növeli. A munka O(K * 100), ami bőven belefér az időlimitbe.
*/
/*
Hint 1: || Egy lépés legfeljebb egy sorral mozdítja el a bábut. Mekkora a legrövidebb út hossza, ha a cél sora r? ||
Hint 2: || A gyökérből a célba r-1 lépésben csak lefelé lépésekkel juthatsz el, és ezek a lépések egyértelműen meghatározzák a célt. Gondolj arra, hogy a cél helyének (p-1) bináris alakja milyen lépéseket ad. ||
Hint 3: || Tárold a helyet bitsorozatként: lefelé lépéskor a végére írsz egy bitet (BL = 0, JL = 1), felfelé lépéskor az utolsó bitet törlöd. Balra és jobbra lépéskor a bitsorozatot eggyel csökkented vagy növeled, átvitellel vagy kölcsönzéssel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int k;
    cin >> k;

    // a bábu helye: p-1 bináris alakja, a legnagyobb helyiérték van elöl;
    // a bitek száma éppen a bábu sora mínusz egy
    vector<int> bits;
    for (int i = 0; i < k; i++) {
        int lepes;
        cin >> lepes;

        if (lepes == 0 || lepes == 1) {        // lefelé: új bit a végére (BL = 0, JL = 1)
            bits.push_back(lepes);
        } else if (lepes == 2) {               // felfelé: az utolsó bit törlése
            bits.pop_back();
        } else if (lepes == 3) {               // balra: a szám eggyel csökken
            int j = (int)bits.size() - 1;
            while (bits[j] == 0) {
                bits[j] = 1;
                j--;
            }
            bits[j] = 0;
        } else {                               // jobbra: a szám eggyel nő
            int j = (int)bits.size() - 1;
            while (bits[j] == 1) {
                bits[j] = 0;
                j--;
            }
            bits[j] = 1;
        }
    }

    // a legrövidebb út hossza a bitek száma, a lépések maguk a bitek
    cout << bits.size() << "\n";
    for (size_t i = 0; i < bits.size(); i++) {
        if (i) cout << ' ';
        cout << bits[i];
    }
    cout << "\n";
    return 0;
}
