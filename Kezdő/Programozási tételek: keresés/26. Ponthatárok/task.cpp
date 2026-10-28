/*
Megoldás lényege:
A csökkentés célja, hogy senki ne maradjon pontosan 1 ponttal egy határ alatt. Az X határ X−d értékre csökkenthető (0 ≤ d ≤ L), ha az X−d−1 pontszámot egyetlen tanuló sem érte el. A pontszámokat logikai tömbbe jelöljük, így minden határra d = 0, 1, …, L sorrendben ellenőrizhető a feltétel; az első ilyen d, vagyis a legkisebb csökkentés adja az új határt. Ha nincs ilyen d, a határ marad. A négy határ külön-külön O(L) lépésben számolható, a domináns költség a beolvasás, O(N + K).
*/
/*
Hint 1: || Egy határ alatt akkor "hiányzik egy pont", ha az X−1 pontszámot senki sem érte el, ilyenkor nem kell csökkenteni. Ezt kell vizsgálnod, miközben a határt d-vel csökkented. ||
Hint 2: || Tárold a tanulók pontszámait egy tömbben (index = pontszám, 0-tól K-ig), így bármelyik pontszám előfordulása O(1)-ben lekérdezhető. ||
Hint 3: || Minden határra d = 0, 1, …, L sorrendben ellenőrizd az X−d−1 pontszámot, és az első olyan d-nél, ahol ez a pontszám nincs meg, az új határ X−d. Figyelj arra, hogy X−d−1 lehet negatív is, ekkor a pontszám természetesen nincs meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k, l;
    cin >> n >> k >> l;
    int hatar[4];
    for (int i = 0; i < 4; i++) {
        cin >> hatar[i];
    }
    vector<bool> van(k + 1, false);
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        van[p] = true;
    }
    for (int i = 0; i < 4; i++) {
        int x = hatar[i];
        int eredmeny = x;
        for (int d = 0; d <= l; d++) {
            int pont = x - d - 1;
            bool letezik = pont >= 0 && van[pont];
            if (!letezik) {
                eredmeny = x - d;
                break;
            }
        }
        cout << eredmeny << '\n';
    }
    return 0;
}
