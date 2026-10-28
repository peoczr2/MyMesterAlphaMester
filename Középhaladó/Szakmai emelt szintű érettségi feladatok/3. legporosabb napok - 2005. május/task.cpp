/*
Megoldás lényege:
Egy napon észlelt összes pormennyiség a 6 mérés összege. Egy menetben haladunk a napokon, és nyilvántartjuk az eddigi legnagyobb napi összeget és az ahhoz tartozó napok sorszámainak listáját. Új maximumnál a lista kiürül, és az aktuális nap kerül bele, egyenlő összegnél a nap hozzáfűződik a listához. Mivel a napokat sorban dolgozzuk fel, a lista növekvő sorrendben marad. Az időigény O(N), a memóriaigény a legporosabb napok számával arányos.
*/
/*
Hint 1: || Egy napon észlelt összes pormennyiség a 6 mérés összege. A feladat azt kéri, hogy gyűjtsd össze azon napok sorszámát, amelyeknél ez az összeg a legnagyobb. ||
Hint 2: || Nem kell az összes napot eltárolni: elég egy aktuális maximumot és a hozzá tartozó napok listáját karbantartani. Ha nagyobb összeg jön, a régi lista törölhető. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    long long legnagyobb = -1;
    vector<int> napok;
    for (int nap = 1; nap <= n; ++nap) {
        long long osszeg = 0;
        for (int j = 0; j < 6; ++j) {
            long long x;
            cin >> x;
            osszeg += x;
        }
        if (osszeg > legnagyobb) {
            legnagyobb = osszeg;
            napok.clear();
        }
        if (osszeg == legnagyobb) napok.push_back(nap);
    }

    cout << napok.size() << '\n';
    for (size_t i = 0; i < napok.size(); ++i) {
        if (i > 0) cout << ' ';
        cout << napok[i];
    }
    cout << '\n';
    return 0;
}
