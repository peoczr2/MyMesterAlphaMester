/*
Megoldás lényege:
A bemenet soraiból az F sorok zárják le a vásárlásokat, ezért a tételeket vásárlásonként listákba gyűjtjük.
Az árat termékenként számoljuk: az első darab 500 Ft, a második 450 Ft, a harmadik és minden további 400 Ft,
vagyis q darab ára 500 + 450 + 400*(q-2), ha q >= 3. A részfeladatokat ezekből egy bejárással kapjuk meg:
a vásárlások száma, az első vásárló tételei, az ARU vásárlásai, illetve a fizetendő összegek.
Az időigény O(N log N), N <= 3000 esetén az időlimit bőven betartható.
*/
/*
Hint 1: || A vásárlásokat az F sor zárja le, ezért a tételeket érdemes egy listába gyűjteni, és F-nél új vásárlást kezdeni. Így a vásárlás sorszáma a lista indexéből adódik. ||
Hint 2: || Az ár nem a tételek száma szerint számítódik, hanem termékenként: ugyanabból a termékből a második darab 450 Ft, a harmadik és minden további 400 Ft. Egy vásárlásban termékenként számold meg a darabszámot (szótárral), majd a darabszámból az árat. ||
Hint 3: || A 3. és 4. részfeladat egyetlen bejárással megvan: vedd a vásárlások sorszámait, amelyekben az ARU szerepel, és jegyezd meg az első és az utolsó találatot. A 6. részfeladatnál a termékek megjelenési sorrendjét tartsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Egy sor beolvasása, a szóközök és a sortörés karakter nélkül.
string beolvas() {
    string sor;
    getline(cin, sor);
    size_t kezdet = sor.find_first_not_of(" \t\r\n");
    if (kezdet == string::npos) return "";
    size_t vege = sor.find_last_not_of(" \t\r\n");
    return sor.substr(kezdet, vege - kezdet + 1);
}

// q darab azonos termék ára: 1. darab 500 Ft, 2. darab 450 Ft, a 3. és további 400 Ft.
long long ar(long long q) {
    long long osszeg = 0;
    if (q >= 1) osszeg += 500;
    if (q >= 2) osszeg += 450;
    if (q >= 3) osszeg += 400 * (q - 2);
    return osszeg;
}

int main() {
    int n = stoi(beolvas());

    // vasarlasok[i]: az (i+1). vásárló tételei
    vector<vector<string>> vasarlasok;
    vector<string> kosar;
    for (int i = 0; i < n; i++) {
        string sor = beolvas();
        if (sor == "F") {
            vasarlasok.push_back(kosar);
            kosar.clear();
        } else {
            kosar.push_back(sor);
        }
    }

    string aru = beolvas();
    long long db = stoll(beolvas());
    int sorszam = stoi(beolvas());
    int vasarlasDb = vasarlasok.size();

    // 1. részfeladat: a fizetések száma
    cout << "#\n" << vasarlasDb << "\n";

    // 2. részfeladat: az első vásárló által vásárolt áruk száma
    cout << "#\n" << vasarlasok[0].size() << "\n";

    // 3. és 4. részfeladat: az ARU első és utolsó vásárlása, illetve a vásárlások száma
    int elso = -1, utolso = -1, aruVasarlas = 0;
    for (int i = 0; i < vasarlasDb; i++) {
        const vector<string>& k = vasarlasok[i];
        if (find(k.begin(), k.end(), aru) != k.end()) {
            if (elso < 0) elso = i + 1;
            utolso = i + 1;
            aruVasarlas++;
        }
    }
    cout << "#\n" << elso << "\n" << utolso << "\n";
    cout << "#\n" << aruVasarlas << "\n";

    // 5. részfeladat: DB darab azonos termék fizetendő összege
    cout << "#\n" << ar(db) << "\n";

    // 6. részfeladat: a SORSZAM-os vásárlás termékei és darabszámuk (megjelenési sorrendben)
    const vector<string>& valasztott = vasarlasok[sorszam - 1];
    vector<string> nevek;
    map<string, long long> mennyiseg;
    for (const string& t : valasztott) {
        if (!mennyiseg.count(t)) nevek.push_back(t);
        mennyiseg[t]++;
    }
    cout << "#\n" << nevek.size() << "\n";
    for (const string& t : nevek) cout << t << " " << mennyiseg[t] << "\n";

    // 7. részfeladat: az egyes vásárlásokban fizetendő összegek
    cout << "#\n";
    for (int i = 0; i < vasarlasDb; i++) {
        map<string, long long> m;
        for (const string& t : vasarlasok[i]) m[t]++;
        long long osszeg = 0;
        for (const auto& p : m) osszeg += ar(p.second);
        if (i > 0) cout << " ";
        cout << osszeg;
    }
    cout << "\n";
    return 0;
}
