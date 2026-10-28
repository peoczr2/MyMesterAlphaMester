/*
Megoldás lényege:
Az előkészítő gép sorban dolgozik, így az i-edik előkészített alkatrész legyártása a prefixösszeg (az addig előkészített darabok előkészítési idejének összege) és a saját gyártási idejének összegénél fejeződik be; a teljes idő ezek maximuma. A gyártási idő szerint csökkenő sorrend optimális: két szomszédos darab felcserélésével látható, hogy a nagyobb gyártási idejű darab előrehozása sosem rontja a maximumot. Ezért az alkatrészeket gyártási idő szerint csökkenően rendezzük, majd végigszámoljuk a prefixösszegeket. Az időigény O(N log N).
*/
/*
Hint 1: || A teljes befejezési idő egy alkatrésznél az addigi előkészítési idők összege + a saját gyártási ideje. ||
Hint 2: || Az a jó, ha a nagyobb gyártási idejű darabok minél korábban kerülnek sorra. ||
Hint 3: || Elég a darabokat a gyártási idő szerint csökkenően rendezni, majd végigszámolni a prefixösszegeket. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> prep(n + 1), make(n + 1);
    for (int i = 1; i <= n; ++i) cin >> prep[i];
    for (int i = 1; i <= n; ++i) cin >> make[i];

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 1);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        if (make[a] != make[b]) return make[a] > make[b];
        return a < b;
    });

    long long prefix = 0, best = 0;
    for (int id : ord) {
        prefix += prep[id];
        best = max(best, prefix + make[id]);
    }

    cout << best << '\n';
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << ord[i];
    }
    cout << '\n';
    return 0;
}