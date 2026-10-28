/*
Megoldás lényege:
A házat egy négyzetrácsként tároljuk: a házon kívüli mezők és a már meglévő szobák mezői foglaltak. Egy új szoba akkor építhető be, ha minden oldala teljes hosszában foglalt mezőkhöz ér (szobához vagy a ház falához), és belül csak szabad mezőket fed le. Ebből következik, hogy az új szoba pontosan egy teljes szabad, összefüggő területet foglal el. Mivel a szabad területek téglalap alakúak, mindegyiknek egyetlen bal felső mezője van, amelynek a bal és a felső szomszédja foglalt. A válasz ezeknek a mezőknek a száma. Az időigény O(W*H + a szobák területe), ahol W és H a ház mérete, a memóriaigény O(W*H) bájt, legfeljebb kb. 16 MB.
*/
/*
Hint 1: || A koordináták mezőket (négyzetrács-cellákat) azonosítanak, a szoba bal felső és jobb alsó mezője is a szobához tartozik. Készíts a házról rácsot, és jelöld a szobák mezőit foglaltnak. ||
Hint 2: || Egy új szoba csak olyan szabad mezőkből álló téglalap lehet, amelynek minden szomszédos mezője foglalt (szoba vagy a házon kívül). Ezért minden olyan szabad téglalap, amelyet foglalt mezők zárnak körül, pontosan egy lehetséges új szoba. ||
Hint 3: || Egy szabad téglalap bal felső mezője az egyetlen olyan szabad mező benne, amelynek a bal és a felső szomszédja foglalt. Ezeket a mezőket számold meg, és a ház határán kívüli mezőket is foglaltnak tekintsd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, fx, fy, ax, ay;
    cin >> n >> fx >> fy >> ax >> ay;
    int w = ax - fx + 1;
    int h = ay - fy + 1;
    int sor = w + 2;  // a ház köré egy foglalt keret kerül
    // foglalt[y * sor + x]: 1, ha a mező foglalt; a keret és a ház határán kívüli mezők 1-esek
    vector<unsigned char> foglalt((h + 2) * sor, 1);
    for (int y = 1; y <= h; y++)
        for (int x = 1; x <= w; x++)
            foglalt[y * sor + x] = 0;

    for (int i = 0; i < n; i++) {
        int bfx, bfy, jax, jay;
        cin >> bfx >> bfy >> jax >> jay;
        int x1 = max(bfx, fx), x2 = min(jax, ax);
        int y1 = max(bfy, fy), y2 = min(jay, ay);
        for (int y = y1; y <= y2; y++)
            for (int x = x1; x <= x2; x++)
                foglalt[(y - fy + 1) * sor + (x - fx + 1)] = 1;
    }

    long long darab = 0;
    for (int y = 1; y <= h; y++) {
        for (int x = 1; x <= w; x++) {
            int i = y * sor + x;
            if (!foglalt[i] && foglalt[i - 1] && foglalt[i - sor]) darab++;
        }
    }
    cout << darab << "\n";
    return 0;
}
