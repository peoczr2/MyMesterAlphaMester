/*
Megoldás lényege: a lift az igényeket a bemenet (jelzési) sorrendjében szolgálja ki, ezért útját egyetlen menetben követjük. Egy igény előtt a lift az aktuális szintről üres menetben a kezdőszintre megy, majd utassal a célszintre, és a célszint lesz az új aktuális szint. Az érintett legalacsonyabb és legmagasabb szint a kezdőszint és az összes kezdő- és célszint szélsőértéke. Felfelé indulás utassal, ha a cél nagyobb a kezdőnél; utas nélkül, ha az aktuális szint kisebb a kezdőszintnél. Egy csapat szabálytalan, ha egy igénye kezdőszintje nem egyezik a csapat előző célszintjével: ekkor a két szint és az igény ideje adja a választ. Az időigény O(K + M), ahol K az igények és M a csapatok száma.
*/
/*
Hint 1: || Tartsd nyilván a lift aktuális szintjét: minden igény előtt a lift az aktuális szintről a kezdőszintre megy üres menetben, majd a célszintre utassal. ||
Hint 2: || A 4. részfeladathoz egyetlen csapat egymás utáni igényeit vesd össze: az előző célszintnek egyeznie kell a következő igény kezdőszintjével, és az első eltérésnél kiírható az eredmény. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Igeny {
    int ora, perc, mp, csapat, induló, cel;
};

int main() {
    int n, m, k, l, s;
    cin >> n >> m >> k >> l >> s;
    vector<Igeny> ig(k);
    for (auto& r : ig)
        cin >> r.ora >> r.perc >> r.mp >> r.csapat >> r.induló >> r.cel;

    // 1. részfeladat: a legalacsonyabb és a legmagasabb érintett szint
    int also = s, felso = s;
    for (const auto& r : ig) {
        also = min({also, r.induló, r.cel});
        felso = max({felso, r.induló, r.cel});
    }
    cout << "#\n" << also << " " << felso << "\n";

    // 2. részfeladat: felfelé indulások utassal és utas nélkül
    int aktualis = s, felfele_utassal = 0, felfele_ures = 0;
    for (const auto& r : ig) {
        if (r.induló > aktualis) felfele_ures++;
        if (r.cel > r.induló) felfele_utassal++;
        aktualis = r.cel;
    }
    cout << "#\n" << felfele_utassal << " " << felfele_ures << "\n";

    // 3. részfeladat: a liftet nem igénybe vevő csapatok
    vector<bool> hasznalt(m + 1, false);
    for (const auto& r : ig) hasznalt[r.csapat] = true;
    vector<int> nem_hasznalt;
    for (int i = 1; i <= m; i++)
        if (!hasznalt[i]) nem_hasznalt.push_back(i);
    cout << "#\n" << nem_hasznalt.size() << "\n";
    for (size_t i = 0; i < nem_hasznalt.size(); i++) {
        if (i) cout << " ";
        cout << nem_hasznalt[i];
    }
    cout << "\n";

    // 4. részfeladat: az L. csapat szabálytalansága (az első eltérés)
    cout << "#\n";
    int elozo_cel = -1;
    bool talalt = false;
    for (const auto& r : ig) {
        if (r.csapat != l) continue;
        if (elozo_cel != -1 && r.induló != elozo_cel) {
            cout << "IGEN\n"
                 << elozo_cel << " " << r.induló << " "
                 << r.ora << " " << r.perc << " " << r.mp << "\n";
            talalt = true;
            break;
        }
        elozo_cel = r.cel;
    }
    if (!talalt) cout << "NEM\n";

    return 0;
}
