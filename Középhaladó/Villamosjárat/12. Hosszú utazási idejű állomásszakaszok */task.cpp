/*
Megoldás lényege:
Egy szakasz megtételi ideje az érkezési idő mínusz az előző megállóból való indulási idő, az első szakasznál az előző indulás a 0. percben van. Egyetlen beolvasási ciklusban minden szakaszra kiszámoljuk ezt az időt, és ha az nagyobb K-nál, a szakasz sorszámát felvesszük a listába. A sorszámok növekvő sorrendben kerülnek a listába, így nincs szükség rendezésre. Először a darabszámot, majd a sorszámokat írjuk ki egy sorba. Az időigény O(N).
*/
/*
Hint 1: || Egy szakasz ideje az érkezési idő mínusz az előző megállóból való indulási idő. Az első szakasz indulási ideje 0. ||
Hint 2: || Egyetlen menetben haladj végig a megállókon, tárold az előző indulási időt, és ha a szakasz ideje nagyobb K-nál, tedd be a sorszámot egy vektorba. Végül a vektor méretét és elemeit írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    int prevDep = 0;  // a 0. állomásról a 0. percben indul a villamos
    vector<int> ans;

    for (int i = 1; i <= n; i++) {
        int dist, arr, dep;
        cin >> dist >> arr >> dep;
        if (arr - prevDep > k) {
            ans.push_back(i);
        }
        prevDep = dep;
    }

    cout << ans.size();
    for (int x : ans) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
