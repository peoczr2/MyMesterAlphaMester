/*
Tejeskocsik

Feladat: N termelő érkezési sorrendben hozza a tejet a begyűjtőpontra, egy időpontban legfeljebb ketten.
A tejet csak a beérkezés sorrendjében lehet elszállítani, egy termelő teje nem osztható szét két kocsi
között, egy kocsiba legfeljebb K tej fér, és minden tejet a beérkezéstől számított legfeljebb T időn
belül el kell vinni. Legalább hány tejeskocsi kell?

Megoldás: A sorrend miatt egy kocsi a termelők egy összefüggő szakaszát viszi el. Egy szakasz akkor
vihető el egy kocsival, ha az összege legfeljebb K, és az utolsó és az első érkezés különbsége legfeljebb
T (a kocsi az utolsó érkezéskor indul). Az ugyanabban az időpontban érkező két termelő között nincs
sorrend, ezért kettejük sorrendje szabadon választható (a 2. minta eredménye is csak így jön ki).
Mohón haladunk: minden kocsiba a lehető legtöbb termelőt rakjuk. Ha egy kocsi vége egy egyszerre érkezett
pár közé esik (csak az egyikük fér be), akkor a nagyobb, még beférő tétel kerül ebbe a kocsiba, a kisebb
pedig a következő kocsi elejére. A mohó lépés után mindig kevesebb (vagy könnyebb) tej marad hátra, mint
bármely más választás után, így a hátralévő rész sem lehet rosszabb: a mohó optimális.

Időigény: O(N).
*/
/*
Hint 1: || A beérkezési sorrend miatt egy kocsi a termelők egy összefüggő szakaszát viszi el. ||
Hint 2: || Egy szakasz akkor jó, ha az összege legfeljebb K, és az első és az utolsó érkezés között legfeljebb T idő telt el. ||
Hint 3: || Mindig a lehető leghosszabb szakaszt tedd egy kocsiba. ||
Hint 4: || Az egyszerre érkező két termelő sorrendje felcserélhető: ha csak az egyikük fér be, a nagyobbat vidd a mostani kocsival. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // beolvasás
    int n, K, T;
    cin >> n >> K >> T;
    vector<int> e(n), m(n);
    for (int i = 0; i < n; i++) cin >> e[i] >> m[i];

    int kocsik = 0;
    int i = 0;               // az első még fel nem rakott termelő
    bool vanMarad = false;   // maradt-e egy kettévágott pár egyik tagja
    int maradIdo = 0, maradTej = 0;

    while (i < n || vanMarad) {
        // új kocsi: az eleje a maradék tétel vagy a következő termelő
        kocsik++;
        int kezdet, terheles = 0;
        if (vanMarad) {
            kezdet = maradIdo;
            terheles = maradTej;
            vanMarad = false;
        } else {
            kezdet = e[i];
        }

        // bővítés időpontonként (egy időpontban 1 vagy 2 termelő érkezik)
        while (i < n && e[i] - kezdet <= T) {
            bool par = (i + 1 < n && e[i + 1] == e[i]);
            if (!par) {
                if (terheles + m[i] > K) break;
                terheles += m[i];
                i++;
                continue;
            }
            int nagy = max(m[i], m[i + 1]), kicsi = min(m[i], m[i + 1]);
            if (terheles + nagy + kicsi <= K) {   // mindkettő befér
                terheles += nagy + kicsi;
                i += 2;
                continue;
            }
            // csak az egyik fér be: lehetőleg a nagyobbat visszük, a másik a következő kocsié
            if (terheles + nagy <= K) maradTej = kicsi;
            else if (terheles + kicsi <= K) maradTej = nagy;
            else break;                            // egyik sem fér be
            maradIdo = e[i];
            vanMarad = true;
            i += 2;
            break;
        }
    }

    // kiírás
    cout << kocsik << '\n';
    return 0;
}
