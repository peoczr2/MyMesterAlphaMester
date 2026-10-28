/*
Megoldás lényege:
Napról napra beolvassuk a kereskedéseket, és részvényenként, illetve naponként összegzünk. Részvényenként nyilvántartjuk, volt-e forgalma, minden forgalmazott napon-e emelkedett az árfolyam (kezdő ár < záró ár), és mekkora volt a napi legnagyobb és legkisebb eladási ár különbsége a legnagyobb értékben. Naponként megszámoljuk a forgalmazott fajtákat, és a napi (záró - kezdő) különbségek összegéből kapjuk a napi veszteséget, ha az negatív.
Ezekből az egyes kérdések egyszerű maximum-, minimum- és számlálási feladatok. Az időigény O(N * R), ami a kis korlátok miatt bőven belefér.
*/
/*
Hint 1: || Napi bontásban dolgozz: minden napnál tudnod kell, hány részvénnyel kereskedtek, és az egyes kereskedéseknél a kezdő, záró, legolcsóbb és legdrágább ár. Az egyes részvényekre külön tömbökben gyűjts adatokat. ||
Hint 2: || A semleges részvények száma: R-ből vond ki azoknak a részvényeknek a számát, amelyeknek legalább egy napon volt forgalma. A stabilitás mérőszáma részvényenként az összes forgalmazott napra vett maximális (legdrágább - legolcsóbb) különbség. ||
Hint 3: || A felfutó részvénynél minden forgalmazott napon ellenőrizd, hogy a kezdő ár kisebb-e a záró árnál. A napi veszteség a napi (záró - kezdő) különbségek összege, ha ez negatív, és a legnagyobb veszteségű nap előfordulásakor válassz a legkorábbit. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Kereskedes {
    int resz, nyito, zaro, legolcsobb, legdragabb;
};

int main() {
    int N, R;
    cin >> N >> R;

    vector<vector<Kereskedes>> nap(N);
    for (int d = 0; d < N; d++) {
        int k;
        cin >> k;
        nap[d].resize(k);
        for (auto &x : nap[d])
            cin >> x.resz >> x.nyito >> x.zaro >> x.legolcsobb >> x.legdragabb;
    }

    vector<bool> forgalmazott(R + 1, false);
    vector<bool> felfuto(R + 1, true);
    vector<long long> legnagyobbKulonbseg(R + 1, LLONG_MIN);
    for (int d = 0; d < N; d++)
        for (auto &x : nap[d]) {
            forgalmazott[x.resz] = true;
            if (x.nyito >= x.zaro) felfuto[x.resz] = false;
            legnagyobbKulonbseg[x.resz] = max(legnagyobbKulonbseg[x.resz],
                                              (long long)x.legdragabb - x.legolcsobb);
        }

    // 1. részfeladat: semleges részvények száma
    cout << "#\n";
    int semleges = 0;
    for (int s = 1; s <= R; s++)
        if (!forgalmazott[s]) semleges++;
    cout << semleges << "\n";

    // 2. részfeladat: a legunalmasabb nap (legkevesebb fajta, de volt forgalom)
    cout << "#\n";
    int unalmasNap = -1;
    int legkevesebbFajta = INT_MAX;
    for (int d = 0; d < N; d++)
        if (!nap[d].empty() && (int)nap[d].size() < legkevesebbFajta) {
            legkevesebbFajta = nap[d].size();
            unalmasNap = d + 1;
        }
    cout << unalmasNap << "\n";

    // 3. részfeladat: a legstabilabb forgalomban levő részvény
    cout << "#\n";
    int stabil = -1;
    for (int s = 1; s <= R; s++)
        if (forgalmazott[s] && (stabil < 0 || legnagyobbKulonbseg[s] < legnagyobbKulonbseg[stabil]))
            stabil = s;
    cout << stabil << "\n";

    // 4. részfeladat: felfutó részvények
    cout << "#\n";
    for (int s = 1; s <= R; s++)
        if (forgalmazott[s] && felfuto[s]) cout << s << "\n";

    // 5. részfeladat: a legrosszabb munkanap és a veszteség
    cout << "#\n";
    int rosszNap = -1;
    long long legnagyobbVesztes = 0;
    for (int d = 0; d < N; d++) {
        long long osszeg = 0;
        for (auto &x : nap[d]) osszeg += (long long)x.zaro - x.nyito;
        long long vesztes = osszeg < 0 ? -osszeg : 0;
        if (vesztes > legnagyobbVesztes) {
            legnagyobbVesztes = vesztes;
            rosszNap = d + 1;
        }
    }
    if (rosszNap < 0) cout << "-1\n";
    else cout << rosszNap << "\n" << legnagyobbVesztes << "\n";

    return 0;
}
