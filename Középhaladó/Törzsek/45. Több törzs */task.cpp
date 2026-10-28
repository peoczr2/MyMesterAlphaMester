/*
Megoldás lényege:
Egy törzs akkor áll háborúban egy évben, ha legalább egy olyan háború zajlik, amelyben részt vesz. Törzsenként nyilvántartjuk, hány folyamatban lévő háborújában vesz részt, és külön számoljuk, hány törzs számlálója nem nulla. Az eseményeket (háború kezdete: +1, a befejező év utáni év: -1, mindkét félre) évszám szerint rendezett map-ben tároljuk, és sorban végigmegyünk rajtuk. Két egymás utáni eseményév között a háborúban álló törzsek száma nem változik, így ha ez legalább Y, a szakasz hosszát hozzáadjuk a válaszhoz. Az időigény O(K log K + N).
*/
/*
Hint 1: || Ugyanúgy érdemes az év-eseményeket végigvinni, mint a háborúk számánál: a kezdő évnél és a befejező év utáni évnél van változás. ||
Hint 2: || Törzsenként külön számlálót kell tartani arról, hányban vesz részt éppen. Egy törzs akkor számít egyszer, ha a számlálója legalább 1, ezért a törzsek számát külön változóban frissítsd, amikor a számláló 0-ról 1-re vagy 1-ről 0-ra vált. ||
Hint 3: || Egy év akkor felel meg, ha a háborúban álló törzsek száma legalább Y. Két egymás utáni eseményév között ez nem változik, így a szakasz hosszát kell hozzáadni a válaszhoz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    // év -> (törzs, változás) párok ettől az évtől kezdve
    map<int, vector<pair<int, int>>> esemeny;
    for (int i = 0; i < k; i++) {
        int a, b, s, e;
        cin >> a >> b >> s >> e;
        esemeny[s].push_back({a, +1});
        esemeny[s].push_back({b, +1});
        esemeny[e + 1].push_back({a, -1});
        esemeny[e + 1].push_back({b, -1});
    }
    int y;
    cin >> y;

    vector<int> aktiv(n + 1, 0); // hány folyamatban lévő háborúban vesz részt az adott törzs
    int torzsek = 0;             // hány törzs áll éppen háborúban
    long long db = 0;
    for (auto it = esemeny.begin(); it != esemeny.end(); ++it) {
        for (auto [t, d] : it->second) {
            if (d > 0) {
                if (aktiv[t]++ == 0) torzsek++;
            } else {
                if (--aktiv[t] == 0) torzsek--;
            }
        }
        auto kov = next(it);
        if (kov != esemeny.end() && torzsek >= y)
            db += kov->first - it->first;
    }
    cout << db << "\n";
    return 0;
}
