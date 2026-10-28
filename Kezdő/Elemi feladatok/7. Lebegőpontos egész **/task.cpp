/*
Megoldás lényege:
A két kitevő legfeljebb 2-vel tér el, ezért a nagyobb kitevőjű szám a-ját annyiszor szorozzuk tízzel, amennyivel a kitevője nagyobb, így mindkét szám a kisebb kitevővel írható fel. Ekkor az összeg és a különbség közönséges egész művelet, értéke legfeljebb 29 899 lehet. A szorzatnál a két a-t szorozzuk (legfeljebb 89 401), a kitevő pedig a két kitevő összege. Az eredményt normalizáljuk: amíg az a utolsó számjegye 0, tízzel osztjuk, és a kitevőt eggyel növeljük; a nulla külön esete 0 0. A különbség negatív is lehet, ilyenkor az a előjelesen szerepel. A művelet ideje konstans.
*/
/*
Hint 1: || Hozd a két számot közös kitevőre: a nagyobb kitevőjű a-t szorozd annyiszor tízzel, amennyivel a kitevője nagyobb. Mivel ez legfeljebb kétszeri szorzás, az összeg és a különbség már egész számmal számolható. ||
Hint 2: || A szorzat a-ja a két a szorzata, a kitevője pedig a két kitevő összege. Az összeg és a különbség kitevője a két kitevő közül a kisebb. ||
Hint 3: || Az eredményt normalizáld: amíg az a utolsó számjegye 0, osztd tízzel, és a kitevőt növeld eggyel. A nulla eredmény külön esetként 0 0 alakban íródik. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Kiírja az a*10^b számot úgy, hogy a utolsó számjegye ne legyen 0
void kiir(long long a, long long b) {
    if (a == 0) {
        cout << "0 0\n";
        return;
    }
    while (a % 10 == 0) {
        a /= 10;
        b++;
    }
    cout << a << " " << b << "\n";
}

int main() {
    long long a1, b1, a2, b2;
    cin >> a1 >> b1 >> a2 >> b2;

    // A nagyobb kitevőjű a-t annyiszor tízzel szorozzuk, amennyivel a kitevője nagyobb
    long long bmin = min(b1, b2);
    long long v1 = a1;
    for (long long i = bmin; i < b1; i++) v1 *= 10;
    long long v2 = a2;
    for (long long i = bmin; i < b2; i++) v2 *= 10;

    kiir(v1 + v2, bmin);      // összeg
    kiir(v1 - v2, bmin);      // különbség
    kiir(a1 * a2, b1 + b2);   // szorzat
    return 0;
}
