/*
Megoldás lényege: a torony alja mindig a legnagyobb láda, a rá kerülő ládák méretei időben szigorúan csökkennek, ezért egy szakasz pontosan akkor pakolható egyetlen toronyba, ha a méretei mind különbözők, és a sorozat előbb szigorúan nő, majd szigorúan csökken (hegyes alak). Ez a tulajdonság részszakaszokra is öröklődik, ezért a sorozatot balról mohón kell bontani: mindig a leghosszabb ilyen szakaszt vágjuk le, és a tornyok száma a szakaszok száma. A szakasz bővítésének ellenőrzése egy utolsó előfordulás tömbbel O(1), így az egész megoldás O(N) idejű.
*/
/*
Hint 1: || Melyik láda lehet a torony alja, és a két oldalról milyen sorrendben kerülhetnek rá a többi ládák? ||
Hint 2: || Egy szakasz akkor egyetlen torony, ha a méretei különbözők, és a sorozat előbb szigorúan nő, majd szigorúan csökken. ||
Hint 3: || Ez részszakaszra is igaz, ezért balról indulva a leghosszabb jó szakaszt vágd le; az egyediséget egy utolsó előfordulás tömbbel ellenőrizd. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    int maxA = *max_element(a.begin(), a.end());
    vector<int> last(maxA + 1, -1);  // az adott méret utolsó előfordulásának indexe

    int towers = 1;   // N >= 2, ezért legalább egy torony van
    int start = 0;    // az aktuális torony első indexe
    bool up = true;   // a toronyban még tart-e a szigorúan növekvő szakasz
    for (int j = 0; j < N; ++j) {
        if (j > 0) {
            bool fits = last[a[j]] < start;  // a toronyban még nincs ilyen méretű láda
            if (fits) {
                if (up) {
                    if (a[j] < a[j - 1]) up = false;
                } else if (a[j] > a[j - 1]) {
                    fits = false;
                }
            }
            if (!fits) {
                ++towers;
                start = j;
                up = true;
            }
        }
        last[a[j]] = j;
    }

    cout << towers << '\n';
    return 0;
}
