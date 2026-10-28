/*
Megoldás lényege:
A vonatok a bemenetben már indulási idő szerint növekvően vannak megadva, ezért egyetlen végigmenéssel
dolgozhatunk, gráfot nem kell építeni. Minden állomásra nyilvántartjuk a legkorábbi érkezési időt: az
első állomáson 0-t (bármikor szállhatunk), a többin végtelent. Egy vonatra akkor tudunk felszállni, ha a
kiindulási állomáson már a vonat indulása előtt, szigorúan kisebb időpontban megérkeztünk. Ilyenkor a
vonat célállomásának legkorábbi érkezési ideje a vonat érkezési idejére javulhat. Korábbi érkezés soha
nem rosszabb, mert onnan legalább olyan vonatokat érünk el, mint később, így a végén a végállomás értéke
adja a választ, vagy -1, ha nem érhető el. Az idő O(M).
*/
/*
Hint 1: || Nem kell gráfot építened: a vonatok indulási idő szerint már rendezve vannak, egyszer végigmehetsz rajtuk. ||
Hint 2: || Tartsd nyilván minden állomásra a legkorábbi érkezési időt. Ha egy vonat indulásakor már a kiindulási állomáson vagy, a célállomás értékét frissítheted a vonat érkezési idejével. ||
Hint 3: || Kezdetben az első állomáson 0 az idő, a többi állomáson végtelen. Mivel a szállás csak szigorúan korábbi érkezéssel lehetséges, az azonos időpont nem elég az átszálláshoz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    const long long INF = LLONG_MAX / 4;
    vector<long long> best(n + 1, INF);
    best[1] = 0;
    for (int i = 0; i < m; i++) {
        int a, b;
        long long ind, erk;
        cin >> a >> b >> ind >> erk;
        if (best[a] < ind) {
            best[b] = min(best[b], erk);
        }
    }
    if (best[n] >= INF) {
        cout << -1 << "\n";
    } else {
        cout << best[n] << "\n";
    }
    return 0;
}
