/*
Megoldás lényege:
Az állomásokat egyetlen bejárással dolgozzuk fel. Az első és az utolsó látogatott állomásból a menetidő az utolsó érkezési és az első indulási idő különbsége. Egy állomás áthaladás, ha az érkezési és az indulási idő egyenlő és nem nulla; megállás, ha mindkét idő nem nulla és az indulás később van. Az első (csak indulási idejű) és az utolsó (csak érkezési idejű) állomás nem számít megállásnak. A 3. részfeladatban minden megállást az előző megálló időtartamával hasonlítunk össze, az első megállásnak nincs előzője, ezért nem kerülhet a listába. A -2 és a -1 közötti választást az dönti el, hogy volt-e egyáltalán megállás. A 4. részfeladatban az egymást követő áthaladó állomások futamait, az 5. részfeladatban az egymást követő megállók futamait keressük, és a leghosszabb megállási futamnál a szigorú összehasonlítás az elsőt tartja meg. Az időigény O(N), a tárigény O(N).
*/
/*
Hint 1: || Minden állomásra döntsd el, hogy áthaladás (érkezési és indulási idő egyenlő és nem nulla), megállás (mindkét idő nem nulla, az indulás később van), vagy nem járt ott a vonat (mindkettő nulla). Az első és az utolsó állomásnál az egyik idő nulla, így ezek nem lehetnek megállások. ||
Hint 2: || A menetidőhöz két állomás kell: az első olyan állomás indulási ideje, ahol az érkezési idő nulla, és az utolsó olyan állomás érkezési ideje, ahol az indulási idő nulla. A megállás hossza az indulási és az érkezési idő különbsége, ezt egy változóban tartsd az előző megállóról. ||
Hint 3: || Az egymást követő állomások futamait egyetlen bejárással kezeld: amíg a feltétel teljesül, bővítsd a futamot, megszakadásnál zárd le. A -2 és -1 kiírásához elég egy logikai jelző, amely azt rögzíti, volt-e egyáltalán megállás. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> erk(n), ind(n);
    for (int i = 0; i < n; i++) cin >> erk[i] >> ind[i];

    auto atha = [&](int i) { return erk[i] != 0 && erk[i] == ind[i]; };
    auto megall = [&](int i) { return erk[i] != 0 && ind[i] != 0 && erk[i] < ind[i]; };

    // 1. részfeladat: menetidő = a végállomás érkezése - a kezdőállomás indulása
    int elso = -1, utolso = -1;
    for (int i = 0; i < n; i++) {
        if (erk[i] != 0 || ind[i] != 0) {
            if (elso == -1) elso = i;
            utolso = i;
        }
    }
    cout << "#\n" << erk[utolso] - ind[elso] << "\n";

    // 2. részfeladat: a megállás nélkül áthaladt állomások száma
    int atha_db = 0;
    for (int i = 0; i < n; i++)
        if (atha(i)) atha_db++;
    cout << "#\n" << atha_db << "\n";

    // 3. részfeladat: azok a megállások, amelyek hosszabbak az előző megállónál
    bool volt_megallas = false, van_elozo = false;
    int elozo_hossz = 0;
    vector<int> tobb;
    for (int i = 0; i < n; i++) {
        if (!megall(i)) continue;
        volt_megallas = true;
        int hossz = ind[i] - erk[i];
        if (van_elozo && hossz > elozo_hossz) tobb.push_back(i + 1);
        van_elozo = true;
        elozo_hossz = hossz;
    }
    cout << "#\n";
    if (!volt_megallas) {
        cout << -2 << "\n";
    } else if (tobb.empty()) {
        cout << -1 << "\n";
    } else {
        for (size_t k = 0; k < tobb.size(); k++) {
            if (k) cout << ' ';
            cout << tobb[k];
        }
        cout << "\n";
    }

    // 4. részfeladat: az áthaladással megtett állomásszakaszok első és utolsó állomása
    cout << "#\n";
    for (int i = 0; i < n;) {
        if (!atha(i)) {
            i++;
            continue;
        }
        int j = i;
        while (j + 1 < n && atha(j + 1)) j++;
        cout << i + 1 << ' ' << j + 1 << "\n";
        i = j + 1;
    }

    // 5. részfeladat: a leghosszabb, mindenhol megállással teli állomásszakasz
    int legh_hossz = 0, legh_kezdet = -1;
    for (int i = 0; i < n;) {
        if (!megall(i)) {
            i++;
            continue;
        }
        int j = i;
        while (j + 1 < n && megall(j + 1)) j++;
        if (j - i + 1 > legh_hossz) {
            legh_hossz = j - i + 1;
            legh_kezdet = i;
        }
        i = j + 1;
    }
    cout << "#\n";
    if (legh_hossz == 0)
        cout << -1 << "\n";
    else
        cout << legh_kezdet + 1 << ' ' << legh_kezdet + legh_hossz << "\n";

    return 0;
}
