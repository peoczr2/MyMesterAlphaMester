/*
Megoldás lényege:
Két szomszédos állomás között a villamos az előző állomásról való indulástól a következő állomásra érkezésig megy, ezért az (i-1). és az i. állomás közötti idő: az i. érkezési idő mínusz az (i-1). indulási idő (a 0. állomásról a 0. percben indul). Elég a szomszédos párokat vizsgálni, mert az érkezési idők nem csökkennek, így két nem szomszédos állomás közötti idő nem lehet kisebb a köztes szomszédos pár idejénél. Egy menetben olvassuk a megállókat, tároljuk az előző indulási időt, és a szigorú < összehasonlítás miatt a legkisebb sorszámú pár marad meg. Az időigény O(N).
*/
/*
Hint 1: || Elég a szomszédos állomáspárokat vizsgálni. Egy pár ideje az egyik állomás indulásától a másik érkezéséig tart. ||
Hint 2: || Egyetlen menetben tartsd nyilván az előző indulási időt (kezdetben 0), és minden sorban számold ki az érkezés és ez közötti különbséget. Szigorú < relációval add meg a legjobb párt, hogy egyenlőségnél a kisebb sorszám maradjon. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long prevDep = 0;  // a 0. állomásról a 0. percben indul a villamos
    long long bestTime = LLONG_MAX;
    int bestFrom = 0;
    int bestTo = 0;

    for (int i = 1; i <= n; i++) {
        long long t, arr, dep;
        cin >> t >> arr >> dep;
        long long time = arr - prevDep;
        if (time < bestTime) {
            bestTime = time;
            bestFrom = i - 1;
            bestTo = i;
        }
        prevDep = dep;
    }

    cout << bestFrom << ' ' << bestTo << ' ' << bestTime << '\n';
    return 0;
}
