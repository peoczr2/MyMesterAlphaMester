/*
Megoldás lényege:
Egy termék haszna az (eladási ár - beszerzési ár) szorozva az eladások számával, és ez negatív is lehet. Mind az N termék hasznát kiszámoljuk, csökkenő sorrendbe rendezzük, majd kiírjuk az első K értéket. A beszerzési ár szerinti rendezésre nincs szükség, mert a haszon közvetlenül a sorban szereplő három számból adódik. Az időigény O(N log N), ami a korlátok mellett nyilvánvalóan elég.
*/
/*
Hint 1: || Egy termék haszna a fajlagos nyereség (eladási és beszerzési ár különbsége) szorozva az eladott darabszámmal. ||
Hint 2: || Számold ki minden termék hasznát egy tömbbe; a legnagyobb K érték megkereséséhez elég a tömböt csökkenő sorrendbe rendezni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<long long> haszon(n);
    for (int i = 0; i < n; ++i) {
        long long beszerzes, eladas, db;
        cin >> beszerzes >> eladas >> db;
        haszon[i] = (eladas - beszerzes) * db;
    }

    sort(haszon.begin(), haszon.end(), greater<long long>());
    for (int i = 0; i < k; ++i) {
        if (i) cout << ' ';
        cout << haszon[i];
    }
    cout << '\n';
    return 0;
}
