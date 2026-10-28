/*
Megoldás lényege:
Minden fal két szomszédos őrhely között húzódik, így N őrhely esetén N-1 fal van. Az i-edik falat akkor kell őrzöttnek számolni, ha az i-edik vagy az (i+1)-edik őrhelyen van őrség.
Ezt egyetlen ciklussal ellenőrizzük: a tömb minden szomszédos párjára megnézzük, hogy a két érték közül legalább az egyik 1-e, és az ilyen falakat megszámoljuk.
Az időigény O(N).
*/
/*
Hint 1: || N őrhely között pontosan eggyel kevesebb fal van, mint ahány őrhely, mert minden fal két szomszédos őrhelyet köt össze. ||
Hint 2: || Minden i-re nézd meg az i-edik és az (i+1)-edik őrhelyet: ha valamelyik őrzött, a közöttük lévő fal is őrzött. Ezt logikai VAGY feltétellel írd le. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> orseg(n);
    for (int i = 0; i < n; i++) {
        cin >> orseg[i];
    }
    int db = 0;
    for (int i = 0; i + 1 < n; i++) {
        if (orseg[i] == 1 || orseg[i + 1] == 1) {
            db++;
        }
    }
    cout << db << endl;
    return 0;
}
