/*
Megoldás lényege:
A képet kétdimenziós tömbben tároljuk: a bemenet sorfolytonos sorrendjében töltjük fel, így a sor- és oszlopindex közvetlenül megadja a képpont helyét.
Az 1. részfeladatban a keresett színt egy teljes bejárással keressük meg.
A 2. részfeladatban elegendő a megadott képpont színét megjegyezni, majd a sorában és az oszlopában megszámolni az egyezéseket.
A 3. részfeladatban a piros, kék és zöld előfordulásait számoljuk; a legnagyobb számot elérő szín nyer, döntetlennél az a szín, amelyik a bejárás során hamarabb éri el ezt a maximumot.
A 4. részfeladatban a sárga pontok legkisebb és legnagyobb sor-, illetve oszlopindexe adja a téglalap két sarkát, ezért egyetlen bejárás elég.
Az időigény a képpontok számával arányos, legfeljebb 100 * 100 művelet.
*/
/*
Hint 1: || A képet érdemes kétdimenziós tömbben tárolni, a bemenet sorfolytonos sorrendjében. Ezután a sor- és oszlopindex közvetlenül megadja a képpont helyét, és a legtöbb kérdés egyszerű bejárással megválaszolható. ||
Hint 2: || A 2. részfeladatban nem kell a teljes képet újra bejárni: elég a megadott képpont színét megjegyezni, majd a sorát és az oszlopát végigvizsgálni. Mivel a koordináták 1-től indulnak, a tömbindexelésnél 1-et kell levonni. ||
Hint 3: || A 3. részfeladatban minden színnek össze kell számolni az előfordulásait, majd a második bejárásban megnézni, melyik szín éri el előbb a maximális számot. A 4. részfeladatban a sárga pontok legkisebb és legnagyobb sor- és oszlopindexe adja a téglalap két sarkát. ||
*/
#include <bits/stdc++.h>
using namespace std;

using Szin = array<int, 3>;  // (R, G, B)

// A piros (0), kék (1) és zöld (2) szín indexe; minden más szín esetén -1.
int tipusIndex(const Szin& c) {
    if (c == Szin{255, 0, 0}) return 0;
    if (c == Szin{0, 0, 255}) return 1;
    if (c == Szin{0, 255, 0}) return 2;
    return -1;
}

int main() {
    Szin keresett;
    cin >> keresett[0] >> keresett[1] >> keresett[2];

    int s, o;
    cin >> s >> o;

    // A bemenet szerint s a sor (1..sz), o az oszlop (1..m); a képpontok sorfolytonosan következnek.
    int sz, m;
    cin >> sz >> m;
    vector<vector<Szin>> kep(sz, vector<Szin>(m));
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < m; j++)
            cin >> kep[i][j][0] >> kep[i][j][1] >> kep[i][j][2];

    // 1. részfeladat: szerepel-e a keresett szín a képen
    cout << "#\n";
    bool van = false;
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < m; j++)
            if (kep[i][j] == keresett) van = true;
    cout << (van ? 1 : 0) << "\n";

    // 2. részfeladat: a megadott képpont színének előfordulása a sorában és az oszlopában
    cout << "#\n";
    Szin pont = kep[s - 1][o - 1];
    int sorban = 0, oszlopban = 0;
    for (int j = 0; j < m; j++)
        if (kep[s - 1][j] == pont) sorban++;
    for (int i = 0; i < sz; i++)
        if (kep[i][o - 1] == pont) oszlopban++;
    cout << sorban << " " << oszlopban << "\n";

    // 3. részfeladat: a piros, kék és zöld szín közül a leggyakoribb
    cout << "#\n";
    const string nevek[3] = {"p", "k", "z"};
    int db[3] = {0, 0, 0};
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < m; j++) {
            int t = tipusIndex(kep[i][j]);
            if (t >= 0) db[t]++;
        }
    int maxDb = max({db[0], db[1], db[2]});
    if (maxDb == 0) {
        cout << "0\n";
    } else {
        // Második bejárás: az a szín nyer, amelyik először éri el a maximális számot.
        int cnt[3] = {0, 0, 0};
        int gyoztes = -1;
        for (int i = 0; i < sz && gyoztes < 0; i++)
            for (int j = 0; j < m && gyoztes < 0; j++) {
                int t = tipusIndex(kep[i][j]);
                if (t >= 0 && ++cnt[t] == maxDb) gyoztes = t;
            }
        cout << nevek[gyoztes] << "\n";
    }

    // 4. részfeladat: a sárga téglalap bal felső és jobb alsó sarka (sor, oszlop)
    cout << "#\n";
    int r1 = INT_MAX, c1 = INT_MAX, r2 = 0, c2 = 0;
    const Szin sarga = {255, 255, 0};
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < m; j++)
            if (kep[i][j] == sarga) {
                r1 = min(r1, i + 1);
                c1 = min(c1, j + 1);
                r2 = max(r2, i + 1);
                c2 = max(c2, j + 1);
            }
    cout << r1 << " " << c1 << " " << r2 << " " << c2 << "\n";

    return 0;
}
