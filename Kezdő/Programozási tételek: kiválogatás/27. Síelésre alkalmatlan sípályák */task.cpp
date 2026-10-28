/*
Megoldás lényege:
A pályákat sorban, egyesével olvassuk be, és minden pályánál megnézzük, hogy a hóréteg vastagsága 0-e. Ha igen, a pálya
sorszámát (1-től indulva) egy vektorba tesszük. Mivel a pályákat sorban olvassuk, a vektor már növekvő sorrendben
tartalmazza a sorszámokat, külön rendezésre nincs szükség. A végén kiírjuk a darabszámot, majd a sorszámokat egy-egy
szóközzel elválasztva. Az időigény O(N), ami a korlátok mellett triviális.
*/
/*
Hint 1: || Nem kell a vastagságokat tárolni: minden beolvasott értéknél csak azt kell eldönteni, hogy 0-e. ||
Hint 2: || Az i-edik beolvasott érték az i-edik pályához tartozik. A sorszámokat egy vektorban gyűjtsd, és a kiírásnál a vektor méretét írd ki először. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> alkalmatlan;
    for (int i = 1; i <= n; ++i) {
        int vastagsag;
        cin >> vastagsag;
        if (vastagsag == 0) alkalmatlan.push_back(i);
    }

    cout << alkalmatlan.size();
    for (int p : alkalmatlan) cout << ' ' << p;
    cout << '\n';
    return 0;
}
