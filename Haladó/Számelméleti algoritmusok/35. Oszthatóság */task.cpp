/*
 * A megadott számok maradékát számoljuk 19, 29 és 551 modullal.
 
Hint 1: || A szövegben adott szabályok mind ugyanarra vezetnek: a szám maradékát kell kiszámolni 19, 29 és 551 szerint. ||
Hint 2: || Mivel a szám nagyon hosszú lehet, karakterenként építsd a maradékot: `r = (10*r + digit) mod m`. ||
*/

#include "../common.hpp"

static int mod_string(const string& s, int mod) {
    int r = 0;
    for (char c : s) r = (r * 10 + (c - '0')) % mod;
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        cout << (mod_string(s, 19) == 0 ? "IGEN" : "NEM") << ' ';
        cout << (mod_string(s, 29) == 0 ? "IGEN" : "NEM") << ' ';
        cout << (mod_string(s, 551) == 0 ? "IGEN" : "NEM") << '\n';
    }
    return 0;
}
