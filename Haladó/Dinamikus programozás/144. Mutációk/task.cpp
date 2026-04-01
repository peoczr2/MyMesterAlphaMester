/*
Megoldási ötlet:
Tekintsük a feladatot szerkesztési távolságnak. Egy megtartott betű vagy változatlan marad,
vagy pontosan egy mutációval az ábécében közvetlenül előtte vagy utána álló betűvé alakulhat
(körkörösen), ennek ára 1. A mondat, hogy egy helyen csak egyféle mutáció történhet, azt
jelenti, hogy ugyanazon a pozíción nem lépkedhetünk végig többször az ábécében: ha a két betű
nem azonos és nem szomszédos, akkor közvetlen átírás nem használható. A beszúrás ára mindig 2,
két szomszédos betű felcserélése 3, a törlés ára viszont attól függ, hogy a jelenlegi kód
elejéről vagy végéről törlünk-e: ott 1, belül 2.

Ezért nem elég a szokásos edit distance. A dinamikus programozásban azt számoljuk,
hogy egy valódi "belső" illesztési szakaszt már elkezdtünk-e. Az illesztés megkezdése
előtt az első kód prefixéből bármit törölhetünk 1 energiáért, és a második kód prefixébe
szabadon szúrhatunk be betűket 2 energiáért. Miután a belső szakasz elindult, már a
szokásos költségek élnek: törlés 2, beszúrás 2, átírás csak azonos vagy szomszédos betűre,
pontos szomszédcsere 3. Bármely DP-állapotból befejezhetjük a megoldást úgy, hogy az első
kód megmaradt suffixét a végéről 1-ért töröljük, a második kód hiányzó suffixét pedig 2-ért
beszúrjuk.

A `dp[i][j]` jelentése: ennyi a legkisebb költség, ha az első kód első `i` betűjét és a
második kód első `j` betűjét már feldolgoztuk, és a belső illesztési szakasz már biztosan
elkezdődött. A kezdet előtti olcsó prefix-kezelés külön képletből jön: `i + 2*j`.
A válasz a DP bármely állapotából lezárható suffixköltséggel együtt minimumként adódik.
Az algoritmus `O(MN)` időt és gördülő sorokkal `O(N)` memóriát használ.
*/
/*
Hint 1: || Két megtartott betűt csak akkor érdemes közvetlenül egymáshoz illeszteni, ha azonosak, vagy körkörösen szomszédosak az ábécében. ||
Hint 2: || A prefixről és suffixről törölt betűk olcsóbbak, ezért érdemes külön kezelni a "még nem kezdtem el a belső illesztést" és a "már benne vagyok" helyzeteket. ||
Hint 3: || Ha már a belső szakaszban vagy, akkor a klasszikus műveletek maradnak: törlés, beszúrás, átírás, valamint egy pontos szomszédcsere. ||
Hint 4: || Nem kell teljes kétdimenziós táblát tárolni: a csere miatt legfeljebb az előző két sorra van szükség. ||
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace {

constexpr int INF = 1'000'000'000;

int atiras_koltseg(char from, char to) {
    if (from == to) {
        return 0;
    }

    int from_idx = from - 'a';
    int to_idx = to - 'a';
    if ((from_idx + 1) % 26 == to_idx || (from_idx + 25) % 26 == to_idx) {
        return 1;
    }

    return INF;
}

}  // namespace

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m = 0;
    int n = 0;
    string elso;
    string masodik;

    cin >> m >> elso >> n >> masodik;

    vector<int> elozo_ketto(n + 1, INF);
    vector<int> elozo(n + 1, INF);
    vector<int> aktualis(n + 1, INF);

    int valasz = m + 2 * n;

    for (int i = 1; i <= m; ++i) {
        fill(aktualis.begin(), aktualis.end(), INF);

        for (int j = 1; j <= n; ++j) {
            int koltseg = INF;
            int betu_koltseg = atiras_koltseg(elso[i - 1], masodik[j - 1]);
            int olcso_prefix = (i - 1) + 2 * (j - 1);

            koltseg = min(koltseg, elozo[j] + 2);
            koltseg = min(koltseg, aktualis[j - 1] + 2);
            koltseg = min(koltseg, elozo[j - 1] + betu_koltseg);
            koltseg = min(koltseg, olcso_prefix + betu_koltseg);

            if (i >= 2 && j >= 2 && elso[i - 2] == masodik[j - 1] && elso[i - 1] == masodik[j - 2]) {
                int olcso_prefix_csere = (i - 2) + 2 * (j - 2);
                koltseg = min(koltseg, elozo_ketto[j - 2] + 3);
                koltseg = min(koltseg, olcso_prefix_csere + 3);
            }

            aktualis[j] = koltseg;

            int suffix_koltseg = (m - i) + 2 * (n - j);
            valasz = min(valasz, aktualis[j] + suffix_koltseg);
        }

        elozo_ketto.swap(elozo);
        elozo.swap(aktualis);
    }

    cout << valasz << '\n';
    return 0;
}