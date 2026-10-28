/*
Megoldás lényege:
Egy nap akkor felel meg, ha a várható minimum hőmérséklet negatív (lehet fagyni), a várható
maximum pedig legalább 0 (lehet olvadni). Egy 0 fokos maximum már olvadást jelent, de egy 0 fokos
minimum még nem jelent fagyást. Minden napot külön megvizsgálunk, a feltételt teljesítő napok
sorszámát egy vektorba gyűjtjük. A kiíráskor előbb a darabszám, utána a sorszámok következnek.
Az időigény O(N), ami N legfeljebb 100 mellett bőven belefér.
*/
/*
Hint 1: || Minden naphoz két szám tartozik. Az egyik a fagyást, a másik az olvadást dönti el, és a napot csak akkor kell kiválasztani, ha mindkét feltétel teljesül. ||
Hint 2: || Figyelj a határesetekre: a minimumnak szigorúan 0 alatt kell lennie a fagyáshoz, a maximumnak viszont már 0-nál is elég az olvadáshoz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> napok;
    for (int i = 1; i <= n; i++) {
        int minimum, maximum;
        cin >> minimum >> maximum;
        if (minimum < 0 && maximum >= 0) {
            napok.push_back(i);
        }
    }

    cout << napok.size();
    for (int nap : napok) {
        cout << " " << nap;
    }
    cout << "\n";
    return 0;
}
