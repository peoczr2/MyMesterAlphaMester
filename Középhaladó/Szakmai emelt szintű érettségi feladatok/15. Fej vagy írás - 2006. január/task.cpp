/*
Megoldás lényege:
A sorozat egy összefüggő, azonos betűkből álló szakasz. Egyetlen, balról jobbra haladó bejárással az összes sorozat végigvehető: egy sorozat ott ér véget, ahol a betű megváltozik. Az F- és az I-sorozatokra külön tartjuk nyilván a leghosszabb hosszt és a hozzá tartozó kezdőpozíciót. Mivel balról jobbra haladunk, a szigorú „nagyobb” összehasonlítás a legkorábban kezdődő leghosszabb sorozatot tartja meg. Ha egy betűből nincs sorozat, a hozzá tartozó érték 0 marad. Az idő O(N), N ≤ 100 000 mellett ez bőven elfér az időkorlátban.
*/
/*
Hint 1: || Egy sorozat összefüggő szakasz, amelynek minden eleme ugyanaz a betű. Ha egy bejárással haladsz balról jobbra, a sorozat végét ott találod meg, ahol a betű megváltozik. ||
Hint 2: || Külön maximumot tarts az F- és az I-sorozatokra is: a leghosszabb hosszt és a kezdőpozíciót. A kezdőpozíciót 1-től számozd, és csak akkor írd felül a maximumot, ha az új sorozat szigorúan hosszabb. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;
    // indexelés: 0 = F, 1 = I
    int bestLen[2] = {0, 0};
    int bestPos[2] = {0, 0};
    int i = 0;
    while (i < n) {
        int j = i;
        while (j < n && s[j] == s[i]) j++;
        int len = j - i;
        int k = (s[i] == 'F') ? 0 : 1;
        if (len > bestLen[k]) {
            bestLen[k] = len;
            bestPos[k] = i + 1;
        }
        i = j;
    }
    cout << bestLen[0] << " " << bestPos[0] << "\n";
    cout << bestLen[1] << " " << bestPos[1] << "\n";
    return 0;
}
