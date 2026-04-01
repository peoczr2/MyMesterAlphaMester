/*
Megoldási ötlet:
Mindig pontosan két gép közül választhatunk: a következő induló és a következő érkező.
Legyen az utoljára kiszolgált gép időpontja `utolso`, ekkor a kifutópálya legkorábban
`utolso + P` perckor használható újra.

Ha mindkét sorrend megengedett, akkor elég a két következő jelöltet összehasonlítani.
Tegyük fel, hogy a következő induló tervezett ideje `f`, a következő érkezőé `l`, és
`f <= l`. Ha az indulót most el lehet engedni úgy, hogy utána az érkező még beleférjen
az `l + V` határidőbe, akkor az `induló, majd érkező` sorrend nem rosszabb az
`érkező, majd induló` sorrendnél: a két gép összes várakozása nem nagyobb, és a második
gépet sem fejezzük be később. Emiatt egy optimális megoldásból minden ilyen "rossz"
szomszédos pár kicserélhető, tehát létezik optimális menetrend, amelyben amikor a kisebb
tervezett idejű gép még választható, akkor azt visszük előre.

Ebből mohó algoritmus következik:
1. ha a következő érkező tervezett ideje kisebb, akkor őt kell lehozni, különben később
   csak rosszabb lenne;
2. ha a következő induló tervezett ideje kisebb vagy egyenlő, akkor csak azt kell
   ellenőrizni, hogy utána a következő érkező még le tud-e szállni időben;
3. ha igen, indulhat az induló, ha nem, akkor most kötelező az érkezőt választani;
4. ha egy érkező már most sem tud időben leszállni, akkor nincs megoldás.

Az összköltséget menet közben összeadjuk. Minden gépet egyszer dolgozunk fel.

Időbonyolultság: O(N + M)
Memóriaigény: O(N + M)
*/
/*
Hint 1: || Egyszerre mindig csak két jelölt van: a következő induló és a következő érkező. ||
Hint 2: || Vizsgáld meg két egymás melletti, felcserélhető döntés költségét: induló-utána-érkező vagy érkező-utána-induló. ||
Hint 3: || Ha a kisebb tervezett idejű gépet előre lehet venni úgy, hogy az érkező határideje nem sérül, akkor ez a csere nem ront a megoldáson. ||
Hint 4: || Ebből egy lineáris mohó szimuláció adódik, ahol csak azt kell figyelni, hogy az érkező még belefér-e az `L + V` korlátba. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int indulok_szama;
    long long varakozasi_koz;
    cin >> indulok_szama >> varakozasi_koz;

    vector<long long> indulas(indulok_szama);
    for (int i = 0; i < indulok_szama; ++i) {
        cin >> indulas[i];
    }

    int erkezok_szama;
    long long max_legi_varakozas;
    cin >> erkezok_szama >> max_legi_varakozas;

    vector<long long> erkezes(erkezok_szama);
    for (int i = 0; i < erkezok_szama; ++i) {
        cin >> erkezes[i];
    }

    int kovetkezo_indulo = 0;
    int kovetkezo_erkezo = 0;
    long long utolso_idopont = -(1LL << 60);
    long long osszes_varakozas = 0;

    auto legkorabbi = [&](long long tervezett) -> long long {
        long long szabad = utolso_idopont + varakozasi_koz;
        return max(tervezett, szabad);
    };

    while (kovetkezo_indulo < indulok_szama || kovetkezo_erkezo < erkezok_szama) {
        if (kovetkezo_indulo == indulok_szama) {
            long long aktualis = legkorabbi(erkezes[kovetkezo_erkezo]);
            if (aktualis > erkezes[kovetkezo_erkezo] + max_legi_varakozas) {
                cout << -1 << '\n';
                return 0;
            }
            osszes_varakozas += aktualis - erkezes[kovetkezo_erkezo];
            utolso_idopont = aktualis;
            ++kovetkezo_erkezo;
            continue;
        }

        if (kovetkezo_erkezo == erkezok_szama) {
            long long aktualis = legkorabbi(indulas[kovetkezo_indulo]);
            osszes_varakozas += aktualis - indulas[kovetkezo_indulo];
            utolso_idopont = aktualis;
            ++kovetkezo_indulo;
            continue;
        }

        long long kov_indulas = indulas[kovetkezo_indulo];
        long long kov_erkezes = erkezes[kovetkezo_erkezo];

        if (kov_indulas <= kov_erkezes) {
            long long indulo_ideje = legkorabbi(kov_indulas);
            long long erkezo_utani_ido = max(kov_erkezes, indulo_ideje + varakozasi_koz);

            if (erkezo_utani_ido <= kov_erkezes + max_legi_varakozas) {
                osszes_varakozas += indulo_ideje - kov_indulas;
                utolso_idopont = indulo_ideje;
                ++kovetkezo_indulo;
            } else {
                long long erkezo_ideje = legkorabbi(kov_erkezes);
                if (erkezo_ideje > kov_erkezes + max_legi_varakozas) {
                    cout << -1 << '\n';
                    return 0;
                }
                osszes_varakozas += erkezo_ideje - kov_erkezes;
                utolso_idopont = erkezo_ideje;
                ++kovetkezo_erkezo;
            }
        } else {
            long long erkezo_ideje = legkorabbi(kov_erkezes);
            if (erkezo_ideje > kov_erkezes + max_legi_varakozas) {
                cout << -1 << '\n';
                return 0;
            }
            osszes_varakozas += erkezo_ideje - kov_erkezes;
            utolso_idopont = erkezo_ideje;
            ++kovetkezo_erkezo;
        }
    }

    cout << osszes_varakozas << '\n';
    return 0;
}