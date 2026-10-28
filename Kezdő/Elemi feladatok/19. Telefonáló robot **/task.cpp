/*
Megoldás lényege:
Minden gombhoz egy (x, y) koordinátát rendelünk: a * gomb (0, 0), a 0 gomb (1, 0), a # gomb (2, 0), az 1–9 gombok pedig 3×3-as rácsot alkotnak, ahol az y tengely észak felé nő. Egy E vagy K utasítás csak az egyik tengely mentén mozdít, ezért két gomb között pontosan annyi utasítás kell, ahány koordináta különbözik. Ha mindkettő különbözik, előbb a K, aztán az E utasítást írjuk ki. Minden számjegyhez egy N utasítás tartozik, a végén a robotkart a # fölé visszük. Mivel minden szakasz minimális, az egész sorozat is minimális, az időigény a számjegyek számával arányos.
*/
/*
Hint 1: || Minden gombhoz rácson egy koordináta-pár tartozik. Egy E vagy K utasítás csak az egyik tengelyen mozdít, így két pont között annyi utasítás kell, ahány koordináta különbözik nullától. ||
Hint 2: || Az előző pozícióból mindig a következő nyomógomb pozíciójába megyünk, és a mozgás után jön az N. A végén a # gombhoz kell menni, a mozgásokat ugyanígy számold. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A gomb koordinátája: x = oszlop (0..2), y = sor a * gomb sorától felfelé
pair<int, int> pos(char c) {
    if (c == '*') return {0, 0};
    if (c == '#') return {2, 0};
    if (c == '0') return {1, 0};
    int d = c - '1';   // 0..8 az 1..9 gombokra
    return {d % 3, 3 - d / 3};
}

int main() {
    string s;
    cin >> s;

    vector<string> commands;
    auto goTo = [&](pair<int, int> from, pair<int, int> to) {
        int dx = to.first - from.first;
        int dy = to.second - from.second;
        if (dx != 0) commands.push_back("K " + to_string(dx));
        if (dy != 0) commands.push_back("E " + to_string(dy));
    };

    pair<int, int> cur = pos('*');
    for (char c : s) {
        pair<int, int> target = pos(c);
        goTo(cur, target);
        commands.push_back("N");
        cur = target;
    }
    goTo(cur, pos('#'));

    for (size_t i = 0; i < commands.size(); ++i) {
        if (i) cout << ' ';
        cout << commands[i];
    }
    cout << '\n';
    return 0;
}
