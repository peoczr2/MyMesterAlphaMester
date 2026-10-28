/*
Megoldás lényege:
A verseny csak szeles napon ('S') rendezhető, a 'C' és a 'V' nap megszakítja a folytonos szeles szakaszt. A versenyek nem fedhetik egymást, ezért minden szeles szakaszt külön vizsgálunk. Egy L hosszú szakaszban L / K (egész osztás) verseny rendezhető, a maradék L mod K nap pedig korlátozza, hány verseny hosszabbítható meg egy nappal: szakaszonként min(L / K, L mod K). A mintán (20 nap, K = 3) a szeles szakaszok hossza 3, 7 és 5, ezekből 1 + 2 + 1 = 4 verseny rendezhető, a meghosszabbíthatók száma 0 + 1 + 1 = 2. Az időigény O(N), N legfeljebb 100 000.
*/
/*
Hint 1: || Csak a szeles napok ('S') alkalmasak versenyre, a 'C' és a 'V' karakter megszakítja a folytonos szeles szakaszt. A feladatot ezért független, összefüggő szeles szakaszokra lehet bontani. ||
Hint 2: || Egy L hosszú szeles szakaszban hány K napos verseny fér el egymás után, egymást nem fedve? Legfeljebb L / K darab, és a maradék L mod K nap korlátozza, hány verseny hosszabbítható meg egy nappal. ||
Hint 3: || Szakaszonként a meghosszabbítható versenyek száma min(L / K, L mod K). A két kért szám a szakaszonkénti értékek összege: az összes verseny és a meghosszabbíthatók száma. Egy balról jobbra haladó bejárás elég, mert N akár 100 000 is lehet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    int versenyek = 0;
    int meghosszabbithato = 0;
    int i = 0;
    while (i < n) {
        if (s[i] != 'S') {
            i++;
            continue;
        }
        int j = i;
        while (j < n && s[j] == 'S') {
            j++;
        }
        int hossz = j - i;
        int db = hossz / k;
        int maradek = hossz % k;
        versenyek += db;
        meghosszabbithato += min(db, maradek);
        i = j;
    }
    cout << versenyek << "\n" << meghosszabbithato << "\n";
    return 0;
}
