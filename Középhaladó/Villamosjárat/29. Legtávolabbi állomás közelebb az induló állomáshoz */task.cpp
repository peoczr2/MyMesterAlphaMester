/*
Megoldás lényege:
Egy i. állomásig az induló állomásról az érkezési idő (arr[i]) alatt jutunk el, a végállomásig tartó út ideje pedig arr[n] - arr[i]. Azt az állomást keressük, amelyre az első érték kisebb a másodiknál. A sorszámok növekvő sorrendben haladva minden találatnál felülírjuk a jelöltet, így a végén a legnagyobb sorszámú (legtávolabbi) találat marad. Ha nincs találat, a válasz -1. Az időigény O(N).
*/
/*
Hint 1: || Minden állomásra két időt kell összehasonlítani: az induló állomástól való eljutás idejét (az érkezési idő) és a végállomásig tartó út idejét (a végállomás érkezési ideje mínusz az adott állomás érkezési ideje). ||
Hint 2: || Az 1. állomástól az utolsó előtti állomásig egyetlen ciklusban haladj végig, és minden olyan állomásnál írd felül a jelöltet, ahol a két idő összehasonlítása teljesül; a ciklus végén a jelölt a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> arr(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        long long t, dep;
        cin >> t >> arr[i] >> dep;
    }

    int ansIdx = -1;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[n] - arr[i]) ansIdx = i;
    }

    if (ansIdx == -1) {
        cout << -1 << '\n';
    } else {
        cout << ansIdx << ' ' << arr[ansIdx] << ' ' << arr[n] - arr[ansIdx] << '\n';
    }
    return 0;
}
