/*
Megoldás lényege:
A bemutatók sorrendjét a bemenet sorai adják, ezért az összes párt egy tömbben tároljuk.
Az 1., 2., 3. és 4. részfeladat egyetlen végigmenéssel vagy egy egyszerű kereséssel megoldható.
A személyek szerepléseit szótárral (map) számoljuk: név -> hány párban szerepelt, külön a fiúknál és a lányoknál.
Mivel a szótár kulcsai rendezve vannak, az 5. és 6. részfeladat nevei is ebből adódnak.
Az időigény O(N log N), N <= 1000 esetén az időlimit bőven betartható.
*/
/*
Hint 1: || A bemutatók sorrendje a bemenet sorrendje, így az 1. részfeladat az első és az utolsó sor. A 2., 3. és 4. részfeladatnál végigmész a párokon, és keresed a tánc, illetve a személy nevét. ||
Hint 2: || Az 5. és 6. részfeladathoz minden személyhez meg kell számolnod, hány párban szerepelt. Két szótár kell: az egyik a fiúkat, a másik a lányokat számolja, a kulcs a név, az érték a darabszám. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Visszaadja a legnagyobb darabszámú neveket (névsorrendben), és kiírja a darabszámukat.
void legtobbetTancoltak(const map<string, int>& szamlalo) {
    int maxDb = 0;
    for (const auto& p : szamlalo) maxDb = max(maxDb, p.second);
    vector<string> nevek;
    for (const auto& p : szamlalo)
        if (p.second == maxDb) nevek.push_back(p.first);
    cout << nevek.size() << "\n";
    for (const string& nev : nevek) cout << nev << "\n";
}

int main() {
    int n;
    cin >> n;
    string t2, e3, t4, e4;
    cin >> t2 >> e3 >> t4 >> e4;

    vector<string> tanc(n), lany(n), fiu(n);
    for (int i = 0; i < n; i++) cin >> tanc[i] >> lany[i] >> fiu[i];

    // 1. részfeladat: az első és az utolsó bemutatott tánc
    cout << "#\n" << tanc[0] << "\n" << tanc[n - 1] << "\n";

    // 2. részfeladat: a T2 tánc előfordulásainak száma
    int t2Db = 0;
    for (int i = 0; i < n; i++)
        if (tanc[i] == t2) t2Db++;
    cout << "#\n" << t2Db << "\n";

    // 3. részfeladat: az E3 személy táncai, előfordulási sorrendben
    vector<string> e3Tancai;
    for (int i = 0; i < n; i++)
        if (lany[i] == e3 || fiu[i] == e3) e3Tancai.push_back(tanc[i]);
    cout << "#\n" << e3Tancai.size() << "\n";
    for (const string& t : e3Tancai) cout << t << "\n";

    // 4. részfeladat: az E4 partnere a T4 táncban, vagy NEM
    string partner = "NEM";
    for (int i = 0; i < n; i++) {
        if (tanc[i] != t4) continue;
        if (lany[i] == e4) partner = fiu[i];
        else if (fiu[i] == e4) partner = lany[i];
    }
    cout << "#\n" << partner << "\n";

    // 5. és 6. részfeladat: hány párban szerepelt az egyes fiúk és lányok
    map<string, int> fiuDb, lanyDb;
    for (int i = 0; i < n; i++) {
        fiuDb[fiu[i]]++;
        lanyDb[lany[i]]++;
    }

    // 5. részfeladat: a résztvevő fiúk és lányok névsora
    cout << "#\n";
    cout << fiuDb.size() << "\n";
    for (const auto& p : fiuDb) cout << p.first << "\n";
    cout << lanyDb.size() << "\n";
    for (const auto& p : lanyDb) cout << p.first << "\n";

    // 6. részfeladat: a legtöbbet táncoló fiúk és lányok
    cout << "#\n";
    legtobbetTancoltak(fiuDb);
    legtobbetTancoltak(lanyDb);
    return 0;
}
