/*
Megoldás lényege:
A legjobb helyezés a legkisebb elért helyezés, az idő ehhez nem kell. Egy változóban tartjuk az eddigi legjobb helyezést
és a hozzá tartozó számlálót: ha jobb (kisebb) helyezés jön, a számlálót 1-re állítjuk, ha ugyanilyen, növeljük.
A versenyeket egyszer, sorrendben dolgozzuk fel, így az időigény O(N).
*/
/*
Hint 1: || Csak a helyezés számít: keresd meg a legkisebb helyezést, és számold meg, hányszor fordul elő. Az idő eredmény most nem kell. ||
Hint 2: || Egy változóban tartsd az eddigi legjobb helyezést és a hozzá tartozó számlálót; ha kisebb helyezés jön, a számlálót nullázd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int bestPlace = INT_MAX; // a legjobb (legkisebb) elért helyezés
    int count = 0;           // hányszor érte el
    for (int i = 0; i < n; i++) {
        int place, minutes, seconds;
        cin >> place >> minutes >> seconds;
        if (place < bestPlace) {
            bestPlace = place;
            count = 1;
        } else if (place == bestPlace) {
            count++;
        }
    }

    cout << bestPlace << ' ' << count << '\n';
    return 0;
}
