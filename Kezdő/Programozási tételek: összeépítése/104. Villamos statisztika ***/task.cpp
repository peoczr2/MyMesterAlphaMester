/*
Megoldás lényege:
Az állapot egyetlen szám: a villamoson lévő utasok száma. Állomásonként először a leszállókat vonjuk le, majd a felszállókat adjuk hozzá. Hibás a bemenet, ha valahol többen szállnának le, mint amennyien a villamoson voltak, ha a végállomáson van felszálló, vagy ha a végállomás után marad utas. Ha az adatok helyesek, az összes utas a felszállók összege, a legnagyobb utasszám az állapot maximuma, a végén üres állomások azok, ahol volt leszálló és nem maradt senki, az üres szakaszok száma pedig azon állomások száma, amelyek után (az utolsó kivételével) nincs utas. A bemenetet egyetlen bejárással, O(N) időben dolgozzuk fel.
*/
/*
Hint 1: || Követd végig az utasok számát állomásról állomásra: egy változó tárolja, hány utas van most a villamoson. Minden állomáson előbb a leszállókat vonod le, utána a felszállókat adod hozzá. ||
Hint 2: || Hibás a bemenet, ha valahol többen szállnának le, mint amennyien a villamoson voltak, ha az első állomáson van leszálló, ha a végállomáson van felszálló, vagy ha a végállomás után marad utas. Ezeket egy-egy feltétellel ellenőrizheted. ||
Hint 3: || Az összes utas a felszállók összege, a legnagyobb utasszám az utasváltozó maximuma. Az üres állomás az, ahol a leszállás után nincs senki, de előtte volt utas; az üres szakaszok száma pedig azoknak az állomásoknak a száma, amelyek után az utolsó előtti állomásig nincs utas. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    bool helyes = true;
    long long utasok = 0;       // a villamoson lévő utasok száma
    long long osszes = 0;       // az összes felszálló utas
    long long maxUtas = 0;      // a legtöbb egyszerre utazó
    long long ureSzakasz = 0;   // üresen megtett állomásközi szakaszok
    vector<int> urites;         // állomások, ahol mindenki leszállt

    for (int i = 1; i <= n; ++i) {
        long long fel, le;
        cin >> fel >> le;

        long long elotte = utasok;
        if (le > elotte) helyes = false;
        utasok = elotte - le + fel;
        osszes += fel;

        if (i == n && (fel != 0 || utasok != 0)) helyes = false;
        if (utasok == 0 && elotte > 0) urites.push_back(i);
        if (i < n && utasok == 0) ++ureSzakasz;
        maxUtas = max(maxUtas, utasok);
    }

    if (!helyes) {
        cout << "HIBA\nHIBA\nHIBA\nHIBA\n";
        return 0;
    }

    cout << osszes << '\n';
    for (size_t i = 0; i < urites.size(); ++i) {
        if (i) cout << ' ';
        cout << urites[i];
    }
    cout << '\n' << maxUtas << '\n' << ureSzakasz << '\n';
    return 0;
}
