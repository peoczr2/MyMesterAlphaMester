/*
Megoldás lényege:
Három szakaszból akkor szerkeszthető háromszög, ha bármely két oldal összege nagyobb a harmadiknál.
Ezt a három feltételt közvetlenül ellenőrizzük minden szakaszhármasra, és a teljesülő hármasok
sorszámát a beolvasás sorrendjében (1-től kezdve) tároljuk, így a kiírt sorszámok már növekvő
sorrendben vannak. A hosszak és összegeik long long típusban szerepelnek. Az időigény O(N).
*/
/*
Hint 1: || Egy szakaszhármas akkor jó, ha mindhárom párra teljesül az egyenlőtlenség; a hosszokat rendezve ezek egyetlen összehasonlításra is redukálhatók. ||
Hint 2: || Minden összehasonlítás egész számokkal történik, lebegőpontos számra nincs szükség; a sorszámot a beolvasási ciklus 1-től számolt indexéből képezd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> szerk; // a szerkeszthető háromszögek sorszámai
    for (int i = 1; i <= n; i++) {
        long long a, b, c;
        cin >> a >> b >> c;
        if (a + b > c && a + c > b && b + c > a)
            szerk.push_back(i);
    }

    cout << szerk.size() << "\n";
    for (int i : szerk)
        cout << i << "\n";
    return 0;
}
