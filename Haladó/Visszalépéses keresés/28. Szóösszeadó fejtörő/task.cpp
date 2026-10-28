/*
Megoldás lényege: a klasszikus SEND + MORE = MONEY fejtörőt nyers erővel oldjuk meg: a 0..9
számjegyek összes sorrendjét (permutációját) végigpróbáljuk, és azt a
hozzárendelést keressük, ahol a SEND és a MORE összege pontosan a MONEY.
A kezdőjegyek (S és M) nem lehetnek nullák. A talált hozzárendelést
S, E, N, D, M, O, R, Y sorrendben írjuk ki. Mivel 10! kb. 3,6 millió sorrend,
az időigény ilyen kicsi feladatnál bőven belefér az időlimitbe.
*/
/*
Hint 1: || Csak nyolc különböző betű szerepel, ezért a 0..9 számjegyek összes kiosztása végigpróbálható. ||
Hint 2: || Egy kiosztás akkor jó, ha a SEND és a MORE számokból képzett összeg pontosan a MONEY szám. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    array<int, 10> d{};
    iota(d.begin(), d.end(), 0);
    do {
        int S = d[0], E = d[1], N = d[2], D = d[3], M = d[4], O = d[5], R = d[6], Y = d[7];
        if (S == 0 || M == 0) continue;
        int send = 1000 * S + 100 * E + 10 * N + D;
        int more = 1000 * M + 100 * O + 10 * R + E;
        int money = 10000 * M + 1000 * O + 100 * N + 10 * E + Y;
        if (send + more == money) {
            cout << "S " << S << '\n';
            cout << "E " << E << '\n';
            cout << "N " << N << '\n';
            cout << "D " << D << '\n';
            cout << "M " << M << '\n';
            cout << "O " << O << '\n';
            cout << "R " << R << '\n';
            cout << "Y " << Y << '\n';
            return 0;
        }
    } while (next_permutation(d.begin(), d.end()));
    return 0;
}