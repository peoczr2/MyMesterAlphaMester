/*
Megoldás lényege:
Az állomásokon a felszállók számát kell figyelembe venni, a leszállókat nem. A legkevesebb felszállót adó állomás sorszámát keressük egy bejárással.
Az utolsó állomásnál (Székesfehérvár) a szöveg szerint biztosan nincs felszálló, ezért ezt az állomást nem vesszük jelöltnek, és csak az
1..N-1. állomások közül választunk (a minták is így készültek). Egyenlőség esetén a kisebb sorszám marad, ezért szigorú "<" összehasonlítás kell.
Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Csak a felszállók száma számít, a leszállókat a feladat szempontjából figyelmen kívül hagyhatod. ||
Hint 2: || Gondold végig, melyik állomások lehetnek jelöltek: a szöveg szerint Székesfehérváron biztosan nincs felszálló, és ezt az állomást a mintakimenetek nem jelölik. ||
Hint 3: || Egy ciklusban keress minimumot az 1. és az (N-1). állomás között, szigorú "<" összehasonlítással, így egyenlőségnél a kisebb sorszám marad. Az N=1 esetet külön kezeld. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> fel(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        long long le;
        cin >> le >> fel[i];
    }

    int lim = (n >= 2) ? n - 1 : 1;  // az utolsó állomást (Székesfehérvár) nem vesszük jelöltnek
    int best = 1;
    for (int i = 2; i <= lim; i++) {
        if (fel[i] < fel[best]) best = i;
    }

    cout << best << "\n";
    return 0;
}
