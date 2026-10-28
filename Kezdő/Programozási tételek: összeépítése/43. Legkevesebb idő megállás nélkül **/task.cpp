/*
Megoldás lényege:
Megállásnak az számít, ahol az érkezési és az indulási idő különbözik; a többi állomáson a villamos csak áthalad.
A határpontok: a 0. percben induló villamos (kezdőpont), a valódi megállások (érkezés és indulás), és a végállomás érkezése.
Egy állómentes szakasz a következő határpont érkezése és az előző határpont indulása közötti idő.
Az állomásokat sorban végigjárva kiszámoljuk ezeket az időtartamokat, és a legkisebbet írjuk ki. Időigény: O(N).
*/
/*
Hint 1: || Csak azokat az időszakokat kell figyelni, amikor a villamos két valódi megálló között halad, és közben nem áll meg. Az áthaladó állomások ebben nem törik meg a szakaszt. ||
Hint 2: || Tartsd nyilván az utolsó megállás indulási idejét, amely a 0. percről indul. Ha egy állomáson megállt a villamos, vagy az utolsó állomás következik, számold ki az érkezés és az előző indulás különbségét. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long best = LLONG_MAX;
    long long lastDep = 0;   // a villamos a 0. percben indul
    for (int i = 0; i < n; i++) {
        long long tav, erk, ind;
        cin >> tav >> erk >> ind;   // a távolság az időtartamokhoz nem kell
        bool megall = erk < ind;
        bool utolso = (i == n - 1);
        if (megall || utolso) {
            best = min(best, erk - lastDep);
            lastDep = ind;
        }
    }
    cout << best << "\n";
    return 0;
}
