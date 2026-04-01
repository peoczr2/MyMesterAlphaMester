/*
 * Boldog számok keresése egy intervallumban. Minden számról eldöntjük, hogy a
 * számjegy-négyzetösszeg ismételt képzése végül 1-be fut-e.
 
Hint 1: || Egy szám sorsa csak a számjegynégyzet-összeg ismételgetésétől függ, ezt kell szimulálni. ||
*/

#include "../common.hpp"

static int next_value(int x) {
    int sum = 0;
    while (x) {
        int d = x % 10;
        sum += d * d;
        x /= 10;
    }
    return sum;
}

static bool happy(int x) {
    unordered_set<int> seen;
    while (x != 1 && x != 7 && !seen.count(x)) {
        seen.insert(x);
        x = next_value(x);
    }
    return x == 1 || x == 7;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;
    bool first = true;
    for (int x = a; x <= b; ++x) {
        if (happy(x)) {
            if (!first) cout << ' ';
            first = false;
            cout << x;
        }
    }
    cout << '\n';
    return 0;
}
