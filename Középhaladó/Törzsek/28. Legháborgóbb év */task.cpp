/*
Megoldás lényege:
Minden háborúhoz két eseményt veszünk fel: a kezdő évnél +1-et, a befejező évet követő évnél -1-et, mert a befejező év is háborús év (zárt intervallum). Az eseményeket évszám szerint rendezzük, majd végigmegyünk rajtuk, és az azonos évhez tartozó eseményeket együtt dolgozzuk fel, így minden évszakasz után ismerjük az aktuális háborúk számát. A számláló csak eseményeknél változik, ezért a legkisebb olyan év, ahol a maximum először elérhető, mindig valamelyik eseményév. Az időigény O(K log K), ami K ≤ 2000 mellett messze az időkorlát alatt marad.
*/
/*
Hint 1: || Gondold végig, mikor változik a háborúk száma: egy háború kezdő évében eggyel nő, a befejező év utáni évben eggyel csökken. Ezeket az eseményeket érdemes egy listába gyűjteni és rendezni. ||
Hint 2: || A befejező évben a háború még tart, a csökkenés csak a következő évben jön. Az azonos évhez tartozó eseményeket együtt dolgozd fel, és csak utána vizsgáld a számlálót. Az első olyan szakasz, ahol a számláló a legnagyobb lesz, adja a legkisebb évet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> esemeny; // (év, változás)
    for (int i = 0; i < k; i++) {
        int a, b, kezd, veg;
        cin >> a >> b >> kezd >> veg;
        esemeny.push_back({kezd, +1});
        esemeny.push_back({veg + 1, -1});
    }
    sort(esemeny.begin(), esemeny.end());

    int aktiv = 0, legtobb = 0, ev = 0;
    size_t i = 0;
    while (i < esemeny.size()) {
        int y = esemeny[i].first;
        while (i < esemeny.size() && esemeny[i].first == y) {
            aktiv += esemeny[i].second;
            i++;
        }
        if (aktiv > legtobb) {
            legtobb = aktiv;
            ev = y;
        }
    }
    cout << ev << " " << legtobb << "\n";
    return 0;
}
