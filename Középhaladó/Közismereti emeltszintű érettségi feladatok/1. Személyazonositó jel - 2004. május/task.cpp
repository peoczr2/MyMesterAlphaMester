/*
Megoldás lényege:
A személyazonosító jel első jegye a nemet és az évszázadot is megadja: 1 és 2 a 1900-as, 3 és 4 a 2000-es évekre utal, páratlan jegy férfit, páros nőt jelent.
A 2–3. jegyből az év, a 4–7. jegyből a hónap és a nap olvasható ki, a 8–10. jegyek számértéke a napon belüli sorszám.
Minden részfeladat ebből közvetlenül kiszámítható: a születésnap-szám az évek különbsége, az idősebb személy a (év, hónap, nap, sorszám) sorrend szerint kisebb.
Az ellenőrző jegy az első tíz jegy súlyozott összege (10, 9, …, 1 súlyokkal) 11-gyel vett maradéka, a 10 maradék hibás azonosítót jelent.
Az időigény konstans, mert minden kérdés néhány művelettel megválaszolható.
*/
/*
Hint 1: || Az első jegy a nemet és az évszázadot is megadja. Az 1 és 2 a 1900-as, a 3 és 4 a 2000-es évek születéseihez tartozik. ||
Hint 2: || A születési év az évszázad és a 2–3. jegyek számértékének összege. A sorszám a 8–10. jegyekből, az ellenőrző jegy az első tíz jegy súlyozott összegéből adódik, ahol az első jegy súlya 10, az utolsóé 1. ||
Hint 3: || Két ember közül az idősebbet úgy találod meg, hogy a születési évet, majd a hónapot és a napot hasonlítod össze. Azonos napon születésnél a kisebb sorszámú a korábbi születés. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A születési év az első jegy alapján dől el (1-2: 1900-as, 3-4: 2000-es évek), a 2-3. jegyek adják az évet.
int szuletesiEv(const string& id) {
    int evszazad = (id[0] - '0') <= 2 ? 1900 : 2000;
    return evszazad + stoi(id.substr(1, 2));
}

// Rendezési kulcs: a kisebb érték korábbi születést jelent.
tuple<int, int, int, int> idoKulcs(const string& id) {
    int ev = szuletesiEv(id);
    int ho = stoi(id.substr(3, 2));
    int nap = stoi(id.substr(5, 2));
    int sorszam = stoi(id.substr(7, 3));
    return make_tuple(ev, ho, nap, sorszam);
}

// Az első tíz jegy súlyozott összegének 11-gyel vett maradéka; -1 jelzi a hibás azonosítót (maradék 10).
int ellenorzoJegy(const string& id) {
    int osszeg = 0;
    for (int i = 0; i < 10; i++) osszeg += (id[i] - '0') * (10 - i);
    int maradek = osszeg % 11;
    return maradek == 10 ? -1 : maradek;
}

int main() {
    string a, b;
    int y;
    cin >> a >> b >> y;

    // 1. részfeladat: az első személy neme
    cout << "#\n";
    cout << ((a[0] - '0') % 2 == 1 ? "ferfi" : "no") << "\n";

    // 2. részfeladat: az első személy születési sorszáma
    cout << "#\n";
    cout << stoi(a.substr(7, 3)) << "\n";

    // 3. részfeladat: hányadik születésnapja van az adott évben
    cout << "#\n";
    cout << y - szuletesiEv(a) << "\n";

    // 4. részfeladat: a két születési év különbsége
    cout << "#\n";
    cout << abs(szuletesiEv(a) - szuletesiEv(b)) << "\n";

    // 5. részfeladat: az idősebb személy azonosítója
    cout << "#\n";
    cout << (idoKulcs(a) <= idoKulcs(b) ? a : b) << "\n";

    // 6. részfeladat: a második személy teljes azonosítója
    cout << "#\n";
    int ell = ellenorzoJegy(b);
    if (ell < 0) {
        cout << "hiba\n";
    } else {
        cout << b.substr(0, 10) << ell << "\n";
    }
    return 0;
}
