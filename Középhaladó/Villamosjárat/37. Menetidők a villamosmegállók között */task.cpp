/*
Megoldás lényege:
Egy állomásszakasz menetideje az érkezési idő mínusz az előző megállóból való indulási idő. Az első szakasznál az előző indulás a 0. percben van. Egyetlen beolvasási ciklusban minden szakaszra kiszámoljuk ezt az időt, és egy vektorba tesszük a sorrendben. Először a szakaszok számát, majd a menetidőket írjuk ki egy sorba. Az időigény O(N).
*/
/*
Hint 1: || Egy szakasz menetideje az érkezési idő mínusz az előző megállóból való indulási idő. Az első szakasz indulási ideje 0. ||
Hint 2: || Tárold az előző indulási időt, és soronként számold ki az aktuális szakasz idejét. Az eredményeket egy vektorba tedd, és a végén írd ki a darabszámot, majd az elemeket. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int prevDep = 0;  // a 0. állomásról a 0. percben indul a villamos
    vector<int> times;

    for (int i = 1; i <= n; i++) {
        int dist, arr, dep;
        cin >> dist >> arr >> dep;
        times.push_back(arr - prevDep);
        prevDep = dep;
    }

    cout << times.size();
    for (int t : times) {
        cout << ' ' << t;
    }
    cout << '\n';
    return 0;
}
