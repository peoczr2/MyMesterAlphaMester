/*
Megoldás lényege: minden tipphez (számhoz) két adatot tartunk nyilván: hányan tippelték, és ki tippelt rá elsőként.
A beolvasás során a sorszám növekedésével haladunk, így az első előfordulásnál rögzítjük a tippelő sorszámát.
Ezután megkeressük a legnagyobb darabszámot, és az ennek megfelelő számokat a számok szerint növekvő sorrendben
írjuk ki, minden ilyen számhoz az első tippelő sorszámával. Egy map-pel a rendezés automatikus, így az időigény
O(N log N), a memóriaigény O(N).
*/
/*
Hint 1: || Minden tipphez elég két adat: hányan tippelték, és melyik versenyző tippelte először. Ezt egyetlen végigmenéssel meg lehet határozni. ||
Hint 2: || A legtöbbször tippelt számok közül minden szám első tippelője nyer, ha több ilyen szám is van. A kimenethez a számokat növekvő sorrendben kell bejárni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; // m, a tipp maximális értéke, a megoldásban nem szükséges
    cin >> n >> m;

    // tipp -> (hányan tippelték, az első tippelő sorszáma)
    map<int, pair<int, int>> info;
    for (int i = 1; i <= n; i++) {
        int tipp;
        cin >> tipp;
        auto &p = info[tipp];
        if (p.first == 0) p.second = i; // az első tippelő
        p.first++;
    }

    int best = 0;
    for (const auto &kv : info) best = max(best, kv.second.first);

    for (const auto &kv : info) {
        if (kv.second.first != best) continue;
        cout << kv.second.second << ' ' << kv.first << ' ' << best << '\n';
    }
    return 0;
}
