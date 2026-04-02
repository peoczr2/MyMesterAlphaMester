/*
Megoldási ötlet:
Legyen `dp[i][j]` az első `i` induló és az első `j` érkező repülő optimális közös
ütemezése. Egy állapothoz két adatot tárolunk:
- `koltseg[i][j]`: a minimális összes várakozás;
- `utolso[i][j]`: az ehhez a minimális költséghez tartozó legkisebb lehetséges utolsó
  pályahasználati időpont.

Miért elég ez az egyetlen pár? Indukcióval bizonyítható dominancia miatt.
Ha egy részmegoldás ugyanarra az `(i, j)` prefixre nem kisebb költséggel és nem korábban
fejeződik be, akkor a folytatásban sem lehet jobb: a következő gép ideje
`max(tervezett, elozo + P)`, tehát az előző idő növelése a hozzáadott várakozást sem
csökkentheti. Ezért minden prefixre elég a lexikografikusan legjobb párt megtartani:
először minimális költség, azon belül minimális befejezési idő.

Átmenetek:
- `(i-1, j)` állapotból az `i.` indulót fűzzük hozzá;
- `(i, j-1)` állapotból a `j.` érkezőt fűzzük hozzá, de csak akkor, ha a kapott idő
  nem nagyobb `Le[j] + V` értéknél.

Minden állapotot pontosan egyszer számolunk ki, és mindegyikből legfeljebb két átmenet van.

Időbonyolultság: O(NM)
Memóriaigény: O(NM)
*/
/*
Hint 1: || Tekints egy prefixet: az első `i` indulót és az első `j` érkezőt már beütemeztük. ||
Hint 2: || Egy ilyen prefix optimális megoldása csak kétféleképpen végződhet: vagy az `i.` indulóval, vagy a `j.` érkezővel. ||
Hint 3: || Ha két részmegoldás ugyanarra a prefixre közül az egyik nem drágább és nem későbbi, akkor a másik teljesen eldobható. ||
Hint 4: || Emiatt minden `(i, j)` állapothoz elég eltárolni a minimális költséget, és holtpontoknál a legkorábbi utolsó időpontot. ||
*/

#include <iostream>
#include <vector>

using namespace std;

struct Allapot {
    long long koltseg;
    long long utolso;
    bool elerheto;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int indulok_szama, erkezok_szama;
    long long varakozasi_koz, max_legi_varakozas;
    cin >> indulok_szama >> varakozasi_koz;

    vector<long long> indulas(indulok_szama + 1);
    for (int i = 1; i <= indulok_szama; ++i) {
        cin >> indulas[i];
    }

    cin >> erkezok_szama >> max_legi_varakozas;
    vector<long long> erkezes(erkezok_szama + 1);
    for (int j = 1; j <= erkezok_szama; ++j) {
        cin >> erkezes[j];
    }

    const long long INF = (1LL << 62);
    const long long NINCS = -(1LL << 60);

    vector<vector<Allapot>> dp(
        indulok_szama + 1,
        vector<Allapot>(erkezok_szama + 1, {INF, INF, false})
    );
    dp[0][0] = {0, NINCS, true};

    auto kovetkezo_ido = [&](long long elozo, long long tervezett) -> long long {
        if (elozo == NINCS) {
            return tervezett;
        }
        return max(tervezett, elozo + varakozasi_koz);
    };

    auto frissit = [&](Allapot& cel, long long uj_koltseg, long long uj_utolso) {
        if (!cel.elerheto || uj_koltseg < cel.koltseg ||
            (uj_koltseg == cel.koltseg && uj_utolso < cel.utolso)) {
            cel.elerheto = true;
            cel.koltseg = uj_koltseg;
            cel.utolso = uj_utolso;
        }
    };

    for (int i = 0; i <= indulok_szama; ++i) {
        for (int j = 0; j <= erkezok_szama; ++j) {
            if (!dp[i][j].elerheto) {
                continue;
            }

            if (i < indulok_szama) {
                long long aktualis = kovetkezo_ido(dp[i][j].utolso, indulas[i + 1]);
                frissit(dp[i + 1][j], dp[i][j].koltseg + aktualis - indulas[i + 1], aktualis);
            }

            if (j < erkezok_szama) {
                long long aktualis = kovetkezo_ido(dp[i][j].utolso, erkezes[j + 1]);
                if (aktualis <= erkezes[j + 1] + max_legi_varakozas) {
                    frissit(dp[i][j + 1], dp[i][j].koltseg + aktualis - erkezes[j + 1], aktualis);
                }
            }
        }
    }

    if (!dp[indulok_szama][erkezok_szama].elerheto) {
        cout << -1 << '\n';
    } else {
        cout << dp[indulok_szama][erkezok_szama].koltseg << '\n';
    }

    return 0;
}