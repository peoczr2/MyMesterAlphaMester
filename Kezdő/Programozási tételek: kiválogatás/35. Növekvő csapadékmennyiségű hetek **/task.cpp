/*
Megoldás lényege: minden hetet külön vizsgálunk: a hét akkor felel meg, ha a 7 napi csapadékmennyiség minden szomszédos párjánál a második szigorúan nagyobb az elsőnél, vagyis a csupa 0 hét nem nőtt. A hetek sorszámát 1-től számozzuk, és a feltételt teljesítőket növekvő sorrendben gyűjtjük, majd kiírjuk a darabszámot és a sorszámokat. Egy hét ellenőrzése hat összehasonlítás, így az összes hét O(N) időben feldolgozható.
*/
/*
Hint 1: || Egy hét akkor felel meg, ha a 7 napi érték minden szomszédos párjánál a második szigorúan nagyobb az elsőnél; a csupa 0 hét tehát nem jó. ||
Hint 2: || A hetek sorszámát a beolvasás sorrendjében számozd 1-től, így a megfelelő hetek listája automatikusan növekvő lesz; a hét 7 értékét egy tömbbe olvasd, és utána ellenőrizd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> jo;
    for (int i = 1; i <= n; i++) {
        int c[7];
        for (int j = 0; j < 7; j++) cin >> c[j];
        bool novekvo = true;
        for (int j = 0; j + 1 < 7; j++)
            if (c[j] >= c[j + 1]) novekvo = false;
        if (novekvo) jo.push_back(i);
    }
    cout << jo.size() << "\n";
    for (size_t i = 0; i < jo.size(); i++) {
        if (i) cout << ' ';
        cout << jo[i];
    }
    cout << "\n";
    return 0;
}
