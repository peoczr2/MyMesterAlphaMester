/*
Megoldás lényege:
A szegéllyel együtt vett téglalap L oszlop széles és H magas, és minden oszlopában legalább H méter magas sziklának kell lennie. A freskó mérete ilyenkor (L-2)*(H-2), mert a négy oldalon egy-egy méter a szegély. Mivel a magasságok legfeljebb 100 lehetnek, minden H értékre (3-tól 100-ig) egyetlen bejárással megkeressük a leghosszabb egymás utáni, legalább H magas oszlopokból álló szakaszt. A megoldás O(100*N) időben fut, ami bőven belefér az időlimitbe.
*/
/*
Hint 1: || A szegély miatt a freskó minden oldalától, azaz balról, jobbról, alulról és felülről 1-1 méter üres marad. Ha a szegéllyel együtt vett téglalap L széles és H magas, akkor a freskó (L-2) széles és (H-2) magas. ||
Hint 2: || A magasságok legfeljebb 100-ak, ezért a teljes téglalap H magasságát rögzíthetjük 3-tól 100-ig. Minden H-ra külön nézzük, mekkora a legszélesebb olyan egymás utáni szakasz, ahol minden oszlop legalább H magas. ||
Hint 3: || H rögzített értéke mellett egy bejárás elég: futó számlálóval számoljuk az egymás utáni, legalább H magas oszlopokat, és ha alacsonyabb oszlop jön, a számláló nullázódik. Ha a maximális hossz L >= 3, a jelölt méret (L-2)*(H-2); a válasz ezek maximuma, és ha nincs ilyen, 0. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> m(n);
    for (int &x : m) cin >> x;

    long long best = 0;
    for (int h = 3; h <= 100; h++) {
        int run = 0;
        int longest = 0;
        for (int i = 0; i < n; i++) {
            run = (m[i] >= h) ? run + 1 : 0;
            longest = max(longest, run);
        }
        if (longest >= 3)
            best = max(best, (long long)(longest - 2) * (h - 2));
    }

    cout << best << "\n";
    return 0;
}
