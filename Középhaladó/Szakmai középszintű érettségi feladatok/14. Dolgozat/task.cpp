/*
Megoldás lényege:
Mivel az érdemjegyek 1 és 5 közötti egész számok, elég öt számlálót tartani: minden beolvasott jegy esetén a hozzá tartozó számláló értékét eggyel növeljük. Az első részfeladat eredménye ezután a számlálók sorrendben, szóközzel elválasztva, és egy # sor előzi meg. A második részfeladatnál a legnagyobb számlálót keressük úgy, hogy csak szigorúan nagyobb értéknél cseréljük a jelöltet: így egyezés esetén a kisebb jegy marad meg. A beolvasás és a számlálás O(N) időben fut, N ≤ 100 000 esetén ez bőven elég.
*/
/*
Hint 1: || Az érdemjegyek száma mindössze öt, ezért elég öt darab számlálót tartani (1-től 5-ig), és minden beolvasott jegynél a megfelelő számlálót növelni. ||
Hint 2: || A leggyakoribb jegy megkereséséhez járd végig a számlálókat, és csak akkor frissítsd a jelöltet, ha a számláló szigorúan nagyobb az eddigi legjobbnál: így egyezés esetén a kisebb jegy marad. Ne felejtsd el, hogy mindkét részfeladat elé külön # sor kell. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int cnt[6] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < n; i++) {
        int e;
        cin >> e;
        cnt[e]++;
    }

    // 1. részfeladat: az egyes érdemjegyek darabszáma növekvő sorrendben
    cout << "#\n";
    for (int g = 1; g <= 5; g++) {
        cout << cnt[g] << (g < 5 ? " " : "\n");
    }

    // 2. részfeladat: a leggyakoribb érdemjegy (egyezésnél a kisebb)
    int best = 1;
    for (int g = 2; g <= 5; g++) {
        if (cnt[g] > cnt[best]) best = g;
    }
    cout << "#\n";
    cout << best << "\n";

    return 0;
}
