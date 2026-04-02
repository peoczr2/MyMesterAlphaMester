/*
Megoldás:
Ha az i-edik sort r[i]-szer, a j-edik oszlopot c[j]-szer kapcsoljuk (0 vagy 1 alkalommal), akkor
az (i,j) lámpa állapota r[i] xor c[j] lesz. Tehát a célmátrixnak ilyen alakúnak kell lennie.

Válasszuk r[1]=0-t. Ekkor c[j] az első sorból, r[i] pedig az első oszlopból egyértelműen kiszámítható,
és utána ellenőrizhető, hogy minden cellára teljesül-e a formula. Ha igen, ez egy megoldás.
A másik lehetséges megoldás ennek a komplementere, amikor minden r és c bitet megfordítunk.
E két megoldás közül a kevesebb kapcsolást igénylőt kell választani.

Az algoritmus O(N*M) időben ellenőriz mindent, és csak az első sort meg az első oszlopot tárolja.
*/
/*
Hint 1: || A lámpa végső állapotát csak az dönti el, hogy az adott sor és oszlop kapcsolásainak paritása mi. ||
Hint 2: || Ha az első sor egyik elemét ismered, abból már az összes oszlopbit kiszámítható. ||
Hint 3: || Az egyik megoldás komplementere is megoldás, ezért elég kettő közül minimumot venni. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> firstRow(m);
    vector<int> firstColumn(n);

    for (int j = 0; j < m; ++j) {
        cin >> firstRow[j];
    }
    firstColumn[0] = firstRow[0];

    bool ok = true;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int value;
            cin >> value;
            if (j == 0) {
                firstColumn[i] = value;
            }
            if ((value ^ firstColumn[i] ^ firstRow[j] ^ firstRow[0]) != 0) {
                ok = false;
            }
        }
    }

    if (!ok) {
        cout << -1 << '\n';
        return 0;
    }

    long long toggles = 0;
    for (int i = 1; i < n; ++i) {
        toggles += firstColumn[i] ^ firstRow[0];
    }
    for (int j = 0; j < m; ++j) {
        toggles += firstRow[j];
    }

    cout << min(toggles, 1LL * n + m - toggles) << '\n';
    return 0;
}