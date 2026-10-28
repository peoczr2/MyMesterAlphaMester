/*
Megoldás lényege:
Egy háború a kezdő évtől a befejező évig bezárólag tart. Minden háborúhoz két eseményt veszünk fel: a kezdő évnél a számláló nő eggyel, a befejező év utáni évnél csökken eggyel. Az eseményeket évszám szerint rendezett map-ben tároljuk, és sorban végigmegyünk rajtuk. Két egymás utáni eseményév között a háborúk száma nem változik, így ha ez a szám legalább Y, a teljes szakasz hosszát hozzáadjuk a válaszhoz. Az időigény O(K log K), mert legfeljebb 2K esemény van.
*/
/*
Hint 1: || Nem kell minden évet külön megvizsgálni: a háborúk száma csak ott változik, ahol egy háború kezdődik vagy véget ér. ||
Hint 2: || Egy háború a befejező évét is beleszámítja, ezért a befejező év utáni évnél kell a számlálót csökkenteni. Ha a kulcs az évszám, a map a sorrendet magától tartja. ||
Hint 3: || Két egymás utáni eseményév között a számláló állandó: ha ez legalább Y, akkor a két év különbségét adjuk a válaszhoz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    // év -> a háborúk számának változása ezen az évtől kezdve
    map<int, int> valtozas;
    for (int i = 0; i < k; i++) {
        int a, b, s, e;
        cin >> a >> b >> s >> e;
        valtozas[s] += 1;
        valtozas[e + 1] -= 1;
    }
    int y;
    cin >> y;

    long long db = 0;
    int aktiv = 0;
    for (auto it = valtozas.begin(); it != valtozas.end(); ++it) {
        aktiv += it->second;
        auto kov = next(it);
        if (kov != valtozas.end() && aktiv >= y)
            db += kov->first - it->first;
    }
    cout << db << "\n";
    return 0;
}
