/*
Megoldás lényege:
Minden tanulóra és minden versenyre megnézzük, hogy részt vett-e, és ha igen, elérte-e az adott versenyhez tartozó minimális pontszámot. Elég egy ilyen versenyt találni, utána a tanuló már bekerül a listába. A pontokat N×M-es táblázatban tároljuk, a -1 jelöli a nem indulást, így az összehasonlítás nem téveszt meg. Az időigény O(N·M), ami a korlátok mellett gyorsan lefut.
A sorszámokat az 1-től N-ig tartó végigmenéssel írjuk ki, így automatikusan növekvő sorrendben jönnek.
*/
/*
Hint 1: || Egy tanuló akkor kerül a kimenetbe, ha legalább egy versenyen indult, és a pontszáma eléri az adott verseny minimumát. ||
Hint 2: || Használj egy bool tömböt a tanulókra: minden versenyt végignézve, ha a tanuló elérte a minimumot, jelöld meg. Végül az 1..N tartományon menve írd ki a megjelöltek számát és sorszámait. ||
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

    vector<bool> eleri(n + 1, false);
    for (int s = 1; s <= n; s++) {
        for (int j = 0; j < m; j++) {
            if (pont[s][j] != -1 && pont[s][j] >= minimum[j]) {
                eleri[s] = true;
            }
        }
    }

    int t = count(eleri.begin(), eleri.end(), true);
    cout << t;
    for (int s = 1; s <= n; s++) {
        if (eleri[s]) {
            cout << ' ' << s;
        }
    }
    cout << '\n';
    return 0;
}
