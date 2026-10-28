/*
Megoldás lényege:
Minden lehetséges 7 napos szakaszt megvizsgálunk: a kezdőnapot 1-től N − 6-ig változtatjuk, és a szakaszon belül kiszámoljuk a legnagyobb és a legkisebb hőmérséklet különbségét. Mivel a szakasz hossza fix (7), egy szakasz bejárása konstans idejű, így az összes szakasz együtt O(N) lépés, ami N ≤ 10 000 mellett bőven belefér az időkorlátba. Az eredményt csak szigorúan nagyobb különbségnél írjuk felül, így egyenlőség esetén a kisebb sorszámú kezdőnap marad. A memóriaigény O(N) a hőmérsékletek tárolása miatt.
*/
/*
Hint 1: || A szakasz hossza mindig 7, ezért minden lehetséges kezdőnapra közvetlenül kiszámolhatod a szakasz legnagyobb és legkisebb hőmérsékletét. ||
Hint 2: || Tartsd nyilván az eddigi legnagyobb különbséget és a hozzá tartozó kezdőnapot; csak szigorúan nagyobb különbségnél írd felül, így egyenlőségnél a korábbi, kisebb sorszám marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int days;
    cin >> days;

    vector<int> temperature(days);
    for (int i = 0; i < days; i++) {
        cin >> temperature[i];
    }

    const int windowLength = 7;
    int bestStart = 1;
    int bestDifference = -1;
    for (int start = 0; start + windowLength <= days; start++) {
        int hi = temperature[start];
        int lo = temperature[start];
        for (int j = start; j < start + windowLength; j++) {
            hi = max(hi, temperature[j]);
            lo = min(lo, temperature[j]);
        }
        if (hi - lo > bestDifference) {
            bestDifference = hi - lo;
            bestStart = start + 1;
        }
    }

    cout << bestStart << "\n";
    return 0;
}
