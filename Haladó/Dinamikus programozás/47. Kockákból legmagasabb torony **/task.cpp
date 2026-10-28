/*
Kockákból legmagasabb torony
Feladat: N kockából (oldalhossz, súly) kell a legmagasabb stabil tornyot építeni: kisebb kockára nem
tehetünk nagyobbat, könnyebbre nem tehetünk nehezebbet (egyenlő megengedett). A torony magassága a
kockák oldalhosszainak összege. Ki kell írni a torony kockáinak M számát, majd a kockákat (oldalhossz,
súly) alulról felfelé.
Ötlet: rendezzük a kockákat (oldal, súly) szerint növekvően. Egy toronyban felfelé haladva mindkét adat
csak csökkenhet vagy maradhat, ezért egy kocka fölé csak a rendezésben előtte álló kocka kerülhet: ez
egy súlyozott leghosszabb növekvő részsorozat. dp[i] = a legmagasabb torony, amelynek az i. (rendezett)
kocka a legalja: dp[i] = oldal[i] + max dp[j] azokra a j < i-kre, ahol oldal[j] <= oldal[i] és
súly[j] <= súly[i]. A felette[i] mutatón alulról felfelé haladva kapjuk a tornyot.
A célfüggvény a torony magassága (oldalhosszak összege), a kiírt M pedig a felhasznált kockák száma.
Több legmagasabb torony is lehet, ilyenkor bármelyik kiírható.
Idő: O(N^2) (N <= 4000), memória: O(N).
*/
/*
Hint 1: || A bemenet sorrendje lényegtelen. Rendezd a kockákat oldalhossz, majd súly szerint: így egy kocka fölé csak előtte álló kocka kerülhet. ||
Hint 2: || Ez egy leghosszabb növekvő részsorozat, csak most nem a kockák számát, hanem az oldalhosszak összegét maximalizáljuk. ||
Hint 3: || dp[i] = oldal[i] + max dp[j] (j < i, oldal[j] <= oldal[i] és súly[j] <= súly[i]). Tárold, melyik kocka került rá, és a legjobb aljától indulva írd ki a kockákat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // beolvasás, rendezés: first = oldalhossz, second = súly
    int n;
    cin >> n;
    vector<pair<int, int>> kocka(n);
    for (int i = 0; i < n; i++) cin >> kocka[i].first >> kocka[i].second;
    sort(kocka.begin(), kocka.end());   // oldal szerint, azon belül súly szerint növekvő

    // dp[i] = a legmagasabb torony, amelynek az i. kocka az alja; felette[i] = a rá tett kocka
    vector<int> dp(n), felette(n, -1);   // magasság legfeljebb 4000 · 20000, belefér az int-be
    for (int i = 0; i < n; i++) {
        dp[i] = kocka[i].first;          // egyedül az i. kocka
        for (int j = 0; j < i; j++) {
            if (kocka[j].first <= kocka[i].first && kocka[j].second <= kocka[i].second
                && dp[j] + kocka[i].first > dp[i]) {
                dp[i] = dp[j] + kocka[i].first;
                felette[i] = j;
            }
        }
    }

    // a legmagasabb torony alja
    int alul = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] > dp[alul]) alul = i;
    }

    // visszafejtés alulról felfelé, kiírás: kockaszám, majd a kockák
    vector<pair<int, int>> torony;
    for (int i = alul; i != -1; i = felette[i]) torony.push_back(kocka[i]);
    cout << torony.size() << '\n';
    for (int k = 0; k < (int)torony.size(); k++) {
        cout << torony[k].first << ' ' << torony[k].second << '\n';
    }
    return 0;
}
