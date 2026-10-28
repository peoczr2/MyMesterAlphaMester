/*
Megoldás lényege:
Az i. állomásszakasz az (i-1). és az i. állomás közötti szakasz, hossza a T_i távolság. Egy szakasz akkor felel meg, ha hossza szigorúan nagyobb minden korábbi szakasz hosszánál; az első szakasz ezt automatikusan teljesíti, mert nincs korábbi. Egy menetben tartjuk az eddigi legnagyobb hosszt, és ha az aktuális szakasz szigorúan nagyobb nála, felvesszük a sorszámát a listába és frissítjük a maximumot. A lista a bejárás sorrendjében, tehát növekvő sorszámokkal készül. Az időigény O(N).
*/
/*
Hint 1: || Az i. állomásszakasz hossza az i. sorban megadott távolság. Hasonlítsd össze minden szakasz hosszát az addig látott legnagyobbal. ||
Hint 2: || Tartsd nyilván az eddigi maximumot (kezdetben 0, mert a távolságok pozitívak), és ha az aktuális szakasz nagyobb nála, vedd fel a sorszámot a listába és frissítsd a maximumot. Az első szakasz így automatikusan bekerül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long best = 0;  // az eddigi leghosszabb szakasz hossza
    vector<int> chosen;

    for (int i = 1; i <= n; i++) {
        long long t, arr, dep;
        cin >> t >> arr >> dep;
        if (t > best) {
            best = t;
            chosen.push_back(i);
        }
    }

    cout << chosen.size();
    for (int x : chosen) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
