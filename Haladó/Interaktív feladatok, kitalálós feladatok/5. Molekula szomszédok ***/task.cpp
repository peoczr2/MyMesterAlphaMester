/*
Megoldás lényege: az 1-es atomból kiindulva egy összefüggő láncot építünk, amely a molekula egy szakasza, és ezt a lánc két végéről (bal és jobb) bővítjük.
A Kozte(v, t) hívás, ha v és t nem szomszédos, olyan atomot ad, amely v szomszédja t felé, vagy t szomszédja v felé; így a válasz mindig a két atom közötti szakaszon van.
Ha a válasz már a láncban lévő atom, akkor t a lánc másik oldalán van, ezért a bővítés irányát megfordítjuk.
A még nem elhelyezett atomokat verem tárolja: a verem tetejét a lánc aktuális végéhez teszteljük, és ha Kozte(vég, tető) a véget vagy a tetőt adja, akkor a tető szomszédos a lánc végével, így elhelyezzük.
Ellenkező esetben a kapott új atomot tesszük a verem tetejére, amely a lánc végéhez közelebb van, így egy atom sem kerül kétszer a verembe.
Minden elhelyezés és minden verembe tétel egyetlen Kozte-hívással jár, az irányváltás pedig verem-életciklusonként legfeljebb egyszer fordul elő, ezért összesen legfeljebb 2N-2 hívás van, ami a 2N-es korláton belül marad.
A végén a Sorrend hívásokkal adjuk meg a lánc sorrendjét; a tükörkép is elfogadott.
*/
/*
Hint 1: || Ne próbálj minden atompárt lekérdezni: elég egy összefüggő láncot a két végén bővíteni, és minden lépésben egy olyan új atomot keresni, amely szomszédos a lánc aktuális végével. ||
Hint 2: || Két atom szomszédságát egyetlen hívással el lehet dönteni: Kozte(x, y) pontosan akkor adja x-et vagy y-t, ha x és y szomszédos. Nem szomszédos párnál a visszakapott atom a két végpont valamelyikének szomszédja, és nem tudhatod előre, melyiké. ||
Hint 3: || Tárold a még nem elhelyezett atomokat veremben, és ha a verem tetejéről kapott válasz már a láncban lévő atom, fordítsd meg a bővítés irányát; így minden atomra átlagosan legfeljebb két hívás jut. ||
*/
#include "muszer.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = Atomszam();
    deque<int> lanc;               // a már elhelyezett, összefüggő szakasz
    vector<char> bent(n + 1, 0);   // bent[a] = 1, ha a már a láncban van
    vector<int> verem;             // még nem elhelyezett atomok; a teteje a lánc végéhez legközelebbi
    bool jobb = true;              // true: a jobb végről bővítünk, false: a bal végről
    lanc.push_back(1);
    bent[1] = 1;
    int keres = 2;                 // a következő, még nem elhelyezett atom keresése
    while ((int)lanc.size() < n) {
        if (verem.empty()) {
            while (bent[keres]) keres++;
            verem.push_back(keres);
            jobb = true;
        }
        int t = verem.back();
        if (jobb) {
            int r = lanc.back();
            int z = Kozte(r, t);
            if (z == r || z == t) {          // t szomszédos a lánc jobb végével
                lanc.push_back(t);
                bent[t] = 1;
                verem.pop_back();
            } else if (bent[z]) {            // a láncbeli atom a válasz: t a bal oldalon van
                jobb = false;
            } else {
                verem.push_back(z);
            }
        } else {
            int l = lanc.front();
            int z = Kozte(l, t);
            if (z == l || z == t) {          // t szomszédos a lánc bal végével
                lanc.push_front(t);
                bent[t] = 1;
                verem.pop_back();
            } else if (bent[z]) {            // a láncbeli atom a válasz: t a jobb oldalon van
                jobb = true;
            } else {
                verem.push_back(z);
            }
        }
    }
    for (int i = 1; i <= n; i++) Sorrend(i, lanc[i - 1]);
    return 0;
}
