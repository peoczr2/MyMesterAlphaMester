/*
Megoldás lényege:
A bemenetet egyszer beolvassuk: 52 hét, hetenként öt szám, és a számok előfordulásait egy gyakorisági tömbben (1..90) rögzítjük.
Az 1. és 2. részfeladatban a kért hét számait rendezve írjuk ki (az 52. hét számai a bemenetben nincsenek rendezve), a 3. részfeladat válasza az, hogy van-e nulla gyakoriságú szám.
A 4. részfeladatban a páratlan számok gyakoriságainak összege, az 5. részfeladatban a teljes gyakorisági tömb adja a választ.
A 6. részfeladatban az 1..90 közötti prímeket osztókereséssel szűrjük, és a nulla gyakoriságúakat írjuk ki.
A megoldás O(52 * 5 + 90 * sqrt(90)) időben fut.
*/
/*
Hint 1: || A húzásokat egy gyakorisági tömbben számold össze: minden kihúzott számnál növeld a hozzá tartozó elemet. Ebből az 3., 4., 5. és 6. részfeladat is közvetlenül leolvasható. ||
Hint 2: || A 1. és 2. részfeladat rendezett kiírás, de figyelj arra, hogy az 52. hét számai a bemenetben nincsenek rendezve. A páratlan húzások száma a gyakorisági tömb páratlan indexű elemeinek összege. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int het;
    cin >> het;
    vector<vector<int>> h(52, vector<int>(5));
    for (int i = 0; i < 52; i++)
        for (int j = 0; j < 5; j++) cin >> h[i][j];

    // gyakoriság: hányszor húzták ki az adott számot
    int db[91] = {0};
    for (int i = 0; i < 52; i++)
        for (int j = 0; j < 5; j++) db[h[i][j]]++;

    // 1. részfeladat: az 52. hét nyerőszámai növekvő sorrendben
    vector<int> u = h[51];
    sort(u.begin(), u.end());
    cout << "#\n";
    for (int j = 0; j < 5; j++) cout << u[j] << (j < 4 ? " " : "\n");

    // 2. részfeladat: az adott hét nyerőszámai növekvő sorrendben
    vector<int> v = h[het - 1];
    sort(v.begin(), v.end());
    cout << "#\n";
    for (int j = 0; j < 5; j++) cout << v[j] << (j < 4 ? " " : "\n");

    // 3. részfeladat: volt-e olyan szám, amit egyszer sem húztak ki
    bool van = false;
    for (int x = 1; x <= 90; x++)
        if (db[x] == 0) van = true;
    cout << "#\n";
    cout << (van ? "van" : "nincs") << "\n";

    // 4. részfeladat: a páratlan számok húzásainak száma
    int paratlan = 0;
    for (int x = 1; x <= 90; x += 2) paratlan += db[x];
    cout << "#\n";
    cout << paratlan << "\n";

    // 5. részfeladat: az egyes számok húzásainak száma
    cout << "#\n";
    for (int x = 1; x <= 90; x++) cout << db[x] << (x < 90 ? " " : "\n");

    // 6. részfeladat: az egyszer sem húzott prímszámok
    vector<int> np;
    for (int x = 2; x <= 90; x++) {
        bool prim = true;
        for (int d = 2; d * d <= x; d++)
            if (x % d == 0) {
                prim = false;
                break;
            }
        if (prim && db[x] == 0) np.push_back(x);
    }
    cout << "#\n";
    cout << np.size() << "\n";
    for (size_t i = 0; i < np.size(); i++) cout << np[i] << (i + 1 < np.size() ? " " : "\n");

    return 0;
}
