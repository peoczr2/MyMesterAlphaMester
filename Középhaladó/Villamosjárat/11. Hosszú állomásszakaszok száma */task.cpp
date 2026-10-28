/*
Megoldás lényege:
Ebben a feladatban a szakaszok hosszát méterben, azaz a megállók közötti távolságokat kell figyelni, az idők nem számítanak. Minden megállónál beolvassuk a távolságot az előzőtől, és ha az nagyobb K-nál, növeljük a számlálót. Az érkezési és az indulási idők beolvasásra kerülnek, de az eredményt nem befolyásolják. Az időigény O(N), ami a korlátok mellett nagyon gyors.
*/
/*
Hint 1: || Itt a távolság (Ti) számít, nem az idő. Az érkezési és indulási időket csak be kell olvasni. ||
Hint 2: || Egyetlen menetben haladj végig a megállókon, és minden megállónál vizsgáld meg, hogy a távolság szigorúan nagyobb-e K-nál. Ha igen, számold meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    int count = 0;
    for (int i = 0; i < n; i++) {
        int dist, arr, dep;  // az idők ebben a feladatban nem számítanak
        cin >> dist >> arr >> dep;
        if (dist > k) {
            count++;
        }
    }

    cout << count << '\n';
    return 0;
}
