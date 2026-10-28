/*
Megoldás lényege:
Csak az számít, hogy egy futam 1 hosszú (B) vagy legalább 2 hosszú (G): belső G törlésekor a két szomszéd mindig G-vé olvad össze. Minden futam végül egy olyan futamba olvad, amelyet a sorozat szélén törlünk; ezek a csoportok egybefüggő, páratlan hosszú szakaszok, és mindegyiknek egyedül, belső törlésekkel egyetlen G-vé kell összehúzódnia. Három szomszédos ilyen szakasz együtt is összehúzható, ezért páratlan M futamnál az egész sorozatnak kell összehúzhatónak lennie, páros M-nél pedig két páratlan hosszú részre kell bontani. Egy 2k+1 hosszú szakasz akkor húzható össze, ha a közepe G (mindig a középsőt töröljük), vagy ha a középtől balra és jobbra eső legközelebbi G távolsága a és c, és a+c <= k. Ilyenkor a bal G-t c-szer törölve a jobb G középre kerül. Ha a+c > k, akkor az a+c-k érték egyik lépéstől sem csökken, így G sosem kerülhet középre. A legközelebbi G-k indexét előre kiszámoljuk, így egy szakasz O(1) idő alatt ellenőrizhető. Páros M esetén minden vágási pontot kipróbálunk, így az időigény O(N).
*/
/*
Hint 1: || Csak a futamok számítanak, és az, hogy 1 hosszúak (B) vagy hosszabbak (G). Ha egy páratlan sok futamból álló szakasz közepe G, akkor mindig a középsőt törölve az egész elfogy. ||
Hint 2: || Ha a közép B, nézd a középhez legközelebbi G-t balra (a távolság) és jobbra (c távolság). A bal G ismételt törlésével a jobb G minden lépésben egyet közeledik a középhez; ez akkor sikerül, ha a+c <= k, ahol a szakasz hossza 2k+1. ||
Hint 3: || Páros sok futamnál a sorozatot két páratlan hosszú részre kell vágni, és mindkét résznek külön teljesítenie kell a fenti feltételt. A legközelebbi G-k indexét előre kiszámolva minden vágás O(1) idő alatt ellenőrizhető. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 0; tc < T; tc++) {
        string s;
        cin >> s;
        // futamok: 1 = G (hossz >= 2), 0 = B (hossz 1)
        vector<int> isG;
        for (size_t i = 0; i < s.size();) {
            size_t j = i;
            while (j < s.size() && s[j] == s[i]) j++;
            isG.push_back(j - i >= 2 ? 1 : 0);
            i = j;
        }
        int m = isG.size();
        // prevG[i]: a legkozelebbi G indexe i-tol balra (i-t is beleertve), nextG[i]: i-tol jobbra
        // ha nincs ilyen, olyan tavoli erteket kap, hogy a feltetel biztosan ne teljesuljon
        vector<int> prevG(m), nextG(m);
        for (int i = 0; i < m; i++)
            prevG[i] = isG[i] ? i : (i > 0 ? prevG[i - 1] : -m);
        for (int i = m - 1; i >= 0; i--)
            nextG[i] = isG[i] ? i : (i + 1 < m ? nextG[i + 1] : 2 * m);
        // a paratlan hosszu [l, r] szakasz osszehuzhato-e egyetlen G-ve
        auto ok = [&](int l, int r) {
            int k = (r - l) / 2, c = l + k;
            if (isG[c]) return true;
            // a = c - prevG[c], cc = nextG[c] - c, feltetel: a + cc <= k
            return nextG[c] - prevG[c] <= k;
        };
        bool ans = false;
        if (m % 2 == 1) {
            ans = ok(0, m - 1);
        } else {
            // elso resz [0, i], masodik resz [i + 1, m - 1], mindketto paratlan hosszu
            for (int i = 0; i + 1 < m && !ans; i += 2)
                if (ok(0, i) && ok(i + 1, m - 1)) ans = true;
        }
        cout << (ans ? "IGEN" : "NEM") << "\n";
    }
    return 0;
}
