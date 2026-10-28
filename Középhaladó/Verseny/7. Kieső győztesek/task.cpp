/*
Megoldás lényege:
Először versenyenként meghatározzuk a győzteseket: a legnagyobb elért pontot elérő tanulók nyernek. Ezután egy tanuló akkor kerül a kimenetbe, ha van olyan A verseny, amelyen nyert, és van tőle különböző B verseny, amelyen indult, de nem érte el a B-beli minimális pontszámot. Ezt az összes (A, B) párra megnézzük, ami O(N·M²) összehasonlítás; 100-as korlátok mellett ez kb. 10^6 művelet, így az időlimitbe bőven belefér.
A kimenetben a sorszámokat növekvő sorrendben írjuk ki, ezért az 1-től N-ig tartó végigmenés már a kívánt sorrendet adja.
*/
/*
Hint 1: || Először versenyenként keresd meg a legnagyobb pontot, és tanulónként jegyezd fel, mely versenyeken nyert. Erre egy N x M-es logikai tábla elég. ||
Hint 2: || Egy tanuló pontosan akkor kerül a listába, ha van olyan A verseny, amelyen nyert, és van olyan B verseny, amelyen indult, de a pontszáma kisebb a B-beli minimumnál. Ezt két egymásba ágyazott ciklussal ellenőrizheted. ||
Hint 3: || Figyelj arra, hogy A és B legyen különböző verseny, és a nem indulást (-1) külön kezeld, hogy ne tűnjön alacsony pontszámnak. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> minimum(m);
    for (int j = 0; j < m; j++) {
        cin >> minimum[j];
    }

    // pont[s][j]: az s. tanuló pontszáma a j. versenyen, -1, ha nem indult
    vector<vector<int>> pont(n + 1, vector<int>(m, -1));
    for (int j = 0; j < m; j++) {
        int indulok;
        cin >> indulok;
        for (int k = 0; k < indulok; k++) {
            int s, p;
            cin >> s >> p;
            pont[s][j] = p;
        }
    }

    // nyert[s][j]: az s. tanuló győzött a j. versenyen (a legnagyobb pontot érte el)
    vector<vector<bool>> nyert(n + 1, vector<bool>(m, false));
    for (int j = 0; j < m; j++) {
        int legjobb = 0;
        for (int s = 1; s <= n; s++) {
            legjobb = max(legjobb, pont[s][j]);
        }
        for (int s = 1; s <= n; s++) {
            nyert[s][j] = (pont[s][j] == legjobb);
        }
    }

    vector<int> kimenet;
    for (int s = 1; s <= n; s++) {
        bool kieso = false;
        for (int a = 0; a < m && !kieso; a++) {
            if (!nyert[s][a]) {
                continue;
            }
            for (int b = 0; b < m && !kieso; b++) {
                if (b == a) {
                    continue;
                }
                if (pont[s][b] != -1 && pont[s][b] < minimum[b]) {
                    kieso = true;
                }
            }
        }
        if (kieso) {
            kimenet.push_back(s);
        }
    }

    cout << kimenet.size();
    for (int s : kimenet) {
        cout << ' ' << s;
    }
    cout << '\n';
    return 0;
}
