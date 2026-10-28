/*
Megoldás lényege:
Egy lépésben a számjegyek összege pontosan 1-gyel csökken, kivéve ha a kivonás
kölcsönzéssel jár. Kölcsönzés akkor kell, ha a számban csak egy nem nulla számjegy
van; ekkor a mögötte álló J nulla mind 9-es lesz, a lépések száma pedig S + 9 * J,
ahol S a számjegyösszeg és J a kölcsönzött nullák száma. Ha a szám hossza L, a
hossz-csökkenésekhez összesen legalább L(L-1)/2 kölcsönzés kell. Ezt a minimumot
úgy érjük el, hogy mindig a legnagyobb nem nulla számjegyet csökkentjük. Kivétel:
d * 10^(L-1) alakú számnál (d >= 2) egy plusz kölcsönzés kell az elején. Az idő O(L).
*/
/*
Hint 1: || Egy lépés a számjegyek összegét pontosan 1-gyel csökkenti, kivéve ha a kivonásnál kölcsönzés történik. Így a lépésszám a számjegyösszegből és a kölcsönzések számából adódik. ||
Hint 2: || Kölcsönzés csak akkor kell, ha a szám egyetlen nem nulla számjegyből áll, a mögötte lévő nullákkal együtt; ilyenkor minden nulla 9-es lesz, és az összeg 9-cel nő. Számold meg, hány nulla kölcsönzése szükséges, ha a szám hossza L. ||
Hint 3: || Mindig a legnagyobb nem nulla számjegyet csökkentsd: így a számjegyek egyenletesen fogynak, és az utolsó maradó nem nulla számjegy 1 lesz, így a kölcsönzés a minimális. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    long long len = s.size();
    long long sum = 0;
    int nonzero = 0;
    char lead = '0';
    for (char ch : s) {
        sum += ch - '0';
        if (ch != '0') {
            ++nonzero;
            lead = ch;
        }
    }
    long long borrows = len * (len - 1) / 2;
    if (nonzero == 1 && lead != '1' && len >= 2) borrows += len - 1;
    cout << sum + 9 * borrows << '\n';
    return 0;
}
