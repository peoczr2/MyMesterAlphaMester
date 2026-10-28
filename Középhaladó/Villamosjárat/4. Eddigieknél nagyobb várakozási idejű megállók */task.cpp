/*
Megoldás lényege:
Egy megállóban a várakozási idő az indulási idő mínusz az érkezési idő. Egy bejárásban nyilvántartjuk az eddigi legnagyobb várakozást, kezdetben -1-gyel, így az első megálló automatikusan bekerül. Ha az aktuális megálló várakozása szigorúan nagyobb a maximumnál, a sorszámát felvesszük a listába, és frissítjük a maximumot. A sorszámok növekvő sorrendben kerülnek a listába. Először a darabszámot, majd a sorszámokat írjuk ki egy sorba. Az időigény O(N).
*/
/*
Hint 1: || Egy megálló várakozási ideje az indulási idő mínusz az érkezési idő. A kérdés az, hogy ez minden megállónál nagyobb-e, mint az összes korábbi megállóé. ||
Hint 2: || Egy ciklusban tartsd nyilván az eddigi legnagyobb várakozást, kezdetben legyen -1 (így az első megálló biztosan bekerül). Ha az aktuális várakozás szigorúan nagyobb, vedd be a sorszámot egy vektorba, és frissítsd a maximumot. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int maxVar = -1;  // az eddigi legnagyobb várakozási idő
    vector<int> ans;

    for (int i = 1; i <= n; i++) {
        int t, erk, ind;
        cin >> t >> erk >> ind;
        int var = ind - erk;
        if (var > maxVar) {
            ans.push_back(i);
            maxVar = var;
        }
    }

    cout << ans.size();
    for (int x : ans) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
