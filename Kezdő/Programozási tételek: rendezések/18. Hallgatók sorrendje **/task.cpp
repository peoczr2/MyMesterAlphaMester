/*
Megoldás lényege:
A hallgatókat három szempont szerint rendezzük: előbb az évfolyam zárthelyi jegy (Ef) szerint csökkenő, azon belül a két csoport zárthelyi jegyének összege (Cs1 + Cs2) szerint csökkenő, végül a röpzárthelyi pont (R) szerint csökkenő sorrendben.
Ha mindhárom érték egyezik, a kisebb sorszámú hallgató kerül előre, ezt a sorszámot utolsó kulcsként figyelembe véve érjük el.
A gyakorlati jegy kiszámítása a rendezési szabályban nem szerepel, ezért nem használjuk.
Az indexeket rendezzük, az adatokat nem mozgatjuk, az időigény O(N log N).
*/
/*
Hint 1: || Az összehasonlítás kulcsai nem a gyakorlati jegy, hanem az évfolyam zárthelyi jegy, a két csoport zárthelyi jegyének összege és a röpzárthelyi pont, ebben a sorrendben. ||
Hint 2: || Mindhárom kulcsot csökkenő irányba kell rendezni, és ha mindegyik egyezik, a kisebb sorszám kerül előre; ezt egy többkulcsos összehasonlító függvény adja meg. ||
Hint 3: || Az 0..N-1 indexekből álló tömböt rendezd az összehasonlító függvénnyel, az adatokat ne mozgasd, és a kiírásnál minden indexhez adj hozzá egyet, mert a sorszámok 1-től indulnak. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> r(n), cs(n), ef(n);
    for (int i = 0; i < n; i++) {
        int cs1, cs2;
        cin >> r[i] >> cs1 >> cs2 >> ef[i];
        cs[i] = cs1 + cs2;
    }

    vector<int> sorrend(n);
    iota(sorrend.begin(), sorrend.end(), 0);
    sort(sorrend.begin(), sorrend.end(), [&](int i, int j) {
        if (ef[i] != ef[j]) return ef[i] > ef[j];
        if (cs[i] != cs[j]) return cs[i] > cs[j];
        if (r[i] != r[j]) return r[i] > r[j];
        return i < j;
    });

    for (int i = 0; i < n; i++) {
        if (i > 0) cout << ' ';
        cout << sorrend[i] + 1;
    }
    cout << '\n';
    return 0;
}
