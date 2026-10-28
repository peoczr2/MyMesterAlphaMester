/*
Megoldás lényege:
Egy fehér kocka akkor kap sorszámot, ha vízszintes vagy függőleges szó kezdete, vagyis bal- vagy felső szomszédja fekete vagy a rács széle, jobb- vagy alsó szomszédja pedig fehér. A sorfolytonos bejárás során a számozott kockákat növekvő sorszámmal látjuk el, és közben a vízszintes, illetve a függőleges kezdő kockák sorszámát külön listába gyűjtjük. Mivel a számok a bejárás sorrendjében keletkeznek, a két lista már rendezett, nincs szükség rendezésre. A kocka vizsgálata állandó időigényű, így az összidő O(N*M).
*/
/*
Hint 1: || Egy fehér kocka pontosan akkor kap számot, ha vízszintes vagy függőleges szó kezdete: balról (vagy fölülről) fekete kocka vagy a rács széle áll, jobbról (vagy alulról) pedig fehér kocka. A rácson kívüli kockákat feketének kell tekinteni. ||
Hint 2: || Járd be a rácsot sorfolytonosan egy számlálóval: minden szókezdő fehér kockát a számláló következő értékével számozz, és a számot tedd a vízszintes, illetve a függőleges listába aszerint, hogy melyik irányú szót kezd. Egy kocka lehet mindkét irányban kezdő, ekkor a száma mindkét listában szerepel, a listák pedig a bejárás miatt automatikusan növekvők lesznek. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for (auto &sor : a) cin >> sor;

    // a rácson kívüli kockák feketének számítanak
    auto feher = [&](int r, int c) {
        return r >= 0 && r < n && c >= 0 && c < m && a[r][c] == '0';
    };

    vector<vector<int>> szam(n, vector<int>(m, 0));
    vector<int> vizszintes, fuggoleges;
    int kovetkezo = 0;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++) {
            if (!feher(r, c)) continue;
            bool vKezdo = !feher(r, c - 1) && feher(r, c + 1);
            bool fKezdo = !feher(r - 1, c) && feher(r + 1, c);
            if (!vKezdo && !fKezdo) continue;
            szam[r][c] = ++kovetkezo;
            if (vKezdo) vizszintes.push_back(kovetkezo);
            if (fKezdo) fuggoleges.push_back(kovetkezo);
        }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (c) cout << ' ';
            if (a[r][c] == '1') cout << '#';
            else cout << szam[r][c];
        }
        cout << "\n";
    }

    cout << vizszintes.size() << "\n";
    for (size_t i = 0; i < vizszintes.size(); i++) {
        if (i) cout << ' ';
        cout << vizszintes[i];
    }
    cout << "\n";

    cout << fuggoleges.size() << "\n";
    for (size_t i = 0; i < fuggoleges.size(); i++) {
        if (i) cout << ' ';
        cout << fuggoleges[i];
    }
    cout << "\n";
    return 0;
}
