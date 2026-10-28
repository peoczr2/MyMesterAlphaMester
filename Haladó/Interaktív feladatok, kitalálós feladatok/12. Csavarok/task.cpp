/*
Megoldás lényege:
Kis csoportnál (legfeljebb 8 csavar) a csavaronként a még szabad anyákon végighaladunk, és az első egyenlőnél párosítunk. Nagyobb csoportnál véletlen csavart (fix magú generátorral, így a futás determinisztikus) választunk, és minden szabad anyával összehasonlítjuk: a 0 eredmény adja a párját, az 1 és -1 eredmények a többi anyát a csavarnál kisebb, illetve nagyobb csoportba sorolják. A párjával a többi csavart is szétválogatjuk ugyanígy (kisebb és nagyobb csoport), majd mindkét csoportot rekurzívan oldjuk meg. A proba hívások átlagos száma nagy n-re kb. 2n*ln(n), kis n-re viszont a n*n/4 korlát fölött lehet, ezért a pontozási feltétel nem minden n-re teljesül. Az eredményt az eredmeny művelet adja, a be- és kimenetet a csavarok könyvtár végzi.
*/
/*
Hint 1: || Válassz ki egy csavart, és próbáld fel az összes még párosítatlan anyára: a 0 eredmény mutatja a hozzá tartozó anyát. ||
Hint 2: || Az 1 és -1 eredmények szétválasztják az anyákat: a csavarnál kisebb belső átmérőjűek külön csoportba tartoznak, mint a nagyobbak. ||
Hint 3: || A megtalált anyával a többi csavart is kettéválogathatod (kisebb és nagyobb csoport), majd a két csoportot ugyanígy, rekurzívan oldd meg. ||
*/
#include <bits/stdc++.h>
#include "csavarok.h"
using namespace std;

static mt19937 rng(20240601);
static vector<int> matchOf;               // matchOf[csavar] = anya sorszáma

void solve(const vector<int>& bolts, const vector<int>& nuts) {
    if (bolts.empty()) return;
    if (bolts.size() == 1) {              // egy csavar maradt: az egy anya lesz a párja
        matchOf[bolts[0]] = nuts[0];
        return;
    }
    if (bolts.size() <= 8) {              // kis csoport: csavaronként keresünk párt
        vector<int> freeNuts = nuts;
        for (size_t i = 0; i < bolts.size(); i++) {
            int b = bolts[i];
            if (freeNuts.size() == 1) {   // az utolsó anya biztosan ehhez tartozik
                matchOf[b] = freeNuts[0];
                break;
            }
            size_t m = freeNuts.size();
            for (size_t j = 0; j < m; j++) {
                if (j == m - 1 || proba(b, freeNuts[j]) == 0) {   // ha minden más anya kizárt, ez a párja
                    matchOf[b] = freeNuts[j];
                    freeNuts.erase(freeNuts.begin() + j);
                    break;
                }
            }
        }
        return;
    }

    int pi = (int)(rng() % bolts.size());
    int pb = bolts[pi];                   // véletlen csavar

    vector<int> nutSmall, nutBig;         // anyák: a pb csavarnál kisebb / nagyobb belső átmérővel
    int pn = -1;                          // a pb csavarhoz tartozó anya
    for (int nt : nuts) {
        int r = proba(pb, nt);            // -1: a csavar kisebb, +1: a csavar nagyobb, 0: egyforma
        if (r == 0) pn = nt;
        else if (r == 1) nutSmall.push_back(nt);
        else nutBig.push_back(nt);
    }
    matchOf[pb] = pn;

    vector<int> boltSmall, boltBig;       // a többi csavar a pn anyához képest
    for (int b : bolts) {
        if (b == pb) continue;
        if (boltSmall.size() == nutSmall.size()) { boltBig.push_back(b); continue; }
        int r = proba(b, pn);
        if (r == -1) boltSmall.push_back(b);
        else boltBig.push_back(b);
    }
    solve(boltSmall, nutSmall);
    solve(boltBig, nutBig);
}

int main() {
    int n = kezdet();
    vector<int> bolts(n), nuts(n);
    iota(bolts.begin(), bolts.end(), 1);
    iota(nuts.begin(), nuts.end(), 1);
    matchOf.assign(n + 1, 0);
    solve(bolts, nuts);
    vector<int> cs(n);
    for (int i = 0; i < n; i++)
        cs[i] = matchOf[i + 1];
    eredmeny(cs.data());
    return 0;
}
