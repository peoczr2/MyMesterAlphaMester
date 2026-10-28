/*
Megoldás lényege:
Minden vízállást készültségi szintre osztunk: 3, ha meghaladja az 1000 cm-t, 2, ha meghaladja a 900 cm-t, 1, ha meghaladja a 800 cm-t, egyébként 0.
Árvíz az egymás melletti, legalább 1 szintű mérések maximális sorozata, ezeket egy balról jobbra haladó bejárással megkapjuk.
Minden árvíznél megkeressük a csúcsmagasság helyét: a sorozat legelső legnagyobb vízállásának sorszámát.
A leggyorsabban elért csúcsmagasságú árvíz az, ahol a kezdet és a csúcs közötti távolság (csúcs - kezdet) a legkisebb; egyenlőség esetén az első marad.
Az algoritmus O(N) időben fut, mert minden mérést legfeljebb kétszer vizsgálunk.
*/
/*
Hint 1: || Az árvizek a legalább elsőfokú készültségű (vagyis 800 cm-nél magasabb) mérések maximális, egymás melletti sorozatai. Egy balról jobbra haladó bejárással mindegyiket megtalálod. ||
Hint 2: || Egy árvízen belül a csúcsmagasság helye az a pozíció, ahol a vízállás a legnagyobb. Ha több azonos maximum van, a legelső kell. Ez a sorozat bejárásával egy egyszerű maximumkereséssel megkapható. ||
Hint 3: || Egy árvíz „gyorsaságát” a kezdete és a csúcsmagasság helye közötti távolság (csúcs - kezdet) adja. Tartsd meg az eddigi legjobb árvizet, és csak szigorúan kisebb távolságnál írd felül, így egyenlőség esetén az első marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int szint(int h) {
    if (h > 1000) return 3;
    if (h > 900) return 2;
    if (h > 800) return 1;
    return 0;
}

struct Arviz {
    int kezdet, vege, csucs;
};

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<Arviz> arvizek;
    int i = 1;
    while (i <= n) {
        if (szint(a[i]) == 0) {
            i++;
            continue;
        }
        int j = i;
        while (j + 1 <= n && szint(a[j + 1]) >= 1) j++;
        int csucs = i;
        for (int k = i + 1; k <= j; k++)
            if (a[k] > a[csucs]) csucs = k;
        arvizek.push_back({i, j, csucs});
        i = j + 1;
    }

    cout << arvizek.size() << '\n';
    if (arvizek.empty()) return 0;

    for (size_t k = 0; k < arvizek.size(); k++) {
        if (k > 0) cout << ' ';
        cout << arvizek[k].kezdet << ' ' << arvizek[k].vege;
    }
    cout << '\n';

    for (size_t k = 0; k < arvizek.size(); k++) {
        if (k > 0) cout << ' ';
        cout << arvizek[k].csucs;
    }
    cout << '\n';

    size_t legjobb = 0;
    for (size_t k = 1; k < arvizek.size(); k++) {
        int tav = arvizek[k].csucs - arvizek[k].kezdet;
        int legjobbTav = arvizek[legjobb].csucs - arvizek[legjobb].kezdet;
        if (tav < legjobbTav) legjobb = k;
    }
    cout << arvizek[legjobb].kezdet << ' ' << arvizek[legjobb].vege << '\n';

    return 0;
}
