/*
Megoldás lényege:
Minden busznál a kihasználtság U / M arányát vizsgáljuk. A buszt zsúfoltnak tekintjük, ha U legalább 0,8 · M, azaz 5 · U ≥ 4 · M. Üresnek tekintjük, ha U kisebb 0,2 · M-nél, azaz 5 · U < M. A törtek elkerülése érdekében a feltételeket egész számokkal, szorzással írjuk fel, így nincs kerekítési hiba. A buszokat egyszer, sorban végigjárjuk, és a feltételnek megfelelő buszok sorszámait két külön listába gyűjtjük. Mivel a sorszámok a bejárás sorrendjében kerülnek a listákba, azok automatikusan növekvő sorrendben lesznek. Az időigény O(N), ami legfeljebb 100 busz esetén bőven elég.
*/
/*
Hint 1: || Egy busz állapotát csak a rajta utazók száma (U) és a férőhelyek száma (M) határozza meg. A 80% és a 20% határokat érdemes egész számokkal, szorzással felírni, így nem kell törtekkel dolgozni. ||
Hint 2: || Egyetlen ciklusban dolgozz: ha 5 * U >= 4 * M, a busz zsúfolt; ha 5 * U < M, a busz üres. Két külön vektorban gyűjtsd a sorszámokat, mert a kimenetben mindkettőnek növekvő sorrendben kell szerepelnie. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> zsufolt, ures;
    for (int i = 1; i <= n; i++) {
        int u;
        cin >> u;
        if (5 * u >= 4 * m) zsufolt.push_back(i);
        if (5 * u < m) ures.push_back(i);
    }

    cout << zsufolt.size();
    for (int x : zsufolt) cout << ' ' << x;
    cout << '\n';

    cout << ures.size();
    for (int x : ures) cout << ' ' << x;
    cout << '\n';

    return 0;
}
