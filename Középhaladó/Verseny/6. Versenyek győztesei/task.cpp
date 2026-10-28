/*
Megoldás lényege:
Minden versenyen megkeressük a legnagyobb elért pontszámot, és az ezt elérő tanulókat győztesnek jelöljük meg. Döntetlen esetén így több tanuló is kap jelölést, ezt a megoldás természetesen kezeli. A tanulók sorszámait a jelölő tömbön végigmenve már növekvő sorrendben kapjuk, így külön rendezésre nincs szükség. A pontokat N×M-es táblázatban tároljuk (-1 jelöli, ha valaki nem indult), így az egész megoldás O(N·M) időben fut.
A minimális pontszámok ebben a feladatban nem befolyásolják a győzteseket, ezért csak beolvassuk őket.
*/
/*
Hint 1: || Egy tanuló akkor győztes, ha valamelyik versenyen a legnagyobb pontot érte el. Döntetlennél mindenki, aki ezt a pontot kapta, győztes. ||
Hint 2: || Használj egy bool tömböt a tanulókra: versenyenként keresd meg a maximumot, és jelöld meg az ezt elérő sorszámokat. Végül az 1..N tartományon menve írd ki a megjelöltek számát és sorszámait. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // A minimumokat ebben a feladatban nem használjuk, csak beolvassuk őket
    for (int j = 0; j < m; j++) {
        int minimum;
        cin >> minimum;
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

    // nyertes[s]: az s. tanuló valamelyik versenyen győztes
    vector<bool> nyertes(n + 1, false);
    for (int j = 0; j < m; j++) {
        int legjobb = 0;
        for (int s = 1; s <= n; s++) {
            legjobb = max(legjobb, pont[s][j]);
        }
        for (int s = 1; s <= n; s++) {
            if (pont[s][j] == legjobb) {
                nyertes[s] = true;
            }
        }
    }

    int t = count(nyertes.begin(), nyertes.end(), true);
    cout << t;
    for (int s = 1; s <= n; s++) {
        if (nyertes[s]) {
            cout << ' ' << s;
        }
    }
    cout << '\n';
    return 0;
}
