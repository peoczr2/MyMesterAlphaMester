/*
Megoldás lényege:
A pontszámok legfeljebb 100 000-ig terjednek, ezért minden lehetséges egész ponthatárt (1-től 100 001-ig) végigpróbálhatunk.
Az A határhoz az a két szám kell, amelyet a feladat maximumként ír elő: a harmadosztályúak közül hányan kapnak legalább A pontot, és a másodosztályúak közül hányan kapnak A-nál kevesebbet. Ennek maximumát kell minimalizálni.
A B határhoz hasonlóan a másodosztályúak közül a legalább B pontosak és az elsőosztályúak közül a B-nél kevesebbet kapottak számának maximumát vizsgáljuk.
A számlálásokat a rendezett pontszámtömbökön végzett lower_bound adja meg, így egy ponthatár O(log N) alatt kiértékelhető.
Ha egy küszöb a korábbinál kisebb vagy egyenlő maximumot ad, frissítünk, így a legnagyobb optimális határ marad meg.
Az időigény O(100 000 · log N), ami a 0,1 mp-es korláton belül van.
*/
/*
Hint 1: || Mindkét határra egy-egy maximum jellegű függvényt kell minimalizálni: az egyik tag a küszöb emelésével csökken, a másik nő. Ezért elég minden lehetséges küszöböt kipróbálni. ||
Hint 2: || A rendezett pontszámtömbökön binárisan keresve (lower_bound) egy küszöbnél azonnal megkapod, hány versenyző van a kívánt oldalon. ||
Hint 3: || Az A-nál a harmadosztályúak közül a legalább A pontosakat és a másodosztályúak közül az A-nál kisebbeket számold, B-nél a másodosztályúak közül a legalább B pontosakat és az elsőosztályúak közül a B-nél kisebbeket. Egyenlő minimumnál a nagyobb küszöböt tartsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int e, m, h;
    cin >> e >> m >> h;
    vector<int> pe(e), pm(m), ph(h);
    for (auto &x : pe) cin >> x;
    for (auto &x : pm) cin >> x;
    for (auto &x : ph) cin >> x;
    sort(pe.begin(), pe.end());
    sort(pm.begin(), pm.end());
    sort(ph.begin(), ph.end());

    // less_cnt(vec, v): hány elem kisebb v-nél
    auto less_cnt = [](const vector<int> &vec, int v) {
        return int(lower_bound(vec.begin(), vec.end(), v) - vec.begin());
    };

    const int LIMIT = 100001;
    int bestA = 0, minA = INT_MAX;
    int bestB = 0, minB = INT_MAX;
    for (int v = 1; v <= LIMIT; ++v) {
        // A: max(#harmadosztályú >= v, #másodosztályú < v) minimális
        int fa = max(h - less_cnt(ph, v), less_cnt(pm, v));
        if (fa <= minA) {
            minA = fa;
            bestA = v;
        }
        // B: max(#másodosztályú >= v, #elsőosztályú < v) minimális
        int fb = max(m - less_cnt(pm, v), less_cnt(pe, v));
        if (fb <= minB) {
            minB = fb;
            bestB = v;
        }
    }
    cout << bestA << '\n' << bestB << '\n';
    return 0;
}
