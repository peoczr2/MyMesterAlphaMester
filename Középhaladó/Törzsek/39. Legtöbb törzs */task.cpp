/*
Megoldás lényege: minden háborút két eseménnyel írunk le: a kezdő évnél +1, a befejező év után álló évnél -1 változás történik. Az eseményeket évszám szerint rendezett map-ben gyűjtjük, így a végigsöprés során minden olyan évszakaszt ismerünk, ahol az aktív háborúk száma nem változik. Ha ez a szám legalább Y, a szakasz minden évét hozzáadjuk a válaszhoz. Az eseményekből legfeljebb 2K darab van, így az időigény O(K log K), ami messze a 0,3 másodperces időlimit alatt marad.
*/
/*
Hint 1: || Egy évben a háború akkor aktív, ha a kezdő- és a befejező évszám közé esik, a két határ is beleszámít. Nem kell minden évet külön vizsgálni, elég azokat az éveket figyelni, ahol a háborúk száma változik. ||
Hint 2: || Készíts egy map-et, amely évszámhoz változást rendel: a háború kezdő évéhez +1, a befejező év utáni évhez -1 kerül. A map-et évek szerint bejárva a futó összeg megadja, hány háború zajlik az aktuális szakaszban. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    map<long long, int> valtozas;
    for (int i = 0; i < k; i++) {
        int haboruzo, ellenseges;
        long long kezdet, vege;
        cin >> haboruzo >> ellenseges >> kezdet >> vege;
        valtozas[kezdet] += 1;
        valtozas[vege + 1] -= 1;
    }
    long long y;
    cin >> y;

    long long valasz = 0;
    long long aktiv = 0;
    auto cur = valtozas.begin();
    while (cur != valtozas.end()) {
        aktiv += cur->second;
        auto nxt = next(cur);
        if (nxt == valtozas.end())
            break;
        if (aktiv >= y)
            valasz += nxt->first - cur->first;
        cur = nxt;
    }
    cout << valasz << "\n";
    return 0;
}
