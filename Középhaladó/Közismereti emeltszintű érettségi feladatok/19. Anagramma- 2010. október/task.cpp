/*
Megoldás lényege:
A szavakat a betűik ábécérendbe rendezett alakjuk jellemzi: két szó pontosan akkor anagramma, ha ez a rendezett alak megegyezik, ezért ezt használjuk kulcsként.
Az 1. részfeladatban a betűk előfordulását 26 elemű tömbbel számoljuk, a 2. részfeladatban minden szó kulcsát kiírjuk, a 3. részfeladatban az SA kulcsával egyező szavakat gyűjtjük ki.
A 4. részfeladatban a leghosszabb szavak a maximális hosszúságúak, az 5. részfeladatban a szavakat hossz, majd kulcs szerint egy map-ben csoportosítjuk, így a csoportok rendezve jönnek ki, a csoporton belül pedig a bemeneti sorrend marad.
A megoldás a szavak összhosszában közel lineáris, a rendezések miatt O(N * L log L) időben fut.
*/
/*
Hint 1: || Egy szó anagramma-kulcsa a betűinek ábécérendbe rendezett alakja, és két szó akkor anagramma, ha kulcsuk megegyezik. Az 2. és 3. részfeladat ezzel egyszerű összehasonlítás. ||
Hint 2: || Az 5. részfeladatnál a szavakat hosszuk, majd kulcsuk szerint csoportosítsd egy map<hossz, map<kulcs, szavak>> szerkezetben: a map rendezetten adja vissza a csoportokat. A T_i számok a megfelelő hosszhoz tartozó csoportok darabszámai. ||
Hint 3: || A 3. részfeladat anagrammái között maga az A indexű szó is szerepel, ezért a számlálásnál ne feledkezz meg róla, és a talált szavakat a bemeneti sorrendben írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, a;
    cin >> n >> a;
    vector<string> s(n);
    for (auto &x : s) cin >> x;
    const string sa = s[a - 1];

    // 1. részfeladat: az SA karakterei és előfordulásaik
    int db[26] = {0};
    for (char c : sa) db[c - 'a']++;
    int m = 0;
    for (int i = 0; i < 26; i++)
        if (db[i] > 0) m++;
    cout << "#\n";
    cout << m << "\n";
    for (int i = 0; i < 26; i++)
        if (db[i] > 0) cout << char('a' + i) << " " << db[i] << "\n";

    // 2. részfeladat: a szavak betűinek ábécérendbe rendezett alakja
    auto kulcs = [](string t) {
        sort(t.begin(), t.end());
        return t;
    };
    cout << "#\n";
    for (auto &x : s) cout << kulcs(x) << "\n";

    // 3. részfeladat: az SA anagrammái (maga az SA is közöttük van)
    const string k = kulcs(sa);
    vector<string> ana;
    for (auto &x : s)
        if (kulcs(x) == k) ana.push_back(x);
    cout << "#\n";
    cout << ana.size() << "\n";
    for (size_t i = 0; i < ana.size(); i++) cout << ana[i] << (i + 1 < ana.size() ? " " : "\n");

    // 4. részfeladat: a leghosszabb szavak
    size_t L = 0;
    for (auto &x : s) L = max(L, x.size());
    vector<string> leg;
    for (auto &x : s)
        if (x.size() == L) leg.push_back(x);
    cout << "#\n";
    cout << L << " " << leg.size() << "\n";
    for (auto &x : leg) cout << x << "\n";

    // 5. részfeladat: anagramma-csoportok hossz szerint, a csoportok kulcs szerint rendezve
    map<size_t, map<string, vector<string>>> csop;
    for (auto &x : s) csop[x.size()][kulcs(x)].push_back(x);
    cout << "#\n";
    for (size_t len = 2; len <= L; len++) {
        size_t t = csop.count(len) ? csop[len].size() : 0;
        cout << t << (len < L ? " " : "\n");
    }
    for (size_t len = 2; len <= L; len++) {
        if (!csop.count(len)) continue;
        for (auto &kv : csop[len]) {
            const vector<string> &v = kv.second;
            for (size_t i = 0; i < v.size(); i++) cout << v[i] << (i + 1 < v.size() ? " " : "\n");
        }
    }

    return 0;
}
