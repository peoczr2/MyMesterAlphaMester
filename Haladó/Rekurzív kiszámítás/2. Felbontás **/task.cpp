/*
Megoldás lényege:
Az 123456789 számjegyei közé csak + vagy - jelet tehetünk, ezért legfeljebb 2^8
lehetőség van. Minden jelkombinációt végigpróbálunk, kiszámítjuk az összeget, és ha
pontosan a keresett számot kapjuk, kiírjuk az adott felbontást.

*/

// Hint 1: || Csak nyolc döntés van, ezért a teljes bejárás bőven belefér. ||
// Hint 2: || A kifejezés mindig az 1 számmal indul, utána minden számjegy elé egy jel kerül. ||
// Hint 3: || Ha megtaláltad a megfelelő maszkot, a konkrét kifejezés szövegét már könnyű összerakni. ||

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long target;
    if (!(cin >> target)) return 0;

    // 8 helyre tehetünk jelet: '-', '+', vagy semmit (összefűzés).
    // Így összesen 3^8 lehetőséget járunk be.
    const int ALL = 6561; // 3^8
    for (int state = 0; state < ALL; ++state) {
        int code = state;
        long long value = 0;
        long long cur = 1;
        int sign = +1;
        string expr = "1";

        for (int d = 2; d <= 9; ++d) {
            int op = code % 3;
            code /= 3;
            if (op == 0) {
                cur = cur * 10 + d;
                expr += to_string(d);
            } else {
                value += sign * cur;
                cur = d;
                if (op == 1) {
                    sign = +1;
                    expr += '+';
                } else {
                    sign = -1;
                    expr += '-';
                }
                expr += to_string(d);
            }
        }
        value += sign * cur;

        if (value == target) {
            cout << expr << '\n';
            return 0;
        }
    }

    cout << "LEHETETLEN\n";
    return 0;
}
