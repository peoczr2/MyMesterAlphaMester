/*
Megoldás lényege:
Minden szomszédos (i, i+1) párra kérdezünk, így a tanulók összefüggő szakaszokra (blokkokra) bomlanak:
egy szakaszon belül minden szomszédpár azonos csoportba tartozik, a szakaszok határán viszont a válasz 0,
tehát a két szomszédos szakasz biztosan különböző csoportba tartozik. Az első két szakasz így két különböző
csoportot (A és B) képvisel. A további szakaszoknak az előző szakasz csoportjától különböző két csoport
egyike lehet, ezért elég az első tagjukat a másik ismert csoport egy tagjával összehasonlítani:
ha 1 a válasz, a szakasz ahhoz a csoporthoz tartozik, ha 0, akkor ez a harmadik csoport, és megvan a három tanuló.
A kérdések száma legfeljebb (N-1) + (N-2) = 2N-3. Minden tanulónak 2 szomszédi kérdése van, a horgonyként
használt tanulók szabad kapacitása pedig a csoportokon belül mindig elegendő, így a 4-es korlát nem sérül.
Időigény: O(N).
*/
/*
Hint 1: || Az összes szomszédos pár lekérdezése után a tanulók összefüggő szakaszokra esnek szét. Ahol a válasz 0, ott két szakasz biztosan különböző csoportba tartozik. ||
Hint 2: || Az első két szakasz csoportja már ismert (A és B). Egy újabb szakasz csak a harmadik csoport lehet, ha nem az előző szakasz csoportja és nem a másik ismert csoport: elég egyetlen kérdés, az ismert másik csoport egy tagjával. ||
Hint 3: || Minden tanuló legfeljebb 4 kérdésben szerepelhet, a szomszédos párok már 2-t felhasználnak. A horgonynak használt csoporttagokat úgy válaszd, hogy még legyen rajtuk szabad kérdés, és a csoportok összesített szabad kapacitását ne csökkentsd a szükségesnél többet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int TanulokSzama();
int Barat(int x, int y);
void Megoldas(int a, int b, int c);

int main() {
    int n = TanulokSzama();

    // Szabad kérdések tanulónként: 4 mínusz a szomszédpárok száma (1 vagy 2).
    vector<int> cap(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int neighbours = (i > 1) + (i < n);
        cap[i] = 4 - neighbours;
    }

    // Szomszédos párok: a 0-s válasz új szakaszt kezd.
    vector<pair<int, int>> blocks;  // [kezdet, vég]
    int start = 1;
    for (int i = 1; i < n; ++i) {
        if (Barat(i, i + 1) == 0) {
            blocks.push_back({start, i});
            start = i + 1;
        }
    }
    blocks.push_back({start, n});

    // Csoportok: 0 = A, 1 = B; a harmadik csoportot keressük.
    // pool[g] a már besorolt, g csoportba tartozó tanulók listája (horgonyok).
    vector<int> pool[2];
    int ptr[2] = {0, 0};
    auto addBlock = [&](int g, int j) {
        for (int i = blocks[j].first; i <= blocks[j].second; ++i) pool[g].push_back(i);
    };

    addBlock(0, 0);
    addBlock(1, 1);
    int a = blocks[0].first;
    int b = blocks[1].first;
    int prev = 1;

    for (int j = 2; j < (int)blocks.size(); ++j) {
        int other = (prev == 0) ? 1 : 0;  // az előző szakasztól és a harmadiktól különböző ismert csoport
        int r = blocks[j].first;

        while (cap[pool[other][ptr[other]]] == 0) ++ptr[other];
        int anchor = pool[other][ptr[other]];

        cap[anchor]--;
        cap[r]--;
        int same = Barat(r, anchor);
        if (same == 0) {
            Megoldas(a, b, r);
            return 0;
        }
        addBlock(other, j);
        prev = other;
    }

    return 0;
}
