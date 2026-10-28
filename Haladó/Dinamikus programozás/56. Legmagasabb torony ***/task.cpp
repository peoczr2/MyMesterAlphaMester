/*
Legmagasabb torony
Feladat: N kockából (oldalhossz, súly) kell a legmagasabb stabil tornyot építeni: kisebb kockára nem
tehetünk nagyobbat, könnyebbre nem tehetünk nehezebbet (egyenlő megengedett). A torony magassága a
kockák oldalhosszainak összege. Ki kell írni a torony kockáinak M számát, majd a sorszámaikat alulról
felfelé.
Ötlet: rendezzük a kockákat (oldal, súly) szerint növekvően. Egy toronyban felfelé haladva mindkét adat
csak csökkenhet vagy maradhat, ezért egy kocka fölé csak a rendezésben előtte álló kocka kerülhet: ez
egy súlyozott leghosszabb növekvő részsorozat. dp[i] = a legmagasabb torony, amelynek az i. (rendezett)
kocka a legalja: dp[i] = oldal[i] + max dp[j] azokra a j < i-kre, ahol oldal[j] <= oldal[i] és
súly[j] <= súly[i]. A felette[i] mutatón alulról felfelé haladva kapjuk a tornyot.
Kimenet: a feladatszöveg és mindkét ki fájl első sora a legmagasabb torony KOCKÁINAK SZÁMA (ki1: 6,
ki2: 42), a feladatszöveg saját példája viszont a magasságot mutatja (40 a 3 helyett). A megoldás a
szöveget és a ki fájlokat követi. Több legmagasabb torony is lehet (akár eltérő kockaszámmal), ezért
ellenőrző program kell.
Idő: O(N^2), memória: O(N).
*/
/*
Hint 1: || A bemenet sorrendje lényegtelen. Rendezd a kockákat oldalhossz, majd súly szerint: így egy kocka fölé csak előtte álló kocka kerülhet. ||
Hint 2: || Ez egy leghosszabb növekvő részsorozat, csak most nem a kockák számát, hanem az oldalhosszak összegét maximalizáljuk. ||
Hint 3: || dp[i] = oldal[i] + max dp[j] (j < i, oldal[j] <= oldal[i] és súly[j] <= súly[i]). Tárold, melyik kocka került rá, és rendezéskor vidd magaddal az eredeti sorszámot. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // beolvasás: kocka[i] = {oldalhossz, súly, eredeti sorszám}
    int n;
    cin >> n;
    vector<vector<int>> kocka(n, vector<int>(3));
    for (int i = 0; i < n; i++) {
        cin >> kocka[i][0] >> kocka[i][1];
        kocka[i][2] = i + 1;
    }
    sort(kocka.begin(), kocka.end());   // oldal szerint, azon belül súly szerint növekvő

    // dp[i] = a legmagasabb torony, amelynek az i. kocka az alja; felette[i] = a rá tett kocka
    vector<int> dp(n), felette(n, -1);   // magasság legfeljebb 1000 · 2000, belefér az int-be
    for (int i = 0; i < n; i++) {
        dp[i] = kocka[i][0];             // egyedül az i. kocka
        for (int j = 0; j < i; j++) {
            if (kocka[j][0] <= kocka[i][0] && kocka[j][1] <= kocka[i][1]
                && dp[j] + kocka[i][0] > dp[i]) {
                dp[i] = dp[j] + kocka[i][0];
                felette[i] = j;
            }
        }
    }

    // a legmagasabb torony alja
    int alul = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] > dp[alul]) alul = i;
    }

    // visszafejtés alulról felfelé, kiírás: kockaszám, majd a sorszámok
    vector<int> torony;
    for (int i = alul; i != -1; i = felette[i]) torony.push_back(kocka[i][2]);
    cout << torony.size() << '\n';
    for (int k = 0; k < (int)torony.size(); k++) {
        if (k > 0) cout << ' ';
        cout << torony[k];
    }
    cout << '\n';
    return 0;
}
