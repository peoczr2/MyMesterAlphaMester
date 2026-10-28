/*
Megoldás lényege:
Egy szakasz menetideje az érkezési idő mínusz az előző megállóból való indulási idő. Az első szakasznál az előző indulás a 0. percben van, az "előző szakasz" idejét pedig 0-nak tekintjük, így az első szakasz mindig beleszámít. Egyetlen beolvasási ciklusban kiszámoljuk minden szakasz idejét, és ha az nagyobb az előzőnél, a sorszámát betesszük a listába. A sorszámok növekvő sorrendben kerülnek a listába, így nincs szükség rendezésre. Először a darabszámot, majd a sorszámokat írjuk ki egy sorba. Az időigény O(N).
*/
/*
Hint 1: || Egy szakasz ideje az érkezési idő és az előző megállóból való indulási idő különbsége. Az első szakasznál az indulási idő 0. ||
Hint 2: || Egyetlen ciklusban haladj végig a megállókon, és tartsd nyilván az előző szakasz idejét. Ha az aktuális szakasz ideje nagyobb az előzőnél, tedd a sorszámát egy vektorba. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int prevDep = 0;   // a 0. állomásról a 0. percben indul a villamos
    int prevTime = 0;  // az első szakasznál az "előző szakasz" ideje 0
    vector<int> ans;

    for (int i = 1; i <= n; i++) {
        int dist, arr, dep;
        cin >> dist >> arr >> dep;
        int t = arr - prevDep;
        if (t > prevTime) {
            ans.push_back(i);
        }
        prevTime = t;
        prevDep = dep;
    }

    cout << ans.size();
    for (int x : ans) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
