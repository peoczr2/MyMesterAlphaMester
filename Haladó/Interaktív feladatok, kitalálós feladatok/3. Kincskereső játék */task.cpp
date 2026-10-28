/*
Megoldás lényege:
A Szomszed művelettel (nem korlátos) az egész fa ismert, ha az 1-es helyet gyökérnek tekintjük.
Minden lépésben a jelenlegi kereső halmaz (összefüggő részfa) centroidjára kérdezünk rá az Ittvan
művelettel. Ha a kincs ott van, készen vagyunk. Különben a válasz megmutatja, melyik szomszéd
irányában van a kincs, így a halmazt a centroid nélküli, ehhez a szomszédhoz tartozó részfára
szűkítjük. Mivel a centroid minden részfája legfeljebb a fele a halmaznak, log2 N kérdés elég.
Ha egyetlen hely maradt, a kincs ott van, ezért arra már nem kérdezünk.
*/
/*
Hint 1: || A Szomszed művelettel a fa szerkezete ingyen megismerhető: Szomszed(x) az x-hez tartozó szülő az 1-es gyökérhez képest, ezért a fa összes élét kikérdezheted. ||
Hint 2: || Keresd a halmaz centroidját: olyan helyet, amelynek minden részfája legfeljebb a halmaz fele. Az Ittvan válasza ennek a helynek a szomszédját adja meg, ahol a kincs van. ||
Hint 3: || Ha az Ittvan a centroidra 0-t ad, a kincs ott van. Egyébként a halmazt szűkítsd a válasz szomszédját tartalmazó komponensre. ||
*/
#include "kincs.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = Helyekszama();

    vector<vector<int>> g(n + 1);
    for (int x = 2; x <= n; x++) {
        int p = Szomszed(x);
        g[x].push_back(p);
        g[p].push_back(x);
    }

    vector<char> inS(n + 1, 1);
    int halmaz = n;
    while (true) {
        if (halmaz == 1) {
            for (int v = 1; v <= n; v++) if (inS[v]) { Kincshely(v); return 0; }
        }

        // Keresünk egy kezdőpontot a halmazban, majd a méreteket egy bejárással számoljuk.
        int s0 = 0;
        for (int v = 1; v <= n && !s0; v++) if (inS[v]) s0 = v;
        vector<int> sorrend, szulo(n + 1, 0), meret(n + 1, 0);
        vector<int> verem{s0};
        szulo[s0] = -1;
        vector<char> vis(n + 1, 0);
        vis[s0] = 1;
        while (!verem.empty()) {
            int u = verem.back(); verem.pop_back();
            sorrend.push_back(u);
            for (int w : g[u]) {
                if (inS[w] && !vis[w]) { vis[w] = 1; szulo[w] = u; verem.push_back(w); }
            }
        }
        for (int i = (int)sorrend.size() - 1; i >= 0; i--) {
            int u = sorrend[i];
            meret[u] += 1;
            if (szulo[u] > 0) meret[szulo[u]] += meret[u];
        }

        // Centroid: olyan csúcs, amelynek minden komponense legfeljebb a fele a halmaznak.
        int cent = s0;
        for (int u : sorrend) {
            int legnagyobb = halmaz - meret[u];
            for (int w : g[u]) {
                if (inS[w] && szulo[w] == u) legnagyobb = max(legnagyobb, meret[w]);
            }
            if (2 * legnagyobb <= halmaz) { cent = u; break; }
        }

        int r = Ittvan(cent);
        if (r == 0) { Kincshely(cent); return 0; }

        // A kincs a r komponensében van: a cent nélküli, r-et tartalmazó részt tartjuk meg.
        vector<char> uj(n + 1, 0);
        vector<int> q{r};
        uj[r] = 1;
        for (size_t h = 0; h < q.size(); h++) {
            int u = q[h];
            for (int w : g[u]) {
                if (w != cent && inS[w] && !uj[w]) { uj[w] = 1; q.push_back(w); }
            }
        }
        inS = uj;
        halmaz = (int)q.size();
    }
    return 0;
}
