/*
Megoldás lényege:
Egy szakasz ideje az érkezési időből kivonva az előző állomásról való indulás idejét adódik; az első szakasznál az indulás a 0. perc. Egyetlen ciklusban haladunk végig az állomásokon, és nyilvántartjuk az eddigi leghosszabb szakasz idejét. Ha az aktuális szakasz szigorúan hosszabb az eddigieknél, a sorszámát felvesszük a listába, a sorszámok növekvő sorrendben érkeznek, így a lista már rendezett. Az első szakasz mindig felkerül, hiszen nincs korábbi szakasz, amivel összehasonlítható lenne. Az időigény O(N).
*/
/*
Hint 1: || Minden szakasz ideje az érkezési idő mínusz az előző állomásról való indulás ideje; az első szakasz esetén az indulás a 0. percben van. ||
Hint 2: || Egyetlen ciklusban tartsd nyilván az eddigi leghosszabb szakasz idejét; ha az aktuális szakasz szigorúan hosszabb, növeld a darabszámot és jegyezd fel a szakasz sorszámát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long prevDep = 0;     // a 0. állomásról a villamos a 0. percben indul
    long long longest = -1;    // az eddigi leghosszabb szakasz ideje
    vector<int> sections;
    for (int i = 1; i <= n; i++) {
        long long t, arr, dep;
        cin >> t >> arr >> dep;
        long long travel = arr - prevDep;
        if (travel > longest) {
            longest = travel;
            sections.push_back(i);
        }
        prevDep = dep;
    }

    cout << sections.size();
    for (int s : sections) cout << ' ' << s;
    cout << '\n';
    return 0;
}
