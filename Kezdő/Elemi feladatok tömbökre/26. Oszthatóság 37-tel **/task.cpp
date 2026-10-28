/*
Megoldás lényege:
Ugyanaz a redukció működik, mint 31-nél, csak az utolsó számjegy 11-szeresét vonjuk le: y = x / 10 - 11 * (x % 10). A köztes értékeket a nemnegatív tartományban írjuk ki, a 0-t még kiírjuk. Az IGEN/NEM döntést viszont az eredeti számból számoljuk (N % 37 == 0), mert a redukció negatív végállapota is lehet 37-tel osztható, például 37 esetén -74, 74 esetén -37 a végeredmény. A lépések száma legfeljebb tíz, így az idő konstans.
*/
/*
Hint 1: || A lépés szerkezete ugyanaz, mint a 31-es feladatnál: az utolsó számjegyet levágod, a maradékból pedig az utolsó számjegy 11-szeresét vonod le. ||
Hint 2: || Az IGEN/NEM döntéshez ne csak a végső értéket nézd: a redukció negatív végállapota is lehet 37-tel osztható. Ezért az eredeti N-et vizsgáld közvetlenül. ||
Hint 3: || A köztes számokat úgy írd ki, mint a 31-es feladatnál: negatív értéknél állj meg kiírás nélkül, a 0-t viszont még írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;

    // a döntés az eredeti számból: osztható-e 37-tel
    bool oszthato = (n % 37 == 0);

    // a köztes számok a kiszámítás sorrendjében
    vector<long long> koztes;
    long long x = n;
    while (true) {
        long long y = x / 10 - 11 * (x % 10);
        if (y < 0) break;          // negatív értéket nem írunk ki
        koztes.push_back(y);
        if (y == 0) break;         // a 0-t még kiírjuk, utána megállunk
        x = y;
    }

    cout << (oszthato ? "IGEN" : "NEM") << "\n";
    for (size_t i = 0; i < koztes.size(); i++) {
        if (i) cout << ' ';
        cout << koztes[i];
    }
    cout << "\n";
    return 0;
}
