/*
Megoldás lényege:
A három maradékfeltétel (mod 5, mod 7, mod 11) együtt egyetlen maradékosztályt határoz meg mod 385,
mert az 5, 7 és 11 páronként relatív prímek (kínai maradéktétel). Ezért a legkisebb jó szám a 0..384
tartományban van, és egy legfeljebb 385 lépéses ciklussal megtalálható. Ha ez a szám nem kisebb 10^N-nél,
nincs legfeljebb N-jegyű megoldás, és a válasz NINCS. Egyébként a további jó számok r + 385*k alakúak,
ezért 10^N-ig 385-ösével lépkedve megszámolhatók. A futásidő elhanyagolható, legfeljebb néhány száz lépés.
*/
/*
Hint 1: || Keress egy olyan számot 0 és 384 között, amelynek 5-tel, 7-tel és 11-gyel való osztási maradéka rendre A, B és C. Ez a szám lesz a legkisebb jó szám. ||
Hint 2: || A többi jó szám a legkisebb + 385, a legkisebb + 770 és így tovább. Számold meg, hány ilyen szám kisebb 10^N-nél; ha a legkisebb már legalább 10^N, akkor nincs ilyen szám. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, a, b, c;
    cin >> n >> a >> b >> c;

    // A legkisebb jó szám 0 és 384 között van (5 * 7 * 11 = 385)
    int r = 0;
    for (int x = 0; x < 385; x++) {
        if (x % 5 == a && x % 7 == b && x % 11 == c) {
            r = x;
            break;
        }
    }

    // hatar = 10^n: a legfeljebb n-jegyű számok száma
    int hatar = 1;
    for (int i = 0; i < n; i++) hatar *= 10;

    if (r >= hatar) {
        cout << "NINCS" << endl;
        return 0;
    }

    // A jó számok r, r + 385, r + 770, ... alakúak
    int darab = 0;
    for (int x = r; x < hatar; x += 385) darab++;

    cout << r << endl;
    cout << darab << endl;
    return 0;
}
