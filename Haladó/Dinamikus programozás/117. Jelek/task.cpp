/*
Megoldási ötlet:
Két különböző kezdőpozícióból induló azonos folytonos rész hossza a két suffix leghosszabb közös prefixe.
Legyen lcp[i][j] ez a hossz az i. és j. pozícióról indulva. Ekkor lcp[i][j] = 1 + lcp[i+1][j+1], ha az aktuális
jelek megegyeznek, különben 0.

Az egész táblát nem kell eltárolni: csak a következő sorra van szükség, ezért gördülő tömbbel O(N) memóriából
megoldható. Minden i<j párnál frissítjük a legjobb ismétlődő rész hosszát, holtversenyben pedig a korábbi kezdést
választjuk.
*/
/*
Hint 1: || Egy ismétlődő folytonos rész két különböző suffix közös prefixeként jelenik meg. ||
Hint 2: || Ha a két aktuális szám azonos, akkor a közös prefix hossza egy plusz a következő pozíciók LCP-je. ||
Hint 3: || A teljes NxN tábla helyett elég két sor, mert csak az i+1 sor j+1 oszlopára hivatkozol. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    vector<int> nextRow(n + 1, 0), currentRow(n + 1, 0);
    int bestLen = 0;
    int bestStart = -1;

    for (int i = n - 1; i >= 0; --i) {
        fill(currentRow.begin(), currentRow.end(), 0);
        for (int j = n - 1; j > i; --j) {
            if (a[i] == a[j]) currentRow[j] = nextRow[j + 1] + 1;
            if (currentRow[j] > bestLen || (currentRow[j] == bestLen && currentRow[j] > 0 && i < bestStart)) {
                bestLen = currentRow[j];
                bestStart = i;
            }
        }
        swap(currentRow, nextRow);
    }

    if (bestLen == 0) {
        cout << -1 << '\n';
        return 0;
    }

    for (int i = 0; i < bestLen; ++i) {
        if (i > 0) cout << ' ';
        cout << a[bestStart + i];
    }
    cout << '\n';
    return 0;
}