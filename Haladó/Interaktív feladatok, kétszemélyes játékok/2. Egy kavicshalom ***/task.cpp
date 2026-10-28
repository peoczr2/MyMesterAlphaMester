/*
Megoldás lényege:
Ez a Fibonacci-nim játék: a kezdő akkor nyerhet, ha a kavicsok száma nem Fibonacci-szám.
A nyerő stratégia: a maradék kavicsok számát felírjuk Zeckendorf-alakban (különböző, egymást nem követő
Fibonacci-számok összegeként), és mindig a legkisebb tagot vesszük el. Az ellenfél y válasza után a maradék
Zeckendorf-felbontásának legkisebb tagja mindig megengedett (legfeljebb 2*y), így az utolsó kavics nálunk marad.
Egy lépés O(log N) időt igényel. A programban a GetN() adja a kavicsok kezdeti számát, az Elvesz(x) hívással
közöljük a lépésünket, és ugyanez a függvény adja vissza az ellenfél válaszát.
*/
/*
Hint 1: || Nézd meg, hogy a kavicsok száma felírható-e Fibonacci-számok összegeként, és melyik a legnagyobb Fibonacci-szám, ami még nem nagyobb a halomnál. ||
Hint 2: || Mohón építsd fel a felbontást: a legnagyobb olyan Fibonacci-számot vond le, ami még belefér, és ismételd a maradékra. ||
Hint 3: || A kapott tagok közül a legkisebbet kell elvenni; az ellenfél lépése után ugyanígy számold ki újra a maradék legkisebb tagját. ||
*/
#include "ellenfel.h"
#include <bits/stdc++.h>
using namespace std;

// A maradék r > 0 Zeckendorf-felbontásának legkisebb tagja.
long long legkisebbZeckendorf(long long r) {
    vector<long long> f = {1, 2};
    while (f.back() <= r) {
        f.push_back(f[f.size() - 1] + f[f.size() - 2]);
    }
    long long kicsi = 0;
    for (int i = (int)f.size() - 1; i >= 0; i--) {
        if (f[i] <= r) {
            r -= f[i];
            kicsi = f[i];
        }
    }
    return kicsi;
}

int main() {
    long r = GetN();                 // a kavicsok kezdeti száma (egyszer hívjuk)
    for (;;) {
        long x = legkisebbZeckendorf(r);
        long y = Elvesz(x);          // a mi lépésünk; a visszaadott szám az ellenfél válasza
        r -= x + y;
    }
}
