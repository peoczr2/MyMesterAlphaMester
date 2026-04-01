/*
Hungarian megoldás: a klasszikus SEND + MORE = MONEY fejtörőt brute force
keressük meg a 10 számjegy permutációi között.

Hint 1: || Csak nyolc betű szerepel, ezért a hozzárendelés bruttó kipróbálható. ||
Hint 2: || A helyes megoldásra az összeadás ellenőrzése azonnal választ ad. ||
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