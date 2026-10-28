/*
Megoldás lényege:
Egy foglalás az E-edik naptól az U-adik napig tart, így a lefoglalt napok száma U - E + 1.
Mivel nincs átfedés, egy terem foglalt napjainak száma a hozzá tartozó foglalások hosszainak összege, a napokat nem kell egyenként végigjárni.
A termekhez egy N+1 hosszú tömböt használunk, és minden foglalásnál a megfelelő terem elemét növeljük a foglalás hosszával.
A K foglalás beolvasása után az 1..N elemeket írjuk ki, az időigény O(K + N).
*/
/*
Hint 1: || Egy foglalás az E-edik naptól az U-adik napig tart. Hány napot jelent ez? Ne a napokat egyesével számold meg. ||
Hint 2: || Tárolj egy tömböt a termek számára, és minden foglalásnál add az U - E + 1 értéket a foglalás termének elemjéhez. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> foglalt(n + 1, 0);
    for (int i = 0; i < k; i++) {
        int t, e, u;
        cin >> t >> e >> u;
        foglalt[t] += u - e + 1;
    }
    for (int t = 1; t <= n; t++) {
        cout << foglalt[t] << (t < n ? " " : "\n");
    }
    return 0;
}
