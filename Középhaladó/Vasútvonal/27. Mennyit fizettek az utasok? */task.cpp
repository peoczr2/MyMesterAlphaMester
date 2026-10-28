/*
Megoldás lényege:
Minden utas annyi szakaszt utazik, ahány szakaszon a vonaton van, és szakaszonként U forintot fizet, így az összes bevétel U-szor az utas-szakasz párok száma.
Az i. állomás után a vonaton lévő utasok száma: előző létszám + felszállók - leszállók, és ez a létszám utazik az i. és i+1. állomás közötti szakaszon.
Ezeket a létszámokat az első N-1 állomás után összegezzük, az utolsó állomás után már nincs szakasz.
A végén az összeget szorozzuk U-val. Az időigény O(N), a memóriaigény O(1); az eredmény nagy lehet, ezért long long.
*/
/*
Hint 1: || Nem kell az utasokat egyenként követni: elég tudni, hány utas utazik az egyes szakaszokon, mert minden utas-szakasz U forintot ér. ||
Hint 2: || Az állomás után a vonaton lévő utasok száma: előző létszám + felszállók - leszállók. Ezt a létszámot kell összegezni az első N-1 állomás után, majd az összeget megszorozni U-val. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long u;
    cin >> n >> u;

    long long cur = 0;                 // a vonaton lévő utasok száma
    long long passenger_sections = 0;  // utas-szakasz párok száma
    for (int i = 1; i <= n; i++) {
        long long le, fel;
        cin >> le >> fel;
        cur = cur - le + fel;
        if (i < n) passenger_sections += cur;
    }

    cout << u * passenger_sections << "\n";
    return 0;
}
