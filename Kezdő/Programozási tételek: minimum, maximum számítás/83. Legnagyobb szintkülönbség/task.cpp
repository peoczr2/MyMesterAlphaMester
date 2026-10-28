/*
Megoldás lényege:
Egy i<j pár szintkülönbsége M_j - M_i. Egy adott j-hez a legjobb i az a hely, ahol j előtt a legalacsonyabb a magasság, ezért balról jobbra haladva elég nyilvántartani az eddigi minimumot és annak sorszámát. Minden j-nél kiszámítjuk a különbséget ehhez a minimumhoz, és ha ez eddig a legnagyobb, elmentjük a párt. Ha a legnagyobb különbség nem pozitív, a magasságok sehol sem nőnek, és a válasz -1. A megoldás egyetlen bejárással, O(N) időben fut.
*/
/*
Hint 1: || Egy j hely esetén az a legjobb kezdőhely, ahol j előtt a legalacsonyabb magasság volt. Így nem kell minden párt külön végignézni. ||
Hint 2: || Balról jobbra haladva tartsd nyilván az eddig látott legkisebb magasságot és annak sorszámát, és minden j-nél vesd össze a M_j - minimum különbséget a legjobb eddigivel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> h(n);
    for (auto &x : h) cin >> x;

    long long best = 0;
    int bi = -1, bj = -1;
    long long minVal = h[0];
    int minIdx = 0;
    for (int j = 1; j < n; j++) {
        long long diff = h[j] - minVal;
        if (diff > best) {
            best = diff;
            bi = minIdx + 1;
            bj = j + 1;
        }
        if (h[j] < minVal) {
            minVal = h[j];
            minIdx = j;
        }
    }

    if (best <= 0)
        cout << -1 << "\n";
    else
        cout << best << " " << bi << " " << bj << "\n";
    return 0;
}
