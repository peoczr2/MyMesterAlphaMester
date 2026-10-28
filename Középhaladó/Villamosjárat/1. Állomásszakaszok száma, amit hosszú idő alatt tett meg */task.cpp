/*
Megoldás lényege:
Egy állomásszakasz megtételi ideje az adott megálló érkezési ideje mínusz az előző megállóból való indulási idő. Az első szakasz a 0. állomásról indul a 0. percben, ezért az előző indulási idő kezdetben 0. Egyetlen beolvasási ciklusban minden megállónál kiszámoljuk ezt az időt, és ha az nagyobb K-nál, növeljük a számlálót. Minden megálló indulási idejét eltároljuk, mert a következő szakasz ettől indul. A megoldás időigénye O(N), ami a korlátok mellett bőven gyors.
*/
/*
Hint 1: || Egy szakasz ideje: az érkezési idő mínusz az előző megállóból való indulási idő. Az első szakasz kezdő indulási ideje a 0. állomáson 0. ||
Hint 2: || Egyetlen menetben haladj végig a megállókon, tárold az előző indulási időt, és minden szakasznál hasonlítsd a különbséget K-hoz szigorúan nagyobb relációval. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    int prevDep = 0;  // a 0. állomásról a 0. percben indul a villamos
    int count = 0;

    for (int i = 0; i < n; i++) {
        int dist, arr, dep;
        cin >> dist >> arr >> dep;
        if (arr - prevDep > k) {
            count++;
        }
        prevDep = dep;
    }

    cout << count << '\n';
    return 0;
}
