/*
Megoldás lényege:
Az 1-es csúcs a fa gyökere, és Szomszed(x) megadja x szülőjét, így N-1 hívással felépíthető a teljes fa; ezek a hívások nem növelik a kérdések számát.
A kérdéseket mindig a jelenlegi részfa súlypontjára (centroid-csúcsára) tesszük fel: ennek minden része legfeljebb a fele a jelenlegi résznek.
Ha Ittvan(c) = 0, a kincs c-ben van. Különben a válasz a kincs felé vezető szomszéd: c-t kivéve megtartjuk azt az összefüggő részt, amelyben ez a szomszéd van, így a lehetséges helyek száma minden kérdéssel legalább felére csökken.
Ezért legfeljebb floor(log2 N) kérdés kell; amikor egyetlen hely marad, azt közöljük a Kincshely eljárással.
Az időigény O(N log N).
*/
/*
Hint 1: || Ha minden kérdésnél a fa súlypontját kérdezed, a maradék lehetséges helyek száma minden lépésben legalább felére csökken. ||
Hint 2: || A Szomszed(x) eredménye x szülője az 1-es csúcs felé: ebből a teljes fa éleit megkapod, és ezek a hívások nem számítanak bele a kérdésekbe. ||
Hint 3: || Ittvan(c) válaszából induló komponensen folytasd a keresést úgy, hogy közben a c csúcsot kivéve a fából; ha egyetlen hely marad, az a kincs helye. ||
*/
#include "kincs.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = Helyekszama();

    // A fa élei: Szomszed(x) az x szülője az 1-es csúcs felé
    vector<vector<int>> szomsz(n + 1);
    for (int x = 2; x <= n; x++) {
        int p = Szomszed(x);
        szomsz[x].push_back(p);
        szomsz[p].push_back(x);
    }

    vector<char> aktiv(n + 1, 1);  // a kincs lehetséges helyei (összefüggő részfa)
    aktiv[0] = 0;
    int darab = n;
    vector<int> sor(n + 1), szulo(n + 1, 0), meret(n + 1, 0);

    while (true) {
        if (darab == 1) {
            for (int v = 1; v <= n; v++) {
                if (aktiv[v]) {
                    Kincshely(v);
                }
            }
            return 0;
        }

        // BFS a jelenlegi részfában: sor-ban a bejárási sorrend, szulo-ban a BFS-szülő
        int r = 1;
        while (!aktiv[r]) {
            r++;
        }
        int db = 0;
        sor[db++] = r;
        szulo[r] = 0;
        for (int k = 0; k < db; k++) {
            int u = sor[k];
            for (int v : szomsz[u]) {
                if (aktiv[v] && v != szulo[u]) {
                    szulo[v] = u;
                    sor[db++] = v;
                }
            }
        }

        // részfa-méretek: a bejárási sorrend visszafelé
        for (int k = 0; k < db; k++) {
            meret[sor[k]] = 1;
        }
        for (int k = db - 1; k > 0; k--) {
            meret[szulo[sor[k]]] += meret[sor[k]];
        }

        // súlypont: olyan csúcs, amelynek minden része legfeljebb db/2
        int c = r;
        for (int k = 0; k < db; k++) {
            int u = sor[k];
            int legnagyobb = db - meret[u];
            for (int v : szomsz[u]) {
                if (aktiv[v] && v != szulo[u]) {
                    legnagyobb = max(legnagyobb, meret[v]);
                }
            }
            if (2 * legnagyobb <= db) {
                c = u;
                break;
            }
        }

        int y = Ittvan(c);
        if (y == 0) {
            Kincshely(c);
            return 0;
        }

        // c kiesik; a kincs az y oldali komponensben van, ezt tartjuk meg
        aktiv[c] = 0;
        vector<char> uj(n + 1, 0);
        vector<int> q = {y};
        uj[y] = 1;
        for (size_t k = 0; k < q.size(); k++) {
            int u = q[k];
            for (int v : szomsz[u]) {
                if (aktiv[v] && !uj[v]) {
                    uj[v] = 1;
                    q.push_back(v);
                }
            }
        }
        aktiv = uj;
        darab = (int)q.size();
    }
}
