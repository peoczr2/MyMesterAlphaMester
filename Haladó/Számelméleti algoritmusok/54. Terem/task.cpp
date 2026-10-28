/*
Megoldás lényege:
A mohó lefedés során a téglalapból mindig a legnagyobb négyzetet vágjuk le, így a maradék téglalap oldalai az euklideszi algoritmus lépéseit követik: a hosszabb oldalból a rövidebbel annyiszor vágunk le négyzetet, amennyi a hányados, majd a maradékkal folytatjuk, amíg valamelyik oldal nulla nem lesz. A hányadosok összege adja az első részfeladat járólapszámát. Egyforma lapok esetén a legnagyobb használható négyzetoldal a két oldal legnagyobb közös osztója, így a darabszám (a / gcd) * (b / gcd). Az idő O(log(min(a, b))).
*/
/*
Hint 1: || A mohó négyzetes lefedés lépésszáma ugyanúgy viselkedik, mint az euklideszi algoritmus hányadosösszege. ||
Hint 2: || Az egyforma lapok esetén a legnagyobb használható lap oldala a két méret gcd-je, és ebből már könnyen kijön a darabszám. ||
*/

#include "../common.hpp"

static long long greedy_tiles(long long a, long long b) {
    long long cnt = 0;
    while (a && b) {
        if (a < b) swap(a, b);
        cnt += a / b;
        a %= b;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b;
    cin >> a >> b;
    cout << greedy_tiles(a, b) << '\n';
    long long g = gcdll(a, b);
    cout << (a / g) * (b / g) << '\n';
    return 0;
}
