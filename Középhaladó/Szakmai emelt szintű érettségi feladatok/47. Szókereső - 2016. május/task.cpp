/*
Megoldás lényege:
A bemenet minden sorát a '*' karakterek mentén bontjuk szét: szó, kezdő sor, kezdő oszlop és irány. Az első részfeladat eredménye a beolvasott szavak száma. A második részfeladatban megkeressük a leghosszabb szó hosszát, a maximális hosszúságú szavakat pedig egy set-be tesszük, amely egyúttal rendezi és egyedivé is teszi őket, így lexikografikus sorrendben írhatók ki. A harmadik részfeladatban egy 16x16-os rácsot '.' karakterekkel töltünk fel, majd minden szó k-adik betűjét a kezdőpozícióból az irány szerint elhelyezzük; az irányt két eltolás-tömb kódolja. Az időigény az összes szóhossz arányos, a memóriaigény állandó rács plusz a bemenet.
*/
/*
Hint 1: || A bemenet sorait a '*' karakter mentén bontsd szét: az első rész a szó, a többi három rész egész szám. Az 1. és 2. részfeladat ebből egyszerű számlálás és maximumkeresés. ||
Hint 2: || Az irány kódjai 1-től 8-ig: 1 jobbra, 5 balra, 3 felfelé, 7 lefelé, a többi átlós; írd fel minden kódhoz a sor- és oszlopváltozást két tömbbe (dr, dc). ||
Hint 3: || A rácsot '.' karakterekkel töltsd fel, majd a szó k-edik betűjét a (sor + k * dr, oszlop + k * dc) cellába írd; a bemenet ellentmondásmentes, így az átfedő cellákban ugyanaz a betű áll. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // irány kódok: 1 jobbra, 2 jobbra-fel, 3 fel, 4 balra-fel, 5 balra, 6 balra-le, 7 le, 8 jobbra-le
    const int dr[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
    const int dc[9] = {0, 1, 1, 0, -1, -1, -1, 0, 1};

    vector<string> szavak;
    vector<int> sorok, oszlopok, iranyok;
    string s;
    while (cin >> s) {
        size_t p1 = s.find('*');
        size_t p2 = s.find('*', p1 + 1);
        size_t p3 = s.find('*', p2 + 1);
        szavak.push_back(s.substr(0, p1));
        sorok.push_back(stoi(s.substr(p1 + 1, p2 - p1 - 1)));
        oszlopok.push_back(stoi(s.substr(p2 + 1, p3 - p2 - 1)));
        iranyok.push_back(stoi(s.substr(p3 + 1)));
    }
    int n = szavak.size();

    // 1. részfeladat: a szavak száma
    cout << "#\n" << n << "\n";

    // 2. részfeladat: a leghosszabb szó hossza, majd a leghosszabb szavak
    size_t maxHossz = 0;
    for (const string &w : szavak) {
        maxHossz = max(maxHossz, w.size());
    }
    set<string> leghosszabb;
    for (const string &w : szavak) {
        if (w.size() == maxHossz) {
            leghosszabb.insert(w);
        }
    }
    cout << "#\n" << maxHossz << "\n";
    for (const string &w : leghosszabb) {
        cout << w << "\n";
    }

    // 3. részfeladat: a 16x16-os feladvány
    vector<string> racs(16, string(16, '.'));
    for (int i = 0; i < n; i++) {
        int d = iranyok[i];
        for (int k = 0; k < (int)szavak[i].size(); k++) {
            int r = sorok[i] + k * dr[d];
            int c = oszlopok[i] + k * dc[d];
            racs[r][c] = szavak[i][k];
        }
    }
    cout << "#\n";
    for (const string &sor : racs) {
        cout << sor << "\n";
    }
    return 0;
}
