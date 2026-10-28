/*
Megoldás lényege:
A rajtszámok 1..N közötti különböző számok, a hiányzó szám az egyetlen, ami nincs meg a versenyzők között. A hiányzó számot bitenként, a legalacsonyabb helyiértéktől építjük fel. Minden k-adik lépésben azokat a versenyzőket tekintjük, akiknek a már ismert alsó k bitje megegyezik a hiányzó szám alsó k bitjével (ők alkotják az aktuális csoportot). Ezek k-adik bitjét kérdezzük le, és összevetjük azzal, hogy az 1..N közötti számok között hány szám 1 ezen a biten. Ha a hiányzó számnak 1 a k-adik bitje, akkor az egyesek száma eggyel kisebb a vártnál, különben pontosan a várt. A következő csoport a hiányzó szám bitjével egyező versenyzőkből áll, így minden lépésben nagyjából felére szűkül. Az összes kérdés száma így kb. 2N, ami a 2N-2 korlátot tartja. A be- és kimenetet a valasz modul végzi, ezért a programban nincs cin/cout.
*/
/*
Hint 1: || Számold ki, hogy az 1..N számok között hány olyan szám van, amelynek a k-adik bitje 1, és vesd össze a versenyzőktől kapott egyesek számával. ||
Hint 2: || Tartsd nyilván csak azokat a versenyzőket, akiknek az eddig lekérdezett alsó bitjei egyeznek a hiányzó szám (már kiderült) alsó bitjeivel, és a következő bitet csak ezekre kérdezd le. ||
Hint 3: || Ha a várt egyesszám és a kapott egyesszám különbsége 1, a hiányzó szám bitje 1; ha nincs különbség, a bit 0. Akkor állj meg, ha már csak egy szám fér bele az aktuális osztályba. ||
*/
#include <bits/stdc++.h>
#include "valasz.h"
using namespace std;

int main() {
    int T = induloszam();          // a rajtszámok 1..T között vannak, a versenyzők száma T-1
    vector<int> group;             // az aktuális csoport: versenyzők, akik az eddigi bitekben egyeznek a hiányzóval
    for (int x = 1; x < T; x++) group.push_back(x);
    int p = 0;                     // a hiányzó szám eddig megismert alsó bitjei
    for (int k = 0; ; k++) {
        int mod = 1 << k;
        vector<int> cls;           // az 1..T számok közül azok, amelyek alsó k bitje p
        for (int v = 1; v <= T; v++)
            if (v % mod == p) cls.push_back(v);
        if (cls.size() == 1) {     // már egyetlen jelölt maradt: ez a hiányzó szám
            megoldas(cls[0]);
            return 0;
        }
        int expOnes = 0;           // a várt egyesek száma a k-adik biten
        for (int v : cls)
            if ((v >> k) & 1) expOnes++;
        vector<int> bit(group.size());
        int ones = 0;
        for (size_t i = 0; i < group.size(); i++) {
            bit[i] = kerdes(group[i], k);
            ones += bit[i];
        }
        int hiany = (ones < expOnes) ? 1 : 0;   // a hiányzó szám k-adik bitje
        p += hiany << k;
        vector<int> ng;
        for (size_t i = 0; i < group.size(); i++)
            if (bit[i] == hiany) ng.push_back(group[i]);
        group = ng;
    }
    return 0;
}
