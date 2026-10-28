/*
Megoldás lényege:
A jegyek sorban, egyenként feldolgozhatók: egy jegy ára a megkezdett 10 km-ek száma szorozva a 10 km-enkénti összeggel, majd az öttel osztható számra kerekítve.
Az 1., 2. és 3. részfeladat egyszerű kiválogatás és összegzés, a teljes utat megtevők a Fel = 0 és Le = Hossz feltételt teljesítik.
A megállók a Fel és Le értékek halmaza, így a végállomás előtti utolsó megálló a Hossz-nál kisebb értékek legnagyobbja, a megállók száma pedig a különböző köztes értékek darabszáma.
Az út adott Táv pontján egy ülést az a jegy foglalja el, amelyre Fel <= Táv < Le teljesül, így a felszállók számítanak, a leszállók nem.
A megoldás lineáris idejű az eladott jegyek számában.
*/
/*
Hint 1: || A jegy ára a megkezdett 10 km-ek számából számolható: (Le - Fel) felfelé kerekítve 10-zel osztva, ezt szorozd meg a 10 km-enkénti összeggel, majd kerekítsd az öttel osztható számra a feladat szabálya szerint. ||
Hint 2: || Egy ülés a Táv pontban akkor foglalt, ha a jegy Fel értéke kisebb vagy egyenlő a Táv-nál, és a Le értéke nagyobb a Táv-nál. A megállók a Fel és Le értékek halmaza; a végállomás előtti utolsó megálló a Hossz-nál kisebb értékek maximuma. ||
Hint 3: || A megállók számánál a kiinduló pontot (0) és a végállomást (Hossz) ne számold bele; a köztes Fel és Le értékeket egy set-ben gyűjtsd, a set mérete adja az 5. részfeladat válaszát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, hossz, osszeg;
    cin >> n >> hossz >> osszeg;
    int tav;
    cin >> tav;
    vector<int> ules(n), fel(n), le(n);
    for (int i = 0; i < n; i++) cin >> ules[i] >> fel[i] >> le[i];

    // 1. részfeladat: az utolsó jegyvásárló ülése és beutazott távolsága
    cout << "#\n";
    cout << ules[n - 1] << " " << le[n - 1] - fel[n - 1] << "\n";

    // 2. részfeladat: a teljes utat végigutazók sorszáma
    vector<int> teljes;
    for (int i = 0; i < n; i++)
        if (fel[i] == 0 && le[i] == hossz) teljes.push_back(i + 1);
    cout << "#\n";
    cout << teljes.size();
    for (int x : teljes) cout << " " << x;
    cout << "\n";

    // 3. részfeladat: a bevétel
    long long bevetel = 0;
    for (int i = 0; i < n; i++) {
        long long km = (le[i] - fel[i] + 9) / 10;
        long long ar = km * osszeg;
        long long r = ar % 5;
        if (r == 1 || r == 2) ar -= r;
        else if (r == 3 || r == 4) ar += 5 - r;
        bevetel += ar;
    }
    cout << "#\n" << bevetel << "\n";

    // 4. részfeladat: a végállomást megelőző utolsó megálló felszállói és leszállói
    int megallo = -1;
    for (int i = 0; i < n; i++) {
        if (fel[i] < hossz) megallo = max(megallo, fel[i]);
        if (le[i] < hossz) megallo = max(megallo, le[i]);
    }
    int felszall = 0, leszall = 0;
    for (int i = 0; i < n; i++) {
        if (fel[i] == megallo) felszall++;
        if (le[i] == megallo) leszall++;
    }
    cout << "#\n" << felszall << " " << leszall << "\n";

    // 5. részfeladat: megállások száma a kiinduló és a célállomás között
    set<int> allomasok;
    for (int i = 0; i < n; i++) {
        if (fel[i] > 0 && fel[i] < hossz) allomasok.insert(fel[i]);
        if (le[i] > 0 && le[i] < hossz) allomasok.insert(le[i]);
    }
    cout << "#\n" << allomasok.size() << "\n";

    // 6. részfeladat: a Táv pontban elfoglalt ülések utasainak sorszáma
    vector<int> foglalt(49, 0);
    for (int i = 0; i < n; i++)
        if (fel[i] <= tav && tav < le[i]) foglalt[ules[i]] = i + 1;
    cout << "#\n";
    for (int s = 1; s <= 48; s++) cout << foglalt[s] << (s < 48 ? " " : "\n");

    return 0;
}
