/*
Megoldás:
Csak azok a helyek érdekesek, ahol valóban árulnak sajtot. Ezek sorszámait egy tömbbe gyűjtjük.
Ha legalább K ilyen hely van, akkor minden egymást követő K darabos blokkra megnézzük az első
és az utolsó hely különbségét. A legkisebb különbségű blokk adja a választ.

Az algoritmus O(N) idejű és O(N) memóriát használ a sajtárusok pozícióira.
*/
/*
Hint 1: || A 0 értékű helyeket teljesen el lehet felejteni, mert ott biztosan nem vásárolunk. ||
Hint 2: || Ha a kiválasztott szakaszban pontosan K sajtárus van, akkor az első és a K-adik sajtárus pozíciója elég a válaszhoz. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> positions;
    for (int i = 1; i <= n; ++i) {
        int value;
        cin >> value;
        if (value == 1) {
            positions.push_back(i);
        }
    }

    if (static_cast<int>(positions.size()) < k) {
        cout << -1 << ' ' << -1 << '\n';
        return 0;
    }

    int bestLeft = positions[0];
    int bestRight = positions[k - 1];
    for (int i = 0; i + k - 1 < static_cast<int>(positions.size()); ++i) {
        int currentLeft = positions[i];
        int currentRight = positions[i + k - 1];
        if (currentRight - currentLeft < bestRight - bestLeft) {
            bestLeft = currentLeft;
            bestRight = currentRight;
        }
    }

    cout << bestLeft << ' ' << bestRight << '\n';
    return 0;
}