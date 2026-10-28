/*
Megoldás lényege:
Minden emberre kiszámoljuk a mai dátum szerinti életkorát: a mai év és a születési év különbségéből 1-et levonunk, ha az idei születésnap még nem volt meg.
A "még nem volt meg" azt jelenti, hogy a (hónap, nap) páros későbbi a mai (hónap, nap) párosnál.
Azokat számoljuk, akiknek az életkora legalább X év, ezt egy feltételes számlálással kapjuk; az időigény O(N).
*/
/*
Hint 1: || Az életkor nem egyszerűen az évszámok különbsége: ha az idei születésnap még nem volt, az életkor eggyel kisebb. ||
Hint 2: || A (hónap, nap) párost hasonlítsd össze úgy, hogy hónap * 100 + nap alakra hozod, így egyetlen számmal lehet összevetni a mai dátummal. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> ev(n), ho(n), nap(n);
    for (int i = 0; i < n; i++) {
        cin >> ev[i] >> ho[i] >> nap[i];
    }
    int x, mai_ev, mai_ho, mai_nap;
    cin >> x >> mai_ev >> mai_ho >> mai_nap;

    int mai = mai_ho * 100 + mai_nap;
    int db = 0;
    for (int i = 0; i < n; i++) {
        int eletkor = mai_ev - ev[i];
        if (ho[i] * 100 + nap[i] > mai) {
            eletkor--;
        }
        if (eletkor >= x) {
            db++;
        }
    }
    cout << db << endl;
    return 0;
}
