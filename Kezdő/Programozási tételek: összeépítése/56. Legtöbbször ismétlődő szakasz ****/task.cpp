/*
Megoldás lényege:
A leírás legfeljebb 255 karakteres, ezért az összes legalább 3 hosszú részszót (kezdőpozíció és hossz szerint) végigpróbáljuk.
Egy részszó előfordulásait balról jobbra keressük, és minden találat után a keresést a részszó hosszával léptetjük, így az átfedő találatok nem számítanak kétszer.
A kiválasztás szempontjai: a legnagyobb előfordulásszám, azonos esetben a leghosszabb részszó, végül a korábban kezdődő.
Ha nincs legalább kétszer előforduló, legalább 3 hosszú szakasz, a válasz -1.
Az időigény n ≤ 255 esetén gyors, a keresés pedig a string beépített find függvényével történik.
*/
/*
Hint 1: || Az összes lehetséges részszót (kezdőpozíció és hossz párban) próbáld ki: legfeljebb 255 karakter esetén ez csak néhány tízezer eset. ||
Hint 2: || Egy kiválasztott részszó előfordulásait a string find függvényével keresd, és minden találat után a keresési pozíciót a részszó hosszával növeld, így az átfedő találatok nem számítanak többször. ||
Hint 3: || A legjobb részszót akkor írd felül, ha nagyobb az előfordulásszáma, vagy azonos számnál hosszabb; mivel a kezdőpozíció szerint növekvő sorrendben jársz, az egyenlő esetben a korábbi marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    string best;
    int bestCnt = 0;

    for (int i = 0; i < n; i++) {
        for (int len = 3; i + len <= n; len++) {
            string t = s.substr(i, len);

            // nem átfedő előfordulások száma balról jobbra
            int cnt = 0;
            size_t pos = 0;
            while ((pos = s.find(t, pos)) != string::npos) {
                cnt++;
                pos += len;
            }

            if (cnt < 2) continue;
            if (cnt > bestCnt || (cnt == bestCnt && len > (int)best.size())) {
                bestCnt = cnt;
                best = t;
            }
        }
    }

    if (bestCnt == 0) cout << -1 << "\n";
    else cout << best << " " << bestCnt << "\n";
    return 0;
}
