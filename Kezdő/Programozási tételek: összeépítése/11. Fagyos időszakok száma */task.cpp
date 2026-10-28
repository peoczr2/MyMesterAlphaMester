/*
Megoldás lényege:
Egy fagyos időszak a negatív értékek olyan maximális, összefüggő szakasza, amelyet se balra, se jobbra nem lehet bővíteni. Balról jobbra haladva elég számolni az átmeneteket: ha egy negatív mérést olvasunk, és az előző nap nem volt negatív, akkor egy új fagyos időszak kezdődik. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Új fagyos időszak akkor kezdődik, amikor negatív értéket látunk, és az előző érték nem volt negatív. ||
Hint 2: || Tartsunk egy logikai változót az előző nap állapotáról, és csak a "nem negatív -> negatív" átmenetnél növeljük a számlálót. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int periods = 0;
    bool prevFrozen = false;
    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        bool frozen = m < 0;
        if (frozen && !prevFrozen) ++periods;
        prevFrozen = frozen;
    }

    cout << periods << '\n';
    return 0;
}
