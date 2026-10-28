/*
Megoldás lényege:
A négy oldalt külön kezeljük. Egy oldal egységnyi darabját akkor fedi szoba falszakasza, ha a szobának ugyanazon a széli vonalon van oldala (például a bal oldalon BFX = FX), és a szoba tartománya tartalmazza az adott sort vagy oszlopot. Minden ilyen szobánál egy különbségtömbbe +1-et írunk a tartomány első eleméhez, és −1-et a tartomány utolsó utáni eleméhez, így a prefixösszegből minden egységnyi darab lefedettsége egy lépésben kiolvasható.
Ezután az oldal lefedetlen egységeinek összefüggő futamait számoljuk: új maximális szakasz ott kezdődik, ahol lefedetlen egység áll, és az előtte lévő egység lefedett vagy az oldal eleje. Az időigény O(N + W + H), ahol W és H az épület szélessége és magassága, ez bőven belefér a 0,1 másodpercbe.
*/
/*
Hint 1: || Minden oldalt külön vizsgálj. Egy oldal egy egységnyi darabját akkor fedi szoba, ha a szobának ugyanazon a széli vonalon van oldala (pl. a bal oldalon BFX = FX), és a szoba tartománya lefedi az adott sort vagy oszlopot. ||
Hint 2: || Különbségtömbbel gyorsan kezelhető a lefedettség: a szoba tartományának első eleméhez írj +1-et, az utolsó utáni eleméhez −1-et, majd a prefixösszeg megmutatja, mely egységek vannak lefedve. ||
Hint 3: || A lefedetlen egységek futamait kell megszámolni: egy új maximális szakasz ott kezdődik, ahol egy lefedett egység után lefedetlen egység következik, vagy ahol az oldal első egysége lefedetlen. ||
*/
#include <bits/stdc++.h>
using namespace std;

int szakaszokSzama(const vector<int>& d, int len) {
    int lefedes = 0, db = 0;
    bool elozoLefedetlen = false;
    for (int i = 0; i < len; i++) {
        lefedes += d[i];
        bool lefedetlen = (lefedes == 0);
        if (lefedetlen && !elozoLefedetlen) db++;
        elozoLefedetlen = lefedetlen;
    }
    return db;
}

int main() {
    int n, fx, fy, ax, ay;
    cin >> n >> fx >> fy >> ax >> ay;
    int szeles = ax - fx + 1;
    int magas = ay - fy + 1;
    vector<int> bal(magas + 1, 0), jobb(magas + 1, 0), also(szeles + 1, 0), felso(szeles + 1, 0);
    for (int i = 0; i < n; i++) {
        int bfx, bfy, jax, jay;
        cin >> bfx >> bfy >> jax >> jay;
        if (bfx == fx) { bal[bfy - fy]++; bal[jay - fy + 1]--; }
        if (jax == ax) { jobb[bfy - fy]++; jobb[jay - fy + 1]--; }
        if (bfy == fy) { felso[bfx - fx]++; felso[jax - fx + 1]--; }
        if (jay == ay) { also[bfx - fx]++; also[jax - fx + 1]--; }
    }
    cout << szakaszokSzama(bal, magas) << " "
         << szakaszokSzama(also, szeles) << " "
         << szakaszokSzama(jobb, magas) << " "
         << szakaszokSzama(felso, szeles) << "\n";
    return 0;
}
