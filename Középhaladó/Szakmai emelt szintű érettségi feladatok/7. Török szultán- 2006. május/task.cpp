/*
Megoldás lényege: a szolgák sorrendjében szimuláljuk az ajtók állapotát, kezdetben minden ajtó zárt. Az első szolga minden ajtót kinyit, a második minden második ajtót bezár, a többi szolga az i, 2i, 3i, ... sorszámú ajtók állapotát megfordítja. Egy k sorszámú ajtót annyi szolga érint, ahány osztója van k-nak, és a végső állapotot ennek paritása határozza meg. Az osztók száma pontosan akkor páratlan, ha k négyzetszám, így a végén nyitva az 1, 4, 9, ... ajtók maradnak. A szimuláció O(N log N) időben fut, ami N <= 1500 mellett bőven belefér.
*/
/*
Hint 1: || Egy ajtó állapotát csak azok a szolgák változtatják meg, akiknek a sorszáma osztója az ajtó sorszámának. ||
Hint 2: || Számold meg, hány szolga érinti a k sorszámú ajtót: ez a k osztóinak száma. Mikor páratlan egy szám osztóinak száma? ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<bool> open(n + 1, false);  // kezdetben minden ajtó zárva

    for (int servant = 1; servant <= n; servant++) {
        for (int door = servant; door <= n; door += servant) {
            if (servant == 1) {
                open[door] = true;           // az első szolga kinyitja
            } else if (servant == 2) {
                open[door] = false;          // a második szolga bezárja
            } else {
                open[door] = !open[door];    // a többi szolga megfordítja
            }
        }
    }

    for (int door = 1; door <= n; door++) {
        if (open[door]) {
            cout << door << '\n';
        }
    }
    return 0;
}
