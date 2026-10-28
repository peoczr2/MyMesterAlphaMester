/*
Megoldás lényege:
Egy dátumot egyetlen számjegysorozatként írunk le: az évszám utolsó két jegye (0 nélkül), utána a hónap és a nap
sorszáma (szintén 0 nélkül), például 82.2.8 esetén 8228. Egy dátum pontosan akkor tükördátum, ha a sorozata
megfordítva is egy érvényes, ugyanabban az évben lévő dátum sorozata. Ezért először az év összes érvényes dátumának
sorozatát egy halmazba gyűjtjük (a szökévet figyelembe véve), majd naptári sorrendben végigmegyünk a dátumokon,
és kiírjuk azokat, amelyek megfordított sorozata szerepel a halmazban. Legfeljebb 366 dátumot vizsgálunk, így
az időigény elhanyagolható.
*/
/*
Hint 1: || Írj le minden dátumot egyetlen számjegysorozatként: az évszám utolsó két jegyét, majd a hónapot és a napot, mindegyiket 0 nélkül. A tükördátum sorozata megfordítva szintén ilyen sorozat lesz. ||
Hint 2: || Egy set<string> halmazba tedd az év összes érvényes dátumának sorozatát; a napok számát tömbben tárold, és szökévben a február 29 is szerepeljen. Ezután hónap, majd nap szerint növekvő sorrendben végigmenve írd ki azokat a dátumokat, amelyek megfordított sorozata benne van a halmazban. ||
*/
#include <bits/stdc++.h>
using namespace std;

bool szokev(int ev) {
    return (ev % 4 == 0 && ev % 100 != 0) || ev % 400 == 0;
}

int main() {
    int ev;
    cin >> ev;

    int ev2 = ev % 100;   // az évszám utolsó két jegye, 0 nélküli alakban
    int napok[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (szokev(ev)) napok[2] = 29;

    // Az év összes érvényes dátumának számjegysorozata
    set<string> sorozatok;
    for (int h = 1; h <= 12; h++) {
        for (int n = 1; n <= napok[h]; n++) {
            sorozatok.insert(to_string(ev2) + to_string(h) + to_string(n));
        }
    }

    // Naptári sorrendben: a tükördátumok kiírása
    for (int h = 1; h <= 12; h++) {
        for (int n = 1; n <= napok[h]; n++) {
            string s = to_string(ev2) + to_string(h) + to_string(n);
            string forditott = string(s.rbegin(), s.rend());
            if (sorozatok.count(forditott)) {
                cout << ev2 << "." << h << "." << n << ".\n";
            }
        }
    }
    return 0;
}
