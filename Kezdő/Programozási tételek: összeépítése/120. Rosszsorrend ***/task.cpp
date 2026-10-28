/*
Megoldás lényege: a rossz sorrendű pár (i < j, a_i > a_j) akkor a legtávolabbi, ha a bal oldali elem a lehető legkorábbi.
Egy adott a_j-hez tehát az első olyan i indexet keressük, amelyre a_i > a_j. A sorozat prefixmaximumai balról jobbra nemcsökkenők,
ezért az első olyan index, ahol a prefixmaximum már nagyobb a_j-nél, bináris kereséssel megtalálható, és ott a_i maga a prefixmaximum.
Minden j-re ezt megvizsgálva megkapjuk a globális legnagyobb távolságot. Ha nincs rossz sorrendű pár, a sorozat rendezett, és -1 a válasz.
Időigény: O(N log N), N <= 500 000 mellett bőven belül van.
*/
/*
Hint 1: || Egy adott jobb oldali a_j elemhez a lehető legtávolabbi bal oldali társ az első olyan elem, amely nagyobb a_j-nél. ||
Hint 2: || Tartsd nyilván a sorozat prefixmaximumait: ezek balról jobbra nemcsökkenő sorozatot alkotnak, így az első olyan index bináris kereséssel megtalálható. ||
Hint 3: || Minden j-re (j >= 1) számold ki ezt az i-t, és ha i < j, a j-i távolságot hasonlítsd a legjobbhoz. Ha egyszer sincs ilyen pár, a válasz -1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int &v : a) cin >> v;

    // elore[i]: az a[0..i] részsorozat legnagyobb eleme (nemcsökkenő)
    vector<int> elore(n);
    for (int i = 0; i < n; i++) elore[i] = (i == 0) ? a[0] : max(elore[i - 1], a[i]);

    int legtavolabb = -1, bi = -1, bj = -1;
    for (int j = 1; j < n; j++) {
        // a legkisebb i, amelyre elore[i] > a[j]; ekkor a[i] = elore[i]
        int i = upper_bound(elore.begin(), elore.begin() + j, a[j]) - elore.begin();
        if (i < j && j - i > legtavolabb) {
            legtavolabb = j - i;
            bi = i;
            bj = j;
        }
    }

    if (legtavolabb < 0) {
        cout << -1 << "\n";
    } else {
        // a minta szerint a második sorba a két elem távolsága kerül
        cout << a[bi] << " " << a[bj] << "\n" << legtavolabb << "\n";
    }
    return 0;
}
