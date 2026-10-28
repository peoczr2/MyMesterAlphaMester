/*
Megoldás lényege:
Minden poszton külön megszámoljuk, hányszor indult az egyes versenyzők, és az eddigi beosztás igazságos, ha a legtöbbször és a legkevesebbszer indított versenyző száma legfeljebb eggyel tér el. Ha az edző igazságos volt, egy poszton az a versenyző indítható igazságosan, akinek ott a legkevesebb volt az indulása, ezért posztonként a minimális darabszámú versenyzőket kell kilistázni. A versenyzőket első előfordulásuk sorrendjében tároljuk, így a kiírás az első forduló sorrendjét követi. Az időigény a bemenet méretével arányos, ami bőven elég.
*/
/*
Hint 1: || Posztonként külön számold, hányszor szerepelt az egyes versenyző ott. Ehhez egy névhez 5 darabszámot tároló szerkezet, például map, jó. ||
Hint 2: || Egy poszton az igazságosság akkor teljesül, ha a legtöbbször és a legkevesebbszer indított versenyző száma legfeljebb 1-gyel tér el. Ezt minden poszton ellenőrizd, a tartalékot is beleértve. ||
Hint 3: || Ha az edző igazságos volt, egy poszton azok indíthatók igazságosan, akiknek ott a minimális a darabszáma. A kiíráshoz tartsd meg a versenyzők első előfordulásának sorrendjét. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int f;
    cin >> f;
    vector<string> versenyzok;             // az első előfordulásuk sorrendjében
    map<string, array<int, 5>> indulas;    // posztonként hányszor indult
    for (int r = 0; r < f; r++) {
        for (int p = 0; p < 5; p++) {
            string nev;
            cin >> nev;
            if (!indulas.count(nev)) {
                indulas[nev] = array<int, 5>{};
                versenyzok.push_back(nev);
            }
            indulas[nev][p]++;
        }
    }

    int minPoszt[5], maxPoszt[5];
    bool igazsagos = true;
    for (int p = 0; p < 5; p++) {
        minPoszt[p] = INT_MAX;
        maxPoszt[p] = INT_MIN;
        for (const string &nev : versenyzok) {
            minPoszt[p] = min(minPoszt[p], indulas[nev][p]);
            maxPoszt[p] = max(maxPoszt[p], indulas[nev][p]);
        }
        if (maxPoszt[p] - minPoszt[p] > 1) igazsagos = false;
    }

    if (!igazsagos) {
        cout << "NEM IGAZSAGOS\n";
        return 0;
    }

    cout << "IGAZSAGOS\n";
    for (int p = 0; p < 4; p++) {
        bool elso = true;
        for (const string &nev : versenyzok) {
            if (indulas[nev][p] != minPoszt[p]) continue;
            if (!elso) cout << ' ';
            cout << nev;
            elso = false;
        }
        cout << '\n';
    }
    return 0;
}
