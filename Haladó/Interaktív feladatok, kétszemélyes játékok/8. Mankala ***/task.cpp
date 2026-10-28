/*
Megoldás lényege:
A játék legfeljebb 8 kavicsos, és minden lépésben pontosan egy kavics tűnik el, így legfeljebb 8 lépés van, a teljes játékfa pedig kicsi.
Rekurzióval döntjük el, hogy az éppen lépő játékos nyer-e: akkor nyer, ha van olyan lépése, amelyre az ellenfél minden válasza után ő maga még nyerő helyzetben van; ha az ellenfélnek nincs lépése, a lépő már nyert, ha pedig neki nincs lépése, veszít.
Egy lépést úgy szimulálunk, hogy a kiválasztott üreg első kavicsát eldobjuk, a többit pedig az óramutató ellenében a következő üregekbe (a sajátot kihagyva) osztjuk.
A kezdőállást a Pit függvényekkel olvassuk be, majd minden körben olyan lépést teszünk (MyMove), amely nyerő helyzetet hagy maga után; az ellenfél lépését a YourMove adja, és ezt a saját állapotunkra is alkalmazzuk.
Az időigény elhanyagolható, mert legfeljebb 2^8 játékágat kell bejárni.
*/
/*
Hint 1: || A kavicsok száma minden lépésben csökken, így a játék véges: írj egy rekurzív függvényt, ami megmondja, hogy az éppen lépő játékos nyer-e az adott állásból. ||
Hint 2: || A szétosztásnál az üregek körsorrendje 1→2→3→4→1; a kiválasztott üreget kihagyva a következő három üreget veszik sorba. Az első kavicsot dobd el, a többit tedd az egyes üregekbe. ||
Hint 3: || Az 1. játékos olyan lépést válasszon, amely után az ellenfél bármely válaszára még van neki nyerő lépése; ha az ellenfélnek nincs lépése, az már nyerés. ||
*/
#include "game.h"
#include <bits/stdc++.h>
using namespace std;

// t[1..4]: az üregek kavicsai; az 1. játékosé az 1. és 2., az ellenfélé a 3. és 4. üreg
typedef array<int, 5> Allas;

// Az i-edik üreg lépése: az első kavics eldobódik, a többit körben szétosztjuk (az i-edik üreget kihagyva)
Allas lep(Allas t, int i) {
    int kavics = t[i] - 1;
    t[i] = 0;
    int kor[3] = {(i % 4) + 1, ((i + 1) % 4) + 1, ((i + 2) % 4) + 1};
    for (int k = 0; k < kavics; k++) {
        t[kor[k % 3]]++;
    }
    return t;
}

bool nyer_en(const Allas& t);

// Az ellenfél lép: igaz, ha minden válasza után az 1. játékos nyer
bool nyer_ellenfel(const Allas& t) {
    for (int i = 3; i <= 4; i++) {
        if (t[i] > 0 && !nyer_en(lep(t, i))) {
            return false;
        }
    }
    return true;
}

// Az 1. játékos lép: igaz, ha van olyan lépése, amely után nyer
bool nyer_en(const Allas& t) {
    for (int i = 1; i <= 2; i++) {
        if (t[i] > 0 && nyer_ellenfel(lep(t, i))) {
            return true;
        }
    }
    return false;
}

int main() {
    Allas t = {0, 0, 0, 0, 0};
    for (int i = 1; i <= 4; i++) {
        t[i] = Pit(i);
    }

    while (true) {
        int valasz = 0;
        for (int i = 1; i <= 2 && valasz == 0; i++) {
            if (t[i] > 0 && nyer_ellenfel(lep(t, i))) {
                valasz = i;
            }
        }
        if (valasz == 0) {  // nincs nyerő lépés: bármelyik szabályos lépés
            for (int i = 1; i <= 2 && valasz == 0; i++) {
                if (t[i] > 0) {
                    valasz = i;
                }
            }
        }
        if (valasz == 0) {  // már nem tudunk lépni
            return 0;
        }
        MyMove(valasz);            // a modul az ellenfél lépését is lejátssza
        t = lep(t, valasz);
        t = lep(t, YourMove());    // az ellenfél lépése: 3 vagy 4
    }
}
