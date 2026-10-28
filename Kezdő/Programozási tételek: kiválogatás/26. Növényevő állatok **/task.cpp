/*
Megoldás lényege:
Az állatok azok az élőlények, amelyek esznek valamit, a növények nem esznek semmit. Egy állat akkor növényevő,
ha az általa megevett élőlények közül egyik sem eszik semmit, vagyis mindegyik prédája növény. Ezért először
összegyűjtjük az ételt evő élőlények halmazát, majd még egyszer végigmegyünk a párokon: ha az evő élőlény
olyan élőlényt eszik, amely a halmazban benne van, akkor ez az állat nem lehet csak növényevő. A kiírásnál az
állatokat a bemenetben először előforduló sorrendben vesszük, így a kimenet sorrendje a mintával egyezik.
Az időigény O(N log N), ami N ≤ 30 mellett triviális.
*/
/*
Hint 1: || Egy élőlény akkor állat, ha eszik valamit. Egy állat akkor csak növényevő, ha az általa evett élőlények egyike sem eszik semmit. ||
Hint 2: || Először gyűjtsd össze, kik szerepelnek az evő oszlopban (ők az állatok). Utána menj végig a párokon újra, és jelöld meg azokat az állatokat, akik olyan élőlényt esznek, amely szerepel ebben a halmazban. ||
Hint 3: || A kiírandó állatokat az első előfordulásuk sorrendjében add ki: egy halmazzal ellenőrizd, hogy egy névvel már találkoztál-e, és ha nem, tedd egy vektorba. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<string, string>> parok(n);
    set<string> eszik;
    for (auto& p : parok) {
        cin >> p.first >> p.second;
        eszik.insert(p.first);
    }

    set<string> latott;
    vector<string> allatok;
    set<string> nemNovenyevo;
    for (const auto& p : parok) {
        if (latott.insert(p.first).second) allatok.push_back(p.first);
        if (eszik.count(p.second)) nemNovenyevo.insert(p.first);
    }

    vector<string> novenyevok;
    for (const string& allat : allatok) {
        if (!nemNovenyevo.count(allat)) novenyevok.push_back(allat);
    }

    cout << novenyevok.size() << '\n';
    for (const string& allat : novenyevok) cout << allat << '\n';
    return 0;
}
