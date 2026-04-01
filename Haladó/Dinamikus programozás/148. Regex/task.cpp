/*
Megoldási ötlet:
Mivel zárójelek csak olyan unió körül jelenhetnek meg, amelynek mindkét oldala zárójelmentes,
egy optimális reguláris kifejezés felírható egymás után konkatenált blokkokként. Egy blokk vagy
egy közös, szó szerint kiírt részsztring, vagy egyetlen `(u|v)` alakú alternatíva, ahol `u` az
`A`, `v` a `B` megfelelő darabja. Emiatt a feladat valójában arról szól, hogyan bontsuk a két
sztringet azonos számú blokkra úgy, hogy az egyenlő blokkokat egyszer írjuk ki, a különbözőket
pedig egyetlen alternációval fedjük le.

Ha egy közös blokk teljes hossza összesen `L`, és a különböző blokkok száma `U`, akkor a teljes
kifejezés hossza

    |A| + |B| - L + 3 * U

lesz, mert minden különböző blokk ára `|u| + |v| + 3`, minden közös blokk ára csak a saját hossza.
Ezért elegendő maximalizálni az

    L - 3 * U

értéket.

Dinamikus programozást használunk. Az `eq[i][j]` a legjobb érték az `A[1..i]`, `B[1..j]`
prefixekre, ha az utolsó blokk közös blokk, és pontosan az `A[i]`, `B[j]` karaktereken ér véget.
Ha `A[i] == B[j]`, akkor ezt a közös blokkot vagy folytatjuk az `eq[i-1][j-1]` állapotból,
vagy egy korábbi határ után új közös blokkot indítunk. Egy új közös blokk indítása előtt biztosan
volt egy különböző blokk, ezért ilyenkor 3 pont levonás jár. A `pref[i][j]` prefixmaximum tárolja,
hogy az eddigi téglalapban mi volt a legjobb lezárt határállapot.

Így a rekurzió:

    eq[i][j] = max(eq[i-1][j-1] + 1, pref[i-1][j-1] - 2), ha A[i] == B[j]

hiszen új közös blokk indításakor `-3 + 1 = -2` a változás. A végén vagy közös blokkal érünk a két
sztring végére, vagy egy utolsó különböző blokk zárja le a maradékot. Az algoritmus `O(|A||B|)`
idejű és gördülő sorokkal `O(|B|)` memóriát használ.
*/
/*
Hint 1: || Egy optimális kifejezésben gondolkodhatsz blokkfelbontásban: közös részeket szó szerint, eltérő részeket egyetlen `(u|v)` blokkal írjuk le. ||
Hint 2: || Ha egy közös blokk összhossza `L`, a különböző blokkok száma pedig `U`, akkor a teljes hossz `|A| + |B| - L + 3U`. Tehát nem közvetlenül a hosszt, hanem az `L - 3U` értéket érdemes maximalizálni. ||
Hint 3: || Az `eq[i][j]` legyen az a legjobb érték, amikor az utolsó blokk közös blokk, és éppen az `i`, `j` pozíciókon ér véget. ||
Hint 4: || Egy új közös blokk csak egy korábbi lezárt határ után indulhat; ehhez elég egy kétdimenziós prefixmaximumot fenntartani. ||
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace {

constexpr int NEG_INF = -1'000'000'000;

int megold(const string& a, const string& b) {
    int n = static_cast<int>(a.size());
    int m = static_cast<int>(b.size());

    vector<int> elozo_eq(m + 1, NEG_INF), aktualis_eq(m + 1, NEG_INF);
    vector<int> elozo_pref(m + 1, 0), aktualis_pref(m + 1, 0);

    elozo_eq[0] = 0;
    elozo_pref[0] = 0;
    for (int j = 1; j <= m; ++j) {
        elozo_pref[j] = 0;
    }

    for (int i = 1; i <= n; ++i) {
        aktualis_eq[0] = NEG_INF;
        aktualis_pref[0] = 0;

        for (int j = 1; j <= m; ++j) {
            aktualis_eq[j] = NEG_INF;

            if (a[i - 1] == b[j - 1]) {
                aktualis_eq[j] = max(elozo_eq[j - 1] + 1, elozo_pref[j - 1] - 2);
            }

            aktualis_pref[j] = max({elozo_pref[j], aktualis_pref[j - 1], aktualis_eq[j]});
        }

        swap(elozo_eq, aktualis_eq);
        swap(elozo_pref, aktualis_pref);
    }

    int legjobb_pont = max(elozo_eq[m], elozo_pref[m] - 3);
    return n + m - legjobb_pont;
}

}  // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tesztek = 0;
    cin >> tesztek;

    while (tesztek-- > 0) {
        string a;
        string b;
        cin >> a >> b;
        cout << megold(a, b) << '\n';
    }

    return 0;
}