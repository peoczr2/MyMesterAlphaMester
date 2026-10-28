/*
Megoldás lényege:
Egy lépésben az utolsó számjegyet levágjuk, a maradék számból pedig levonjuk az utolsó számjegy háromszorosát. Ez a lépés nem változtatja meg az oszthatóságot 31-gyel, ezért a számot addig redukáljuk, amíg a kapott szám negatív nem lesz. A nemnegatív köztes értékeket kiírjuk, a negatívat nem, és ha az utolsó kiírt szám 0, a szám osztható 31-gyel. Minden lépésben a számjegyek száma legalább eggyel csökken, így legfeljebb tíz lépés van, az idő konstans.
*/
/*
Hint 1: || Az x szám utolsó számjegye x % 10, a levágás utáni rész x / 10. Egy lépés eredménye tehát: y = x / 10 - 3 * (x % 10). ||
Hint 2: || Ismételd a lépést, és minden kapott nemnegatív értéket írj ki. Ha negatív értéket kapsz, állj meg anélkül, hogy kiírnád; ha 0-t kapsz, azt még írd ki, majd állj meg. Az IGEN a 0 végállapotnak felel meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long x;
    cin >> x;

    // a közbülső számok a kiszámítás sorrendjében
    vector<long long> koztes;
    while (true) {
        long long y = x / 10 - 3 * (x % 10);
        if (y < 0) break;          // negatív értéket nem írunk ki
        koztes.push_back(y);
        if (y == 0) break;         // a 0-t még kiírjuk, utána megállunk
        x = y;
    }

    bool oszthato = !koztes.empty() && koztes.back() == 0;
    cout << (oszthato ? "IGEN" : "NEM") << "\n";
    for (size_t i = 0; i < koztes.size(); i++) {
        if (i) cout << ' ';
        cout << koztes[i];
    }
    cout << "\n";
    return 0;
}
