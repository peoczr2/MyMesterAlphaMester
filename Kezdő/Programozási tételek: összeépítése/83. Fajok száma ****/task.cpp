/*
Megoldás lényege:
Minden fajra a [LU, LR] zárt évintervallum az az időszak, amikor a faj élt, így az egyes években a fajszám az intervallumok lefedettsége. Az eseményeket (a LU évhez +1, a LR+1 évhez -1) rendezve végigmegyünk rajtuk, és két egymást követő esemény között a fajszám állandó, így a szakasz hossza egyszerűen kiszámolható. A maximális fajszámú szakaszok hosszait összegezzük; ha találunk nagyobb fajszámot, az eddigi összeget újraindítjuk. Az időigény O(N log N), a rendezés miatt.
*/
/*
Hint 1: || Minden faj egy [LU, LR] zárt évintervallumban élt, így az adott évben a fajszám az intervallumok lefedettsége. Nem kell minden évet külön végigvinni, elég az intervallumok kezdő és záró pontjait nézni. ||
Hint 2: || Készíts eseménylistát: a LU évhez +1, a LR+1 évhez -1 tartozik. Ha ezt az évek szerint rendezed, két egymást követő esemény között a fajszám nem változik. ||
Hint 3: || A rendezett eseményeken végigmenve minden szakasz hosszát (a következő esemény éve mínusz az aktuális év) csak akkor adod hozzá a végeredményhez, ha ott a fajszám a legnagyobb eddig látott érték; nagyobb fajszámnál a korábbi összeget ki kell nullázni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<long long, int>> esemeny;
    esemeny.reserve(2 * n);
    for (int i = 0; i < n; ++i) {
        long long lr, lu;
        cin >> lr >> lu;
        esemeny.push_back({lu, +1});
        esemeny.push_back({lr + 1, -1});
    }
    sort(esemeny.begin(), esemeny.end());

    long long aktualis = 0, legjobb = 0, evek = 0;
    size_t i = 0;
    while (i < esemeny.size()) {
        long long x = esemeny[i].first;
        while (i < esemeny.size() && esemeny[i].first == x) {
            aktualis += esemeny[i].second;
            ++i;
        }
        if (i == esemeny.size()) break;
        long long hossz = esemeny[i].first - x;
        if (aktualis == 0) continue;
        if (aktualis > legjobb) {
            legjobb = aktualis;
            evek = hossz;
        } else if (aktualis == legjobb) {
            evek += hossz;
        }
    }

    cout << evek << '\n';
    return 0;
}
