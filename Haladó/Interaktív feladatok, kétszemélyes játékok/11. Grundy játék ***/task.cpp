/*
Megoldás lényege:
Grundy-játék: egy kupacot két, nem azonos méretű kupacra kell bontani, az nyer, aki utoljára tud lépni.
Sprague–Grundy-tétel szerint minden m elemű kupachoz Grundy-érték tartozik: g(m) a { g(k) xor g(m-k) : 1 <= k < m/2 }
halmaz legkisebb ki nem fordult nemnegatív egésze (mex). Az egész játék értéke a kupacok értékeinek xora.
A kezdő akkor nyer, ha ez az xor nem nulla: ekkor van olyan kupac és felosztás, amellyel az xor nullára csökken.
Ezt minden lépésünkben keressük meg: a 3-nál nagyobb kupacokra a táblázatból kikeressük a megfelelő k felosztást.
Az előkészítés O(N^2), egy lépés a kupacok számával arányos. A Kezd(n) készíti elő a táblázatot, az EnLepesem(m,k)
adja a saját lépésünket (kupac mérete és a felosztás k), a TeLepesed(m,k) az ellenfél lépését kapja; mindkettő
frissíti a kupacok állapotát.
*/
/*
Hint 1: || A kupacok függetlenek egymástól: minden kupachoz kiszámolható egy nyerő szám (Grundy-érték), és ezeket xor-ral össze lehet adni. ||
Hint 2: || Egy m elemű kupac értéke a lehetséges felosztások értékeinek xor-ja szerint legkisebb ki nem fordult szám (mex). Ezt az N-ig terjedő értékekre dinamikus programozással számold ki. ||
Hint 3: || Ha az összes kupac értékének xora nem nulla, keress olyan kupacot és felosztást, amelytől az xor nulla lesz; a táblázatban előre eltárolhatod, melyik k adja a kívánt értéket. ||
*/
#include "grundy.h"
#include <bits/stdc++.h>
using namespace std;

int N;                          // a kezdeti kupac mérete
vector<int> g;                  // g[h]: h elemű kupac Grundy-értéke (a 127 alatti értékek miatt az xor 256-nál kisebb)
vector<vector<int>> opt;        // opt[h][v]: olyan k (1 <= k < h-k), amelyre g[k] xor g[h-k] = v (v < g[h] esetén); 0, ha nincs
vector<int> cnt;                // cnt[h]: hány h elemű kupac van (csak a 3-nál nagyobbak számítanak)
int T = 0, nagy = 0;            // T: a kupacok értékeinek xora, nagy: a 3-nál nagyobb kupacok száma

static void hozzaad(int h) {
    if (h >= 3) { cnt[h]++; T ^= g[h]; nagy++; }
}

static void elvesz(int h) {
    if (h >= 3) { cnt[h]--; T ^= g[h]; nagy--; }
}

void Kezd(int n) {
    N = n;
    g.assign(N + 1, 0);
    opt.assign(N + 1, vector<int>());
    for (int h = 1; h <= N; h++) {
        vector<char> van(256, 0);
        for (int k = 1; 2 * k < h; k++) {
            van[g[k] ^ g[h - k]] = 1;
        }
        int m = 0;
        while (van[m]) m++;
        g[h] = m;
        opt[h].assign(m, 0);
        for (int k = 1; 2 * k < h; k++) {
            int v = g[k] ^ g[h - k];
            if (v < m && opt[h][v] == 0) opt[h][v] = k;
        }
    }
    cnt.assign(N + 1, 0);
    T = 0;
    nagy = 0;
    hozzaad(N);
}

void EnLepesem(int &m, int &k) {
    // a mi lépésünk: olyan kupac és felosztás, amely az xort nullázza
    int ph = -1, pk = -1;
    for (int h = 3; h <= N && ph < 0; h++) {
        if (cnt[h] == 0) continue;
        int v = T ^ g[h];
        if (v < g[h] && opt[h][v] != 0) {
            ph = h;
            pk = opt[h][v];
        }
    }
    if (ph < 0) {                    // a kezdőállás vesztes: bármely legális lépés
        for (int h = 3; h <= N; h++) {
            if (cnt[h] > 0) { ph = h; pk = 1; break; }
        }
    }
    m = ph;
    k = pk;
    elvesz(ph);
    hozzaad(pk);
    hozzaad(ph - pk);
}

void TeLepesed(int m, int k) {
    // az ellenfél lépése: a m elemű kupacot k és m-k elemű kupacra bontotta
    elvesz(m);
    hozzaad(k);
    hozzaad(m - k);
}
