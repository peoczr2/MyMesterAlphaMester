/*
Megoldás lényege:
A 123456789 számjegyei közé mindenhova kerülhet + jel, - jel, vagy semmi (ekkor a számjegyek összefűződnek), így összesen 3^8 = 6561 kifejezés van. Ezeket mind végigpróbáljuk: minden kifejezés értékét az előjeles tagok összegeként számoljuk, és az első olyan kifejezést írjuk ki, amelynek értéke N. Ha egyik sem ad N-et, a válasz LEHETETLEN. Az időigény konstans, mert 6561 kifejezés van, mindegyik 8 lépéses.
*/
/*
Hint 1: || Csak nyolc döntés van, ezért a teljes bejárás bőven belefér. ||
Hint 2: || A kifejezés mindig az 1-essel indul, a többi számjegy elé + jel, - jel vagy semmi kerülhet. ||
*/
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
