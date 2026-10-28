/*
Megoldás lényege:
Egy szám sorsa csak a számjegyeinek négyzetösszegétől függ, ezért minden A..B közötti számra egyesével szimuláljuk az átalakítást. A folyamat akkor ér véget, ha 1-et vagy 7-et kapunk (mindkettő boldog szám, a 7-ből is 1 lesz), vagy ha ciklusba kerül, és ebben a ciklusban sem 1, sem 7 nincs. A ciklust úgy szűrjük ki, hogy eltároljuk a már látott értékeket, így a szimuláció mindig véges. A 100 000-es határig a négyzetösszeg legfeljebb 405, ezért a ciklusok nagyon rövidek, és az összidő O(B - A) lépés, ami a 0,5 mp-es időlimit alatt bőven belefér.
*/
/*
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
