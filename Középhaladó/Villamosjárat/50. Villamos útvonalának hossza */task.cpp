/*
Megoldás lényege:
A villamos útvonalának hossza a szomszédos megállók közötti távolságok összege: az i. sor első száma az (i-1). és az i. megálló közötti út hossza. Az érkezési és indulási idők nem befolyásolják a hosszt, ezeket figyelmen kívül hagyjuk. Egy bejárásban összegezzük a Ti értékeket, az eredményt 64 bites egészben tároljuk. Időigény O(N).
*/
/*
Hint 1: || Az útvonal hossza a szomszédos megállók közötti távolságok összege. Ezeket a sorok első száma adja, az idők ebben nem játszanak szerepet. ||
Hint 2: || Egy ciklusban olvasd be a sorokat, és egy összegző változóhoz mindig az első számot add hozzá. A végén csak az összeget írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long osszes = 0;
    for (int i = 1; i <= n; i++) {
        long long tav, erk, ind;
        cin >> tav >> erk >> ind;
        osszes += tav;
    }
    cout << osszes << '\n';
    return 0;
}
