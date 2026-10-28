/*
Megoldás lényege:
Az elkerített rész egy egyszerű (nem önmetsző) ortogonális poligon. Minden fára pont-benne-van tesztet végzünk: jobbra mutató félegyenest húzunk, és megszámoljuk, hányszor metszi a poligon függőleges éleit. Páratlan metszésszám esetén a pont belül, páros esetén kívül van. A bemenet garantálja, hogy egy fa sem esik kerítésszakaszra, így a szabály egyértelmű.
Idő: O(N*M), ami a korlátokra elegendő.
*/
/*
Hint 1: || Az elkerített rész ortogonális poligon: egy pont akkor van benne, ha a jobbra húzott félegyenes páratlan számú függőleges kerítésszakaszt metsz. ||
Hint 2: || Minden kivágandó fára külön-külön végigmész a függőleges éleken, és a metszések számának paritása dönt; összesen O(N·M) lépés. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    vector<long long> x(N), y(N);
    for (int i = 0; i < N; ++i) {
        cin >> x[i] >> y[i];
    }

    int M;
    cin >> M;

    for (int qi = 0; qi < M; ++qi) {
        long long qx, qy;
        cin >> qx >> qy;

        bool inside = false;
        for (int i = 0, j = N - 1; i < N; j = i++) {
            // Vertical edges only (orthogonal polygon).
            if (x[i] == x[j]) {
                long long yy1 = y[i], yy2 = y[j];
                bool straddle = (yy1 > qy) != (yy2 > qy);
                if (straddle && x[i] > qx) {
                    inside = !inside;
                }
            }
        }

        cout << (inside ? "IGEN" : "NEM") << '\n';
    }

    return 0;
}
