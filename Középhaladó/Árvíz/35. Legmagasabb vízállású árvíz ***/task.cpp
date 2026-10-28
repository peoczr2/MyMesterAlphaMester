/*
Megoldás lényege:
A mérések készültségi szintje a vízállásból adódik: 1000 cm felett 3-as, 900 cm felett 2-es, 800 cm felett 1-es szint, egyébként 0.
A folyószakaszok a leghosszabb egymás melletti, azonos szintű mérések, ezért egy balról jobbra haladó bejárással megkaphatók.
Az árvízvédelmi készültség legalább elsőfokú, ezért a legmagasabb vízállást csak az 1-es vagy nagyobb szintű mérések között keressük.
Ha több mérés is eléri a maximumot, a legkorábbit választjuk, így a legelső ilyen folyószakasz kerül ki.
A kiválasztott mérés körül balra és jobbra addig lépünk, amíg a szint nem változik: a két határ adja a szakasz kezdő és záró sorszámát.
Az időigény O(N), ami N ≤ 10 000 esetén messze az időlimit (0,1 mp) alatt van.
*/
/*
Hint 1: || Először minden mérést sorolj készültségi szintbe. Az árvízmentes mérések (800 cm-nél nem magasabbak) a keresésből kimaradnak. ||
Hint 2: || Egy menetben, balról jobbra haladva tartsd nyilván a legnagyobb olyan vízállást, amely árvízi szintű. Azonos értéknél ne írd felül a korábbi indexet. ||
Hint 3: || A legnagyobb érték helyéből indulva lépkedj balra és jobbra, amíg a szint ugyanaz marad. A kapott két sorszám adja a folyószakasz kezdetét és végét. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Készültségi szint: 0 = nincs árvíz, 1 = elsőfokú, 2 = másodfokú, 3 = harmadfokú
int szint(int magassag) {
    if (magassag > 1000) return 3;
    if (magassag > 900) return 2;
    if (magassag > 800) return 1;
    return 0;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // A legmagasabb árvízi vízállás és az első előfordulásának helye
    int legmagasabb = 0, hely = 0;
    for (int i = 1; i <= n; i++) {
        if (szint(a[i]) > 0 && a[i] > legmagasabb) {
            legmagasabb = a[i];
            hely = i;
        }
    }

    if (hely == 0) {
        cout << 0 << '\n';
        return 0;
    }

    // A folyószakasz határai: a hely körüli, azonos szintű mérések
    int bal = hely, jobb = hely;
    while (bal > 1 && szint(a[bal - 1]) == szint(a[hely])) bal--;
    while (jobb < n && szint(a[jobb + 1]) == szint(a[hely])) jobb++;

    cout << legmagasabb << '\n';
    cout << bal << '\n';
    cout << jobb << '\n';
    return 0;
}
