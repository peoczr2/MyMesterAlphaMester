#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
Minden folyó legfeljebb egy másikba folyik bele, ezért a rendszer egy gyökerezett
erdő, ahol a szülő a folyásirány szerinti következő folyó. Két folyó akkor
összefolyó, ha a szülőláncaik találkoznak.

A feladat tehát egy egyszerű LCA-szituáció egy olyan fában, ahol minden csúcsnak
legfeljebb egy szülője van. Elég kiszámítani a két folyó mélységét, a mélyebbet
felhozni, majd együtt lépkedni felfelé az első közös csúcsig.

Hint 1: || A közös összefolyás a két folyó downstream szülőláncainak első közös eleme. ||
Hint 2: || Ha az egyik folyó mélyebben van, először azt kell felhozni a másik szintjére. ||
Hint 3: || Ha a két lánc mindig ugyanazon a szinten halad, az első egyező csúcs lesz a válasz. ||
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, X, Y;
    cin >> N >> M >> X >> Y;

    vector<int> parent(N + 1, 0);
    vector<vector<int>> children(N + 1);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        parent[b] = a;
        children[a].push_back(b);
    }

    auto depth = [&](int v) {
        int d = 0;
        while (v != 0) {
            ++d;
            v = parent[v];
        }
        return d;
    };

    int dx = depth(X), dy = depth(Y);
    int cx = X, cy = Y;
    int stepsX = 0, stepsY = 0;

    while (dx > dy) {
        cx = parent[cx];
        --dx;
        ++stepsX;
    }
    while (dy > dx) {
        cy = parent[cy];
        --dy;
        ++stepsY;
    }

    while (cx != 0 && cy != 0 && cx != cy) {
        cx = parent[cx];
        cy = parent[cy];
        ++stepsX;
        ++stepsY;
    }

    if (cx == 0 || cy == 0) {
        cout << "NEM\n";
    } else {
        cout << "IGEN\n";
        cout << stepsX << ' ' << stepsY << '\n';
    }
    return 0;
}