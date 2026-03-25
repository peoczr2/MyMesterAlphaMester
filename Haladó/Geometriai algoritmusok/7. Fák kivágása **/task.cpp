/*
Megoldás lényege:
A kerítés egy egyszerű (nem önmetsző) ortogonális poligon. Minden fára pont-bennevan tesztet
végzünk: jobbra mutató félegyenest veszünk, és megszámoljuk, hányszor metszi a poligon
függőleges éleit. Páratlan metszésszám esetén a pont belül van, páros esetén kívül.
A bemenet garantálja, hogy egy fa sem esik kerítésszakaszra, így a szabványos ray-casting
feltétel biztonságosan használható.

Idő: O(N*M), ami a korlátokra elegendő.
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
