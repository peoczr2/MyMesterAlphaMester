/*
Megoldás lényege:
A bemenet elején a kulcsszót szóként, utána a K értéket egész számként olvassuk be. Ezután a kategóriákat soronként, a nevük, a túlélők és az eltűntek számának hármasaként dolgozzuk fel, és közben összegezzük a kategóriák számát és az utasok összlétszámát. A kulcsszót a név részsztringjeként keressük, az összes utas a túlélők és az eltűntek összege. Az eltűntek arányát egész aritmetikával vizsgáljuk: az eltűntek száma szorozva százzal akkor haladja meg a K százalékot, ha nagyobb, mint K szorozva az utasok számával, így nincs lebegőpontos hiba. A legtöbb túlélővel rendelkező kategóriákat két menetben határozzuk meg: először a maximumot keressük, majd a bemenet sorrendjében kiírjuk az összes olyan kategóriát, ahol ez szerepel. Az időigény O(M), ahol M a kategóriák száma, a memóriaigény O(M).
*/
/*
Hint 1: || A kulcsszót és a K értéket szóközök vagy sortörések választják el, ezért mindkettőt szóként olvasd be a cin-ből. A kategóriák számát egyszerűen az olvasott hármasok darabszámából kapod meg, a bemenet végéig olvass. ||
Hint 2: || A kulcsszó részlet kereséséhez a string find függvénye adja a megoldást: ha a találat pozíciója nem string::npos, a név tartalmazza a kulcsszót. A kiírt szám a kategória utasainak összlétszáma, vagyis a túlélők és az eltűntek összege. ||
Hint 3: || Az arány vizsgálatánál ne számolj törtet: az eltűntek száma szorozva százzal legyen nagyobb, mint K szorozva az utasok számával. A legtöbb túlélőnél először keresd meg a maximumot, majd írd ki sorrendben az összes olyan kategóriát, amelyben ez a maximum szerepel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string kulcsszo;
    long long K;
    cin >> kulcsszo >> K;

    vector<string> nevek;
    vector<long long> tulelok, eltuntek;
    string nev;
    long long tul, elt;
    while (cin >> nev >> tul >> elt) {
        nevek.push_back(nev);
        tulelok.push_back(tul);
        eltuntek.push_back(elt);
    }
    int m = nevek.size();

    // 1. részfeladat: a kategóriák száma
    cout << "#\n";
    cout << m << "\n";

    // 2. részfeladat: az utasok összlétszáma
    long long osszes = 0;
    for (int i = 0; i < m; i++) {
        osszes += tulelok[i] + eltuntek[i];
    }
    cout << "#\n";
    cout << osszes << "\n";

    // 3. részfeladat: a kulcsszót tartalmazó kategóriák és utasaik száma
    cout << "#\n";
    for (int i = 0; i < m; i++) {
        if (nevek[i].find(kulcsszo) != string::npos) {
            cout << nevek[i] << " " << tulelok[i] + eltuntek[i] << "\n";
        }
    }

    // 4. részfeladat: a K százaléknál nagyobb eltűnt arányú kategóriák
    cout << "#\n";
    for (int i = 0; i < m; i++) {
        long long utasok = tulelok[i] + eltuntek[i];
        if (eltuntek[i] * 100 > K * utasok) {
            cout << nevek[i] << "\n";
        }
    }

    // 5. részfeladat: a legtöbb túlélővel rendelkező kategóriák
    long long legtobb = LLONG_MIN;
    for (int i = 0; i < m; i++) {
        legtobb = max(legtobb, tulelok[i]);
    }
    cout << "#\n";
    for (int i = 0; i < m; i++) {
        if (tulelok[i] == legtobb) {
            cout << nevek[i] << "\n";
        }
    }

    return 0;
}
