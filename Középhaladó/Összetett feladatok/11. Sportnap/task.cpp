/*
Megoldás lényege:
A nevezéseket egy T x S-es logikai táblázatba (nevezett[tanulo][sportag]) gyűjtjük, és közben számoljuk, hány nevezése van az egyes tanulóknak (többszörösen is), és jelöljük, ki nevezett többször ugyanarra a sportágra. Ebből az X-es tanuló nevezésszáma, a legkisebb többszörösen nevező tanuló, a sportágankénti (különböző) tanulók száma, a legtöbb sportágban induló tanuló és a sportágpárok is közvetlenül kiadódnak.
Két sportág akkor rendezhető egyszerre, ha nincs olyan tanuló, aki mindkettőre nevezett: az (a, b) párokat a < b feltétellel, növekvő sorrendben vizsgáljuk. Az időigény O(S^2 * T), ami a kis korlátok miatt bőven belefér.
*/
/*
Hint 1: || Egy T x S-es logikai táblázatban tárold, ki melyik sportágra nevezett, és közben számold a tanulónkénti nevezések számát (a többszöröseket is). A táblázat segít a többi kérdésben is. ||
Hint 2: || A többszörös nevezés megtalálásánál figyelj arra, hogy a második nevezéskor már be van jelölve a táblázatban. A legtöbb sportágban induló tanuló a különböző sportágak számából adódik, és döntetlennél a kisebb sorszám nyer. ||
Hint 3: || Egy (a, b) sportágpárt akkor írj ki, ha nincs olyan tanuló, aki mindkettőre nevezett. Két egymásba ágyazott ciklussal, a < b feltétellel, a tanulók mentén végigmenve ellenőrizheted ezt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int T, S, N;
    cin >> T >> S >> N;

    vector<int> nevezesekSzama(T + 1, 0);        // a tanuló összes nevezése (többszörös is)
    vector<bool> tobbszoros(T + 1, false);      // volt-e ugyanarra a sportágra többszörös nevezése
    vector<vector<bool>> nevezett(T + 1, vector<bool>(S + 1, false));

    for (int i = 0; i < N; i++) {
        int t, s;
        cin >> t >> s;
        nevezesekSzama[t]++;
        if (nevezett[t][s]) tobbszoros[t] = true;
        nevezett[t][s] = true;
    }

    int X;
    cin >> X;

    // 1. részfeladat: az X sorszámú tanuló nevezéseinek száma
    cout << "#\n";
    cout << nevezesekSzama[X] << "\n";

    // 2. részfeladat: legkisebb sorszámú, többször nevező tanuló (vagy -1)
    cout << "#\n";
    int elsoTobbszoros = -1;
    for (int t = 1; t <= T; t++)
        if (tobbszoros[t]) {
            elsoTobbszoros = t;
            break;
        }
    cout << elsoTobbszoros << "\n";

    // 3. részfeladat: sportágankénti nevezések száma (többszörös egynek számít)
    vector<int> letszam(S + 1, 0);
    for (int t = 1; t <= T; t++)
        for (int s = 1; s <= S; s++)
            if (nevezett[t][s]) letszam[s]++;
    cout << "#\n";
    for (int s = 1; s <= S; s++)
        cout << letszam[s] << (s < S ? " " : "\n");

    // 4. részfeladat: a legtöbb sportágban induló tanuló (döntetlennél a legkisebb sorszám)
    cout << "#\n";
    int legtobbT = 1, legtobbDb = -1;
    for (int t = 1; t <= T; t++) {
        int db = count(nevezett[t].begin(), nevezett[t].end(), true);
        if (db > legtobbDb) {
            legtobbDb = db;
            legtobbT = t;
        }
    }
    cout << legtobbT << "\n";

    // 5. részfeladat: egyidőben rendezhető sportágpárok
    cout << "#\n";
    for (int a = 1; a <= S; a++)
        for (int b = a + 1; b <= S; b++) {
            bool kozos = false;
            for (int t = 1; t <= T; t++)
                if (nevezett[t][a] && nevezett[t][b]) {
                    kozos = true;
                    break;
                }
            if (!kozos) cout << a << " " << b << "\n";
        }

    return 0;
}
