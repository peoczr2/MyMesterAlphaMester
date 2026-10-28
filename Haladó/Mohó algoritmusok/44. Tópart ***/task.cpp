/*
Feladat: Egy tó körül M parcella van körben (M után újra 1 jön). N vállalkozó mindegyike egy A..B körívet kér
(ha B < A, akkor A..M és 1..B). Minél több vállalkozót kell kiválasztani úgy, hogy a kért szakaszaik ne
fedjék egymást (közös parcella sem lehet), és meg kell adni a sorszámaikat.

Ötlet: Egyenesen ez a klasszikus intervallumütemezés: mindig a legkorábban végződő, még elférő szakaszt
választjuk. A kört egy s "vágási pontnál" kiegyenesítjük: a választott szakaszok az [s, s+M-1] parcellákon
belül legyenek (a kört kétszer egymás után írjuk: 1..2M). Az optimális megoldásnál van olyan s, ahol egyik
választott szakasz sem lóg át, ezért a válasz az egyenes mohó eredményének maximuma az összes s = 1..M-re.
Mohó lépés: ha az első szabad parcella p, akkor a p-nél nem korábban kezdődő szakaszok közül a legkorábban
végződőt választjuk (vegeMin[p], hátulról számolt minimum), és p a vége utáni parcellára ugrik.
Hogy ne kelljen minden s-re végiglépkedni, "bináris ugrótáblát" készítünk: ugras[j][p] = hova jutunk p-ből
2^j mohó választás után. Ezzel egy s-re O(log M) idő alatt megszámoljuk, hány szakasz fér az [s, s+M-1]
részbe. A legjobb s-ből a mohó lépéseket egyenként végigjárva kiírjuk a választott vállalkozókat.
Lépésszám: O(N + M log M), memória: O(M log M) (a szakaszokat nem tároljuk, csak kezdőpontonként a legjobbat).
*/
/*
Hint 1: || Egyenes parton ez a klasszikus feladat: mindig a legkorábban végződő, még elférő szakaszt válaszd. ||
Hint 2: || A kört vágd el valahol: ha a vágásnál egyik választott szakasz sem lóg át, egyenes feladatot kapsz. Írd a kört kétszer egymás után, és próbáld ki minden s kezdőpontra az [s, s+M-1] részt. ||
Hint 3: || Minden p parcellára előre kiszámolható, hogy a p-nél nem korábban kezdődő szakaszok közül melyik végződik a legkorábban, így egy mohó lépés O(1). ||
Hint 4: || Hogy M kezdőpontra ne kelljen egyenként lépkedni, készíts ugrótáblát: hová jutsz p-ből 2^j mohó lépés után. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // beolvasás
    int n, m, k;
    cin >> n >> m >> k;
    int L = 2 * m;          // a kétszer egymás után írt part: 1..2M
    int VEG = L + 1;        // "elfogytak a szakaszok" jelölés
    vector<int> vegeMin(L + 2, INT_MAX), kiMin(L + 2, 0);  // kezdőpontonként a legkorábban végződő szakasz
    auto felvesz = [&](int a, int b, int id) {
        if (b < vegeMin[a]) { vegeMin[a] = b; kiMin[a] = id; }
    };
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        if (a <= b) {
            felvesz(a, b, i);          // első kör
            felvesz(a + m, b + m, i);  // második kör
        } else {
            felvesz(a, b + m, i);      // átlóg az M -> 1 határon
        }
    }

    // vegeMin[p] = a p-nél nem korábban kezdődő szakaszok legkisebb vége (hátulról minimum)
    for (int p = L - 1; p >= 1; p--) {
        if (vegeMin[p + 1] < vegeMin[p]) { vegeMin[p] = vegeMin[p + 1]; kiMin[p] = kiMin[p + 1]; }
    }

    // ugras[0][p] = az első szabad parcella egy mohó választás után
    int LOG = 1;
    while ((1 << LOG) <= m) LOG++;
    vector<vector<int>> ugras(LOG, vector<int>(L + 2, VEG));
    for (int p = 1; p <= L; p++) {
        if (vegeMin[p] != INT_MAX) ugras[0][p] = vegeMin[p] + 1;
    }
    for (int j = 1; j < LOG; j++) {
        for (int p = 1; p <= L + 1; p++) ugras[j][p] = ugras[j - 1][ugras[j - 1][p]];
    }

    // minden s vágási pontra: hány szakasz fér az [s, s+M-1] részbe (az utolsó vége legfeljebb s+M-1)
    int legjobb = -1, legjobbS = 1;
    for (int s = 1; s <= m; s++) {
        int p = s, db = 0;
        for (int j = LOG - 1; j >= 0; j--) {
            if (ugras[j][p] <= s + m) { p = ugras[j][p]; db += 1 << j; }
        }
        if (db > legjobb) { legjobb = db; legjobbS = s; }
    }

    // rekonstrukció: a legjobb s-ből egyenként végigjárjuk a mohó választásokat
    vector<int> valasztott;
    int p = legjobbS;
    while (ugras[0][p] <= legjobbS + m) {
        valasztott.push_back(kiMin[p]);
        p = ugras[0][p];
    }

    // kiírás
    cout << valasztott.size() << '\n';
    for (int i = 0; i < (int)valasztott.size(); i++) cout << valasztott[i] << (i + 1 < (int)valasztott.size() ? ' ' : '\n');
    return 0;
}
