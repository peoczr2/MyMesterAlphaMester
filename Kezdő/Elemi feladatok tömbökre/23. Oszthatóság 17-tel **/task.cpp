/*
Megoldás lényege:
Ha x = 10a + b, ahol b az utolsó számjegy, akkor az a − 5b szám ugyanúgy osztható 17-tel, mint x, mert 10(a − 5b) = x − 51b, és 51 osztható 17-tel. Ezért a sorozat minden eleme ugyanazt a 17-es maradékot adja vissza, mint az eredeti szám, és a lépést addig ismételjük, amíg a kapott szám nem lesz negatív. Minden lépésben a jegyek száma csökken, így legfeljebb néhány lépés van. Az IGEN/NEM döntést az N közvetlen 17-es maradéka adja, a közbülső számokat pedig a lépések sorrendjében írjuk ki.
*/
/*
Hint 1: || Ha x = 10a + b (b az utolsó számjegy), akkor 10(a − 5b) = x − 51b, és mivel 51 osztható 17-tel, x pontosan akkor osztható 17-tel, ha a − 5b is az. ||
Hint 2: || Ismételd a műveletet: a = x / 10 és b = x % 10 szerint számold ki a következő számot, és állj meg, ha a kapott szám negatív lenne. A 0-t még írd ki, utána viszont már ne folytasd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;

    cout << (n % 17 == 0 ? "IGEN" : "NEM") << '\n';

    vector<long long> koztes;
    long long x = n;
    while (true) {
        long long y = x / 10 - 5 * (x % 10);
        if (y < 0) break;   // negatív eredménynél megállunk, ezt nem írjuk ki
        koztes.push_back(y);
        if (y == 0) break;  // a 0 még kiíródik, utána megállunk
        x = y;
    }

    for (size_t i = 0; i < koztes.size(); i++) {
        if (i) cout << ' ';
        cout << koztes[i];
    }
    cout << '\n';
    return 0;
}
