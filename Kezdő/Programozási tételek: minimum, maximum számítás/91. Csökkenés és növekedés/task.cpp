/*
Megoldás lényege:
A sorozat elemeit nem kell tárolni: az X[i+1] = (a·X[i] + b) mod m képletet egyesével kiszámoljuk, és közben egy menetben követjük a folyamatosan csökkenő és a folyamatosan növekvő szakasz aktuális hosszát. Minden új elemet az előzővel hasonlítunk össze: ha kisebb, a csökkenő szakasz nő, különben újraindul (hossza 1); ha nagyobb, a növekvő szakasz nő, különben újraindul. Mindkét szakasz legnagyobb hosszát megjegyezzük. A szorzat a·X legfeljebb 2^40 lehet, ezért 64 bites egészet használunk. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || A szakasz hosszát egy menetben nyilvántarthatod: elég minden új elemet az előzővel összevetni. ||
Hint 2: || Két külön számlálót tarts: az egyik a csökkenő, a másik a növekvő szakasz aktuális hosszát mutatja; ha a folytatás nem teljesül, a számláló 1-re áll vissza. ||
Hint 3: || A szorzat a·X akár 2^40 nagyságú is lehet, ezért a számításhoz használj 64 bites egészet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x, a, b, m;
    int n;
    cin >> x >> a >> b >> m >> n;

    // a sorozat X[1]..X[n]: az első elem X[1] = (a*X[0] + b) mod m
    long long elozo = (a * x + b) % m;
    int csokkenoHossz = 1, novekvoHossz = 1;
    int legCsokkeno = 1, legNovekvo = 1;
    for (int i = 2; i <= n; i++) {
        long long aktualis = (a * elozo + b) % m;
        if (aktualis < elozo) {
            csokkenoHossz++;
        } else {
            csokkenoHossz = 1;
        }
        if (aktualis > elozo) {
            novekvoHossz++;
        } else {
            novekvoHossz = 1;
        }
        legCsokkeno = max(legCsokkeno, csokkenoHossz);
        legNovekvo = max(legNovekvo, novekvoHossz);
        elozo = aktualis;
    }

    cout << legCsokkeno << "\n" << legNovekvo << "\n";
    return 0;
}
