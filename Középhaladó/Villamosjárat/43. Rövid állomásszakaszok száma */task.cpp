/*
Megoldás lényege:
Egy állomásszakasz hossza az adott megálló távolsága az előzőtől, vagyis minden sor első száma. A K méternél rövidebb szakaszokat úgy számoljuk, hogy minden távolságot K-hoz hasonlítunk szigorúan kisebb relációval, mert a K-val egyenlő szakasz nem rövidebb. A 0. állomástól az első megállóig tartó szakasz is beleszámít. Egyetlen beolvasási ciklus van, az időigény O(N).
*/
/*
Hint 1: || Egy szakasz hosszát az adott sor első száma adja. A másik két szám, az érkezési és indulási idő, most nem számít. ||
Hint 2: || Használj egy számlálót, és minden szakasznál, ha a hossz szigorúan kisebb K-nál, növeld meg. Egyenlőség esetén ne növeld. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    int count = 0;
    for (int i = 0; i < n; i++) {
        int dist, arr, dep;
        cin >> dist >> arr >> dep;
        if (dist < k) {
            count++;
        }
    }

    cout << count << '\n';
    return 0;
}
