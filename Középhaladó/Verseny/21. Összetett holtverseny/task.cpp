/*
Megoldás lényege:
Csak azok értékelhetők az összetett versenyben, akik minden versenyen indultak és elérték az adott verseny minimumát; ezek összpontszámát számoljuk ki. Egy összpontszám helyezése 1 plusz a nála nagyobb összpontszámú értékelhető tanulók száma, így azonos pontszámnál a helyezés közös. Pontszámonként megszámoljuk az értékelhető tanulókat (az összpontszám legfeljebb 10000), majd csökkenő pontszám szerint bejárva minden olyan helyezést kiírunk, amelyhez legalább két tanuló tartozik. Az időigény O(N·M + 10000), ami gyors.
*/
/*
Hint 1: || Először állapítsd meg, kik értékelhetők: minden versenyen szerepeljenek, és a pontszámuk a verseny minimumát érje el. Csak ezeknek számold ki az összpontszámát. ||
Hint 2: || Pontszámonként számold meg az értékelhető tanulókat. Csökkenő pontszám szerint haladva a helyezés mindig 1 plusz az eddig megszámolt, nála jobb tanulók száma; ha az aktuális pontszámhoz legalább 2 tanuló tartozik, ez a helyezés holtverseny. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> minimum(m);
    for (int i = 0; i < m; i++) {
        cin >> minimum[i];
    }

    vector<int> jo(n + 1, 0), ossz(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int ind;
        cin >> ind;
        for (int j = 0; j < ind; j++) {
            int s, p;
            cin >> s >> p;
            ossz[s] += p;
            if (p >= minimum[i]) {
                jo[s]++;
            }
        }
    }

    const int MAXOSSZ = 100 * 100;
    vector<int> db(MAXOSSZ + 1, 0);
    for (int x = 1; x <= n; x++) {
        if (jo[x] == m) {
            db[ossz[x]]++;
        }
    }

    vector<int> helyek;
    int felette = 0;
    for (int v = MAXOSSZ; v >= 0; v--) {
        if (db[v] >= 2) {
            helyek.push_back(felette + 1);
        }
        felette += db[v];
    }

    cout << helyek.size();
    for (int h : helyek) {
        cout << ' ' << h;
    }
    cout << '\n';
    return 0;
}
