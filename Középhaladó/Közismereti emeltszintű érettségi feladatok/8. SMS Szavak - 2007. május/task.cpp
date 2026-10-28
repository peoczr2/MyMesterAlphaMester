/*
Megoldás lényege:
Minden szó kódját a betű-billentyű megfeleltetéssel állítjuk elő: minden betűt a hozzá tartozó számjegyre cserélünk, így a kód karakterlánc lesz. A kódok előfordulásait egy szótárban (map) tároljuk, így egy kódhoz tartozó szavak száma egy lekérdezéssel megkapható. A leghosszabb szó, az öt karakternél rövidebb szavak száma és az X kódhoz tartozó szavak egyetlen bejárással meghatározhatók. A több szót tartalmazó kódok szavait a bemeneti sorrendben, a kód szerint stabilan rendezve írjuk ki, a legtöbb szót tartalmazó kód pedig az első olyan szó kódja, amelynek kódjában a legtöbb szó van. Az időigény O(N log N), ami az N ≤ 600 korlát mellett messze elfér.
*/
/*
Hint 1: || Először minden szóhoz számold ki a kódját: a betűt a betű-billentyű táblázat szerinti számjegyre cseréld. Ezután minden kérdés a kódok és a szavak egyszerű összehasonlításával megválaszolható. ||
Hint 2: || Gyűjtsd a kódok előfordulásait egy szótárba (map<string, int>), így egy kódhoz tartozó szavak száma egy lekérdezéssel adódik. A 4., 5. és 6. részfeladat ebből már számolható. ||
Hint 3: || Az 5. részfeladatban a sorokat a kód szerint rendezd stabil rendezéssel, így egy kódon belül megmarad a bemeneti sorrend. A 6. részfeladatnál szigorú > összehasonlítással keresd a legnagyobb számú kódot, így az első ilyen szó kódját kapod. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A betűhöz tartozó billentyű számjegye (a, b, c -> 2; d, e, f -> 3; ...; w, x, y, z -> 9).
char billentyu(char c) {
    if (c <= 'c') return '2';
    if (c <= 'f') return '3';
    if (c <= 'i') return '4';
    if (c <= 'l') return '5';
    if (c <= 'o') return '6';
    if (c <= 's') return '7';
    if (c <= 'v') return '8';
    return '9';
}

string kod(const string& szo) {
    string r;
    for (char c : szo) r += billentyu(c);
    return r;
}

int main() {
    string x;
    cin >> x;
    int n;
    cin >> n;

    vector<string> szavak(n), kodok(n);
    for (int i = 0; i < n; i++) {
        cin >> szavak[i];
        kodok[i] = kod(szavak[i]);
    }

    map<string, int> db;  // kódonként a szavak száma
    for (const string& k : kodok) db[k]++;

    // 1. részfeladat: a leghosszabb szó és hossza (az első ilyen)
    int legh = 0;
    for (int i = 1; i < n; i++) {
        if (szavak[i].size() > szavak[legh].size()) legh = i;
    }
    cout << "#\n";
    cout << szavak[legh] << " " << szavak[legh].size() << "\n";

    // 2. részfeladat: az öt karakternél rövidebb szavak száma
    int rovid = 0;
    for (const string& s : szavak) {
        if (s.size() < 5) rovid++;
    }
    cout << "#\n";
    cout << rovid << "\n";

    // 3. részfeladat: az X kódhoz tartozó szavak
    cout << "#\n";
    bool elso = true;
    for (int i = 0; i < n; i++) {
        if (kodok[i] == x) {
            if (!elso) cout << " ";
            cout << szavak[i];
            elso = false;
        }
    }
    cout << "\n";

    // 4. részfeladat: azon szavak száma, amelyek kódjához több szó tartozik
    vector<int> tobbes;
    for (int i = 0; i < n; i++) {
        if (db[kodok[i]] >= 2) tobbes.push_back(i);
    }
    cout << "#\n";
    cout << tobbes.size() << "\n";

    // 5. részfeladat: ezek kódja és szava, a kód szerint rendezve (számértékben)
    stable_sort(tobbes.begin(), tobbes.end(), [&](int a, int b) {
        const string& ka = kodok[a];
        const string& kb = kodok[b];
        if (ka.size() != kb.size()) return ka.size() < kb.size();
        return ka < kb;
    });
    cout << "#\n";
    for (int i : tobbes) {
        cout << kodok[i] << " " << szavak[i] << "\n";
    }

    // 6. részfeladat: a legtöbb szóhoz tartozó kód
    string legtobbKod;
    int legtobbDb = 0;
    for (int i = 0; i < n; i++) {
        if (db[kodok[i]] > legtobbDb) {
            legtobbDb = db[kodok[i]];
            legtobbKod = kodok[i];
        }
    }
    cout << "#\n";
    cout << legtobbKod << "\n";

    // 7. részfeladat: a legtöbb szóhoz tartozó kód összes szava
    cout << "#\n";
    elso = true;
    for (int i = 0; i < n; i++) {
        if (kodok[i] == legtobbKod) {
            if (!elso) cout << " ";
            cout << szavak[i];
            elso = false;
        }
    }
    cout << "\n";

    // 8. részfeladat: a szavak kódjai az eredeti sorrendben
    cout << "#\n";
    for (int i = 0; i < n; i++) {
        cout << kodok[i] << "\n";
    }
    return 0;
}
