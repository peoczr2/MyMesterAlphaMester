/*
Megoldás lényege:
Egy megállóban akkor nem áll meg a villamos, ha az érkezési és az indulási idő megegyezik. Az összes megállót egyetlen ciklusban beolvassuk, és ha találunk ilyen sort, egy logikai jelzőt állítunk be. A távolságokra a feladatban nincs szükség. A végén a jelző alapján 1-et vagy 0-t írunk ki. Az időigény O(N).
*/
/*
Hint 1: || Egy állomáson akkor nem áll meg a villamos, ha az érkezési és az indulási idő ugyanaz. Elég azt eldönteni, hogy van-e ilyen állomás. ||
Hint 2: || Olvasd be az összes megállót egy ciklusban, minden sornál hasonlítsd össze az érkezési és az indulási időt, és egy logikai változóban tárold az eredményt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    bool van = false;
    for (int i = 0; i < n; i++) {
        int t, erk, ind;
        cin >> t >> erk >> ind;
        if (erk == ind) {
            van = true;
        }
    }

    cout << (van ? 1 : 0) << '\n';
    return 0;
}
