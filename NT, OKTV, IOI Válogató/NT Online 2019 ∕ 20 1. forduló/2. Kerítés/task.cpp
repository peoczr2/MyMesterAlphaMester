/*
Megoldás lényege:
Minden léc állapota elég jól leírható az utolsó festés(ek) alapján. Ha az utolsó
két festés azonos színű, akkor a léc piros vagy zöld; ha különböző, akkor barna.
A barna állapotnál is számít, hogy az utolsó festés piros vagy zöld volt, mert
ugyanazzal a színnel még egyszer átfestve újra tiszta piros vagy zöld lesz.

Ezért minden lécet 5 állapot valamelyikében tartunk nyilván:
- fehér,
- tiszta piros,
- tiszta zöld,
- barna, utolsó festés piros,
- barna, utolsó festés zöld.
Minden festési műveletet végigiterálunk az érintett szakaszon, és alkalmazzuk az
állapotátmenetet. N legfeljebb 1000, M legfeljebb 100, ezért ez bőven elég.
Az időigény O(N · M), ami legfeljebb 10^5 lépés.
*/
/*
Hint 1: || Nem kell a festések teljes történetét tárolni: elég minden léchez egy állapotot nyilvántartani, és minden festésnél ezt az állapotot frissíteni. ||
Hint 2: || Öt állapot kell: fehér, tiszta piros, tiszta zöld, valamint a barna két fajtája aszerint, hogy az utolsó festés piros vagy zöld volt. Ha az utolsó két festés azonos színű, a léc tiszta színű lesz. ||
Hint 3: || P festésnél a fehér, a piros és a barna (utolsó festés piros) lécek pirosak lesznek, a zöld és a barna (utolsó festés zöld) lécek barna (utolsó festés piros) állapotba kerülnek. Z festésnél a szerep szimmetrikusan cserélődik. ||
*/
#include <bits/stdc++.h>
using namespace std;

enum Allapot {
    FEHER,
    PIROS,
    ZOLD,
    BARNA_PIROS,
    BARNA_ZOLD
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> allapot(n + 1, FEHER);

    for (int muvelet = 0; muvelet < m; ++muvelet) {
        char szin;
        int l, r;
        cin >> szin >> l >> r;
        for (int i = l; i <= r; ++i) {
            if (szin == 'P') {
                if (allapot[i] == FEHER || allapot[i] == PIROS) allapot[i] = PIROS;
                else if (allapot[i] == ZOLD) allapot[i] = BARNA_PIROS;
                else if (allapot[i] == BARNA_PIROS) allapot[i] = PIROS;
                else allapot[i] = BARNA_PIROS;
            } else {
                if (allapot[i] == FEHER || allapot[i] == ZOLD) allapot[i] = ZOLD;
                else if (allapot[i] == PIROS) allapot[i] = BARNA_ZOLD;
                else if (allapot[i] == BARNA_ZOLD) allapot[i] = ZOLD;
                else allapot[i] = BARNA_ZOLD;
            }
        }
    }

    int piros = 0, zold = 0;
    for (int i = 1; i <= n; ++i) {
        if (allapot[i] == PIROS) ++piros;
        else if (allapot[i] == ZOLD) ++zold;
    }

    cout << piros << ' ' << zold << '\n';
    return 0;
}
