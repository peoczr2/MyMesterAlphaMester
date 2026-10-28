/*
Megoldás lényege:
Minden folyó legfeljebb egy másikba folyik bele, ezért a folyók gyökerezett erdőt
alkotnak, ahol a szülő a folyásirány szerinti következő folyó. Két folyó akkor folyik
össze, ha a szülőláncaik első közös csúcsban találkoznak. Ez egy LCA-feladat: kiszámítjuk
a két folyó mélységét, a mélyebbet a másik szintjére hozzuk, majd együtt lépkedünk
felfelé az első közös csúcsig. A kiírt két szám az egyes folyók által az összefolyásig
megtett lépések száma. Az időigény O(N), mert egy lekérdezés láncai legfeljebb N hosszúak.
*/
/*
Hint 1: || A két folyó összefolyása a szülőláncaik első közös eleme. ||
Hint 2: || Ha az egyik folyó mélyebben van, először azt kell felhozni a másik szintjére. ||
Hint 3: || Azonos mélységtől mindkét láncot egy lépéssel emelve az első egyező csúcs lesz az összefolyás. ||
*/
#include <bits/stdc++.h>
using namespace std;

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