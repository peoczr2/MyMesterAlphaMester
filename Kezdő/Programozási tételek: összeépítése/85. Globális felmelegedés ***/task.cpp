/*
Megoldás lényege:
Az évek átlaghőmérséklete mindig ugyanannyi (M) napból számolódik, ezért az átlagok sorrendje megegyezik az éves hőmérsékletösszegek sorrendjével, így elég az összegeket kiszámolni és összehasonlítani. A legmelegebb év az összegek maximuma (több azonos esetén a legelső). A leghosszabb növekvő szakasz kezdetét úgy kapjuk, hogy az E évtől visszafelé lépkedünk, amíg az előző év összege kisebb az aktuálisnál; az utoljára elért év adja a kezdő évet. A napi kérdésekhez napokra bontva meghatározzuk minden nap legmelegebb értékét az összes évben, és ezt az idei, illetve az egyes évek értékeivel hasonlítjuk össze. Az egész megoldás O(N·M) időben fut, ami a korlátok mellett bőven elég.
*/
/*
Hint 1: || Nem kell átlagot osztással számolni: minden év ugyanannyi napot tartalmaz, ezért az éves hőmérsékletösszegek sorrendje ugyanaz, mint az átlagoké. ||
Hint 2: || A B részhez az E évtől visszafelé haladj, amíg az előző év összege kisebb az aktuálisnál. Az utoljára elért év sorszáma adja a keresett kezdő évet. ||
Hint 3: || A C és D részhez napokra bontva számold ki minden nap maximumát az összes évben, majd nézd meg, hogy az idei év, illetve az egyes évek mely napokon érik el ezt a maximumot. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> h(n, vector<int>(m));
    vector<long long> ossz(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> h[i][j];
            ossz[i] += h[i][j];
        }
    }

    // A: a legnagyobb átlagú év (több egyforma esetén a legelső)
    int e = 0;
    for (int i = 1; i < n; ++i) {
        if (ossz[i] > ossz[e]) e = i;
    }
    cout << e + 1 << '\n';

    // B: az E évvel záruló leghosszabb, évről évre nőtt szakasz kezdete
    int s = e;
    while (s > 0 && ossz[s - 1] < ossz[s]) --s;
    if (s < e) cout << s + 1;
    cout << '\n';

    // napi maximum az összes évben
    vector<int> napiMax(m, INT_MIN);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            napiMax[j] = max(napiMax[j], h[i][j]);
        }
    }

    // C: az idei év azon napjainak száma, amelyeken más évben nem volt melegebb
    int c = 0;
    for (int j = 0; j < m; ++j) {
        if (h[n - 1][j] == napiMax[j]) ++c;
    }
    cout << c << '\n';

    // D: a legrégebbi év, amelynek volt olyan napja, amelyen nem volt melegebb
    int d = -1;
    for (int i = 0; i < n && d == -1; ++i) {
        for (int j = 0; j < m; ++j) {
            if (h[i][j] == napiMax[j]) {
                d = i;
                break;
            }
        }
    }
    cout << d + 1 << '\n';

    return 0;
}
