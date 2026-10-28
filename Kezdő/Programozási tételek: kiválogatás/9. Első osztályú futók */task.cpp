/*
Megoldás lényege:
Egyetlen bejárással végigmegyünk a futókon, és mindegyik eredményét összehasonlítjuk a szinthatárral.
Az első osztályú eredmény a szinthatárt eléri vagy meghaladja, ezért az egyenlőség is bekerül a listába.
A futók sorszámait a bemenet sorrendjében kapjuk, így a kiírt sorszámok már növekvő sorrendben vannak.
Kiírásnál előbb az első osztályú futók száma, utána a sorszámok következnek, szóközzel elválasztva.
Az időigény N-nel arányos, ami legfeljebb 100 lépés, így a korlátok mellett bőven belefér.
*/
/*
Hint 1: || Minden futóra elég egyetlen összehasonlítás: a futó eredményét kell a szinthatárral vetni össze, a többi futó eredménye ehhez nem kell. ||
Hint 2: || Gyűjtsd egy vektorba azoknak a futóknak a sorszámát, akiknek az eredménye legalább H, és kiírás előtt számold meg az elemeket. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, h;
    cin >> n >> h;
    vector<int> first;
    for (int i = 1; i <= n; ++i) {
        int result;
        cin >> result;
        if (result >= h) first.push_back(i);
    }

    cout << first.size();
    for (int id : first) cout << ' ' << id;
    cout << '\n';
    return 0;
}
